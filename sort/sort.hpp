#ifndef SORT_HPP
#define SORT_HPP
#include <vector>

/**
 * In-place sorting using algorithm package
 */
void cheat_sort(std::vector<int> &nums);

/**
 * In-place radix sort
 */
void radix_sort(std::vector<int> &nums);

/**
 * In-place merge sort
 */
void merge_sort(std::vector<int> &nums);

/**
 * Concurrent merge sort
 */
void concurrent_merge_sort(std::vector<int> &nums, int max_depth);

#endif