#include "Player.h"

Player::Player(sf::RenderWindow& window) : health(3.f), jumpFlag(false), isOnPlatform(false), dy(0), score(0) {
    position.x = (window.getSize().x - size.x) / 2;
    position.y = window.getSize().y - size.y - 111;
}

void Player::move(sf::RenderWindow& window, std::array<Thing, 8> platforms) {
    sf::Vector2f pos, sz;
    for (int i = 0; i < 8; i += 1) {
        Thing currentPlatform = platforms[i];

        if (position.y + size.y == currentPlatform.getPosition().y
         && position.x + size.x >= currentPlatform.getPosition().x
         && position.x <= currentPlatform.getPosition().x + currentPlatform.getSize().x) {
            pos = currentPlatform.getPosition(), sz = currentPlatform.getSize();
            isOnPlatform = true; break;
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed((sf::Keyboard::Left))) {
        position.x += speed;

        if (isOnPlatform && position.x >= pos.x + sz.x) {
            isOnPlatform = false;
            jumpFlag = true;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { dy = 0; }
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed((sf::Keyboard::Right))) {
        position.x -= speed;

        if (isOnPlatform && position.x + size.x <= pos.x) {
            isOnPlatform = false;
            jumpFlag = true;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { dy = 0; }
        }
    }

    if (position.x <= 0) { position.x = 0; }
    if (position.x >= window.getSize().x - size.x) {
        position.x = window.getSize().x - size.x;
    }

    const float gravity = 0.6f;
    const float jumpVelocity = -15.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jumpFlag) {
        jumpFlag = true;
        dy = jumpVelocity;
        isOnPlatform = false;
    }


    if (jumpFlag) {
        dy += gravity;
        position.y += dy;

        for (const auto& platform : platforms) {
            ///sf::FloatRect playerBounds(position, size);
            ///sf::FloatRect platformBounds(platform.getPosition(), platform.getSize());

            // Check if player is touching the bottom side of the platform

                if (position.y + size.y >= platform.getPosition().y  // Player's bottom reaches or goes below platform's top
                    && position.y + size.y <= platform.getPosition().y + 25 // Player's bottom is within 10 pixels of platform's top
                    && position.x + size.x >= platform.getPosition().x
                    && position.x <= platform.getPosition().x + platform.getSize().x
                    && dy > 0) {  // Player is moving downwards (falling)

                    // Snap player on top of the platform
                    position.y = platform.getPosition().y - size.y;
                    jumpFlag = false;
                    dy = 0.f;

                    isOnPlatform = true;
                }
            }


        if (position.y >= window.getSize().y - size.y - 111) {
            position.y = window.getSize().y - size.y - 111;
            jumpFlag = false;
            isOnPlatform = false;
            dy = 0.f;
        }
    }
}

void Player::increaseScore(int addedScore) { score += addedScore; }

void Player::decreaseHealth(float damage) { health -= damage; }

int Player::getScore() const  { return score; }

float Player::getHealth() const { return health; }