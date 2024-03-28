#include <vector>

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// RETURN ITERATOR OF FOUND ELEMENT OF VEC.END(), NEED OVERLOADED ==
template <typename T>
typename std::vector<T>::iterator FindInVector(std::vector<T>& vec, const T& target);

// RETURN ITERATOR OF POPPED ELEMENT OF VEC.END(), NEED OVERLOADED ==
template <typename T>
typename std::vector<T>::iterator PopFromVector(std::vector<T>& vec, const T& target);

#endif