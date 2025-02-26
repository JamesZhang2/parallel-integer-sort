#include "sort_serial.hpp"
#include "util.hpp"
#include <iostream>
#include <vector>

using namespace std;

/**
 * Read from stdin until end of file, sort numbers, then print to stdout
 */
int main() {
    vector<int> nums;
    while (true) {
        int a;
        cin >> a;
        if (cin.eof()) {
            break;
        }
        nums.push_back(a);
    }
    radix_sort(nums);
    print_vector(nums);
}
