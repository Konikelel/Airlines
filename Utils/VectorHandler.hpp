#include <algorithm>
#include <vector>

#include "Flight.hpp"
#include "Person.hpp"
#include "Plane.hpp"

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// ADD ELEMENT TO THE END OF THE VECTOR
template <typename VecType, typename T>
T& addVector(std::vector<VecType>& vec, T& target) {
    vec.push_back(target);
    return vec.back();
}

// RETURN ITERATOR OF FOUND ELEMENT OR VEC.END()
template <typename VecType, typename T>
typename std::vector<VecType>::iterator findVector(std::vector<VecType>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename VecType, typename T>
bool existVector(std::vector<VecType>& vec, const T& target) {
    return findVector<VecType, T>(vec, target) != vec.end();
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename VecType, typename T>
bool deleteVector(std::vector<VecType>& vec, const T& target) {
    auto targetElement = findVector<VecType, T>(vec, target);

    if (targetElement == vec.end())
        return false;

    vec.erase(targetElement);
    vec.shrink_to_fit();
    return true;
}

// COMPARISON OPERATOR
bool operator==(const Person& one, const Person& other);

bool operator==(const Flight& one, const Flight& other);

bool operator==(const Plane& one, const Plane& other);

#endif