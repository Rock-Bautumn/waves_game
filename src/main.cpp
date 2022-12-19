#include "waves.h"
#include "map.h"
#include "player.h"
#include "wave.h"
#include "ship.h"

int main()
{
    int y = 5, x = 5, pchoice = 0;

    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    if (can_change_color())
    {
        start_color();
        init_color(COLOR_BLUE, 0, 384, 555);
        init_color(COLOR_YELLOW, 963, 842, 690);
        // 8 = test, 9 = sea, 10 = sand, 11 = sky, 12 = text on sea
        init_pair(8, COLOR_MAGENTA, COLOR_GREEN);
        init_pair(9, COLOR_YELLOW, COLOR_BLUE);
        init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(11, COLOR_CYAN, COLOR_CYAN);
        init_pair(12, COLOR_WHITE, COLOR_BLUE);

        attron(COLOR_PAIR(9));
    }

    Wave *wave = new Wave();
    Player *plr = new Player(wave, 9, 46, CHAR_PLAYER);
    Ship *ship = new Ship();

    do
    {
        erase();
        print_base(plr->get_trash_qty());
        plr->display();
        wave->update();
        wave->display();
        ship->update();
        ship->display();
        refresh();
        pchoice = plr->getmv();
        usleep(8000); // 8000 microseconds = 125 delays per second (fps limiter)
    } while (pchoice != 'x');

    nodelay(stdscr, FALSE);

    if (has_colors())
    {
        attroff(COLOR_PAIR(9));
    }

    // mvprintw(0, 0, "🔥\n");

    // mvprintw(y, x, "Press any key to exit...\n");
    endwin();
    return EXIT_SUCCESS;
}
