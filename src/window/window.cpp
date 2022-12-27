//
// Created by william rodriguez on 27/12/22.
//
#include "window.h"
#include "../cchar/cchar.h"
#include "../map.h"
#include <ncursesw/ncurses.h>

void Window::set_color() {
    if (!has_colors()) {
        mvprintw(2, 8, "This game is designed to be used where colors can be changed.");
        mvprintw(3, 1, "You might still be able to see different shades of gray with colored emoji.");
        mvprintw(6, 27, "Do you want to continue?");
        endwin();
        exit_curses(EXIT_FAILURE);
        std::exit(EXIT_FAILURE);
    }
    start_color();
    init_color(COLOR_BLUE, 0, 384, 555);
    init_color(COLOR_YELLOW, 963, 842, 690);
    // 8 = test, 9 = sea, 10 = sand, 11 = sky, 12 = text on sea
    init_pair(9, COLOR_YELLOW, COLOR_BLUE);
    init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(11, COLOR_CYAN, COLOR_CYAN);
    init_pair(12, COLOR_WHITE, COLOR_BLUE);

    attron(COLOR_PAIR(9));
}

void Window::print_base(int trash_count) {
    Cchar sand{WC_SAND, 10};
    Cchar sky{WC_SKY, 11};
    Cchar tree{WC_TREE, 10};
    Cchar bin{WC_BIN, 10};
    Cchar magla{WC_MAGLA, 10};


    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 79; x++) {
            if (y < 4)
               sky.add();
            else if (((y == 12 && x == 74) || (y == 21 && x == 68)) ||
                     ((y == 11 && x == 58) || (y == 14 && x == 60)) ||
                     (64 < x && x < 68 && 18 < y && y < 21) ||
                     (50 < x && x < 54 && 20 < y && y < 23)) {
                tree.add();
                x++;
            } else if (y == 12 && x == 51) {
                magla.add();
                x++;
            } else if (y == 13 && x == 53) {
                bin.add();
                // x++; We don't need this
            } else if (y > 8 && x > 45)
                sand.add();
            else if (y == 9 && x == 1) {
                printw("Trash in bin:%3d", trash_count);
                x += 15;
            } else if (y == 10 && x == 1) {
                printw("Holding trash [");
                x += 14;
            } else if (y == 10 && x == 18)
                printw("]");
            else
                printw(" ");
        }
        printw("\n");
    }
}
