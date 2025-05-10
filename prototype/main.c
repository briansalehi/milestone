#include <stdio.h>
#include <ncurses.h>

int main(int argc, char argv)
{
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    clear();
    printw("Press q to quit");
    refresh();
    mvprintw(1, 0, "Title");
    refresh();
    mvprintw(3, 0, "Description");
    refresh();
    getch();
    endwin();
}
