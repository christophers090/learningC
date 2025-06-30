Sliding Window Maximum
You are given an array of integers nums and an integer k. There is a sliding window of size k that starts at the left edge of the array. The window slides one position to the right until it reaches the right edge of the array.

Return a list that contains the maximum element in the window at each step.

Example 1:

Input: nums = [1,2,1,0,4,2,6], k = 3

Output: [2,2,4,4,6]

Explanation: 
Window position            Max
---------------           -----
[1  2  1] 0  4  2  6        2
 1 [2  1  0] 4  2  6        2
 1  2 [1  0  4] 2  6        4
 1  2  1 [0  4  2] 6        4
 1  2  1  0 [4  2  6]       6
Constraints:

1 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
1 <= k <= nums.length

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<pair<int, int>> stack;
        vector<int> res;
        int maxIndex = 0;

        for(int i = 0; i < nums.size(); i++){
            while(!stack.empty()){
                auto it = stack.back();
                if(nums[i] >= it.first){
                    stack.pop_back();
                    maxIndex = 0;  // Reset maxIndex when stack changes
                } else {
                    break;
                }
            }

            stack.push_back({nums[i], i});

            while(maxIndex < stack.size() && i - stack[maxIndex].second >= k){
                maxIndex++;
            }
            
            // Ensure maxIndex is within bounds
            if(maxIndex >= stack.size()) maxIndex = 0;
            
            if(i >= k - 1){
                res.push_back(stack[maxIndex].first);
            }
        }

        return res;
    }
};
