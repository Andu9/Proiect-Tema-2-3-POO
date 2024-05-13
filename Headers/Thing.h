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
        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        virtual void draw(sf::RenderWindow& window);
        void setPosition();
        bool checkCollision(Thing& other);
};

#endif //OOP_THING_H
