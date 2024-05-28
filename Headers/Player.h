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
        template<typename T>
        friend bool checkCollision(const Player& player, const T& trap);

        explicit Player(sf::RenderWindow& window, const std::string& fileName);
        void move(sf::RenderWindow& window, std::array<Thing, 8> platforms);
        void increaseHealth(float addedHealth);
        void decreaseHealth(float damage);
        void increaseScore(int addedScore);
        int getScore() const;
        float getHealth() const;
        void setScore(int _score);
        void setHealth(float _health);
};

template<typename T>
bool checkCollision(const Player& player, const T& trap) {
    sf::FloatRect playerBounds(player.position, player.size);
    sf::FloatRect trapBounds(trap.getPosition(), trap.getSize());

    return playerBounds.intersects(trapBounds);
}

#endif