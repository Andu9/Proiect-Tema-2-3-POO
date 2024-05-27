#ifndef OOP_SAW_H
#define OOP_SAW_H

#include "FiniteChoice.h"

class Saw : public FiniteChoice {
    private:
        int signOnGround, signFly;
        bool onGround;
        std::pair<float, float> initialPosition;

    public:
        explicit Saw(const std::string& fileName);
        void spawn() override;
        void move(sf::RenderWindow& window) override;
        FiniteChoice* clone() const override;
};

#endif
