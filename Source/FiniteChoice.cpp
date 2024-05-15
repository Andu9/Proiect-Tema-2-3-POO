#include "../Headers/FiniteChoice.h"

#include <random>

std::vector<std::pair<float, float>> FiniteChoice::choices1{};
std::vector<std::pair<float, float>> FiniteChoice::choices2{};

FiniteChoice::FiniteChoice(const std::vector<std::pair<float, float>>& _choices, const std::string& fileName, int which) : Trap(1.f, fileName) {
    if (which == 1 && choices1.size() == 0) {
        choices1 = _choices;
    } else if (which == 2 && choices2.size() == 0) {
        choices2 = _choices;
    }
}

int FiniteChoice::getRandom(int Max) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> gen(0, Max);
    return gen(eng);
}

std::pair<float, float> FiniteChoice::choose(int which) {
    int index = 0;
    std::pair<float, float> chosen{};
    if (which == 1) {
        index = getRandom(int(choices1.size()));
        chosen = choices1[index];
        choices1.erase(choices1.begin() + index);
    } else {
        index = getRandom(int(choices2.size()));
        chosen = choices2[index];
        choices2.erase(choices2.begin() + index);
    }
    return chosen;
}