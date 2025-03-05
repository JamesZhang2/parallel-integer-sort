#include "sort_serial.hpp"
#include "util.hpp"
#include <vector>

using namespace std;

/**
 * Read from stdin until end of file, sort numbers, then print to stdout
 */
int main() {
    vector<int> nums;
    int a;
    while (scanf("%d", &a) == 1) {
        nums.push_back(a);
    }
    radix_sort(nums);
    print_vector(nums);
}
