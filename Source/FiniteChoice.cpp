#include "../Headers/FiniteChoice.h"

#include <random>

std::array<std::vector<std::pair<float, float>>, 3> FiniteChoice::choices{};

FiniteChoice::FiniteChoice(const std::vector<std::pair<float, float>>& _choices, const std::string& fileName, int which) : Trap(1.f, fileName), hasCollided(std::array<bool, 2>{false, false}) {
    if (choices[which - 1].empty()) {
        choices[which - 1] = _choices;
    }
}

int FiniteChoice::getRandom(int Max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<int> gen(0, Max);
    return gen(eng);
}

bool FiniteChoice::getHasCollided(int index) const {
    return hasCollided[index];
}

void FiniteChoice::setHasCollided(int index, bool _val) {
    hasCollided[index] = _val;
}

std::pair<float, float> FiniteChoice::choose(int which) {
    if ((which - 1) * (which - 2) * (which - 3) != 0) {
        throw InvalidTrapType("No such trap type!\n");
    }

    int index;
    std::pair<float, float> chosen{};
    index = getRandom(int(choices[which - 1].size()) - 1);
    chosen = choices[which - 1][index];
    choices[which - 1].erase(choices[which - 1].begin() + index);
    return chosen;
}