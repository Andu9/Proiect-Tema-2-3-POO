#ifndef OOP_MOVEABLETHING_H
#define OOP_MOVEABLETHING_H

#include "Thing.h"

class MoveableThing : public Thing {
    protected:
        float speed;

    public:
        MoveableThing();
        MoveableThing(float _speed);
        MoveableThing(sf::Vector2f _size, sf::Vector2f _position, float speed);
};

#endif
