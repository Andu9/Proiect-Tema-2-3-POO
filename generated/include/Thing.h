#ifndef OOP_THING_H
#define OOP_THING_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Collision.h"

class Thing {
    protected:
        sf::Vector2f size;
        sf::Vector2f position;
        sf::RectangleShape box;

    public:
        Thing();
        Thing(sf::Vector2f _size, sf::Vector2f _position);
        virtual void draw(sf::RenderWindow& window);
        void setPosition();
};

#endif //OOP_THING_H
