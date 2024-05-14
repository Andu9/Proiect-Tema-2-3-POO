#include "../Headers/Cannonball.h"

CannonBall::CannonBall(const std::string& fileName) : FiniteChoice(std::vector<std::pair<float, float>> {{91.f, 376.f},
                                                                                                                {91.f, 256.f},
                                                                                                                {91.f, 136.f},
                                                                                                                {951.f, 376.f},
                                                                                                                {951.f, 256.f},
                                                                                                                {951.f, 136.f}}, fileName), sign(-1) {
}


void CannonBall::spawn() {
    initialPosition = this->choose();

    if (initialPosition.first == 91.f) {
        textureCannon.loadFromFile("./CannonLeft.png");
        cannon.setTexture(textureCannon);
        cannon.setPosition(initialPosition.first, initialPosition.second);
    } else {
        textureCannon.loadFromFile("./CannonRight.png");
        cannon.setTexture(textureCannon);
        cannon.setPosition(initialPosition.first, initialPosition.second);
    }

    position.x = initialPosition.first;
    position.y = initialPosition.second;

    cannon.setPosition(position.x, position.y);

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
    window.draw(cannon);
    position.x += sign * speed;
    if (position.x <= 0 || position.x >= window.getSize().x) {
        this->resetCoordinates();
    }
}

