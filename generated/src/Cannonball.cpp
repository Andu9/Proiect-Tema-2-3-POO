#include "Cannonball.h"

CannonBall::CannonBall() : FiniteChoice(std::vector<std::pair<float, float>> {{91.f, 376.f},
                                                                              {91.f, 256.f},
                                                                              {91.f, 136.f},
                                                                              {951.f, 376.f},
                                                                              {951.f, 256.f},
                                                                              {951.f, 136.f}}) {}


void CannonBall::spawn() {
    initialPosition = this->choose();

    position.x = initialPosition.first;
    position.y = initialPosition.second;

    if (initialPosition.first == 91.f) {
        sign = 1;
    } else {
        sign = -1;
    }

    size.x = 40.f;
    size.y = 40.f;

    box.setSize(size);

    speed = 5.f;
}

void CannonBall::resetCoordinates() {
    position.x = initialPosition.first;
}

void CannonBall::move(sf::RenderWindow& window) {
    position.x += sign * speed;
    if (position.x <= 0 || position.x >= window.getSize().x) {
        this->resetCoordinates();
    }
}

