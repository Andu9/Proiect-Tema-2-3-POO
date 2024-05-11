#ifndef OOP_PLATFORM_H
#define OOP_PLATFORM_H

#include "Thing.h"

class Platform : public Thing {
    private:


    public:
        Platform(sf::Vector2f _size, sf::Vector2f _position);
        void draw(sf::RenderWindow& window);
};

#endif