#pragma once

#include <set>

template <typename T>
void add_sets(std::set<T> &result_set, const std::set<T> &first_set, const std::set<T> &second_set) ;

template <typename T, typename... Sets>
void add_sets(std::set<T> &result_set, const std::set<T> &first_set, const Sets &... sets) ;

