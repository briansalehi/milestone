#include <flashback/library.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

constexpr std::string library_action_list{"list resources"};
constexpr std::string library_action_search{"search resource"};
constexpr std::string resource_action_view{"view notes"};
constexpr std::string resource_action_add{"add resource"};
constexpr std::string resource_action_edit{"edit resource"};
constexpr std::string resource_action_remove{"remove resource"};
constexpr std::string note_action_expand{"expand"};
constexpr std::string note_action_next{"next"};
constexpr std::string note_action_previous{"previous"};
constexpr std::string note_action_collect{"collect"};
constexpr std::string note_action_add{"add note"};
constexpr std::string note_action_edit{"edit note"};
constexpr std::string note_action_remove{"remove note"};

library::library(std::filesystem::path const& data_path):
    _library_actions{
        library_action_list,
        library_action_search
    },
    _resource_actions{
        resource_action_view,
        resource_action_add,
        resource_action_edit,
        resource_action_remove
    },
    _note_actions{
        note_action_expand,
        note_action_next,
        note_action_previous,
        note_action_collect,
        note_action_add,
        note_action_edit,
        note_action_remove
    },
    _stream{std::cerr, std::cin},
    _data_path{data_path},
    _resources{},
    _subjects{}
{
}

void library::init()
{
    if (std::filesystem::exists(_data_path) && std::filesystem::is_directory(_data_path))
    {
        loader database{_data_path};
        database.fetch_content();
        _resources = std::move(database.resources());
    }
    else
    {
        std::error_code ec{};
        throw std::filesystem::filesystem_error("invalid base path"s, _data_path, ec);
    }

    while (true)
    {
        try
        {
            perform_library_actions();
        }
        catch (std::exception const& exp)
        {
            _stream.write(exp.what(), console::color::darkred);
        }
    }
}

library::library_actions library::prompt_library_actions()
{
    unsigned int index = 0;

    _stream.write("Select an action: ", console::color::white, false);

    std::ranges::for_each(_library_actions, [&index, this](auto const& action) mutable {
        _stream.write(std::to_string(++index) + ". " + action + "  ", console::color::orange, false);
    });

    index = _stream.read_size("\nAction", console::color::white) - 1;

    if (index < 0 || index > _library_actions.size())
        throw std::out_of_range("out of range"s);

    library_actions action;

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

    _stream.write("Select an action: ", console::color::white, false);

    std::ranges::for_each(_resource_actions, [&index, this](auto const& action) mutable {
        _stream.write(std::to_string(++index) + ". " + action + "  ", console::color::orange, false);
    });

    index = _stream.read_size("\nAction", console::color::white) - 1;

    if (index < 0 || index > _resource_actions.size())
        throw std::out_of_range("out of range"s);

    resource_actions action;

    if (_resource_actions.at(index) == resource_action_view)
        action = resource_actions::show;
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
    else if (_note_actions.at(index) == note_action_collect)
        action = note_actions::collect;
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
            expand_note(resource_index, note_index);
            break;
        case note_actions::next:
            break;
        case note_actions::previous:
            break;
        case note_actions::collect:
            collect_note(resource_index, note_index);
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

    auto writer = [&index, this](auto const& res) mutable {
        _stream.write(std::to_string(++index) + ". " + res->title(), console::color::pink);
    };

    std::ranges::for_each(_resources, writer);

    resource_index = _stream.read_size("Select a resource", console::color::white) - 1;

    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range");

    while (true)
    {
        try
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

            _stream.write(std::to_string(resource_index+1) + ". " + selected_resource->title(), console::color::pink, false);
            _stream.write("(" + std::to_string(note_count) + " notes available,", console::color::green, false);
            _stream.write(std::to_string(collectable) + " collectable,", console::color::green, false);
            _stream.write(std::to_string(collected) + " collected)", console::color::green);

            perform_resource_actions(resource_index);
        }
        catch (std::exception const& exp)
        {
            _stream.write(exp.what(), console::color::darkred);
        }
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

void library::expand_note(std::size_t const resource_index, std::size_t const note_index)
{
    _stream.write(_resources.at(resource_index)->take_note(note_index)->description());
}

void library::collect_note(std::size_t const resource_index, std::size_t const note_index)
{
    std::shared_ptr<note> note = _resources.at(resource_index)->take_note(note_index);
    std::string title = _stream.read_string("Enter subject", console::color::white);
    auto subject_predicate = [&title](auto s) { return s->title() == title; };
    auto subject_iterator = std::ranges::find_if(_subjects, subject_predicate);
    std::shared_ptr<subject> selected_subject{nullptr};

    if (subject_iterator != _subjects.cend())
    {
        _stream.write("Subject found", console::color::green);
        selected_subject = *subject_iterator;
    }
    else
    {
        bool inserted = false;
        std::string answer = _stream.read_string("Subject not found, make one? (y/n)", console::color::darkred);

        if (answer == "y")
            std::tie(subject_iterator, inserted) = _subjects.insert(std::make_shared<subject>(title));

        if (inserted)
        {
            _stream.write("Subject " + title + " created");
            selected_subject = *subject_iterator;
        }
        else
        {
            throw std::runtime_error("failed to create new subject");
        }
    }

    std::string topic_name = _stream.read_string("Enter topic", console::color::white);
}
