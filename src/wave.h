#ifndef WAVE_H
#define WAVE_H

#include "waves.h"
#define LC_WAVE L"🌊"
#define LC_TRASH1 L"👢"
#define LC_TRASH2 L"📰"
#define LC_TRASH3 L"🧴"
#define LC_TRASH4 L"🩲"
#define LC_TRASH5 L"🧸"
#define LC_TRASH6 L"💿"
#define FLIPPA L"🩴"

class Wave
{
    public:
        char beach[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Wave(void);
        long int get_start();
        void update();
        void display();
        void clean_beach(int beach_num);
        cchar_t *get_trash(int beach_num);

    private:
        cchar_t wave_char;
        cchar_t trash1_char;
        cchar_t trash2_char;
        cchar_t trash3_char;
        cchar_t trash4_char;
        cchar_t trash5_char;
        cchar_t trash6_char;
        struct timespec start_time;
        struct timespec last_update;
};

Wave::Wave(void)
{
    setcchar(&wave_char, LC_WAVE, WA_NORMAL, 9, NULL);
    setcchar(&trash1_char, LC_TRASH1, WA_NORMAL, 10, NULL);
    setcchar(&trash2_char, LC_TRASH2, WA_NORMAL, 10, NULL);
    setcchar(&trash3_char, LC_TRASH3, WA_NORMAL, 10, NULL);
    setcchar(&trash4_char, LC_TRASH4, WA_NORMAL, 10, NULL);
    setcchar(&trash5_char, LC_TRASH5, WA_NORMAL, 10, NULL);
    setcchar(&trash6_char, LC_TRASH6, WA_NORMAL, 10, NULL);
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
    size_t frame_num;

    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    frame_num = this_time.tv_sec - start_time.tv_sec;
    if ((this_time.tv_sec - last_update.tv_sec) > 0)
    {
        last_update.tv_sec = this_time.tv_sec;
        if (beach[frame_num] == 0 && 5 == rand() % 6 + 1)
            beach[frame_num] = rand() % 6 + 1;
    }

    // mvin_wch(frame_num + 9, 47, &beach_square);
    // mvadd_wch(2, 2, &beach_square);

    if (frame_num >= 15)
    {
        clock_gettime(CLOCK_MONOTONIC_COARSE, &start_time);
        last_update.tv_sec = start_time.tv_sec;
        last_update.tv_nsec = start_time.tv_nsec;
    }

}
cchar_t *Wave::get_trash(int beach_num)
{
    int beach_val = beach[beach_num];

    switch (beach_val)
    {
    case 1:
        return &trash1_char;
    case 2:
        return &trash2_char;
    case 3:
        return &trash3_char;
    case 4:
        return &trash4_char;
    case 5:
        return &trash5_char;
    case 6:
        return &trash6_char;
    default:
        return &wave_char;
    }
}

void Wave::clean_beach(int beach_num)
{
    beach[beach_num] = 0;
}
void Wave::display()
{
    struct timespec this_time;
    int yLoc, i;

    clock_gettime(CLOCK_MONOTONIC_COARSE, &this_time);
    yLoc = this_time.tv_sec - start_time.tv_sec;
    mvadd_wch(9 + yLoc, 44, &wave_char);
    for (i = 0; i < 15; i++)
    {
        if (beach[i] != 0)
            mvadd_wch(9 + i, 46, get_trash(i));
    }
}

#endif /* WAVE_H */
