#include <flashback/training.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

training::training():
    _connection{"postgres://postgres@localhost:5432/flashback"},
    _practice_queue{},
    _practice_start_time{},
    _stream{std::cin, std::cout}
{
    if (_connection.is_open())
    {
        _stream.clear();
        _stream << color::orange;
        _stream.header("Flashback >> Trainer");
    }
    else
    {
        throw std::runtime_error("cannot connect to database");
    }
}

void training::init()
{
    perform_space_actions();
}

char training::prompt_space_actions()
{
    _stream << style::bold << color::white;
    _stream << "\nSelect an action:\n\n";
    _stream << color::pink;

    std::map<char, std::string> actions{
        {'p', "begin practice session"},
        {'s', "practice a specific subject"}
    };

    auto print_action = [this](std::pair<char, std::string> const& action) {
        _stream << "  [" << action.first << "] " << action.second << "\n";
    };

    std::ranges::for_each(actions, print_action);

    char action;

    _stream << style::bold << color::white << "\nAction: ";
    std::cin >> action;

    return action;
}

void training::perform_space_actions()
{
    switch (prompt_space_actions())
    {
        case 'p': start_practice_session(); break;
        case 's': practice_subject(); break;
        default: throw std::invalid_argument("invalid operation");
    }
}

void training::start_practice_session()
{
    pqxx::work queue_query{_connection};
    pqxx::result practice_results = queue_query.exec(R"(
        select max(p.id) as practice_id,
               max(p.question) as practice_question,
               max(p.answer) as practice_answer,
               max(p.last_usage) as practice_last_usage,
               max(p.elapsed_time) as practice_elapsed_time
        from practices p
        inner join topics t on t.id = p.topic
        group by (t.subject, t.id, p.last_usage)
        order by p.last_usage desc nulls first, t.subject asc, t.id asc
    )");
    queue_query.commit();

    auto queue_inserter = [this](pqxx::row const& row) {
        int id = row[0].as<int>();
        std::string question = row[1].as<std::string>();
        std::string answer = row[2].is_null() ? "" : row[2].as<std::string>();
        std::string last_usage = row[3].is_null() ? ""s : row[3].as<std::string>();
        int elapsed_time = row[4].is_null() ? 0 : row[4].as<int>();

        auto generated_practice = std::make_shared<practice>(id);
        generated_practice->question(question);
        generated_practice->answer(answer);
        //generated_practice->last_usage(std::chrono::days{last_usage});
        generated_practice->elapsed_time(std::chrono::seconds{elapsed_time});

        _practice_queue.push_back(generated_practice);
    };

    if (practice_results.size() == 0)
        throw std::runtime_error("practice queue empty");

    std::ranges::for_each(practice_results, queue_inserter);

    auto queue_iterator = [this](std::shared_ptr<practice> active_practice) {
        pqxx::work practice_query{_connection};
        pqxx::row practice_results = practice_query.exec1(R"(
            select s.title, t.title
            from practices p
            inner join topics t on t.id = p.topic
            inner join subjects s on s.id = t.subject
            where p.id = )" + std::to_string(active_practice->id())
        );
        practice_query.commit();

        std::string subject_title{practice_results[0].as<std::string>()};
        std::string topic_title{practice_results[1].as<std::string>()};

        _stream.clear();
        _stream << color::reset << color::orange;
        _stream.header("Flashback >> Trainer >> " + subject_title + " >> " + topic_title);

        _stream << style::bold << color::blue << "\n";
        _stream << active_practice->question() << "\n";
        _stream << color::reset;

        _practice_start_time = std::chrono::steady_clock::now();

        perform_practice_actions(active_practice);
    };

    std::ranges::for_each(_practice_queue, queue_iterator);
}

std::size_t training::get_record_id(pqxx::result const& results)
{
    std::size_t index{1};
    std::map<std::size_t, std::size_t> index_map{};

    std::ranges::for_each(results, [&index, &index_map, this](pqxx::row subject_row) {
        index_map[index] = subject_row[0].as<std::size_t>();
        _stream << index << ". " << subject_row[1].as<std::string>() << "\n";
        ++index;
    });

    _stream << "\nSubject: ";
    std::cin >> std::ws >> index;

    if (index >= index_map.size())
        throw std::out_of_range("invalid index");

    return index_map.find(index)->second;
}

void training::practice_subject()
{
    pqxx::work list_subjects{_connection};
    pqxx::result subjects = list_subjects.exec("select id, title from subjects");
    list_subjects.commit();

    std::size_t subject_id = get_record_id(subjects);

    pqxx::work queue_query{_connection};
    pqxx::result practice_results = queue_query.exec(R"(
        select max(p.id) as practice_id,
               max(p.question) as practice_question,
               max(p.answer) as practice_answer,
               max(p.last_usage) as practice_last_usage,
               max(p.elapsed_time) as practice_elapsed_time
        from practices p
        inner join topics t on t.id = p.topic
        where t.subject = )" + std::to_string(subject_id) + R"(
        group by (t.subject, t.id, p.last_usage)
        order by p.last_usage desc nulls first, t.subject asc, t.id asc
    )");
    queue_query.commit();

    auto queue_inserter = [this](pqxx::row const& row) {
        int id = row[0].as<int>();
        std::string question = row[1].as<std::string>();
        std::string answer = row[2].is_null() ? "" : row[2].as<std::string>();
        std::string last_usage = row[3].is_null() ? ""s : row[3].as<std::string>();
        int elapsed_time = row[4].is_null() ? 0 : row[4].as<int>();

        auto generated_practice = std::make_shared<practice>(id);
        generated_practice->question(question);
        generated_practice->answer(answer);
        //generated_practice->last_usage(std::chrono::days{last_usage});
        generated_practice->elapsed_time(std::chrono::seconds{elapsed_time});

        _practice_queue.push_back(generated_practice);
    };

    if (practice_results.size() == 0)
        throw std::runtime_error("practice queue empty");

    std::ranges::for_each(practice_results, queue_inserter);

    auto queue_iterator = [this](std::shared_ptr<practice> active_practice) {
        pqxx::work practice_query{_connection};
        pqxx::row practice_results = practice_query.exec1(R"(
            select s.title, t.title
            from practices p
            inner join topics t on t.id = p.topic
            inner join subjects s on s.id = t.subject
            where p.id = )" + std::to_string(active_practice->id())
        );
        practice_query.commit();

        std::string subject_title{practice_results[0].as<std::string>()};
        std::string topic_title{practice_results[1].as<std::string>()};

        _stream.clear();
        _stream << color::reset << color::orange;
        _stream.header("Flashback >> Trainer >> " + subject_title + " >> " + topic_title);

        _stream << style::bold << color::blue << "\n";
        _stream << active_practice->question() << "\n";
        _stream << color::reset;

        _practice_start_time = std::chrono::steady_clock::now();

        perform_practice_actions(active_practice);
    };

    std::ranges::for_each(_practice_queue, queue_iterator);
}

char training::prompt_practice_actions()
{
    std::map<char, std::string> actions{
        {'a', "see answer of practice"},
        {'s', "solved practice"},
        {'k', "skip this practice"}
    };

    _stream << style::bold << color::pink << "\n";

    auto print_action = [this](std::pair<char, std::string> const& action) {
        _stream << "  [" << action.first << "] " << action.second << "\n";
    };

    std::ranges::for_each(actions, print_action);

    char action;
    _stream << "\nAction: ";
    std::cin >> action;

    return action;
}

void training::perform_practice_actions(std::shared_ptr<practice> active_practice)
{
    switch (prompt_practice_actions())
    {
        case 'a': print_practice_answer(active_practice); break;
        case 's': mark_practice_solved(active_practice); break;
        case 'k': break;
    }
}

void training::print_practice_answer(std::shared_ptr<practice> active_practice)
{
    _stream << color::reset << color::gray;
    _stream << active_practice->answer();
    _stream << color::reset << color::green << "\n";
    perform_practice_actions(active_practice);
}

void training::mark_practice_solved(std::shared_ptr<practice> active_practice)
{
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _practice_start_time);

    pqxx::work update_query{_connection};
    update_query.exec0(
        "update practices "s +
        "set last_usage = now(), "s +
        "elapsed_time = "s + std::to_string(elapsed.count()) +
        " where id = "s + std::to_string(active_practice->id())
    );
    update_query.commit();

    _stream << color::reset << color::green;
    _stream << "Practice solved, press enter to continue";
    _stream << color::reset;
    std::cin.ignore();
    std::cin.get();
}
