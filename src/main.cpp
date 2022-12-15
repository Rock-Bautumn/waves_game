#include "waves.h"
#include "map.h"
#include "player.h"



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
        init_pair(8, COLOR_MAGENTA, COLOR_GREEN);
        init_pair(9, COLOR_GREEN, COLOR_BLUE);
        init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(11, COLOR_CYAN, COLOR_CYAN);
    } 
    // getch();
    Player *plr = new Player(20, 20, CHAR_PLAYER);

    do
    {
        erase();
        print_base();
        plr->display();
        refresh();
        pchoice = plr->getmv();
        usleep(8000); // 8000 microseconds = 125 delays per second (fps limiter)
    } while (pchoice != 'x');
    nodelay(stdscr, FALSE);



    // mvprintw(0, 0, "🔥\n");
    /*
    printw("columns is %d, lines is %d\n", COLS, LINES);
    getch();
 */


    // printw("€ 🔥\n");             literal Unicode
    // mvprintw(y, x, "Press any key to exit...\n");              literal Unicode

    // getch();
    endwin();
    return EXIT_SUCCESS;
}
