#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "../Headers/Player.h"
#include "../Headers/GoldenCarrot.h"
#include "../Headers/Arrow.h"
#include "../Headers/Cannonball.h"
#include "../Headers/SpikeyBall.h"

#include <SFML/Graphics.hpp>

class Game {
    private:
        sf::RenderWindow window;

        sf::Texture texture;
        sf::Sprite background;

        Player player;

        std::array<Thing, 8> platforms;

        Arrow currentArrow;
        Carrot currentCarrot;
        GoldenCarrot goldenCarrot;

        bool lost;

        sf::Clock timer;
        std::vector<FiniteChoice *> traps;
        std::vector<int> choices;

        static int getRandom(int Maxim);

    public:
        Game();
        void drawThings();
        void run();
};

#endif
