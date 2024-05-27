#include "Headers/Game.h"

int main() {
    Game currentGame;
    try {
        currentGame.run();
    }
    catch(GeneralException&) {
        currentGame.close();
    }
    return 0;
 }

