#include "Thing.h"

Thing::Thing() : size{50, 50}, position{10, 10} {
    box.setSize(size);
    box.setFillColor(sf::Color::White);
}

Thing::Thing(sf::Vector2f _size, sf::Vector2f _position) : size(_size), position(_position) {
    box.setSize(size);
    box.setFillColor(sf::Color::White);
}

sf::Vector2f Thing::getSize() const { return size; }

sf::Vector2f Thing::getPosition() const { return position; }

void Thing::setPosition() {
    box.setPosition(position);
}

void Thing::draw(sf::RenderWindow& window) {
    window.draw(box);
}

bool Thing::checkCollision(Thing& other) {
    sf::FloatRect playerBounds(position, size);
    sf::FloatRect carrotBounds(other.getPosition(), other.getSize());

    return playerBounds.intersects(carrotBounds);
}