#include "VectorHandler.h"

#include <algorithm>
#include <vector>

template <typename T>
typename std::vector<T>::iterator FindInVector(std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}

template <typename T>
typename std::vector<T>::iterator PopFromVector(std::vector<T>& vec, const T& target) {
    auto targetElement = FindInVector<T>(vec, target);

    if (targetElement == vec.end())
        return vec.end();

    return vec.erase(targetElement);
}