#ifndef OOP_FINITECHOICE_H
#define OOP_FINITECHOICE_H

#include <vector>
#include <utility>
#include <memory>

#include "Trap.h"

#include <utility>
#include <array>
#include "../Headers/Exceptions.h"

class FiniteChoice : public Trap {
    protected:
        std::array<bool, 2> hasCollided;
        static std::array<std::vector<std::pair<float, float>>, 3> choices;

        static int getRandom(int Max);

    public:

        virtual void spawn() = 0;
        virtual void move(sf::RenderWindow& window) = 0;

        void setHasCollided(int index, bool _hasCollided);
        bool getHasCollided(int index) const;

        static std::pair<float, float> choose(int which);
        explicit FiniteChoice(const std::vector<std::pair<float, float>>& _choices, const std::string& fileName, int which);
};

#endif


