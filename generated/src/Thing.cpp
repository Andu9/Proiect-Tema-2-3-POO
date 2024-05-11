#include "Thing.h"

Thing::Thing() : size{50, 50}, position{10, 10} {
    box.setSize(size);
    box.setFillColor(sf::Color::White);
}

Thing::Thing(sf::Vector2f _size, sf::Vector2f _position) : size(_size), position(_position) {
    box.setSize(size);
    box.setFillColor(sf::Color::White);
}

void Thing::setPosition() {
    box.setPosition(position);
}

void Thing::draw(sf::RenderWindow& window) {
    window.draw(box);
}

