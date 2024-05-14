#include "../Headers/Saw.h"

Saw::Saw() : MoveableThing(7.f), FiniteChoice(std::vector<std::pair<float, float>> {{800.f, 420.f}, {500.f, 420.f}}),
            signOnGround(-1), signFly(-1), onGround(true), hasCollided(false) {}

void Saw::spawn() {
    initialPosition = this->choose();

    position.x = initialPosition.first;
    position.y = initialPosition.second;

    size.x = 115.f;
    size.y = 57.f;

    box.setSize(size);

    box.setFillColor(sf::Color::Magenta);

    if (initialPosition.first == 130.f) {
        signOnGround = 1;
    } else {
        signOnGround = -1;
    }
}

void Saw::resetCoordinates() {
    position.x = initialPosition.first;
    position.y = initialPosition.second;
}

void Saw::move(sf::RenderWindow& window) {
    if (onGround == true) {
        position.x += float(signOnGround) * speed;

        if (position.x <= 0.f || int(position.x + size.x) >= int(window.getSize().x)) {
            signOnGround = -signOnGround;
            onGround = false;
        }
    } else {
        position.y += float(signFly) * speed;


        if (position.y <= 0) {
            signFly = -signFly;
        } else if (position.y + size.y >= window.getSize().y - 111.f) {
            signFly = -signFly;
            onGround = true;
        }
    }
}

bool Saw::getHasCollided() const { return hasCollided; }

void Saw::setHasCollided(bool collided) { hasCollided = collided; }