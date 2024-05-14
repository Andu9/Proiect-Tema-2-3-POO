#ifndef OOP_CARROT_H
#define OOP_CARROT_H

#include "Thing.h"
#include <random>
#include <SFML/Graphics.hpp>

class Carrot : virtual public Thing {
    protected:
        int score;

        static float getRandom(float Min, float Max);

    public:
        Carrot(sf::RenderWindow& window, int _score, const std::string& fileName);
        void resetCoordinates(sf::RenderWindow& window);
        int getScore() const;
};

#endif
