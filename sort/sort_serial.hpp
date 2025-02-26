#ifndef SORT_SERIAL_HPP
#define SORT_SERIAL_HPP
#include <vector>

/**
 * In-place sorting using algorithm package
 */
void cheat_sort(std::vector<int> &nums);

/**
 * In-place radix sort
 */
void radix_sort(std::vector<int> &numbers);

/**
 * In-place merge sort
 */
void merge_sort(std::vector<int> &nums);

#endif