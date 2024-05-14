#ifndef OOP_CANNONBALL_H
#define OOP_CANNONBALL_H

#include "FiniteChoice.h"

class CannonBall : public FiniteChoice {
    private:
        int sign;
        sf::Texture textureCannon;
        sf::Sprite cannon;
        std::pair<float, float> initialPosition;

    public:
        CannonBall(const std::string& fileName);
        void spawn();
        void resetCoordinates();
        void move(sf::RenderWindow& window);
};

#endif
