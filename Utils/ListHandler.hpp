#include <algorithm>
#include <list>

#include "Flight.hpp"
#include "Person.hpp"
#include "Plane.hpp"

#ifndef LIST_HANDLER_H
#define LIST_HANDLER_H

// ADD ELEMENT TO THE END OF THE VECTOR
template <typename T>
T& addList(std::list<T>& list, const T& target) {
    list.push_back(target);
    return list.back();
}
// RETURN ITERATOR OF FOUND ELEMENT OR VEC.END()
template <typename T>
typename std::list<T>::iterator findList(std::list<T>& list, const T& target) {
    return std::find(list.begin(), list.end(), target);
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename T>
bool existList(std::list<T>& list, const T& target) {
    return findList<T>(list, target) != list.end();
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename T>
bool deleteList(std::list<T>& list, const T& target) {
    auto targetElement = findList<T>(list, target);

    if (targetElement == list.end())
        return false;

    list.erase(targetElement);
    return true;
}

#endif