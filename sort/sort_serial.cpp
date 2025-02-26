#include "sort_serial.hpp"
#include "util.hpp"
#include <algorithm>
#include <vector>
using namespace std;

void cheat_sort(vector<int> &nums) { sort(nums.begin(), nums.end()); }

void radix_sort(vector<int> &nums) {
    for (int i = 0; i < 32; i++) {
        vector<int> vec0, vec1;
        // reserve changes the capacity (so we don't need to resize),
        // but it doesn't change the size of the vector
        vec0.reserve(nums.size());
        vec1.reserve(nums.size());
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
