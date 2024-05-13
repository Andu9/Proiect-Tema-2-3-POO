#include "FiniteChoice.h"

#include <random>

FiniteChoice::FiniteChoice(std::vector<std::pair<float, float>> _choices) : Trap(1.f), choices(_choices) {}

int FiniteChoice::getRandom(int Max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    static std::uniform_int_distribution<int> gen(0, Max);
    return gen(eng);
}

bool FiniteChoice::checkEmpty() { return choices.empty(); }

std::pair<float, float> FiniteChoice::choose() {
    int index = getRandom(int(choices.size() - 1));
    std::pair<float, float> chosen = choices[index];
    choices.erase(choices.begin() + index);
    return chosen;
}