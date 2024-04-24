#include <random>
#include <vector>

#include "VectorHandler.hpp"

unsigned int generateId() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> int_dist(100000000, 999999999);

    return int_dist(rng);
}