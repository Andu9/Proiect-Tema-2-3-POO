#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <array>
#include "MoveableThing.h"

class Player : public MoveableThing {
    private:
        unsigned int health;
        bool jumpFlag;
        bool isOnPlatform;
        float dy;
        int score;
        int i;

    public:
        Player(sf::RenderWindow& window);
        void move(sf::RenderWindow& window, std::array<Thing, 8> platforms);
        void increaseScore(int addedScore);
        int getScore() const;
};


#endif