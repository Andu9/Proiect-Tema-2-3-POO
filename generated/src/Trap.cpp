#include "Trap.h"

Trap::Trap(float _damage) : damage(_damage), timer() {}

float Trap::getDamage() const { return damage; }

