Longest Repeating Character Replacement
    You are given a string s consisting of only uppercase english characters and an integer k.You can choose up to
        k characters of the string and replace them with any other uppercase English character.

    After performing at most k replacements,
    return the length of the longest substring which contains only one distinct character.

           Example 1 :

    Input : s = "XYYX",
            k = 2

            Output : 4 Explanation : Either replace the 'X' s with 'Y' s,
            or replace the 'Y' s with 'X' s.

                Example 2 :

    Input : s = "AAABABB",
            k = 1

                Output : 5 Constraints :

                1 <= s.length <= 1000 0 <= k <= s.length

                                                class Solution
{
public:
    int characterReplacement(string s, int k)
    {
        if (s.empty())
            return 0; // Handle empty string
        if (k >= s.length())
            return s.length();

        int l = 0, maxLen = 0;
        vector<int> counts(26, 0);

        for (int r = 0; r < s.length(); r++)
        {
            int index = s[r] - 'A';

            counts[index]++;

            while ((r - l + 1) - getMaxCount(counts) > k)
            {
                counts[s[l] - 'A']--;
                l++;
            }

            maxLen = max(maxLen, r - l + 1);
        }

        return maxLen;
    }

    int getMaxCount(vector<int> &counts)
    {
        int maxVal = 0;
        for (int count : counts)
        {
            maxVal = max(maxVal, count);
        }
        return maxVal;
    }
};
