#include <milestone/screens.hpp>

using namespace milestone;

screens::screens()
{
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
}

screens::~screens()
{
    endwin();
}

void screens::print(int const row, int const column, std::string const& text)
{
    clear();
    mvprintw(row, column, "%s\n", text.c_str());
    mvprintw(LINES - 1, 0, "Press q to quit");
    refresh();
    getchar();
}
