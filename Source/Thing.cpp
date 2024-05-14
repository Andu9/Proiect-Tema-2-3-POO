#include "../Headers/Thing.h"

Thing::Thing(const std::string& fileName) : size{50, 50}, position{10, 10}, texture(), image() {
    texture.loadFromFile(fileName);
    image.setTexture(texture);

    box.setSize(size);
    box.setFillColor(sf::Color::White);
}

Thing::Thing(sf::Vector2f _size, sf::Vector2f _position, const std::string& fileName) : size(_size), position(_position),
         texture(), image() {

    texture.loadFromFile(fileName);
    image.setTexture(texture);

    box.setSize(size);
}

sf::Vector2f Thing::getSize() const { return size; }

sf::Vector2f Thing::getPosition() const { return position; }

void Thing::setPosition() {
    box.setPosition(position);
    image.setPosition(position.x - (texture.getSize().x - size.x) / 2, position.y - (texture.getSize().y - size.y) / 2);
}

void Thing::draw(sf::RenderWindow& window) {
    //window.draw(box);
    window.draw(image);
}

void Thing::initTextures(const std::string& fileName) {
    texture.loadFromFile(fileName);
    image.setTexture(texture);
}

bool Thing::checkCollision(const Thing& other) {
    sf::FloatRect playerBounds(position, size);
    sf::FloatRect otherBounds(other.getPosition(), other.getSize());

    return playerBounds.intersects(otherBounds);
}