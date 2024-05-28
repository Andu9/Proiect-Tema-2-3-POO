#include "../Headers/SpikeyBall.h"

SpikeyBall::SpikeyBall(const std::string& fileName) : FiniteChoice(std::vector<std::pair<float, float>> {{505.f, 37.f}, {228.f, 37.f}, {760.f, 37.f}}, fileName, 2),
                                                      signVertical(1.f), signHorizontal(1.f) {}

void SpikeyBall::spawn() {
    initialPosition = this->choose(2);

    position.x = initialPosition.first;
    position.y = initialPosition.second;

    size.x = 47.f;
    size.y = 43.f;

    box.setSize(size);

    box.setFillColor(sf::Color::Green);

    if (initialPosition.first == 760.f) {
        signHorizontal = -signHorizontal;
    }
}

void SpikeyBall::move(sf::RenderWindow& window) {
    if (initialPosition.first != 505.f) {
        position.x += float(signHorizontal) * speed;

        if (position.x <= 0 || position.x + size.x >= static_cast<float>(window.getSize().x)) {
            signHorizontal = -signHorizontal;
        }
    }

    position.y += float(signVertical) * speed;

    if (position.y <= 0 || position.y + size.y >= static_cast<float>(window.getSize().y) - 111.f) {
        signVertical = -signVertical;
    }
}

std::shared_ptr<FiniteChoice> SpikeyBall::clone() const {
    return std::make_shared<SpikeyBall>(*this);
}
