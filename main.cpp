#include "Headers/Game.h"

int main() {
    int noPlayers; std::cin >> noPlayers;
    while (noPlayers != 1 && noPlayers != 2) {
        std::cin >> noPlayers;
    }

    if (noPlayers == 1) {
        Game<1> game; game.run();
    } else {
        Game<2> game; game.run();
    }
    return 0;
}

