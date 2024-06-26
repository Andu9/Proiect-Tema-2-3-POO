#ifndef OOP_ARROW_H
#define OOP_ARROW_H

#include "Trap.h"

class Arrow : public Trap {
    private:
        static const float gravity;
        float verticalSpeed;

        static float getRandom(float Max);
    public:
        explicit Arrow(sf::RenderWindow& window, const std::string& fileName);
        void resetCoordinates(sf::RenderWindow& window);
        void move(sf::RenderWindow& window);
};

#endif