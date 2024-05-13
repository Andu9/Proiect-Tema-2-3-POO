#include "Trap.h"

Trap::Trap(float _damage) : timer(), damage(_damage) {}

float Trap::getDamage() const { return damage; }

