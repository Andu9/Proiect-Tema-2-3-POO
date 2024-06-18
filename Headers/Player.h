#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <array>
#include "MoveableThing.h"

class Player : public MoveableThing {
    private:
        float health;
        bool jumpFlag;
        bool isOnPlatform;
        float dy;
        int score;

    public:
        Player() = default;

        explicit Player(const sf::RenderWindow& window, const std::string& fileName);
        void move(sf::RenderWindow& window, std::array<Thing, 8> platforms, int player);
        void increaseHealth(float addedHealth);
        void decreaseHealth(float damage);
        void increaseScore(int addedScore);
        int getScore() const;
        float getHealth() const;
        void reset(const sf::RenderWindow& window, const std::string& fileName);
};

#endif