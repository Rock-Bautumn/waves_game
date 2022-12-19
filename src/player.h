#ifndef PLAYER_H
#define PLAYER_H

#include "waves.h"
#include "map.h"
#include "wave.h"

#define CHAR_PLAYER L"🧍‍♀️"

enum facing_directions { UNUSED_DIR, FACING_UP, FACING_LEFT, FACING_RIGHT, FACING_DOWN };


int safe_to_move(wchar_t *new_loc_char)
{
    if  (wcsncmp(WC_TREE, new_loc_char, 3) == 0)
        return FALSE;
    else if (wcsncmp(WC_BIN, new_loc_char, 2) == 0)
        return FALSE;
    else if  (wcsncmp(LC_TRASH1, new_loc_char, 2) == 0)
        return FALSE;
    else if (wcsncmp(LC_TRASH2, new_loc_char, 2) == 0)
        return FALSE;
    else if (wcsncmp(LC_TRASH3, new_loc_char, 2) == 0)
        return FALSE;
    else if (wcsncmp(LC_TRASH4, new_loc_char, 2) == 0)
        return FALSE;
    else if (wcsncmp(LC_TRASH5, new_loc_char, 2) == 0)
        return FALSE;
    else if (wcsncmp(LC_TRASH6, new_loc_char, 2) == 0)
        return FALSE;
    else if (wcsncmp(WC_MAGLA, new_loc_char, 2) == 0)
        return FALSE;
    return TRUE;
}


class Player
{
    public:
        Player(Wave *wave, int y, int x, const wchar_t *c);
        void mvup();
        void mvdn();
        void mvrt();
        void mvlt();
        int getmv();
        void display();
        void update();
        int get_trash_qty();
        int fire_is_lit();

    private:
        Wave *wave;
        int xLoc, yLoc, bin_trash_qty = 0, face_direction = UNUSED_DIR;
        cchar_t charchar = { 0 };
        cchar_t standingon;
        wchar_t item_holding_char[5] = L"";
        cchar_t item_hold_print_char = { 0 };
        struct timespec fire_start_time = { 0 , 0 };
        cchar_t fire_char = { 0 };

        struct timespec last_update;
        int grabbed_trash(int facing_y, int facing_x);
        int tossed_trash(int facing_y, int facing_x);
        int used_magla(int facing_y, int facing_x);
        void action();
};

Player::Player(Wave *this_wave, int y, int x,  const wchar_t *c)
{
    xLoc = x;
    yLoc = y;

    wave = this_wave;
    setcchar(&charchar, c, WA_NORMAL, 10, NULL);
    setcchar(&fire_char, WC_FIRE, WA_NORMAL, 10, NULL);

}

void Player::mvup()
{
    face_direction = FACING_UP;
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
    face_direction = FACING_DOWN;
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
    face_direction = FACING_LEFT;
    mvin_wch(yLoc, xLoc - 1, &standingon);
    if (xLoc < 47 || !safe_to_move(standingon.chars))
        return;
    xLoc--;
}

void Player::mvrt()
{
    face_direction = FACING_RIGHT;
    mvin_wch(yLoc, xLoc + 1, &standingon);
    if (xLoc > 76 || !safe_to_move(standingon.chars))
        return;
    mvin_wch(yLoc, xLoc + 2, &standingon);
    if (!safe_to_move(standingon.chars))
        return;
    xLoc++;
}

int Player::fire_is_lit()
{
    if (fire_start_time.tv_sec == 0)
        return FALSE;
    return TRUE;
}

int Player::grabbed_trash(int facing_y, int facing_x)
{
    cchar_t facing_block = { 0 };
    wchar_t *fb_chars;

    if (wcsncmp(item_holding_char, L"", 2) != 0)
        return FALSE;

    mvin_wch(facing_y, facing_x, &facing_block);
    fb_chars = facing_block.chars;

    if (wcsncmp(LC_TRASH1, fb_chars, 2) == 0)
        goto hold_it;
    else if (wcsncmp(LC_TRASH2, fb_chars, 2) == 0)
        goto hold_it;
    else if (wcsncmp(LC_TRASH3, fb_chars, 2) == 0)
        goto hold_it;
    else if (wcsncmp(LC_TRASH4, fb_chars, 2) == 0)
        goto hold_it;
    else if (wcsncmp(LC_TRASH5, fb_chars, 2) == 0)
        goto hold_it;
    else if (wcsncmp(LC_TRASH6, fb_chars, 2) == 0)
        goto hold_it;

    return FALSE;

    hold_it:
    wcsncpy(item_holding_char, facing_block.chars, 2);
    setcchar(&item_hold_print_char, facing_block.chars, WA_NORMAL, 12, NULL);
    wave->clean_beach(facing_y - 9);
    return TRUE;
}

int Player::tossed_trash(int facing_y, int facing_x)
{
    cchar_t facing_block = { 0 };
    wchar_t *fb_chars;

    mvin_wch(facing_y, facing_x, &facing_block);
    fb_chars = facing_block.chars;
    if (wcsncmp(WC_BIN, fb_chars, 2) == 0)
    {
        if (wcsncmp(item_holding_char, L"", 2) != 0)
        {
            wcsncpy(item_holding_char, L"", 2);
            wcsncpy(item_hold_print_char.chars, L"", 2);
            bin_trash_qty++;
            if (bin_trash_qty > 999)
                bin_trash_qty = 999;
        }
        return TRUE;
    }
    return FALSE;
}


int Player::used_magla(int facing_y, int facing_x)
{
    cchar_t facing_block = { 0 };
    wchar_t *fb_chars;

    mvin_wch(facing_y, facing_x, &facing_block);
    fb_chars = facing_block.chars;
    if (wcsncmp(WC_MAGLA, fb_chars, 2) != 0)
        return FALSE;

    if (bin_trash_qty > 0)
    {
        clock_gettime(CLOCK_MONOTONIC_COARSE, &fire_start_time);
        last_update.tv_sec = fire_start_time.tv_sec;
    }
    return TRUE;
}


void Player::action()
{
    int facing_x = xLoc;
    int facing_y = yLoc;

    if (face_direction == FACING_UP)
    {
        if (yLoc < 10)
            return;
        facing_y--;
    }
    else if (face_direction == FACING_LEFT)
    {
        if (xLoc < 47)
            return;
        facing_x--;
    }
    else if (face_direction == FACING_RIGHT)
    {
        if (xLoc > 77)
            return;
        facing_x += 2;
    }
    else if (face_direction == FACING_DOWN)
    {
        if (yLoc > 22)
            return;
        facing_y++;
    }
    if (grabbed_trash(facing_y, facing_x) == TRUE)
        ;
    else if (tossed_trash(facing_y, facing_x) == TRUE)
        ;
    else if (used_magla(facing_y, facing_x) == TRUE)
        ;
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
        case ' ':
            action();
            break;
        default:
            break;
    }
    return choice;
}

void Player::update()
{
    struct timespec this_time;
    size_t frame_num;

    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    frame_num = this_time.tv_sec - fire_start_time.tv_sec;
    if (frame_num < 0)
        return;
    // do once per second
    if ((this_time.tv_sec - last_update.tv_sec) > 0)
    {
        if (fire_is_lit())
        {
            bin_trash_qty--;

            if (bin_trash_qty <= 0)
                fire_start_time.tv_sec = 0;

        }
        last_update.tv_sec = this_time.tv_sec;
    }

}

void Player::display()
{
    mvadd_wch(yLoc, xLoc, &charchar);
    mvadd_wchstr(10, 16, &item_hold_print_char);
    if (fire_is_lit())
        mvadd_wch(12, 53, &fire_char);

}

int Player::get_trash_qty()
{
    return bin_trash_qty;
}


#endif /* PLAYER_H */
