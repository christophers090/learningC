Binary Search
You are given an array of distinct integers nums, sorted in ascending order, and an integer target.

Implement a function to search for target within nums. If it exists, then return its index, otherwise, return -1.

Your solution must run in 
O
(
l
o
g
n
)
O(logn) time.

Example 1:

Input: nums = [-1,0,2,4,6,8], target = 4

Output: 3
Example 2:

Input: nums = [-1,0,2,4,6,8], target = 3

Output: -1
Constraints:

1 <= nums.length <= 10000.
-10000 < nums[i], target < 10000


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size();

        while(r>l){
            int mid = (l + r)/2;
            int val = nums[mid];

            if(val == target) return mid;
            if(val > target){
                r = mid;
            } else {
                l = mid;
            }
        }
        return -1;
    }
};
