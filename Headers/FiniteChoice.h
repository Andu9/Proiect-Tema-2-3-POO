#ifndef OOP_FINITECHOICE_H
#define OOP_FINITECHOICE_H

#include <vector>
#include <utility>

#include "Trap.h"

#include <utility>

class FiniteChoice : public Trap {
    protected:
        static std::vector<std::pair<float, float>> choices;

        static int getRandom(int Max);

    public:
        std::pair<float, float> choose();
        bool checkEmpty();
        explicit FiniteChoice(const std::vector<std::pair<float, float>>& _choices, const std::string& fileName);
};

#endif


