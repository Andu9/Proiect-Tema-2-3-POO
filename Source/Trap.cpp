#include "../Headers/Trap.h"

Trap::Trap(float _damage, const std::string& fileName) : MoveableThing(fileName), timer(), damage(_damage) {}

float Trap::getDamage() const { return damage; }

