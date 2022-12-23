#pragma once

#include <string>
#include <filesystem>

namespace flashback
{

class resource
{
public:
    explicit resource(std::string const&, unsigned int, std::filesystem::path);
    resource(resource const&);
    resource(resource&&) noexcept;
    resource& operator=(resource const&);
    resource& operator=(resource&&) noexcept;

    std::string title() const;
    void title(std::string const&);
    void title(std::string&&);

    unsigned int chapters() const;
    void chapters(

private:
    std::string _title;
    unsigned int _chapters;
    std::filesystem::path _entity_path;
};

} // flashback
