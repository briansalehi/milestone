#include <book.hpp>
#include <resource-loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

resource_loader::resource_loader(std::filesystem::path const& entities_path):
    _entities_path{entities_path}
{
}

resource_loader::~resource_loader()
{
}

std::filesystem::path resource_loader::entities_path() const
{
    return _entities_path;
}

std::vector<std::shared_ptr<resource>> resource_loader::resources() const
{
    return _resources;
}

void resource_loader::fetch_content()
{
    for (auto const& entity_path: std::filesystem::directory_iterator{_entities_path})
        build_resource(entity_path);
}

std::shared_ptr<resource> resource_loader::build_resource(std::filesystem::path const& entity_path)
{
    if (entity_path.extension() != ".md")
        return nullptr;

    std::shared_ptr<book> book{};
    std::ifstream entity{entity_path, std::ios::in};

    if (entity.is_open())
    {
        std::string line;
        std::getline(entity, line);

        std::regex pattern{R"(#\s*\[(.*)\]\(.*\))"s};
        std::smatch results;

        if (std::regex_match(line, results, pattern))
            std::cout << results[1] << std::endl;
        else
            std::cerr << "no match for " << line << std::endl;
    }

    entity.close();

    return book;
}
