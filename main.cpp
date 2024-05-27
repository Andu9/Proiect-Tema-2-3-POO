#include "Headers/Game.h"

int main() {
    Game currentGame;
    try {
        currentGame.run();
    }
    catch(MissingTexture&) {
        currentGame.close();
    }
    catch(MissingFont&) {
        currentGame.close();
    }
    return 0;
 }

