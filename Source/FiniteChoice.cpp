#include "../Headers/FiniteChoice.h"

#include <random>

std::vector<std::pair<float, float>> FiniteChoice::choices1{};
std::vector<std::pair<float, float>> FiniteChoice::choices2{};
std::vector<std::pair<float, float>> FiniteChoice::choices3{};

FiniteChoice::FiniteChoice(const std::vector<std::pair<float, float>>& _choices, const std::string& fileName, int which) : Trap(1.f, fileName), hasCollided(false) {
    if (which == 1 && choices1.empty()) {
        choices1 = _choices;
    } else if (which == 2 && choices2.empty()) {
        choices2 = _choices;
    } else if (which == 3 && choices3.empty()) {
        choices3 = _choices;
    }
}

bool FiniteChoice::getHasCollided() const { return hasCollided; }

void FiniteChoice::setHasCollided(bool _hasCollided) { hasCollided = _hasCollided; }

int FiniteChoice::getRandom(int Max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<int> gen(0, Max);
    return gen(eng);
}

std::pair<float, float> FiniteChoice::choose(int which) {
    int index = 0;
    std::pair<float, float> chosen{};
    if (which == 1) {
        index = getRandom(int(choices1.size()) - 1);
        chosen = choices1[index];
        choices1.erase(choices1.begin() + index);
    } else if (which == 2) {
        index = getRandom(int(choices2.size()) - 1);
        chosen = choices2[index];
        choices2.erase(choices2.begin() + index);
    } else {
        index = getRandom(int(choices3.size()) - 1);
        chosen = choices3[index];
        choices3.erase(choices3.begin() + index);
    }
    return chosen;
}