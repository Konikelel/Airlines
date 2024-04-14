#include <algorithm>
#include <list>

#include "Flight.hpp"
#include "Person.hpp"
#include "Plane.hpp"

#ifndef LIST_HANDLER_H
#define LIST_HANDLER_H

// RETURN ITERATOR OF FOUND ELEMENT OR VEC.END()
template <typename T>
typename std::list<T>::iterator findList(std::list<T>& list, const T& target) {
    return std::find(list.begin(), list.end(), target);
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename T>
bool existList(std::list<T>& list, const T& target) {
    return findList(list, target) != list.end();
}

// RETURN ITERATOR OF POPPED ELEMENT OR VEC.END()
template <typename T>
typename std::list<T>::iterator popList(std::list<T>& list, const T& target) {
    typename std::list<T>::iterator targetElement = findList<T>(list, target);

    if (targetElement != list.end())
        list.erase(targetElement);

    return targetElement;
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename T>
bool deleteList(std::list<T>& list, const T& target) {
    return popList<T>(list, target) != list.end();
}

#endif