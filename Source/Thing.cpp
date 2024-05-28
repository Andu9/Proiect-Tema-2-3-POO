#include "../Headers/Thing.h"

Thing::Thing(const std::string& fileName) : size{50, 50}, position{10, 10}, texture(), image() {
    if (!texture.loadFromFile(fileName)) {
        throw MissingTexture("Texture wasn't found!\n");
    }
    image.setTexture(texture);

    box.setSize(size);
    box.setFillColor(sf::Color::White);
}

Thing::Thing(sf::Vector2f _size, sf::Vector2f _position, const std::string& fileName) : size(_size), position(_position),
         texture(), image() {

    if (!texture.loadFromFile(fileName)) {
        throw MissingTexture("Texture wasn't found!\n");
    }
    image.setTexture(texture);

    box.setSize(size);
}

sf::Vector2f Thing::getSize() const { return size; }

sf::Vector2f Thing::getPosition() const { return position; }

void Thing::setPosition() {
    box.setPosition(position);
    image.setPosition(position.x - (static_cast<float>(texture.getSize().x) - size.x) / 2, position.y - (static_cast<float>(texture.getSize().y) - size.y) / 2);
}

void Thing::draw(sf::RenderWindow& window) {
    window.draw(image);
}

void Thing::initTextures(const std::string& fileName) {
    if (!texture.loadFromFile(fileName)) {
        throw MissingTexture("Texture wasn't found!\n");
    }
    image.setTexture(texture);
}
