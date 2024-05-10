#include "MoveableThing.h"

MoveableThing::MoveableThing() : speed(0) {}

MoveableThing::MoveableThing(float _speed) : speed(_speed) {}

MoveableThing::MoveableThing(sf::Vector2f _size, sf::Vector2f _position, float _speed = 0) :
                            Thing(_size, _position), speed(_speed) {}

void MoveableThing::moveHorizontal(float sign) { position.x += sign * speed; }