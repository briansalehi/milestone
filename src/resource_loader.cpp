#include <flashback/resource.hpp>
#include <flashback/loader.hpp>
#include <flashback/book.hpp>

using namespace std::literals::string_literals;
using namespace flashback;

loader::loader(std::string const& address): _connection{address}
{
}

loader::~loader()
{
}

std::vector<std::shared_ptr<resource>> loader::resources() const
{
    return _resources;
}

void loader::fetch_content()
{
    pqxx::work work{_connection};
    pqxx::result resources = work.query<long>("select id from resources"s);
    std::ranges::for_each(resources, [this](pqxx::row const& r) { add_resource(r[0]); });
}

void loader::add_resource(unsigned long int const id)
{
    pqxx::work work{_connection};
    pqxx::row resource_info = work.query1<std::string, std::string, std::string>(
        R"(select name, description, purchase_link
        from resources where id = )"s + work.quote(std::to_string(id))
    );
    pqxx::result notes = work.query<std::string, std::string, std::string, bool, bool>(
        R"(select title, description, position, collected, collectable
        from notes where resource = )"s + work.quote(std::to_string(id))
    );
    work.commit();

    std::shared_ptr<book> partial_book = std::make_shared<book>();
    partial_book->name(resource_info[0]);
    partial_book->description(resource_info[1]);
    partial_book->link(resource_info[2]);

    std::ranges::for_each(notes, [&partial_book](pqxx::row const& record) {
        std::shared_ptr<note> partial_note = std::make_shared<note>();
        partial_note->title(record[0]);
        partial_note->description(record[1]);
        partial_note->position(record[2]);
        partial_note->collected(record[3].as<bool>());
        partial_note->collectable(record[4].as<bool>());

        partial_book->add_note(std::move(partial_note));
    });

    _resources.push_back(std::move(partial_book));
}
