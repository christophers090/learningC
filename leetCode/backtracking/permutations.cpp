class Solution
{
public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<bool> used(nums.size(), false);
        vector<int> cur;
        dfs(nums, cur, used, res);
        return res;
    }

    dfs(vector<int> &nums, vector<int> &cur, vector<bool> &used, vector<vector<int>> res)
    {
        if (total = nums.size())
        {
            res.push_back(cur);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i])
                continue;
            cur.push_back(nums[i]);
            used[i] = true;
            dfs(nums, cur, used, res);
            cur.pop();
            used[i] = false;
        }
        return;
    }
};

class Solution
{
    vector<vector<int>> res;

public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        backtrack(nums, 0);
        return res;
    }

    void backtrack(vector<int> &nums, int idx)
    {
        if (idx == nums.size())
        {
            res.push_back(nums);
            return;
        }
        for (int i = idx; i < nums.size(); i++)
        {
            swap(nums[idx], nums[i]);
            backtrack(nums, idx + 1);
            swap(nums[idx], nums[i]);
        }
    }
};