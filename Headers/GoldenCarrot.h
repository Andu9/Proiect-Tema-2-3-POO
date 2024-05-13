#ifndef OOP_GOLDENCARROT_H
#define OOP_GOLDENCARROT_H

#include "Carrot.h"

class GoldenCarrot : public Carrot {
    private:
        sf::Clock timer;
        bool appears;

    public:
        GoldenCarrot(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void isTaken();
};

#endif