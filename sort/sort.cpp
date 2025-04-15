#include "sort.hpp"
#include "util.hpp"
#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void cheat_sort(vector<int> &nums) { sort(nums.begin(), nums.end()); }

void radix_sort(vector<int> &nums) {
    vector<int> vec0, vec1;
    vec0.resize(nums.size());
    vec1.resize(nums.size());

    for (int i = 0; i < 32; i++) {
        int p0 = 0;
        int p1 = 0;
        for (int num : nums) {
            if ((num & (1 << i)) == 0) {
                vec0[p0++] = num;
            } else {
                vec1[p1++] = num;
            }
        }
        int idx = 0;
        if (i < 31) {
            // collect vec0, then vec1
            for (int j = 0; j < p0; j++) {
                nums[idx++] = vec0[j];
            }
            for (int j = 0; j < p1; j++) {
                nums[idx++] = vec1[j];
            }
        } else {
            // collect vec1, then vec0
            for (int j = 0; j < p1; j++) {
                nums[idx++] = vec1[j];
            }
            for (int j = 0; j < p0; j++) {
                nums[idx++] = vec0[j];
            }
        }
    }
}

void concurrent_merge_sort_aux(vector<int> &nums, vector<int> &buffer,
                               int first, int last, int cur_depth) {
    bool fork = cur_depth > 0; // whether to fork into two threads
    if (first == last) {
        // don't do anything for singleton
        return;
    } else if (first + 1 == last) { // swap pairs if needed
        if (nums[first] > nums[last]) {
            buffer[first] = nums[first];
            nums[first] = nums[last];
            nums[last] = buffer[first];
        }
    } else { // sort two halves and merge
        int middle = (first + last) / 2;
        if (fork) {
            std::thread t1(concurrent_merge_sort_aux, std::ref(nums),
                           std::ref(buffer), first, middle, cur_depth - 1);
            std::thread t2(concurrent_merge_sort_aux, std::ref(nums),
                           std::ref(buffer), middle + 1, last, cur_depth - 1);
            t1.join();
            t2.join();
        } else {
            concurrent_merge_sort_aux(nums, buffer, first, middle, 0);
            concurrent_merge_sort_aux(nums, buffer, middle + 1, last, 0);
        }
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

void concurrent_merge_sort(vector<int> &nums, int max_depth) {
    int n = nums.size();
    if (n == 0)
        return;
    vector<int> buffer(n);
    concurrent_merge_sort_aux(nums, buffer, 0, n - 1, max_depth);
}

void merge_sort(vector<int> &nums) { concurrent_merge_sort(nums, 0); }
