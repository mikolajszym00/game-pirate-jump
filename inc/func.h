#ifndef PIRATE_JUMP_FUNC_H
#define PIRATE_JUMP_FUNC_H

#include <utility>
#include <random>
#include <chrono>

#include <iostream>

inline bool intersect(std::pair<int, int> p1, std::pair<int, int> p2) {
    if (p1.first > p2.second || p2.first > p1.second) {
        return false;
    }

    return true;
}

inline bool generate_true_with_prob(double prob) {
    if (prob == 1) {
        return true;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::bernoulli_distribution distribution(prob);

    int v = distribution(generator);

    return v;
}

inline int generate_int_from_interval(const std::pair<int, int> &range) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::uniform_int_distribution<int> distribution(range.first, range.second);

    return distribution(generator);
}

#endif //PIRATE_JUMP_FUNC_H
