#ifndef OOP_ARROW_H
#define OOP_ARROW_H

#include "Trap.h"

class Arrow : public Trap {
    private:
        static const float gravity;
        float verticalSpeed;

        static float getRandom(float Min, float Max);
    public:
        Arrow(sf::RenderWindow& window);
        void resetCoordinates(sf::RenderWindow& window);
        void move(sf::RenderWindow& window);
};

#endif