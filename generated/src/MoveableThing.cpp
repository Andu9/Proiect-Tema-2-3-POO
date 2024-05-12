#include "MoveableThing.h"

MoveableThing::MoveableThing() : speed(8.f) {}

MoveableThing::MoveableThing(float _speed) : speed(_speed) {}

MoveableThing::MoveableThing(sf::Vector2f _size, sf::Vector2f _position, float _speed = 0) :
                            Thing(_size, _position), speed(_speed) {}

