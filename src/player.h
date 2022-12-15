#ifndef PLAYER_H
#define PLAYER_H

#include "waves.h"

#include "map.h"

#define CHAR_PLAYER L"🧍‍♀️"
#define ISLAND_Y 33
#define ISLAND_X 9

int safe_to_move(wchar_t *new_loc_char)
{
    if  (wcsncmp(WC_TREE, new_loc_char, 3) == 0)
        return FALSE;
    else if (wcsncmp(WC_BIN, new_loc_char, 2) == 0)
        return FALSE;
    /* else if (wcsncmp(WC_MAGLA, new_loc_char, 3) == 0)
        return FALSE;
    */
    return TRUE;
}


class Player
{
    public:
        Player(int y, int x, const wchar_t *c);
        void mvup();
        void mvdn();
        void mvrt();
        void mvlt();
        int getmv();
        void display();


    private:
        int xLoc, yLoc;
        cchar_t charchar = { 0 };
        cchar_t standingon;
};

Player::Player(int y, int x,  const wchar_t *c)
{
    xLoc = x;
    yLoc = y;
    setcchar(&charchar, c, WA_NORMAL, 10, NULL);

}

void Player::mvup()
{

    mvin_wch(yLoc - 1, xLoc, &standingon);
    if (yLoc == 9 || !safe_to_move(standingon.chars))
        return;
    mvin_wch(yLoc - 1, xLoc + 1, &standingon);
    if (!safe_to_move(standingon.chars))
        return;
    yLoc--;

}


void Player::mvdn()
{

    mvin_wch(yLoc + 1, xLoc, &standingon);
    if (yLoc == 23 || !safe_to_move(standingon.chars))
        return;
    mvin_wch(yLoc + 1, xLoc + 1, &standingon);
    if (!safe_to_move(standingon.chars))
        return;
    yLoc++;

}

void Player::mvlt()
{

    mvin_wch(yLoc, xLoc - 1, &standingon);
    if (xLoc == 0 || !safe_to_move(standingon.chars))
        return;
    xLoc--;

}

void Player::mvrt()
{

    mvin_wch(yLoc, xLoc + 1, &standingon);
    if (xLoc == 31 || !safe_to_move(standingon.chars))
        return;
    mvin_wch(yLoc, xLoc + 2, &standingon);
    if (!safe_to_move(standingon.chars))
        return;
    xLoc++;

}

int Player::getmv()
{
    int choice = getch();

    switch(choice)
    {
        case KEY_UP:
            mvup();
            break;
        case KEY_DOWN:
            mvdn();
            break;
        case KEY_LEFT:
            mvlt();
            break;
        case KEY_RIGHT:
            mvrt();
            break;
        default:
            break;
    }
    return choice;
}

void Player::display()
{
    mvadd_wch(yLoc, xLoc, &charchar);
}

#endif /* PLAYER_H */
