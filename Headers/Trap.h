#ifndef OOP_TRAP_H
#define OOP_TRAP_H

#include "MoveableThing.h"

class Trap : public MoveableThing {
    protected:
        sf::Clock timer;
        float damage;

    public:
        explicit Trap(float _damage, const std::string& fileName);
        float getDamage() const;
};

#endif