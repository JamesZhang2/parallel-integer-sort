#include "sort.hpp"
#include "util.hpp"
#include <iostream>
#include <vector>

using namespace std;

/**
 * Read from stdin until end of file, sort numbers, then print to stdout
 */
int main(int argc, char *argv[]) {
    vector<int> nums;
    int a;
    while (scanf("%d", &a) == 1) {
        nums.push_back(a);
    }
    int MAX_DEPTH = 5;
    if (argc == 1) {
        // Default
        concurrent_merge_sort(nums, MAX_DEPTH);
        // merge_sort(nums);
    } else if (argc >= 2) {
        string method = argv[1];
        if (method == "serial_radix") {
            radix_sort(nums);
        } else if (method == "serial_merge") {
            merge_sort(nums);
        } else if (method == "concurrent_merge") {
            if (argc >= 3) {
                MAX_DEPTH = atoi(argv[2]);
            }
            concurrent_merge_sort(nums, MAX_DEPTH);
        } else if (method == "cheat") {
            cheat_sort(nums);
        } else {
            cerr << "Unknown sorting method " << method << endl;
            return 1;
        }
    } else {
        cerr << "Incorrect number of arguments" << endl;
        return 1;
    }

    print_vector(nums);
}
