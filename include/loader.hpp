///
/// \page loaders Loaders
/// \brief Database Connections and Loading Components
///
/// Loaders are objecs making connections to databases and fetching required data,
/// or opening files and reading them line by line to aquire data.
///
/// @startuml
/// abstract class Loader {
///     # open(): bool
///     # do_whatever_the_fuck_needed_to_make_product(): std::vector<Product>
///     # close(): void
/// }
///
/// class ResourceLoader {
///     + open(): bool
///     + close(): void
///     + fetch_resources(): std::vector<Resource>
/// }
/// @enduml
///
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

class loader
{
public:
    explicit loader(std::filesystem::path const&);
    virtual ~loader();

    loader(loader const&) = delete;
    loader& operator=(loader const&) = delete;
    loader(loader&&) = delete;
    loader& operator=(loader&&) = delete;

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
