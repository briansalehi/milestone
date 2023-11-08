#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/topic.hpp>
#include <flashback/practice.hpp>
//#include <flashback/library.hpp>
//#include <flashback/training.hpp>
//#include <flashback/console.hpp>
//#include <flashback/loader.hpp>
//#include <flashback/space.hpp>

#include <thread>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <filesystem>

namespace flashback
{

class dashboard
{
public:
    explicit dashboard(argument_parser const&);

private:
    std::vector<std::shared_ptr<topic>> parse_topic(std::filesystem::directory_entry const&) const;

    /*
    void open();

    std::shared_ptr<space> build_space(char);

    char prompt_space();

    void enter_space(std::shared_ptr<space>);
    */

private:
    std::vector<std::shared_ptr<topic>> _topics;
};

} // flashback
