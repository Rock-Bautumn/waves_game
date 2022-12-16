#ifndef WAVE_H
#define WAVE_H

#include "waves.h"
#define LC_WAVE L"🌊"

/*
    wave start
    last frame time finished
*/
class Wave
{
    public:
        Wave(void);
        long int get_start();
        void update();
        void display();


    private:
        cchar_t wave_char;
        struct timespec start_time;
        struct timespec last_update;
};

Wave::Wave(void)
{
    setcchar(&wave_char, LC_WAVE, WA_NORMAL, 9, NULL);
    clock_gettime(CLOCK_MONOTONIC_COARSE, &start_time);
    last_update.tv_sec = start_time.tv_sec;
    last_update.tv_nsec = start_time.tv_nsec;
}

long int Wave::get_start()
{
    return start_time.tv_sec;
}
void Wave::update()
{
    struct timespec this_time;
    cchar_t beach_square;
    //    mvin_wch(yLoc - 1, xLoc, &standingon);

    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    if ((this_time.tv_sec - last_update.tv_nsec) > 0)
    {
        mvin_wch((this_time.tv_sec - start_time.tv_sec) + 11, 47, &beach_square);
        mvadd_wch(2, 2, &beach_square);
        last_update.tv_nsec = this_time.tv_sec;
    }
    if ((this_time.tv_sec - start_time.tv_sec) >= 15)
    {
        clock_gettime(CLOCK_MONOTONIC_COARSE, &start_time);
        last_update.tv_sec = start_time.tv_sec;
        last_update.tv_nsec = start_time.tv_nsec;
    }

}

void Wave::display()
{
    struct timespec this_time;
    int yLoc;
    
    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    yLoc = this_time.tv_sec - start_time.tv_sec - 2;
    mvadd_wch(11 + yLoc, 44, &wave_char);
}

#endif /* WAVE_H */
