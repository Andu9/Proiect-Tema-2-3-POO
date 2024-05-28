#ifndef OOP_THING_H
#define OOP_THING_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Headers/Exceptions.h"

class Thing {
    protected:
        sf::Vector2f size;
        sf::Vector2f position;
        sf::RectangleShape box;

        sf::Texture texture;
        sf::Sprite image;

    public:
        Thing() = default;
        Thing& operator=(const Thing& other);
        Thing(const Thing& oth);
        explicit Thing(const std::string& fileName);
        Thing(sf::Vector2f _size, sf::Vector2f _position, const std::string& fileName);
        void initTextures(const std::string& fileName);

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;

        virtual void draw(sf::RenderWindow& window);
        void setPosition();

        virtual ~Thing() = default;
};

#endif
