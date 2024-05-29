#ifndef OOP_MOVEABLETHING_H
#define OOP_MOVEABLETHING_H

#include "Thing.h"

class MoveableThing : public Thing {
    protected:
        float speed{};

    public:
        bool checkCollision(const Thing& thing) {
            sf::FloatRect playerBounds(position, size);
            sf::FloatRect trapBounds(thing.getPosition(), thing.getSize());

            return playerBounds.intersects(trapBounds);
        }

        MoveableThing() = default;
        explicit MoveableThing(const std::string& fileName);
};

#endif
