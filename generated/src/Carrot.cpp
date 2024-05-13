#include "Carrot.h"

float Carrot::getRandom(float Min, float Max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_real_distribution<float> gen(Min, Max);
    return gen(eng);
}

Carrot::Carrot(sf::RenderWindow& window, int _score) : score(_score) {
    size = sf::Vector2f(63.f, 61.f);
    box.setSize(size);
    position.x = getRandom(0, window.getSize().x - size.x);
    position.y = getRandom(0, window.getSize().y - 111 - size.y);
    box.setFillColor(sf::Color(255, 165, 0));
}

void Carrot::resetCoordinates(sf::RenderWindow& window) {
    position.x = getRandom(0, window.getSize().x - size.x);
    position.y = getRandom(0, window.getSize().y - 111 - size.y);
}

int Carrot::getScore() const { return score; }