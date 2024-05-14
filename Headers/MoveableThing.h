#ifndef OOP_MOVEABLETHING_H
#define OOP_MOVEABLETHING_H

#include "Thing.h"

class MoveableThing : public Thing {
    protected:
        float speed;

    public:
        MoveableThing() = default;
        explicit MoveableThing(const std::string& fileName);
        explicit MoveableThing(float _speed) : speed(_speed) {};
        explicit MoveableThing(float _speed, const std::string& fileName);
        MoveableThing(sf::Vector2f _size, sf::Vector2f _position, float speed, const std::string& fileName);
};

#endif
