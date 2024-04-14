#include <vector>

#include "Person.hpp"
#include "VectorHandler.hpp"

int main() {
    std::vector<int> example = {1, 2, 3, 4};

    auto vecEnd = example.end();

    auto result1 = findVector(example, 2);
    bool result2 = existVector(example, 2);
    vecEnd = example.end();

    auto result4 = deleteVector(example, 2);
    vecEnd = example.end();
    result2 = existVector(example, 2);
    result2 = existVector(example, 4);

    return 0;
}