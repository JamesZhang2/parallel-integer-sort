#include "sort.hpp"
#include "util.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

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
        vector<int> concurrent_merge = test;
        cheat_sort(cheat);
        radix_sort(radix);
        merge_sort(merge);
        int MAX_DEPTH = 3;
        concurrent_merge_sort(concurrent_merge, MAX_DEPTH);
        assert(cheat == radix);
        assert(cheat == merge);
        assert(cheat == concurrent_merge);
    }
    cout << "All tests passed!" << endl;
}

int main() { test_sort(); }
