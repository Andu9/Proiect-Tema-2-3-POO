#include "../Headers/MoveableThing.h"

MoveableThing::MoveableThing(const std::string& fileName) : Thing(fileName), speed(5.f) {}

MoveableThing::MoveableThing(float _speed, const std::string& fileName) : Thing(fileName), speed(_speed) {}

MoveableThing::MoveableThing(sf::Vector2f _size, sf::Vector2f _position, float _speed = 0, const std::string& fileName = "") :
                            Thing(_size, _position, fileName), speed(_speed) {}

