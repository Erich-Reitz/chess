#include "add_sets.hpp"
#include <set>
#include <vector>

template <typename T>
void add_sets(std::vector<T> &result_set, const std::vector<T> &first_set, const std::vector<T> &second_set) {
    result_set.insert(result_set.end(), first_set.begin(), first_set.end());
    result_set.insert(result_set.end(), second_set.begin(), second_set.end());
}

template <typename T, typename... Sets>
void add_sets(std::vector<T> &result_set, const std::vector<T> &first_set, const Sets&... sets) {
    add_sets(result_set, sets...);
    result_set.insert(result_set.end(), first_set.begin(), first_set.end());
}




