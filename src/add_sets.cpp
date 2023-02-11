#include "add_sets.hpp"
#include <set>

template <typename T>
void add_sets(std::set<T> &result_set, const std::set<T> &first_set, const std::set<T> &second_set) {
    result_set.insert(first_set.begin(), first_set.end());
    result_set.insert(second_set.begin(), second_set.end());
}

template <typename T, typename... Sets>
void add_sets(std::set<T> &result_set, const std::set<T> &first_set, const Sets&... sets) {
    add_sets(result_set, sets...);
    result_set.insert(first_set.begin(), first_set.end());
}

