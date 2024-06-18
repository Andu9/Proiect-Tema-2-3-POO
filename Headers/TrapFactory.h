#ifndef OOP_TRAPFACTORY_H
#define OOP_TRAPFACTORY_H

#include <memory>
#include "Exceptions.h"

class TrapFactory {
    public:
        static std::shared_ptr<FiniteChoice> getTrap(int option) {
            if (option == 0) {
                return std::make_shared<CannonBall>("./CannonBall.png");
            } else if (option == 1) {
                return std::make_shared<SpikeyBall>("./SpikeyBall.png");
            } else if (option == 2) {
                return std::make_shared<Saw>("./Saw.png");
            }
            throw InvalidTrapType("Invalid trap type!\n");
        }
};

#endif
