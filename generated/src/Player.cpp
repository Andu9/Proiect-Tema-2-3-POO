#include "Player.h"

Player::Player(sf::RenderWindow& window) : MoveableThing(10.f), health(3) {
    position.x = (window.getSize().x - size.x) / 2;
    position.y = window.getSize().y - size.y - 10;

    std::cout << "health: " << health << '\n';
    std::cout << "speed: " << speed << '\n';
    std::cout << "position: " << box.getPosition().x << ' ' << box.getPosition().y << '\n';
    std::cout << "size: " << size.x << ' ' << size.y << '\n';
}

void Player::jump() {

}