#include <algorithm>
#include <vector>

#include "Flight.hpp"
#include "Person.hpp"
#include "Plane.hpp"

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// ADD ELEMENT TO THE END OF THE VECTOR
template <typename T>
T& addVector(std::vector<T>& vec, const T& target) {
    vec.push_back(target);
    return vec.back();
}

// RETURN ITERATOR OF FOUND ELEMENT OR VEC.END()
template <typename T>
typename std::vector<T>::const_iterator findVector(const std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}

template <typename T>
typename std::vector<T>::iterator findVector(std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}
// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename T>
bool existVector(const std::vector<T>& vec, const T& target) {
    return findVector<T>(vec, target) != vec.end();
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename T>
bool deleteVector(std::vector<T>& vec, const T& target) {
    auto targetElement = findVector<T>(vec, target);

    if (targetElement == vec.end())
        return false;

    vec.erase(targetElement);
    vec.shrink_to_fit();
    return true;
}

#endif