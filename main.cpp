#include "Headers/Game.h"
#include <fstream>

int main() {
    unsigned short input; std::cin >> input;
    while (input != 1 && input != 2) {
        std::cin >> input;
    }



    if (input == 1) {
        std::ifstream fin("highScore.txt");
        int x; fin >> x;
        Game<1> game(x); game.run();
    } else {
        std::ifstream fin("highScore.txt");
        int x; fin >> x;
        Game<2> game(x); game.run();
    }
    return 0;
}

