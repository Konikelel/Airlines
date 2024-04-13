#include <algorithm>
#include <vector>

#include "Flight.hpp"
#include "Person.hpp"
#include "Plane.hpp"

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// RETURN ITERATOR OF FOUND ELEMENT OR VEC.END()
template <typename T>
typename std::vector<std::reference_wrapper<T>>::iterator findVector(std::vector<std::reference_wrapper<T>>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}

template <typename T>
typename std::vector<T>::iterator findVector(std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename T>
bool existVector(std::vector<std::reference_wrapper<T>>& vec, const T& target) {
    return findVector(vec, target) != vec.end();
}

template <typename T>
bool existVector(std::vector<T>& vec, const T& target) {
    return findVector(vec, target) != vec.end();
}

// RETURN ITERATOR OF POPPED ELEMENT OR VEC.END()
template <typename T>
typename std::vector<std::reference_wrapper<T>>::iterator popVector(std::vector<std::reference_wrapper<T>>& vec, const T& target) {
    typename std::vector<std::reference_wrapper<T>>::iterator targetElement = findVector<T>(vec, target);

    if (targetElement != vec.end())
        vec.erase(targetElement);

    return targetElement;
}

template <typename T>
typename std::vector<T>::iterator popVector(std::vector<T>& vec, const T& target) {
    typename std::vector<T>::iterator targetElement = findVector<T>(vec, target);

    if (targetElement != vec.end())
        vec.erase(targetElement);

    return targetElement;
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename T>
bool deleteVector(std::vector<std::reference_wrapper<T>>& vec, const T& target) {
    return popVector<T>(vec, target) != vec.end();
}

template <typename T>
bool deleteVector(std::vector<T>& vec, const T& target) {
    return popVector<T>(vec, target) != vec.end();
}
// COMPARISON OPERATOR
bool operator==(const Person& one, const Person& other);

bool operator==(const Flight& one, const Flight& other);

bool operator==(const Plane& one, const Plane& other);

#endif