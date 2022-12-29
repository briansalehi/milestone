#include <book.hpp>
#include <loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

loader::loader(std::filesystem::path const& entities_path):
    _entities_path{entities_path}
{
}

loader::~loader()
{
}

std::filesystem::path loader::entities_path() const
{
    return _entities_path;
}

std::vector<std::shared_ptr<resource>> loader::resources() const
{
    return _resources;
}

void loader::fetch_content()
{
    auto join = [this](auto const& p) { _resources.push_back(build_resource(p)); };
    std::ranges::for_each(std::filesystem::directory_iterator(_entities_path), join);
}

std::shared_ptr<resource> loader::build_resource(std::filesystem::path const& entity_path)
{
    if (entity_path.extension() != ".md")
        return nullptr;

    std::shared_ptr<book> book{};
    std::ifstream entity{entity_path, std::ios::in};

    if (entity.is_open())
    {
        _content << entity.get();

        std::string line;
        std::getline(entity, line);

        std::regex pattern{R"(#\s*\[(.*)\]\(.*\))"s};
        std::smatch results;

        if (std::regex_match(line, results, pattern))
        {
            std::cout << results[1] << std::endl;

            std::string title{results[1]};
            std::string description{};
        }
        else
        {
            std::cerr << "no match for " << line << std::endl;
        }
    }

    entity.close();

    return book;
}
