/*
A palindrome is a string that reads the same forward and backward.

Example 1:

Input: s = "abc"


Output: 6
Explanation: "a", "a", "a", "aa", "aa", "aaa". Note that different substrings are counted as different palindromes even if the string contents are the same.
Test

*/

#include <string>

class Solution
{
public:
    int countSubstrings(std::string s)
    {
        int count = 0;
        for (int i = 0; i < s.size(); i++)
        {
            int l = i;
            int r = i - 1;

            while (l < s.size() && r >= 0)
            {
                if (s[l] != s[r])
                {
                    break;
                }
                count++;
                l++;
                r--;
            }

            l = i + 1;
            r = i - 1;

            while (l < s.size() && r >= 0)
            {
                if (s[l] != s[r])
                {
                    break;
                }
                count++;
                l++;
                r--;
            }
        }

        return count;
    }
};
