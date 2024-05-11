#ifndef OOP_COLLISION_H
#define OOP_COLLISION_H

#include <SFML/Graphics.hpp>

class Collision {
    private:
        sf::RectangleShape shape;

    public:
        Collision(sf::RectangleShape& _shape);
        bool detectCollision(Collision other, float push);

        sf::Vector2f GetPosition();
        sf::Vector2f GetHalfSize();
};

#endif
