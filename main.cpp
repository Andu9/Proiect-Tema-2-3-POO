#include "Headers/Game.h"
#include <fstream>

int main() {
    while (true) {
        std::cout << "To close the game type -1\n";
        short input; std::cout << "Input the number of players (either 1 or 2): "; std::cin >> input;
        while (input != 1 && input != 2 && input != -1) {
            std::cout << "That is not right! Choose 1 or 2: "; std::cin >> input;
        }
        std::cout << '\n';

        if (input == -1) {
            break;
        }

        if (input == 1) {
            std::ifstream fin("highScore.txt");
            int x; fin >> x;
            Game<1> game(x);
            try {
                game.run();
            } catch(GeneralException&) {
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
    }
    return 0;
}

