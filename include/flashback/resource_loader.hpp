#pragma once

#include <flashback/resource.hpp>
#include <flashback/loader.hpp>

#include <pqxx/pqxx>

#include <memory>
#include <vector>
#include <ranges>
#include <algorithm>

namespace flashback
{
class resource_loader: public loader
{
public:
    explicit resource_loader(std::string const&);
    virtual ~resource_loader();

    virtual void fetch_content() override;
    virtual bool connected() const override;

    std::vector<std::shared_ptr<resource>> resources() const;

private:
    void add_resource(unsigned long int const);

private:
    pqxx::connection _connection;
    std::vector<std::shared_ptr<resource>> _resources;
};

} // flashback
