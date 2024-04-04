#include <algorithm>
#include <vector>

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// RETURN ITERATOR OF FOUND ELEMENT OR VEC.END()
template <typename T>
typename std::vector<T>::iterator findVector(std::vector<T>& vec, const T& target) {
    return std::find(vec.begin(), vec.end(), target);  // ERROR WHEN TRYING WITH CONST
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename T>
bool existVector(const std::vector<T>& vec, const T& target) {
    return findVector(vec, target) != vec.end();
}

// RETURN ITERATOR OF POPPED ELEMENT OR VEC.END()
template <typename T>
typename std::vector<T>::iterator popVector(std::vector<T>& vec, const T& target) {
    typename std::vector<T>::iterator targetElement = findVector<T>(vec, target);

    if (targetElement != vec.end())
        vec.erase(targetElement);

    return targetElement;
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename T>
bool deleteVector(std::vector<T>& vec, const T& target) {
    return popVector<T>(vec, target) != vec.end();
}

#endif