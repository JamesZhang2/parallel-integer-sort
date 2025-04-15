#include "sort.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void cheat_sort(vector<int> &nums) { sort(nums.begin(), nums.end()); }

/**
 * Looks at the numbers in nums in the range [start, end),
 * puts the numbers whose bth least-significant bit is 0 into bucket0
 * and the numbers whose bth least-significant bit is 1 into bucket1
 */
void radix_sort_helper(const vector<int> &nums, int start, int end,
                       vector<int> &bucket0, vector<int> &bucket1, int b) {
    bucket0.resize(end - start);
    bucket1.resize(end - start);
    int p0 = 0;
    int p1 = 0;
    for (int i = start; i < end; i++) {
        if ((nums[i] & (1 << i)) == 0) {
            bucket0[p0++] = nums[i];
        } else {
            bucket1[p1++] = nums[i];
        }
    }
}

void concurrent_radix_sort(vector<int> &nums, int num_threads) {
    int size = nums.size();
    int length_per_thread = nums.size() / num_threads;

    for (int b = 0; b < 32; b++) {
        vector<std::thread> threads;
        vector<vector<int>> buckets_0(num_threads, vector<int>());
        vector<vector<int>> buckets_1(num_threads, vector<int>());
        for (int t = 0; t < num_threads; t++) {
            int start = t * length_per_thread;
            int end = t == num_threads - 1 ? nums.size()
                                           : (t + 1) * length_per_thread;
            threads.emplace_back(radix_sort_helper, ref(nums), start, end,
                                 ref(buckets_0[t]), ref(buckets_1[t]), t);
        }
        for (int t = 0; t < num_threads; t++) {
            threads[t].join();
        }

        if (b < 31) {
            // collect 0 buckets, then 1 buckets
            int cur = 0;
            for (int t = 0; t < num_threads; t++) {
                copy(buckets_0[t].begin(), buckets_0[t].end(),
                     nums.begin() + cur);
                cur += buckets_0[t].size();
            }
            for (int t = 0; t < num_threads; t++) {
                copy(buckets_1[t].begin(), buckets_1[t].end(),
                     nums.begin() + cur);
                cur += buckets_1[t].size();
            }
            assert(cur == size);
        } else {
            // collect 1 buckets, then 0 buckets
            int cur = 0;
            for (int t = 0; t < num_threads; t++) {
                copy(buckets_1[t].begin(), buckets_1[t].end(),
                     nums.begin() + cur);
                cur += buckets_1[t].size();
            }
            for (int t = 0; t < num_threads; t++) {
                copy(buckets_0[t].begin(), buckets_0[t].end(),
                     nums.begin() + cur);
                cur += buckets_0[t].size();
            }
            assert(cur == size);
        }
    }
}

void radix_sort(vector<int> &nums) { concurrent_radix_sort(nums, 1); }

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
