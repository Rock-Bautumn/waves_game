#ifndef SHIP_H
#define SHIP_H

#include "waves.h"
#include "player.h"

#define LC_SHIP L"🛳️"

class Ship
{
    public:
        Ship(Player *);
        long int get_start();
        void update();
        void display();
        void look_for_fire();

    private:
        Player *plr;
        cchar_t ship_char;
        struct timespec start_time;
        struct timespec last_update;
        size_t seen_smoke_secs = 0;
        void win_game();
};

Ship::Ship(Player *this_plr)
{
    plr = this_plr;
    setcchar(&ship_char, LC_SHIP, WA_NORMAL, 9, NULL);
    clock_gettime(CLOCK_MONOTONIC_COARSE, &start_time);
    start_time.tv_sec += rand() % 20 + 5;
    last_update.tv_sec = start_time.tv_sec;
    last_update.tv_nsec = start_time.tv_nsec;
}

long int Ship::get_start()
{
    return start_time.tv_sec;
}

void Ship::look_for_fire()
{
    if (plr->fire_is_lit())
        seen_smoke_secs++;

}
void Ship::update()
{
    struct timespec this_time;
    size_t frame_num;

    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    frame_num = this_time.tv_sec - start_time.tv_sec;
    if (frame_num < 0)
        return;
    // do once per second
    if ((this_time.tv_sec - last_update.tv_sec) > 0)
    {
        look_for_fire();
        last_update.tv_sec = this_time.tv_sec;
    }

    if (seen_smoke_secs == 5)
        win_game();

    if (frame_num == rand() % 3 + 15)
    {
        seen_smoke_secs = 0;
        clock_gettime(CLOCK_MONOTONIC_COARSE, &start_time);
        start_time.tv_sec += rand() % 180 + 180;
        last_update.tv_sec = start_time.tv_sec;
        last_update.tv_nsec = start_time.tv_nsec;
    }

}

void Ship::win_game()
{


    mvprintw(19, 10, "You were rescued by the ship!");
    mvprintw(20, 16, "You won the game!");
    mvprintw(22, 12, "Press any key to exit...");
    mvprintw(4, 20, "                    ");
    
    mvadd_wch(8, 50, &ship_char);

    nodelay(stdscr, FALSE);
    getch();
    endwin();
    exit(0);
}


void Ship::display()
{
    struct timespec this_time;
    int xLoc;

    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    xLoc = this_time.tv_sec - start_time.tv_sec;
    if (xLoc < 0)
        return;
    mvadd_wch(4, 40 - xLoc, &ship_char);
}

#endif /* SHIP_H */
