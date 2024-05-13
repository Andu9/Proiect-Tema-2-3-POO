#ifndef OOP_CANNONBALL_H
#define OOP_CANNONBALL_H

#include "FiniteChoice.h"

class CannonBall : public FiniteChoice {
    private:
        int sign;
        std::pair<float, float> initialPosition;

    public:
        CannonBall();
        void spawn();
        void resetCoordinates();
        void move(sf::RenderWindow& window);
};

#endif
