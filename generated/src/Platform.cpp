#include "Platform.h"

Platform::Platform(sf::Vector2f _size, sf::Vector2f _position) : Thing(_size, _position) {}

void Platform::draw(sf::RenderWindow& window) {
    box.setPosition(position);
    window.draw(box);
}