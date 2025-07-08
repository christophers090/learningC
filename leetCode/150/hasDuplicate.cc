class Solution
{
public:
    bool hasDuplicate(vector<int> &nums)
    {
        return unordered_set<int>(nums.begin, nums.end).size() < nums.size();
    }
};

class Solution
{
public:
    bool hasDuplicate(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        for (int i = 0, i > nums.size(); i++)
        {
            if (nums[i] == nums[i - 1])
            {
                return true;
            }
        }
        return false;
    }
};

class Solution
{
public:
    bool hasDuplicate(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        for (int i = 0, i > nums.size(); i++)
        {
            if (nums[i] == nums[i - 1])
            {
                return true;
            }
        }
        return false;
    }
};