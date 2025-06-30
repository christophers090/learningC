Partition Equal Subset Sum
    You are given an array of positive integers nums.

    Return true if you can partition the array into two subsets,
    subset1 and subset2 where sum(subset1) == sum(subset2).Otherwise, return false.

                                                                             Example 1 :

    Input : nums = [ 1, 2, 3, 4 ]

                                                                             Output : true Explanation : The array can be partitioned as[1, 4] and
                                                                                                         [ 2, 3 ].

                                                                                                         Example 2 :

    Input : nums = [ 1, 2, 3, 4, 5 ]

                                                                             Output : false Constraints :

                                                                                      1 <= nums.length
                                                                                      <= 100 1 <= nums[i] <= 50

                                                                                      class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int totalSum = 0;
        for (int num : nums)
        {
            totalSum += num;
        }

        if (totalSum % 2 != 0)
            return false;

        int target = totalSum / 2;
        return dfs(0, nums, 0, target);
    }

    bool dfs(int i, vector<int> &nums, int currentSum, int target)
    {
        if (currentSum == target)
            return true;
        if (currentSum > target || i >= nums.size())
            return false;
        if (dfs(i + 1, nums, currentSum + nums[i], target))
            return true;
        if (dfs(i + 1, nums, currentSum, target))
            return true;
        return false;
    }
};

2. Dynamic Programming(Top - Down) class Solution
{
public:
    vector<vector<int>> memo;
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
        }
        if (sum % 2 != 0)
        {
            return false;
        }
        memo.resize(nums.size(), vector<int>(sum / 2 + 1, -1));

        return dfs(nums, 0, sum / 2);
    }

    bool dfs(vector<int> &nums, int i, int target)
    {
        if (i == nums.size())
        {
            return target == 0;
        }
        if (target < 0)
        {
            return false;
        }
        if (memo[i][target] != -1)
        {
            return memo[i][target];
        }

        memo[i][target] = dfs(nums, i + 1, target) ||
                          dfs(nums, i + 1, target - nums[i]);
        return memo[i][target];
    }
};

Time &Space Complexity
    Time complexity : O(
                          n
∗ t
                              a
                                  r
                                      g
                                          e
                                              t)
                          O(n∗target)
                              Space complexity : O(
                                                     n
∗ t
                                                         a
                                                             r
                                                                 g
                                                                     e
                                                                         t)
                                                     O(n∗target)
                                                         Where
                                                 n
                                                 n is the length of the array
                                                 n
                                                 u
                                                 m
                                                 s
                                                 nums and t
                                                 a
                                                 r
                                                 g
                                                 e
                                                 t
                                                 target is the sum of array elements divided by 2. 3. Dynamic Programming(Bottom - Up)

                                                     class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
        }
        if (sum % 2 != 0)
        {
            return false;
        }

        int target = sum / 2;
        int n = nums.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= target; j++)
            {
                if (nums[i - 1] <= j)
                {
                    dp[i][j] = dp[i - 1][j] ||
                               dp[i - 1][j - nums[i - 1]];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[n][target];
    }
};

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
        }
        if (sum % 2 != 0)
        {
            return false;
        }

        int target = sum / 2;
        bitset<10001> dp;
        dp[0] = 1;

        for (int num : nums)
        {
            dp |= dp << num;
        }

        return dp[target];
    }
};