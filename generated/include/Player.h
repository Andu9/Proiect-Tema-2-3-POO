#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "MoveableThing.h"

class Player : public MoveableThing {
    private:
        unsigned int health;

    public:
        Player(sf::RenderWindow& window);
        void jump();
};


#endif