#include "waves.h"
#include "map.h"

void print_base(int trash_qty)
{
    int y;
    int x;
    cchar_t sand = { 0 };
    cchar_t sky = { 0 };
    cchar_t tree = { 0 };
    cchar_t bin = { 0 };
    cchar_t magla = { 0 };

    setcchar(&sky, WC_SKY, WA_NORMAL, 11, NULL);
    setcchar(&sand, L"▓", WA_NORMAL, 10, NULL);
    setcchar(&tree, WC_TREE, WA_NORMAL, 10, NULL);
    setcchar(&bin, WC_BIN, WA_NORMAL, 10, NULL);
    setcchar(&magla, WC_MAGLA, WA_NORMAL, 10, NULL);

    for (y = 0; y < 24; y++)
    {
        for (x = 0; x < 79; x++)
        {
            if (y < 4)
                add_wch(&sky);
            else if ((y == 12 && x == 74) || (y == 21 && x == 68))
            {
                add_wch(&tree);
                x++;
            }
            else if ((y == 11 && x == 58) || (y == 14 && x == 60))
            {
                add_wch(&tree);
                x++;
            }                
            else if (64 < x && x < 68 && 18 < y && y < 21)
            {
                add_wch(&tree);
                x++;
            }
            else if (50 < x && x < 54 && 20 < y && y < 23)
            {
                add_wch(&tree);
                x++;
            }
            else if (y == 12 && x == 51)
            {
                add_wch(&magla);
                x++;
            }
            else if (y == 13 && x == 53)
            {
                add_wch(&bin);
                // x++; We don't need this for some reason
            }
            else if (y > 8 && x > 45)
                add_wch(&sand);
            else if (y == 9 && x == 1)
            {
                printw("Trash in bin:%3d", trash_qty);
                x += 15;
            }
            else if (y == 10 && x == 1)
            {
                printw("Holding trash [");
                x += 14;
            }
            else if (y == 10 && x == 18)
                printw("]");
            else
                printw(" ");
        }
        printw("\n");
    }

}
