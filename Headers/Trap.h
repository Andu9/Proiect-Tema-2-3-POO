#ifndef OOP_TRAP_H
#define OOP_TRAP_H

#include "MoveableThing.h"

class Trap : virtual public MoveableThing {
    protected:
        sf::Clock timer;
        float damage;

    public:
        Trap(float _damage);
        float getDamage() const;
};

#endif