#pragma once

#include <regex>
#include <memory>
#include <ranges>
#include <sstream>
#include <fstream>
#include <iostream> // remove this
#include <algorithm>
#include <filesystem>

namespace flashback
{
class resource;

class resource_loader
{
public:
    explicit resource_loader(std::filesystem::path const&);
    virtual ~resource_loader();

    resource_loader(resource_loader const&) = delete;
    resource_loader& operator=(resource_loader const&) = delete;
    resource_loader(resource_loader&&) = delete;
    resource_loader& operator=(resource_loader&&) = delete;

    std::filesystem::path entities_path() const;
    std::vector<std::shared_ptr<resource>> resources() const;

    void fetch_content();

private:
    std::shared_ptr<resource> build_resource(std::filesystem::path const&);

private:
    std::filesystem::path _entities_path;
    std::ostringstream _content;
    std::vector<std::shared_ptr<resource>> _resources;
};

} // flashback
