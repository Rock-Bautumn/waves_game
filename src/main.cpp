#include "waves.hpp"
#include "player.h"
#include "wave.cpp"
#include "ship.h"
#include "window/window.h"
#include <memory>

using std::make_shared, std::make_unique;

int main() {
    Window window;
    window.set_color();

    // RAII implementation == safety use of memory heap
    {
        auto wave = make_shared<Wave>();
        auto plr = make_shared<Player>(wave, 9, 46, CHAR_PLAYER);
        auto ship = make_unique<Ship>(plr);
        nodelay(stdscr, TRUE);
        while (plr->getmv() != 'x') {
            erase();
            window.print_base(plr->get_trash_qty());
            plr->update();
            plr->display();
            wave->update();
            wave->display();
            ship->update();
            ship->display();
            refresh();
            usleep(8000); // 8000 microseconds = 125 delays per second (fps limiter)
        }
    }
    window.close();
}
