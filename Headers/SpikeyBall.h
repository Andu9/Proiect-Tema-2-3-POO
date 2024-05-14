#ifndef OOP_SPIKEYBALL_H
#define OOP_SPIKEYBALL_H

#include "../Headers/FiniteChoice.h"

class SpikeyBall : public FiniteChoice {
    private:
        std::pair<float, float> initialPosition;
        int signVertical, signHorizontal;

    public:
        SpikeyBall(const std::string& fileName);
        void spawn();
        void move(sf::RenderWindow& window);
};

#endif
