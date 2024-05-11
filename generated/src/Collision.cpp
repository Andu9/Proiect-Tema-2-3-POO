#include "Collision.h"
#include <cmath>

Collision::Collision(sf::RectangleShape& _shape) : shape(_shape) {}

sf::Vector2f Collision::GetPosition() { return shape.getPosition(); }

sf::Vector2f Collision::GetHalfSize() { return shape.getSize() / 2.f; }

bool Collision::detectCollision(Collision other, float push) {
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.f || intersectY < 0.f) {
        push = std::min(std::max(push, 0.f), 1.f);

        if (intersectX > intersectY) {
            if (deltaX < 0.f) {
                shape.move(intersectX * (1.f - push), 0.f);
                other.shape.move(-intersectX * push, 0.f);
            } else {
                shape.move(-intersectX * (1.f - push), 0.f);
                other.shape.move(intersectX * push, 0.f);
            }
        } else {
            if (deltaY < 0.f) {
                shape.move(0.f, intersectY * (1.f - push));
                other.shape.move(0.f, -intersectY * push);
            } else {
                shape.move(0.f, -intersectY * (1.f - push));
                other.shape.move(0.f, intersectY * push);
            }
        }

        return true;
    }

    return false;
}