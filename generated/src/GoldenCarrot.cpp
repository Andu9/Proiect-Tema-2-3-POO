#include "GoldenCarrot.h"

GoldenCarrot::GoldenCarrot(sf::RenderWindow& window) : Carrot(window, 3), timer(), appears(false) {
    box.setFillColor(sf::Color::Yellow);
}

void GoldenCarrot::draw(sf::RenderWindow& window) {
    if (appears) {
        this->Thing::draw(window);
    } else {
        position.x = -100.f;
        position.y = -100.f;
    }

    if (timer.getElapsedTime().asSeconds() >= 5.f) {
        appears = true, timer.restart();
        this->resetCoordinates(window);
    } else if (timer.getElapsedTime().asSeconds() >= 3.f and appears) {
        appears = false, timer.restart();
    }
}

void GoldenCarrot::isTaken() { timer.restart(), appears = false; }
