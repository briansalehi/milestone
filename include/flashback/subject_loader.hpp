#pragma once

#include <pqxx/pqxx>

namespace flashback
{
class subject;

class subject_loader
{
public:
    explicit subject_loader(std::string const&);
    virtual ~subject_loader();

    std::string database_address() const;
    std::vector<std::shared_ptr<subject>> subjects() const;

    void fetch_content();

private:
    void add_subject(std::string const&);

private:
    std::string _database_address;
    std::shared_ptr<subject_builder> _builder;
    std::vector<std::shared_ptr<subject>> _subjects;
};

} // flashback
