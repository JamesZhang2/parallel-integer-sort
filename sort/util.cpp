#include <iostream>
#include <string>
#include <vector>
using namespace std;

void print_vector(const vector<int> &nums, const string &delimiter) {
    if (nums.size() == 0) {
        return;
    }
    for (int i = 0; i < nums.size() - 1; i++) {
        cout << nums[i] << delimiter;
    }
    cout << nums[nums.size() - 1] << endl;
}

void print_vector(const vector<int> &nums) {
    for (int number : nums) {
        cout << number << endl;
    }
}
