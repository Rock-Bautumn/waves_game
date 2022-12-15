#include "waves.h"
#include "map.h"

void print_base(void)
{
    int y;
    int x;
    // cchar_t standingon;
    cchar_t sand = { 0 };
    cchar_t sky = { 0 };
    cchar_t tree = { 0 };
    cchar_t bin = { 0 };

    if (can_change_color())
    {
        setcchar(&sky, WC_SKY, WA_NORMAL, 11, NULL);
        setcchar(&sand, L"▓", WA_NORMAL, 10, NULL);
        setcchar(&tree, WC_TREE, WA_NORMAL, 10, NULL);
        setcchar(&bin, WC_BIN, WA_NORMAL, 10, NULL);

        attron(COLOR_PAIR(9));
    }
    for (y = 0; y < 24; y++)
    {
        for (x = 0; x < 79; x++)
        {
            /*
            else
                printw("🔥");
            */
            if (y < 4)
                add_wch(&sky);
            else if ((y == 11 && x == 4) || (y == 14 && x == 8))
                {
                    add_wch(&tree);
                    x++;
                }
            else if (4 < x && x < 8 && 20 < y && y < 23)
                {
                    add_wch(&tree);
                    x++;
                }
            else if (y == 16 && x == 17)
                {
                    add_wch(&bin);
                    // x++;
                }
            else if (y > 8 && x < 33)
                add_wch(&sand);
                // printw("▓");
            else
                printw("░");
        }
        printw("\n");
    }
    refresh();
    /* mvin_wch(11, 4, &standingon);


    mvadd_wch(2, 2, &standingon);
    if (wcsncmp(standingon.chars, tree.chars, 2) == 0)
            mvadd_wch(2, 20, &standingon);
    */
    attroff(COLOR_PAIR(9));

}
