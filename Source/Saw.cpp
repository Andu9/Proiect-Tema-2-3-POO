#include "../Headers/Saw.h"

Saw::Saw() : FiniteChoice(std::vector<std::pair<float, float>> {{800.f, 420.f}, {500.f, 420.f}}),
             onGround(true), signFly(-1) {}

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

    speed = 7.f;
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

/*
    position.x += float(sign) * speed;

    if (position.x <= 0.f || int(position.x + size.x) >= int(window.getSize().x)) {
        sign = -sign;

    }*/
}