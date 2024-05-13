#ifndef OOP_SAW_H
#define OOP_SAW_H

#include "FiniteChoice.h"

class Saw : public FiniteChoice {
    private:
        int sign;
        std::pair<float, float> initialPosition;

    public:
        Saw();
        void spawn();
        void move(sf::RenderWindow& window);
};

#endif
