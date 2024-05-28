#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "../Headers/Player.h"
#include "../Headers/GoldenCarrot.h"
#include "../Headers/Arrow.h"
#include "../Headers/Cannonball.h"
#include "../Headers/SpikeyBall.h"
#include "../Headers/Saw.h"
#include "../Headers/Exceptions.h"

#include <memory>
#include <SFML/Graphics.hpp>

template<const unsigned short T>
class Game {
    private:
        sf::RenderWindow window;

        sf::Texture texture;
        sf::Sprite background;

        std::array<std::shared_ptr<Player>, T> players;

        std::array<Thing, 8> platforms;

        sf::Font font;

        std::array<sf::Text, T> currentScores;
        std::array<sf::Text, T> currentHealths;

        Arrow currentArrow;
        Carrot currentCarrot;
        GoldenCarrot goldenCarrot;

        bool lost, pause;

        sf::Clock timer;
        sf::Clock totalTimer;
        std::vector<std::shared_ptr<FiniteChoice>> traps;
        std::vector<int> choices;

        static int getRandom(int Maxim);

    public:
        Game();
        Game(const Game& oth) = delete;
        Game& operator=(const Game& oth);

        void close();
        void drawThings();
        void run();
        void drawLost();
        void reset();
        void drawPause();
        ~Game();
};

#endif
