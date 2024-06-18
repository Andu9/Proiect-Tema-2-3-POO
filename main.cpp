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
        Game<1> game(x);

        try {
            game.run();
        } catch(GeneralException& err) {
            game.close();
        }
    } else {
        std::ifstream fin("highScore.txt");
        int x; fin >> x;
        Game<2> game(x);

        try {
            game.run();
        } catch(GeneralException&) {
            game.close();
        }
    }
    return 0;
}

