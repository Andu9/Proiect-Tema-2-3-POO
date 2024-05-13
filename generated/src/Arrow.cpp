#include "Arrow.h"
#include <random>

const float Arrow::gravity = 0.3f;

float Arrow::getRandom(float Min, float Max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    static std::uniform_real_distribution<float> gen(Min, Max);
    return gen(eng);
}

Arrow::Arrow(sf::RenderWindow& window) : Trap(0.5f), verticalSpeed(0) {
    size.x = 35.f, size.y = 85.f;
    box.setSize(size);
    position.y = -size.y;
    position.x = getRandom(0, window.getSize().x - size.x);
    box.setFillColor(sf::Color::Cyan);
}

void Arrow::resetCoordinates(sf::RenderWindow& window) {
    verticalSpeed = 0.f;
    position.x = getRandom(0, window.getSize().x - size.x);
    position.y = -size.y;
}

void Arrow::move(sf::RenderWindow& window) {
    verticalSpeed += gravity;
    position.y += verticalSpeed;


    if (position.y >= window.getSize().y) {
        this->resetCoordinates(window);
    }
}

