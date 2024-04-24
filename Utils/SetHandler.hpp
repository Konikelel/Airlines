#include <algorithm>
#include <set>

#ifndef SET_HANDLER_H
#define SET_HANDLER_H

// ADD ELEMENT TO THE END OF THE VECTOR
template <typename T>
bool addSet(std::set<std::reference_wrapper<T>>& set, T& target) {
    return set.insert(target).second;
}

// RETURN ITERATOR OF FOUND ELEMENT OR SET.END()
template <typename T>
typename std::set<std::reference_wrapper<T>>::const_iterator findSet(const std::set<std::reference_wrapper<T>>& set, const T& target) {
    return std::find(set.begin(), set.end(), target);
}

template <typename T>
typename std::set<std::reference_wrapper<T>>::iterator findSet(std::set<std::reference_wrapper<T>>& set, const T& target) {
    return std::find(set.begin(), set.end(), target);
}

// RETURN BOOL IF ELEMENT EXIST IN VECTOR
template <typename T>
bool existSet(const std::set<std::reference_wrapper<T>>& set, const T& target) {
    return findSet<T>(set, target) != set.end();
}

// RETURN BOOL IF ELEMENT WAS DELETED
template <typename T>
bool deleteSet(std::set<std::reference_wrapper<T>>& set, const T& target) {
    auto targetElement = findSet<T>(set, target);

    if (targetElement == set.end())
        return false;

    set.erase(targetElement);
    return true;
}

#endif