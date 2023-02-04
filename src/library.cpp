#include <flashback/practice.hpp>
#include <flashback/library.hpp>
#include <flashback/subject.hpp>
#include <flashback/topic.hpp>
#include <flashback/note.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

library::library():
    _stream{std::cin, std::cout},
    _database_address{"postgres://postgres@localhost:5432/flashback"s},
    _connection{"postgres://postgres@localhost:5432/flashback"s},
    _resources{},
    _subjects{}
{
    if (_connection.is_open())
    {
        _stream.clear();
        _stream << color::red;
        _stream.header("Flashback >> Library");
    }
    else
    {
        throw std::runtime_error("cannot connect to database");
    }

    resource_loader resource_bank{_database_address};
    resource_bank.fetch_content();
    _resources = std::move(resource_bank.resources());
}

void library::init()
{
    perform_space_actions();
}

std::size_t library::count() const
{
    return _resources.size();
}

char library::prompt_space_actions()
{
    _stream << style::bold << color::white;
    _stream << "\nSelect an action:\n\n";
    _stream << color::pink;

    std::map<char, std::string> actions{
        {'i', "select resource from list"},
        {'s', "search resource"}
    };

    auto print_action = [](std::pair<char, std::string> const& action) {
        std::cout << "  [" << action.first << "] " << action.second << "\n";
    };

    std::ranges::for_each(actions, print_action);

    char action;

    _stream << color::white;
    _stream << "\nAction: ";
    std::cin >> action;
    _stream << color::reset;

    return action;
}

char library::prompt_resource_actions(unsigned int const resource_index)
{
    pqxx::work collectable_query{_connection};
    pqxx::field count_field = collectable_query.exec(
        "select count(n.id) from resources r "s +
        "inner join notes n on r.id = n.resource "s +
        "where n.collectable = true and n.collected = false "s +
        "and r.id = " + std::to_string(resource_index)
    )[0][0];
    collectable_query.commit();

    std::size_t uncollected_count{};

    if (count_field.is_null())
        uncollected_count = 0;
    else
        uncollected_count = count_field.as<std::size_t>();

    _stream << style::bold << color::white;
    _stream << "\nSelect an action:\n\n";
    _stream << color::pink;

    std::map<char, std::string> actions{
        {'v', "view notes"},
        {'e', "edit resource"},
        {'r', "remove resource (restricted)"}
    };

    if (uncollected_count > 0)
        actions.insert({'x', "export notes"});

    auto print_action = [](std::pair<char, std::string> const& action) {
        std::cout << "  [" << action.first << "] " << action.second << "\n";
    };

    std::ranges::for_each(actions, print_action);

    char action;

    _stream << color::white;
    _stream << "\nAction: ";
    std::cin >> action;
    _stream << color::reset;

    return action;
}

char library::prompt_note_actions()
{
    _stream << style::bold << color::white;
    _stream << "Select an action:\n\n";
    _stream << color::pink;

    std::map<char, std::string> actions{
        {'x', "export to practice"},
        {'m', "mark as not collectable"},
        {'n', "next note"},
        {'e', "edit note"},
        {'r', "remove note"}
    };

    auto print_action = [](std::pair<char, std::string> const& action) {
        std::cout << "  [" << action.first << "] " << action.second << "\n";
    };

    std::ranges::for_each(actions, print_action);

    char action;

    _stream << color::white;
    _stream << "\nAction";
    std::cin >> action;
    _stream << color::reset;

    return action;
}

void library::perform_space_actions()
{
    switch (prompt_space_actions())
    {
        case 'i': select_resource();
        case 's': /*search_resource();*/ break;
        default:  throw std::runtime_error("undefined action");
    }
}

void library::perform_resource_actions(unsigned int const resource_index)
{
    switch (prompt_resource_actions(resource_index))
    {
        case 'x': extract_notes(resource_index); break;
        case 'v': view_note(resource_index); break;
        case 'e': /*edit_resource(resource_index);*/ break;
        case 'r': /*remove_resource(resource_index);*/ break;
        default:  throw std::runtime_error("undefined action");
    }
}

void library::perform_note_actions(unsigned int const resource_index, unsigned int const note_index)
{
    switch (prompt_note_actions())
    {
        case 'x': view_note_description(resource_index, note_index); break;
        case 'm': break;
        case 'n': break;
        case 'e': break;
        case 'r': break;
        default:  throw std::runtime_error("undefined action");
    }
}

void library::select_resource()
{
    pqxx::work resource_query{_connection};
    pqxx::result resources = resource_query.exec(
        R"(select r.id, r.name, count(n.id) as total,
            (select count(nn.id) from notes nn
             where nn.resource = r.id and nn.collectable = true
             and nn.collected = true) as collected_notes
        from resources r
        left join notes n on r.id = n.resource
        group by (r.id)
        order by total desc)"
    );
    resource_query.commit();

    _stream.clear();
    _stream << color::red;
    _stream.header("Flashback >> Library >> Resources");
    _stream << color::reset;

    std::size_t index{};
    std::size_t representable_resource_index{};

    std::map<std::size_t, std::size_t> index_mapping{};

    auto writer = [&index, &index_mapping, this](pqxx::row const& res) mutable {
        _stream << color::blue << style::bold;
        _stream << ++index << ". ";
        _stream << std::setw(43) << res[1].as<std::string>().substr(0, 40);
        _stream << color::white << " (";
        _stream << color::green << res[3].as<std::string>();
        _stream << color::white << " collected, ";
        _stream << color::red << res[2].as<int>() - res[3].as<int>();
        _stream << color::white << " uncollected, ";
        _stream << color::orange << res[2].as<std::string>();
        _stream << color::white << " notes)\n";
        _stream << color::reset;

        index_mapping.insert({index, res[0].as<std::size_t>()});
    };

    _stream << style::bold << color::blue << "\n";
    std::ranges::for_each(resources, writer);

    while (std::cin.good())
    {
        _stream << color::white;
        _stream << "\nSelect a resource: ";
        std::cin >> representable_resource_index;
        _stream << color::reset;

        if (representable_resource_index < resources.size())
            break;

        _stream << style::bold << color::red;
        _stream << "Invalid resource index, try again!\n";
        _stream << color::reset;
    }

    std::size_t real_resource_index = index_mapping[representable_resource_index];
    pqxx::row row = resources[real_resource_index];

    unsigned int note_count{0};
    unsigned int collected{0};
    unsigned int collectable{0};

    _stream.clear();
    _stream << color::red;
    _stream.header("Flashback >> Library >> Resources");
    _stream << style::bold << color::orange << "\n";
    _stream << row[1].as<std::string>();
    _stream << style::bold << color::green << " (";
    _stream << note_count << " notes available, ";
    _stream << collectable << " collectable, ";
    _stream << collected << " collected)\n";
    _stream << color::reset;

    perform_resource_actions(real_resource_index);
}

void library::view_note(unsigned int const resource_index)
{
    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range"s);

    std::shared_ptr<resource> selected_resource = _resources.at(resource_index);

    unsigned int note_index{};

    std::ranges::for_each(selected_resource->notes(),
        [&note_index, &resource_index, this](std::shared_ptr<note> note) {
            _stream << color::blue;
            _stream << ++note_index << ". " << note->title();
            _stream << color::reset;
            perform_note_actions(resource_index, note_index);
    });
}

void library::view_note_description(std::size_t const resource_index, std::size_t const note_index)
{
    _stream << _resources.at(resource_index)->take_note(note_index)->description();
}

void library::extract_notes(std::size_t const resource_index)
{
    pqxx::work uncollected_query{_connection};
    pqxx::result uncollected_notes = uncollected_query.exec(
        "select id, title, description, position, collected, collectable"s
        + " from notes where resource = "s
        + std::to_string(resource_index)
        + " and collected = false and collectable = true"s
    );
    uncollected_query.commit();

    std::ranges::for_each(uncollected_notes, [this](pqxx::row const& note_row) {
        prompt_extraction_actions(note_row);
    });
}

void library::prompt_extraction_actions(pqxx::row const& note_row)
{
    auto selected_note = std::make_shared<note>(note_row[0].as<unsigned long>());
    selected_note->title(note_row[1].as<std::string>());
    selected_note->description(note_row[2].as<std::string>());
    selected_note->position(note_row[3].as<std::string>());
    selected_note->collected(note_row[4].as<bool>());
    selected_note->collectable(note_row[5].as<bool>());

    _stream.clear();
    _stream << color::red;
    _stream.header("Flashback >> Library >> Resources");
    _stream << style::bold << color::orange << "\n";
    _stream << selected_note->title() << "\n\n";
    _stream << color::reset << style::dim << color::white;
    _stream << selected_note->description() << "\n\n";
    _stream << color::reset << style::bold << color::white;
    _stream << "Select an action:\n\n";
    _stream << color::pink;

    std::map<char, std::string> actions{
        {'x', "export to practice"},
        {'n', "mark not collectable"},
        {'c', "mark collectable"},
        {'s', "skip this note"},
        {'q', "quit"}
    };

    auto print_action = [](std::pair<char, std::string> const& action) {
        std::cout << "  [" << action.first << "] " << action.second << "\n";
    };

    std::ranges::for_each(actions, print_action);

    char action;

    _stream << style::bold << color::white;
    _stream << "\nAction: ";
    std::cin >> action;
    _stream << color::reset;

    switch (action)
    {
        case 'x':
        {
            std::shared_ptr<subject> selected_subject = take_subject();
            if (!selected_subject)
                break;

            std::shared_ptr<topic> selected_topic = take_topic(selected_subject);
            if (!selected_topic)
                break;

            std::shared_ptr<practice> result = make_practice(selected_note, selected_topic);
            if (!result)
                break;

            selected_topic->add_practice(result);

            _stream << color::green;
            _stream << "Practice imported into ";
            _stream << selected_subject->title();
            _stream << ", " << selected_topic->title();
            std::cin.get();
            break;
        }
        case 'n':
        {
            pqxx::work marking_query{_connection};
            marking_query.exec0(
                "update notes set collectable = false where id = "
                + std::to_string(selected_note->id())
            );
            marking_query.commit();

            _stream << style::bold << color::green;
            _stream << "Note marked as not collectable";
            _stream << color::reset;
            break;
        }
        case 'c':
        {
            pqxx::work marking_query{_connection};
            marking_query.exec0(
                "update notes set collectable = true where id = "
                + std::to_string(selected_note->id())
            );
            marking_query.commit();

            _stream << style::bold << color::green;
            _stream << "Note marked as collectable";
            _stream << color::reset;
            break;
        }
        case 's':
        {
            break;
        }
        case 'q':
        {
            return;
        }
    }
}

std::shared_ptr<subject> library::take_subject()
{
    pqxx::nontransaction nontransaction{_connection};
    std::shared_ptr<subject> generated_subject{};

    std::string title;

    _stream << style::bold << color::white;
    _stream << "Enter subject name: ";
    std::getline(std::cin >> std::ws, title);
    _stream << color::reset;

    if (title.empty())
        throw std::runtime_error("subject name cannot be empty");

    pqxx::result subject_result = nontransaction.exec(
        "select id from subjects where title = "s + _connection.quote(title)
    );
    nontransaction.commit();

    if (subject_result[0][0].is_null())
    {
        char accepted;

        _stream << style::bold << color::white;
        _stream << "Create subject? [N/y] ";
        std::cin >> accepted;
        _stream << color::reset << "\n";

        switch (accepted)
        {
            case 'y':
            {
                pqxx::transaction transaction{_connection};

                pqxx::row id_row = transaction.exec1(
                    "insert into subjects (title) values (" +
                    _connection.quote(title)
                    + ") returning id"
                );
                transaction.commit();

                unsigned long int id = id_row[0].as<unsigned long int>();
                generated_subject = std::make_shared<subject>(id);
                generated_subject->title(title);

                _stream << style::bold << color::green;
                _stream << "Subject \"" << title << "\" created\n";
                _stream << color::reset;
                break;
            }
            default:
            {
                _stream << style::bold << color::red << "Cancelled\n" << color::reset;
            }
        }
    }
    else
    {
        unsigned long int id = subject_result[0][0].as<unsigned long int>();
        generated_subject = std::make_shared<subject>(id);
        generated_subject->title(title);

        _stream << color::green;
        _stream << "Selected " << title << " subject\n";
        _stream << color::reset;
    }

    return generated_subject;
}

std::shared_ptr<topic> library::take_topic(std::shared_ptr<subject> selected_subject)
{
    if (!selected_subject)
        return nullptr;

    pqxx::nontransaction nontransaction{_connection};
    std::shared_ptr<topic> generated_topic{};

    std::string title;

    _stream << style::bold << color::white;
    _stream << "Enter topic name: ";
    std::getline(std::cin >> std::ws, title);
    _stream << color::reset;

    if (title.empty())
        throw std::runtime_error("topic name cannot be empty");

    pqxx::result topic_result = nontransaction.exec(
        "select id from topics where subject = "s +
        std::to_string(selected_subject->id()) +
        " and title = " + _connection.quote(title)
    );
    nontransaction.commit();

    if (topic_result[0][0].is_null())
    {
        char confirmed;

        _stream << style::bold << color::white;
        _stream << "Create topic? [N/y] ";
        std::cin >> confirmed;
        _stream << color::reset;

        switch (confirmed)
        {
            case 'y':
            {
                pqxx::transaction transaction{_connection};

                pqxx::row id_row = transaction.exec1(
                        "insert into topics (title, subject) values (" +
                        _connection.quote(title) + ", " +
                        std::to_string(selected_subject->id()) + ") returning id"
                        );
                transaction.commit();

                unsigned long int id = id_row[0].as<unsigned long int>();
                generated_topic = std::make_shared<topic>(id);
                generated_topic->title(title);
                selected_subject->add_topic(generated_topic);

                _stream << style::bold << color::green;
                _stream << "Topic \"" << title << "\" created\n";
                _stream << color::reset;
                break;
            }
            default:
            {
                _stream << style::bold << color::red << "Cancelled\n" << color::reset;
            }
        }
    }
    else
    {
        unsigned long int id = topic_result[0][0].as<unsigned long int>();
        generated_topic = std::make_shared<topic>(id);
        generated_topic->title(title);
        selected_subject->add_topic(generated_topic);

        _stream << color::green;
        _stream << "Selected " << title << " topic\n";
        _stream << color::reset;
    }

    return generated_topic;
}

std::shared_ptr<practice> library::make_practice(std::shared_ptr<note> selected_note, std::shared_ptr<topic> selected_topic)
{
    if (!selected_note || !selected_topic)
        return nullptr;

    pqxx::transaction insert_tx{_connection};
    std::string question{};
    std::string answer{selected_note->description()};
    std::shared_ptr<practice> generated_practice{};

    char overwrite;

    _stream << style::bold << color::white;
    _stream << "Overwrite question? [N/y] ";
    std::cin >> overwrite;
    _stream << color::reset;

    switch (overwrite)
    {
        case 'y':
        {
            _stream << style::bold << color::white;
            _stream << "Question: ";
            std::getline(std::cin >> std::ws, question);
            _stream << color::reset;
            break;
        }
        default:
        {
            question = selected_note->title();
        }
    }

    pqxx::row id_row = insert_tx.exec1(
        "insert into practices (question, answer, topic, origin) values ("s +
        _connection.quote(question) + ", " +
        _connection.quote(answer) + ", " +
        std::to_string(selected_topic->id()) + ", " +
        std::to_string(selected_note->id()) + ") returning id"
    );
    insert_tx.commit();

    pqxx::transaction update_tx{_connection};
    update_tx.exec0(
        "update notes set collected = true where id = "s +
        std::to_string(selected_note->id())
    );
    update_tx.commit();

    unsigned long int id = id_row[0].as<unsigned long int>();

    generated_practice = std::make_shared<practice>(id);
    generated_practice->question(question);
    generated_practice->answer(answer);

    return generated_practice;
}
