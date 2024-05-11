#include "Player.h"

Player::Player(sf::RenderWindow& window) : health(3), jumpFlag(false), dy(0) {
    position.x = (window.getSize().x - size.x) / 2;
    position.y = window.getSize().y - size.y - 10;

    std::cout << "health: " << health << '\n';
    std::cout << "speed: " << speed << '\n';
    std::cout << "position: " << box.getPosition().x << ' ' << box.getPosition().y << '\n';
    std::cout << "size: " << size.x << ' ' << size.y << '\n';
}

void Player::move(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= speed;
    }

    if (position.x <= 0) { position.x = 0; }
    if (position.x >= window.getSize().x - size.x) {
        position.x = window.getSize().x - size.x;
    }

    const float gravity = 0.5f;
    const float jumpVelocity = -10.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jumpFlag) {
        jumpFlag = true;
        dy = jumpVelocity;
    }

    if (jumpFlag) {
        dy += gravity;
        position.y += dy;

        if (position.y >= window.getSize().y - size.y) {
            position.y = window.getSize().y - size.y;
            jumpFlag = false;
            dy = 0.f;
        }
    }

/*        jumpFlag = true;
        dy += 0.2;
        position.y += dy;

        if (position.y >= window.getSize().y - size.y) {
            jumpFlag = false;
            dy -= 10.f;
        }
    */
}