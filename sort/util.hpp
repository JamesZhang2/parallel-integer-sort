#ifndef UTIL_HPP
#define UTIL_HPP
#include <string>
#include <vector>

/**
 * Prints the vector to stdout, where the elements are separated by the given
 * delimiter. Prints a newline after printing the last element.
 */
void print_vector(const std::vector<int> &nums, std::string delimiter);

/**
 * Prints the vector to stdout, where each element is printed on a new line.
 * Prints a newline after printing the last element.
 */
void print_vector(const std::vector<int> &nums);

#endif
