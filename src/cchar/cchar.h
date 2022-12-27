//
// Created by william rodriguez on 27/12/22.
//

#ifndef WAVES_GAME_CCHAR_H
#define WAVES_GAME_CCHAR_H

#include <ncursesw/curses.h>

class Cchar {
    cchar_t cchar;
public:

    Cchar(const wchar_t *wch, short attr){
        setcchar(&cchar, wch, WA_NORMAL, attr, nullptr);
    }

    void add(){
        add_wch(&cchar);
    }
};


#endif //WAVES_GAME_CCHAR_H
