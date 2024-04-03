#include <algorithm>
#include <vector>

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// RETURN ITERATOR OF FOUND ELEMENT OF VEC.END(), NEED OVERLOADED ==
template <typename T>
typename std::vector<T>::iterator findInVector(std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);  // ERROR WHEN TRYING WITH CONST
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR, NEED OVERLOADED ==
template <typename T>
bool existInVector(std::vector<T>& vec, const T& target) {
    return findInVector(vec, target) != vec.end();
}

// RETURN ITERATOR OF POPPED ELEMENT OF VEC.END(), NEED OVERLOADED ==
template <typename T>
typename std::vector<T>::iterator popFromVector(std::vector<T>& vec, const T& target) {
    auto targetElement = findInVector<T>(vec, target);

    if (targetElement == vec.end())
        return vec.end();

    return vec.erase(targetElement);
}

#endif