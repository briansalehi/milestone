#include <flashback/note.hpp>
#include <flashback/book.hpp>
#include <flashback/resource.hpp>
#include <flashback/resource_loader.hpp>

using namespace std::literals::string_literals;
using namespace flashback;

resource_loader::resource_loader(std::string const& address): _connection{address}
{
}

resource_loader::~resource_loader()
{
    if (_connection.is_open())
        _connection.close();
}

void resource_loader::fetch_content()
{
    pqxx::work tx{_connection};
    pqxx::result resources = tx.exec("select id from resources"s);
    tx.commit();
    std::ranges::for_each(resources, [this](pqxx::row const& row) {
        add_resource(row.at(0).as<unsigned long int>());
    });
}

bool resource_loader::connected() const
{
    return _connection.is_open();
}

std::vector<std::shared_ptr<resource>> resource_loader::resources() const
{
    return _resources;
}

void resource_loader::add_resource(unsigned long int const id)
{
    pqxx::work tx{_connection};
    pqxx::row resource_info = tx.exec1(
        R"(select name, description, purchase_link
        from resources where id = )"s + tx.quote(std::to_string(id))
    );
    pqxx::result notes = tx.exec(
        R"(select title, description, position, collected, collectable
        from notes where resource = )"s + tx.quote(std::to_string(id))
    );
    tx.commit();

    std::shared_ptr<book> partial_book = std::make_shared<book>();
    partial_book->name(resource_info[0].as<std::string>());
    partial_book->description(resource_info[1].is_null() ? std::string{} : resource_info[1].as<std::string>());
    partial_book->link(resource_info[2].is_null() ? std::string() : resource_info[2].as<std::string>());

    std::ranges::for_each(notes, [&partial_book](pqxx::row const& record) {
        std::shared_ptr<note> partial_note = std::make_shared<note>();
        partial_note->title(record[0].as<std::string>());
        partial_note->description(record[1].is_null() ? std::string{} : record[1].as<std::string>());
        partial_note->position(record[2].is_null() ? std::string{} : record[2].as<std::string>());
        partial_note->collected(record[3].as<bool>());
        partial_note->collectable(record[4].as<bool>());

        partial_book->add_note(std::move(partial_note));
    });

    _resources.push_back(std::move(partial_book));
}
