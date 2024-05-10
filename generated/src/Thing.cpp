#include "Thing.h"

Thing::Thing() : size{50, 50}, position{10, 10} {
    box.setFillColor(sf::Color::White);
}

Thing::Thing(sf::Vector2f _size, sf::Vector2f _position) : size(_size), position(_position) {
    box.setFillColor(sf::Color::White);
}

void Thing::draw(sf::RenderWindow& window) {
    box.setPosition(position);
    box.setSize(size);
    window.draw(box);
}