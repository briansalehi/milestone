#include <card.hpp>

using namespace flashback;

card::card(std::stringstream& block)
{
    using namespace std::string_literals;

    bool block_scoped = false;

    std::getline(block, header);

    if (header == "<details>")
    {
        block_scoped = true;
        std::regex pattern{R"(<summary>(.*)</summary>)"};
        std::smatch untagged;
        std::getline(block, header);

        if (std::regex_match(header, untagged, pattern))
            header = untagged[1];
        else
            std::invalid_argument("header is not surrounded by <summary> tag");

        //header.erase(header.find_first_of("<"), header.find_first_of(">"));
        //header.erase(header.find_last_of("<"), header.find_last_of(">"));
    }

    std::string buffer;
    while (block_scoped && std::getline(block, buffer))
    {
        if (buffer == "</details>")
            break;

        body << buffer << "\n";
    }

    while (std::getline(block, buffer))
    {
        if (buffer == "</details>")
            break;

        resources << buffer << "\n";
    }
}
