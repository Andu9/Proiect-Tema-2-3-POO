#ifndef OOP_MOVEABLETHING_H
#define OOP_MOVEABLETHING_H

#include "Thing.h"

class MoveableThing : public Thing {
    protected:
        float speed{};

    public:
        MoveableThing() = default;
        explicit MoveableThing(const std::string& fileName);
};

#endif
