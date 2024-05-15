#include "../Headers/Cannonball.h"

CannonBall::CannonBall(const std::string& fileName) : FiniteChoice(std::vector<std::pair<float, float>> {{40.f, 376.f},
                                                                                                                {40.f, 256.f},
                                                                                                                {40.f, 136.f},
                                                                                                                {904.f, 376.f},
                                                                                                                {904.f, 256.f},
                                                                                                                {904.f, 136.f}}, fileName, 1), sign(-1) {}


void CannonBall::spawn() {
    initialPosition = this->choose(1);


    if (initialPosition.first == 40.f) {
        textureCannon.loadFromFile("./CannonLeft.png");
        cannon.setTexture(textureCannon);
    } else {
        textureCannon.loadFromFile("./CannonRight.png");
        cannon.setTexture(textureCannon);
    }

    position.x = initialPosition.first;
    position.y = initialPosition.second;

    cannon.setPosition(position.x, position.y);

    if (position.x == 40.f) {
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

