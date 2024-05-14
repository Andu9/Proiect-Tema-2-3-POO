#ifndef OOP_GOLDENCARROT_H
#define OOP_GOLDENCARROT_H

#include "Carrot.h"

class GoldenCarrot : public Carrot {
    private:
        sf::Clock timer;
        bool appears;

    public:
        explicit GoldenCarrot(sf::RenderWindow& window, const std::string& fileName);
        void draw(sf::RenderWindow& window);
        void isTaken();
};

#endif