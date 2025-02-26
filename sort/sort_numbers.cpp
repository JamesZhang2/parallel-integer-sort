#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;

void print_vector(const vector<int> &nums) {
    for (int number : nums) {
        cout << number << endl;
    }
}

void cheat_sort(vector<int> &nums) { sort(nums.begin(), nums.end()); }

/**
 * In-place radix sort
 */
void radix_sort(vector<int> &numbers) {
    vector<int> nums = numbers; // copies numbers into nums
    for (int i = 0; i < 32; i++) {
        vector<int> vec0, vec1;
        for (int num : nums) {
            if ((num & (1 << i)) == 0) {
                vec0.push_back(num);
            } else {
                vec1.push_back(num);
            }
        }
        int idx = 0;
        if (i < 31) {
            // collect vec0, then vec1
            for (int num : vec0) {
                nums[idx++] = num;
            }
            for (int num : vec1) {
                nums[idx++] = num;
            }
        } else {
            // collect vec1, then vec0
            for (int num : vec1) {
                nums[idx++] = num;
            }
            for (int num : vec0) {
                nums[idx++] = num;
            }
        }
    }
    // copy back to numbers
    for (int i = 0; i < nums.size(); i++) {
        numbers[i] = nums[i];
    }
}

void merge_sort_aux(vector<int> &nums, vector<int> &buffer, int first,
                    int last) {
    // cout << first << ", " << last << endl;
    // assert(first <= last);
    if (first == last) { // don't do anything for singleton
        return;
    } else if (first + 1 == last) { // swap pairs if needed
        if (nums[first] > nums[last]) {
            buffer[first] = nums[first];
            nums[first] = nums[last];
            nums[last] = buffer[first];
        }
    } else { // sort two halves and merge
        int middle = (first + last) / 2;
        merge_sort_aux(nums, buffer, first, middle);
        merge_sort_aux(nums, buffer, middle + 1, last);
        int p1 = first;
        int p2 = middle + 1;
        int pb = first;
        while (p1 <= middle && p2 <= last) {
            if (nums[p1] < nums[p2]) {
                buffer[pb] = nums[p1];
                p1++;
            } else {
                buffer[pb] = nums[p2];
                p2++;
            }
            pb++;
        }
        // finish last cases
        if (p1 <= middle) {
            for (int i = p1; i <= middle; i++) {
                buffer[pb++] = nums[i];
            }
        }
        if (p2 <= last) {
            for (int i = p2; i <= last; i++) {
                buffer[pb++] = nums[i];
            }
        }

        // copy back to nums
        for (int i = first; i <= last; i++) {
            nums[i] = buffer[i];
        }
    }
}

void merge_sort(vector<int> &nums) {
    int n = nums.size();
    if (n == 0)
        return;
    vector<int> buffer(n);
    merge_sort_aux(nums, buffer, 0, n - 1);
}

void test_sort() {
    vector<int> vec0{4, 6, 2, 3, 9, 7, 10, 1};
    vector<int> dup{5, 1, 1, 5, 6, 4, 1, 9, 2, 2, 4};
    vector<int> empty{};
    vector<int> singleton{42};
    vector<int> pair{4, 32};
    vector<int> pair_same{-5, -5};
    vector<int> negs{-3, -6, -7, -2, -1, -9, -14, -25, -18, -8};
    vector<int> extremes{INT_MAX, INT_MIN, 0, 1, -1};
    vector<int> mixed{1,    6,   -2,    0,     9,  -23, 8, 12345,
                      -987, 275, 57923, 31415, -7, -23, 0};
    vector<vector<int>> tests{vec0,      dup,  empty,    singleton, pair,
                              pair_same, negs, extremes, mixed};
    for (vector<int> test : tests) {
        vector<int> cheat = test;
        vector<int> radix = test;
        vector<int> merge = test;
        cheat_sort(cheat);
        radix_sort(radix);
        merge_sort(merge);
        assert(cheat == radix);
        assert(cheat == merge);
    }
}

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
    // test_sort();
    radix_sort(nums);
    print_vector(nums);
}
