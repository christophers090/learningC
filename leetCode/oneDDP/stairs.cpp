Climbing Stairs
You are given an integer n representing the number of steps to reach the top of a staircase. You can climb with either 1 or 2 steps at a time.

Return the number of distinct ways to climb to the top of the staircase.

Example 1:

Input: n = 2

Output: 2
Explanation:

1 + 1 = 2
2 = 2
Example 2:

Input: n = 3

Output: 3
Explanation:

1 + 1 + 1 = 3
1 + 2 = 3
2 + 1 = 3
Constraints:

1 <= n <= 30


2. Dynamic Programming (Top-Down)
class Solution {
public:
    vector<int> cache;
    int climbStairs(int n) {
        cache.resize(n, -1);
        return dfs(n, 0);
    }

    int dfs(int n, int i) {
        if (i >= n) return i == n;
        if (cache[i] != -1) return cache[i];
        return cache[i] = dfs(n, i + 1) + dfs(n, i + 2);
    }
};
Time & Space Complexity
Time complexity: 
O
(
n
)
O(n)
Space complexity: 
O
(
n
)
O(n)
3. Dynamic Programming (Bottom-Up)
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
Time & Space Complexity
Time complexity: 
O
(
n
)
O(n)
Space complexity: 
O
(
n
)
O(n)
4. Dynamic Programming (Space Optimized)
class Solution {
public:
    int climbStairs(int n) {
        int one = 1, two = 1;
        
        for (int i = 0; i < n - 1; i++) {
            int temp = one;
            one = one + two;
            two = temp;
        }
        
        return one;
    }
};