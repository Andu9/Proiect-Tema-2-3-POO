#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "../Headers/Player.h"
#include "../Headers/GoldenCarrot.h"
#include "../Headers/Arrow.h"
#include "../Headers/Cannonball.h"
#include "../Headers/SpikeyBall.h"
#include "../Headers/Saw.h"
#include "../Headers/Exceptions.h"
#include "../Headers/TrapFactory.h"
#include "../Headers/TextBuilder.h"

#include <memory>
#include <string>
#include <array>
#include <unordered_map>
#include <fstream>
#include <SFML/Graphics.hpp>

template<unsigned short T>
class Game {
    private:
        static int highScore;
        static std::array<sf::Vector2f, 2> healthTextPos;
        static std::array<sf::Vector2f, 2> scoreTextPos;

        sf::RenderWindow window;

        sf::Texture texture;
        sf::Sprite background;

        std::unordered_map<int, bool> isAlive;
        std::array<Player, T> players;

        std::array<Thing, 8> platforms;

        std::array<Text, T> currentScores;
        std::array<Text, T> currentHealths;

        Arrow currentArrow;
        Carrot currentCarrot;
        GoldenCarrot goldenCarrot;

        bool lost, pause;

        sf::Clock timer;
        sf::Clock totalTimer;
        std::vector<std::shared_ptr<FiniteChoice>> traps;
        std::vector<int> choices;

        int sum();

        static int getRandom(int Maxim);

    public:
        [[maybe_unused]] explicit Game(int);
        Game(const Game& oth) = delete;

        void close();
        void drawThings();
        void run();
        void drawLost();
        void reset();
        void drawPause();
        ~Game();

        template<typename X, typename Y>
        friend bool checkCollision(const X& thing1, const Y& thing2);
};

template<typename X, typename Y>
bool checkCollision(const X& thing1, const Y& thing2) {
    sf::FloatRect bounds1(thing1.getPosition(), thing1.getSize());
    sf::FloatRect bounds2(thing2.getPosition(), thing2.getSize());

    return bounds1.intersects(bounds2);
}

#endif
