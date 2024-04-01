#include <algorithm>
#include <vector>

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// RETURN ITERATOR OF FOUND ELEMENT OF VEC.END(), NEED OVERLOADED ==
template <typename T>
typename std::vector<T>::iterator FindInVector(std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}

// RETURN ITERATOR OF POPPED ELEMENT OF VEC.END(), NEED OVERLOADED ==
template <typename T>
typename std::vector<T>::iterator PopFromVector(std::vector<T>& vec, const T& target) {
    auto targetElement = FindInVector<T>(vec, target);

    if (targetElement == vec.end())
        return vec.end();

    return vec.erase(targetElement);
}

#endif