#include <flashback/library.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

library::library(std::filesystem::path const& data_path):
    _resource_actions{"view notes", "add resource", "edit resource", "remove resource"},
    _note_actions{"next note", "previous note", "promote note", "add note", "edit note", "remove note"},
    _data_path{data_path},
    _resources{}
{
}

void library::init()
{
    auto builder = [this](auto const& entry) {
        flashback::markdown_book_builder builder{entry.path()};
        builder.read_title();
        builder.read_chapters();
        _resources.push_back(builder.result());
    };

    if (std::filesystem::exists(_data_path) && std::filesystem::is_directory(_data_path))
    {
        std::ranges::for_each(std::filesystem::directory_iterator(_data_path), builder);
        std::cerr << _resources.size() << " resources loaded:\n\n";

        select_resource();
    }
    else
    {
        throw std::runtime_error("invalid resource path: "s + _data_path.string());
    }
}

library::resource_actions library::prompt_resource_actions() const
{
    unsigned int index = 0;

    std::cerr << "Select an action:\n";
    std::ranges::for_each(_resource_actions, [&index](auto const& action) mutable {
        std::cerr << ++index << ". " << action << "\n";
    });

    std::cin >> index;

    if (index < 0 || index > _resource_actions.size())
        throw std::out_of_range("out of range [1,"s + std::to_string(_resource_actions.size()) + "]"s);

    resource_actions action;

    if (_resource_actions.at(index) == "view notes")
        action = resource_actions::show;
    else if (_resource_actions.at(index) == "add resource")
        action = resource_actions::add;
    else if (_resource_actions.at(index) == "edit resource")
        action = resource_actions::edit;
    else if (_resource_actions.at(index) == "remove resource")
        action = resource_actions::remove;
    else
        action = resource_actions::undefined;

    return action;
}

library::note_actions library::prompt_note_actions() const
{
    unsigned int index = 0;

    std::cerr << "Select an action:\n";
    std::ranges::for_each(_note_actions, [&index](auto const& action) mutable {
        std::cerr << ++index << ". " << action << "\n";
    });

    std::cin >> index;

    if (index < 0 || index > _note_actions.size())
        throw std::out_of_range("out of range [1,"s + std::to_string(_note_actions.size()) + "]"s);

    note_actions action;

    if (_note_actions.at(index) == "next note")
        action = note_actions::next;
    else if (_note_actions.at(index) == "previous note")
        action = note_actions::previous;
    else if (_note_actions.at(index) == "promote note")
        action = note_actions::promote;
    else if (_note_actions.at(index) == "add note")
        action = note_actions::add;
    else if (_note_actions.at(index) == "edit note")
        action = note_actions::edit;
    else if (_note_actions.at(index) == "remove note")
        action = note_actions::remove;
    else
        action = note_actions::undefined;

    return action;
}

void library::perform_resource_actions()
{
    switch (prompt_resource_actions())
    {
        case resource_actions::show:
            break;
        case resource_actions::add:
            break;
        case resource_actions::edit:
            break;
        case resource_actions::remove:
            break;
        case resource_actions::undefined:
        default:
            throw std::runtime_error("undefined resource action to perform");
    }
}

void library::perform_note_actions()
{
    switch (prompt_note_actions())
    {
        case note_actions::next:
            break;
        case note_actions::previous:
            break;
        case note_actions::promote:
            break;
        case note_actions::add:
            break;
        case note_actions::edit:
            break;
        case note_actions::remove:
            break;
        case note_actions::undefined:
        default:
            throw std::runtime_error("undefined note action to perform");
    }
}

void library::select_resource()
{
    unsigned int index{};
    unsigned int resource_index{};

    auto writer = [&index](auto const& res) mutable {
        std::cerr << "\e[1;35m  " << ++index << ". " << res->title() << "\e[0m" << "\n";
    };

    std::ranges::for_each(_resources, writer);

    std::cerr << "Select a resource: ";
    std::cin >> resource_index;

    view_note(resource_index);
    perform_resource_actions();
}

void library::view_note(unsigned int resource_index)
{
    if (resource_index < 0 || resource_index > _resources.size())
        throw std::out_of_range("out of range [1,"s + std::to_string(_resources.size()) + "]"s);

    std::shared_ptr<resource> selected_resource = _resources.at(resource_index);
    unsigned int index{};
    unsigned int note_index{};

    auto writer = [&index](auto const& note) {
        std::cerr << "\e[1;35m  " << ++index << ". " << note->title() << "\e[0m" << "\n";
    };

    std::ranges::for_each(selected_resource->notes(), writer);
}

void library::export_note(std::shared_ptr<note>)
{
}
