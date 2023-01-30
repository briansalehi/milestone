#include <flashback/note.hpp>
#include <flashback/subject.hpp>
#include <flashback/topic.hpp>
#include <flashback/practice.hpp>
#include <flashback/library.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

constexpr std::string library_action_list{"list resources"};
constexpr std::string library_action_search{"search resource"};

constexpr std::string resource_action_extract{"extract notes"};
constexpr std::string resource_action_view{"view notes"};
constexpr std::string resource_action_add{"add resource"};
constexpr std::string resource_action_edit{"edit resource"};
constexpr std::string resource_action_remove{"remove resource"};

constexpr std::string note_action_expand{"expand"};
constexpr std::string note_action_next{"next"};
constexpr std::string note_action_previous{"previous"};
constexpr std::string note_action_add{"add note"};
constexpr std::string note_action_edit{"edit note"};
constexpr std::string note_action_remove{"remove note"};

library::library():
    _library_actions{
        library_action_list,
        library_action_search
    },
    _resource_actions{
        resource_action_extract,
        resource_action_view,
        resource_action_add,
        resource_action_edit,
        resource_action_remove
    },
    _note_actions{
        note_action_expand,
        note_action_next,
        note_action_previous,
        note_action_add,
        note_action_edit,
        note_action_remove
    },
    _stream{std::cin, std::cout},
    _database_address{"postgres://postgres@localhost:5432/flashback"s},
    _connection{_database_address},
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
    perform_library_actions();
}

std::size_t library::count() const
{
    return _resources.size();
}

char library::prompt_library_actions()
{
    std::vector<std::string> actions{
        "[i] list resources",
        "[s] search resource"
    };

    char action;

    _stream << style::bold << color::white;
    _stream << "\nSelect an action:\n\n";
    _stream << color::pink;

    //std::ranges::copy(actions, std::ostream_iterator<int>(std::cout, "\n"));
    std::ranges::for_each(actions, [](std::string const& s) { std::cout << "  " << s << "\n"; });

    _stream << color::white;
    _stream << "\nAction: ";
    std::cin >> action;
    _stream << color::reset;

    return action;
}

char library::prompt_resource_actions()
{
    std::vector<std::string> actions{
        "[x] export notes",
        "[v] view notes",
        "[a] add resource",
        "[e] edit resource",
        "[r] remove resource (restricted)"
    };

    char action;

    _stream << style::bold << color::white;
    _stream << "\nSelect an action:\n\n";
    _stream << color::pink;

    //std::ranges::copy(actions, std::ostream_iterator<int>(std::cout, "\n"));
    std::ranges::for_each(actions, [](std::string const& s) { std::cout << "  " << s << "\n"; });

    _stream << color::white;
    _stream << "\nAction: ";
    std::cin >> action;
    _stream << color::reset;

    return action;
}

char library::prompt_note_actions()
{
    std::vector<std::string> actions{
        "[x] export to practice",
        "[m] mark as not collectable",
        "[n] next note",
        "[e] edit note",
        "[r] remove note"
    };

    char action;

    _stream << style::bold << color::white;
    _stream << "Select an action:\n\n";
    _stream << color::pink;

    //std::ranges::copy(actions, std::ostream_iterator<int>(std::cout, "\n"));
    std::ranges::for_each(actions, [](std::string const& s) { std::cout << s << "\n"; });

    _stream << color::white;
    _stream << "\nAction";
    std::cin >> action;
    _stream << color::reset;

    return action;
}

void library::perform_library_actions()
{
    switch (prompt_library_actions())
    {
        case 'i': select_resource();
        case 's': /*search_resource();*/ break;
        default:  throw std::runtime_error("undefined action");
    }
}

void library::perform_resource_actions(unsigned int const resource_index)
{
    switch (prompt_resource_actions())
    {
        case 'x': extract_notes(resource_index); break;
        case 'v': view_note(resource_index); break;
        case 'a': /*add_resource(resource_index);*/ break;
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
    _stream.clear();
    _stream << color::red;
    _stream.header("Flashback >> Library >> Resources");
    _stream << color::reset;

    unsigned int index{};
    unsigned int resource_index{};

    auto writer = [&index, this](auto const& res) mutable {
        _stream << ++index << ". " << res->name() << "\n";
    };

    _stream << style::bold << color::blue << "\n";
    std::ranges::for_each(_resources, writer);

    _stream << color::white;
    _stream << "\nSelect a resource: ";
    std::cin >> resource_index;
    resource_index--;
    _stream << color::reset;

    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range");
    else
        _stream.clear();

    std::shared_ptr<resource> selected_resource = _resources.at(resource_index);
    unsigned int note_count = selected_resource->notes().size();
    unsigned int collected = std::ranges::count_if(
        selected_resource->notes(),
        [](std::shared_ptr<note> note) { return note->collected(); }
    );
    unsigned int collectable = std::ranges::count_if(
        selected_resource->notes(),
        [](std::shared_ptr<note> note) { return note->collectable(); }
    );

    _stream << color::red;
    _stream.header("Flashback >> Library >> Resources");
    _stream << style::bold << color::orange << "\n";
    _stream << selected_resource->name();
    _stream << style::bold << color::green << " (";
    _stream << note_count << " notes available, ";
    _stream << collectable << " collectable, ";
    _stream << collected << " collected)\n";
    _stream << color::reset;

    perform_resource_actions(resource_index);
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
    std::vector<std::string> actions{
        "[x] export to practice",
        "[c] mark not collectable",
        "[s] skip this note",
        "[q] quit"
    };

    for (auto selected_note: _resources.at(resource_index)->notes())
    {
        char action;

        _stream.clear();
        _stream << color::red;
        _stream.header("Flashback >> Library >> Resources");
        _stream << style::bold << color::orange << "\n";
        _stream << selected_note->title() << "\n";
        _stream << color::reset << style::dim << color::white;
        _stream << selected_note->description();
        _stream << color::reset << style::bold << color::white;
        _stream << "\n\nSelect an action:\n\n";
        _stream << color::pink;

        //std::ranges::copy(actions, std::ostream_iterator<int>(std::cout, "\n"));
        std::ranges::for_each(actions, [](std::string const& s) {
            std::cout << "  " << s << "\n";
        });

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
                    continue;

                std::shared_ptr<topic> selected_topic = take_topic(selected_subject);
                if (!selected_topic)
                    continue;

                std::shared_ptr<practice> result = make_practice(selected_note, selected_topic);
                if (!result)
                    continue;

                selected_topic->add_practice(result);

                _stream << color::green;
                _stream << "Practice imported into ";
                _stream << selected_subject->title();
                _stream << ", " << selected_topic->title();
                break;
            }
            case 'c':
            {
                break;
            }
            case 's':
            {
                break;
            }
            case 'q':
            {
                break;
            }
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
    std::cin >> title;
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
    std::cin >> title;
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
        std::cin.get();
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
            std::cin >> question;
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
