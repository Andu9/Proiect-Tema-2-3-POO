#include "Saw.h"

Saw::Saw() : FiniteChoice(std::vector<std::pair<float, float>> {{800.f, 400.f}, {500.f, 400.f}}) {}

void Saw::spawn() {
    initialPosition = this->choose();

    position.x = initialPosition.first;
    position.y = initialPosition.second;

    size.x = 115.f;
    size.y = 57.f;

    box.setSize(size);

    box.setFillColor(sf::Color::Magenta);

    if (initialPosition.first == 130.f) {
        sign = 1;
    } else {
        sign = -1;
    }

    speed = 7.f;
}

void Saw::move(sf::RenderWindow& window) {
    position.x += float(sign) * speed;

    if (position.x <= 0.f || int(position.x + size.x) >= int(window.getSize().x)) {
        sign = -sign;
        std::cout << "Coliziune\n";
    }
}