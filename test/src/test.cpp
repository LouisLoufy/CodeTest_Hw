#include "dbg.h"

#include <iostream>
#include <string>
#include <thread>

void const_pointer_vs_pointer_to_const() {
    int x = 0;
    int y = 0;

    const int *ptr1 = &x;
    int const *ptr2 = &x;
    int *const ptr3 = &x;
}

int main() {

    return 0;
}

// #include <vector>
// #include "dbg.h"

// class Solution {
// public:
//     void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
//         std::vector<int> nums;
//         std::vector<int> nums1_new(nums1.begin(), nums1.begin() + m);
//         dbg(nums, nums1_new);

//         for (int i = 0; i < nums1.size(); i++) {
//             if (nums1_new.empty()) {
//                 nums.insert(nums.end(), nums2.begin(), nums2.end());
//                 dbg(nums, nums1_new);
//                 break;
//             } else if (nums2.empty()) {
//                 nums.insert(nums.end(), nums1_new.begin(), nums1_new.end());
//                 dbg(nums, nums1_new);
//                 break;
//             }

//             if (nums1_new[0] < nums2[0]) {
//                 nums.push_back(nums1_new[0]);
//                 nums1_new.erase(nums1_new.begin());
//                 dbg(nums, nums1_new);
//             } else {
//                 nums.push_back(nums2[0]);
//                 nums2.erase(nums2.begin());
//                 dbg(nums, nums1_new);
//             }
//         }

//         nums1 = nums;
//     }
// };

// int main() {
//     Solution solution;

//     std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
//     int m = 3;
//     std::vector<int> nums2 = {2, 5, 6, 0, 0, 0};
//     int n = 3;

//     solution.merge(nums1, m, nums2, n);

//     for (int num : nums1) {
//         std::cout << num << " ";
//     }

//     std::cout << std::endl;

//     return 0;
// }