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

library::library(std::string const& database_address):
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
    _stream{std::cerr, std::cin},
    _database_address{database_address},
    _connection{database_address},
    _resources{},
    _subjects{}
{
    if (_connection.is_open())
        _stream.write("\nLibrary", console::color::pink);
    else
        throw std::runtime_error("cannot connect to database");

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

library::library_actions library::prompt_library_actions()
{
    std::size_t index = 0;

    _stream.write("\nSelect an action: ", console::color::white, false);

    std::ranges::for_each(_library_actions, [&index, this](auto const& action) mutable {
        _stream.write(std::to_string(++index) + ". " + action + "  ", console::color::orange, false);
    });

    library_actions action{library_actions::undefined};

    index = _stream.read_size("\nAction", console::color::white) - 1;

    if (index > _library_actions.size())
        throw std::out_of_range("out of range"s);

    if (_library_actions.at(index) == library_action_list)
        action = library_actions::list_resources;
    else if (_library_actions.at(index) == library_action_search)
        action = library_actions::search_resource;
    else
        action = library_actions::undefined;

    return action;
}

library::resource_actions library::prompt_resource_actions()
{
    unsigned int index = 0;

    _stream.write("\nSelect an action: ", console::color::white, false);

    std::ranges::for_each(_resource_actions, [&index, this](auto const& action) mutable {
        _stream.write(std::to_string(++index) + ". " + action + "  ", console::color::orange, false);
    });

    index = _stream.read_size("\nAction", console::color::white) - 1;

    if (index < 0 || index > _resource_actions.size())
        throw std::out_of_range("out of range"s);

    resource_actions action;

    if (_resource_actions.at(index) == resource_action_view)
        action = resource_actions::show;
    else if (_resource_actions.at(index) == resource_action_extract)
        action = resource_actions::extract;
    else if (_resource_actions.at(index) == resource_action_add)
        action = resource_actions::add;
    else if (_resource_actions.at(index) == resource_action_edit)
        action = resource_actions::edit;
    else if (_resource_actions.at(index) == resource_action_remove)
        action = resource_actions::remove;
    else
        action = resource_actions::undefined;

    return action;
}

library::note_actions library::prompt_note_actions()
{
    unsigned int index = 0;

    _stream.write("Select an action: ", console::color::white, false);

    std::ranges::for_each(_note_actions, [&index, this](auto const& action) mutable {
        _stream.write(std::to_string(++index) + ". " + action + "  ", console::color::orange, false);
    });

    index = _stream.read_size("\nAction", console::color::white) - 1;

    if (index < 0 || index > _note_actions.size())
        throw std::out_of_range("out of range"s);

    note_actions action;

    if (_note_actions.at(index) == note_action_expand)
        action = note_actions::expand;
    else if (_note_actions.at(index) == note_action_next)
        action = note_actions::next;
    else if (_note_actions.at(index) == note_action_previous)
        action = note_actions::previous;
    else if (_note_actions.at(index) == note_action_add)
        action = note_actions::add;
    else if (_note_actions.at(index) == note_action_edit)
        action = note_actions::edit;
    else if (_note_actions.at(index) == note_action_remove)
        action = note_actions::remove;
    else
        action = note_actions::undefined;

    return action;
}

void library::perform_library_actions()
{
    switch (prompt_library_actions())
    {
        case library_actions::list_resources:
        {
            select_resource();
            break;
        }
        case library_actions::search_resource:
        {
            //search_resource();
            break;
        }
        default:
        {
            throw std::runtime_error("undefined action");
        }
    }
}

void library::perform_resource_actions(unsigned int const resource_index)
{
    switch (prompt_resource_actions())
    {
        case resource_actions::extract:
        {
            extract_notes(resource_index);
            break;
        }
        case resource_actions::show:
        {
            view_note(resource_index);
            break;
        }
        case resource_actions::add:
        {
            //add_resource(resource_index);
            break;
        }
        case resource_actions::edit:
        {
            //edit_resource(resource_index);
            break;
        }
        case resource_actions::remove:
        {
            //remove_resource(resource_index);
            break;
        }
        default:
        {
            throw std::runtime_error("undefined action");
        }
    }
}

void library::perform_note_actions(unsigned int const resource_index, unsigned int const note_index)
{
    switch (prompt_note_actions())
    {
        case note_actions::expand:
            view_note_description(resource_index, note_index);
            break;
        case note_actions::next:
            break;
        case note_actions::previous:
            break;
        case note_actions::add:
            break;
        case note_actions::edit:
            break;
        case note_actions::remove:
            break;
        case note_actions::undefined:
        default:
            throw std::runtime_error("undefined action");
    }
}

void library::select_resource()
{
    unsigned int index{};
    unsigned int resource_index{};

    _stream.clear();
    _stream.write("Resource list:\n", console::color::white);

    auto writer = [&index, this](auto const& res) mutable {
        _stream.write(std::to_string(++index) + ". " + res->name(), console::color::pink);
    };

    std::ranges::for_each(_resources, writer);

    resource_index = _stream.read_size("\nSelect a resource", console::color::white) - 1;

    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range");
    else
        _stream.clear();

    while (true)
    {
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

        _stream.write(std::to_string(resource_index+1) + ". " + selected_resource->name(), console::color::pink, false);
        _stream.write("(" + std::to_string(note_count) + " notes available,", console::color::green, false);
        _stream.write(std::to_string(collectable) + " collectable,", console::color::green, false);
        _stream.write(std::to_string(collected) + " collected)", console::color::green);

        perform_resource_actions(resource_index);
    }
}

void library::view_note(unsigned int const resource_index)
{
    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range"s);

    std::shared_ptr<resource> selected_resource = _resources.at(resource_index);

    unsigned int note_index{};

    std::ranges::for_each(selected_resource->notes(),
        [&note_index, &resource_index, this](std::shared_ptr<note> note) {
            _stream.write(std::to_string(++note_index) + ". " + note->title(), console::color::blue);
            perform_note_actions(resource_index, note_index);
    });
}

void library::view_note_description(std::size_t const resource_index, std::size_t const note_index)
{
    _stream.write(_resources.at(resource_index)->take_note(note_index)->description());
}

void library::extract_notes(std::size_t const resource_index)
{
    for (auto selected_note: _resources.at(resource_index)->notes())
    {
        if (selected_note->collectable() && !selected_note->collected())
        {
            _stream.clear();
            _stream.write(selected_note->title(), console::color::blue);
            _stream.write(selected_note->description(), console::color::gray);

            if (_stream.read_bool("Extract this note", console::color::white))
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
                _stream.write(
                    "Practice imported into " +
                    selected_subject->title() + ", " +
                    selected_topic->title(),
                    console::color::green
                );
            }
        }
    }
}

std::shared_ptr<subject> library::take_subject()
{
    pqxx::nontransaction nontransaction{_connection};
    std::shared_ptr<subject> generated_subject{};

    std::string title{_stream.read_string("Enter subject name", console::color::white)};

    if (title.empty())
        throw std::runtime_error("subject name cannot be empty");

    pqxx::result subject_result = nontransaction.exec("select id from subjects where title = "s + _connection.quote(title));
    nontransaction.commit();

    if (subject_result[0][0].is_null())
    {
        if (_stream.read_bool("Create subject", console::color::white))
        {
            pqxx::transaction transaction{_connection};

            pqxx::row id_row = transaction.exec1("insert into subjects (title) values (" + _connection.quote(title) + ") returning id");
            transaction.commit();

            unsigned long int id = id_row[0].as<unsigned long int>();
            generated_subject = std::make_shared<subject>(id);

            _stream.write("Subject " + title + " created", console::color::green);
        }
    }
    else
    {
        unsigned long int id = subject_result[0][0].as<unsigned long int>();
        generated_subject = std::make_shared<subject>(id);

        _stream.write("Subject " + title + " selected", console::color::dimgreen);
    }

    return generated_subject;
}

std::shared_ptr<topic> library::take_topic(std::shared_ptr<subject> selected_subject)
{
    if (!selected_subject)
        return nullptr;

    pqxx::nontransaction nontransaction{_connection};
    std::shared_ptr<topic> generated_topic{};

    std::string title{_stream.read_string("Enter topic name", console::color::white)};

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
        if (_stream.read_bool("Create topic", console::color::white))
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

            _stream.write("Topic " + title + " created", console::color::green);
        }
    }
    else
    {
        unsigned long int id = topic_result[0][0].as<unsigned long int>();
        generated_topic = std::make_shared<topic>(id);

        _stream.write("Topic " + title + " selected", console::color::dimgreen);
    }

    selected_subject->add_topic(generated_topic);

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

    if (_stream.read_bool("Overwrite question", console::color::white))
        question = _stream.read_string("Question", console::color::white);
    else
        question = selected_note->title();

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
