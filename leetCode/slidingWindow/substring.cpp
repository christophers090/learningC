Longest Substring Without Repeating Characters
    Given a string s,
    find the length of the longest substring without duplicate characters.

    A substring is a contiguous sequence of characters within a string.

    Example 1 :

    Input : s = "zxyzxyz"

                Output : 3 Explanation : The string "xyz" is the longest without duplicate characters.

                                         Example 2 :

    Input : s = "xxxx"

                Output : 1 Constraints :

                0 <= s.length <= 1000 s may consist of printable ASCII characters.

                                 class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {

        int l = 0, r = 1, maxLen = 0;
        unordered_set<char> inSub{s[0]};

        while (true)
        {
            while (inSub.find(s[r]) == inSub.end())
            {
                inSub.insert(s[r]);
                r++;
                maxLen = max(maxLen, r - l);
                if (r == s.length())
                    return maxLen;
            }
            while (inSub.find(s[r]) != inSub.end())
            {
                inSub.erase(s[l]);
                l++;
            }
        }
    }
};
