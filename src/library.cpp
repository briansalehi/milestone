#include <flashback/library.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

constexpr std::string resource_action_view{"view notes"};
constexpr std::string resource_action_add{"add resource"};
constexpr std::string resource_action_edit{"edit resource"};
constexpr std::string resource_action_remove{"remove resource"};
constexpr std::string note_action_next{"next note"};
constexpr std::string note_action_previous{"previous note"};
constexpr std::string note_action_collect{"collect note"};
constexpr std::string note_action_add{"add note"};
constexpr std::string note_action_edit{"edit note"};
constexpr std::string note_action_remove{"remove note"};

library::library(std::filesystem::path const& data_path):
    _resource_actions{
        resource_action_view,
        resource_action_add,
        resource_action_edit,
        resource_action_remove
    },
    _note_actions{
        note_action_next,
        note_action_previous,
        note_action_collect,
        note_action_add,
        note_action_edit,
        note_action_remove
    },
    _data_path{data_path},
    _resources{}
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
            select_resource();
        }
        catch (std::exception const& exp)
        {
            std::cerr << "\e[1;31m" << exp.what() << "\e[0m\n";
        }
    }
}

library::resource_actions library::prompt_resource_actions() const
{
    unsigned int index = 0;

    std::cerr << "\nSelect an action:\n";
    std::ranges::for_each(_resource_actions, [&index](auto const& action) mutable {
        std::cerr << ++index << ". " << action << " ";
    });

    std::cin >> index;
    --index;

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

library::note_actions library::prompt_note_actions() const
{
    unsigned int index = 0;

    std::cerr << "\nSelect an action:\n";

    std::ranges::for_each(_note_actions, [&index](auto const& action) mutable {
        std::cerr << ++index << ". " << action << " ";
    });

    std::cin >> index;
    --index;

    if (index < 0 || index > _note_actions.size())
        throw std::out_of_range("out of range"s);

    note_actions action;

    if (_note_actions.at(index) == note_action_next)
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

void library::perform_resource_actions(unsigned int resource_index)
{
    switch (prompt_resource_actions())
    {
        case resource_actions::show:
        {
            unsigned int note_index{};

            std::ranges::for_each(_resources.at(resource_index)->notes(),
                [&note_index, this](std::shared_ptr<note> note) {
                    std::cerr << "\e[1;32m  "
                              << ++note_index << ". "
                              << note->title() << "\e[0m\n";
                    perform_note_actions(note_index);
                }
            );
            break;
        }
        case resource_actions::add:
        {
            break;
        }
        case resource_actions::edit:
        {
            break;
        }
        case resource_actions::remove:
        {
            break;
        }
        case resource_actions::undefined:
        {
        }
        default:
        {
            throw std::runtime_error("undefined action");
        }
    }
}

void library::perform_note_actions(unsigned int)
{
    switch (prompt_note_actions())
    {
        case note_actions::next:
            break;
        case note_actions::previous:
            break;
        case note_actions::collect:
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

    auto writer = [&index](auto const& res) mutable {
        std::cerr << "\e[1;34m  "
                  << ++index << ". " << res->title()
                  << "\e[0m\n";
    };

    std::ranges::for_each(_resources, writer);

    std::cerr << "\nSelect a resource: ";
    std::cin >> resource_index;
    --resource_index;

    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range");

    while (true)
    {
        try
        {
            std::cerr << "\n\e[1;32mSelected : "
                << _resources.at(resource_index)->title()
                << "\e[0m\n";
            perform_resource_actions(resource_index);
        }
        catch (std::exception const& exp)
        {
            std::cerr << "\e[1;31m" << exp.what() << "\e[0m\n";
        }
    }
}

void library::view_note(unsigned int resource_index)
{
    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range"s);

    std::shared_ptr<resource> selected_resource = _resources.at(resource_index);
    unsigned int note_index{};

    //std::cerr << "\e[1;36m  " << ++note_index << ". " << note->title() << "\e[0m\n";
}

void library::export_note(std::shared_ptr<note>)
{
}
