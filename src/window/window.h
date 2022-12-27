//
// Created by william rodriguez on 27/12/22.
//

#ifndef WAVES_GAME_WINDOW_H
#define WAVES_GAME_WINDOW_H

#include <clocale>
#include <cstdlib>
#include <ncursesw/ncurses.h>

class Window {
public:
    Window() {
        setlocale(LC_ALL, "");

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
    }

    void set_color();

    void close() {
        nodelay(stdscr, FALSE);
        if (has_colors())
            attroff(COLOR_PAIR(9));
        endwin();
    }

    void print_base(int trash_count);
};


#endif //WAVES_GAME_WINDOW_H
