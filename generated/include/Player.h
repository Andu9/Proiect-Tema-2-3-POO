#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "MoveableThing.h"

class Player : public MoveableThing {
    private:
        unsigned int health;
        bool jumpFlag;
        float dy;

    public:
        Player(sf::RenderWindow& window);
        void move(sf::RenderWindow& window);
};


#endif