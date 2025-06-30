/*

*/

#include <vector>
#include <unordered_set>

class Solution
{
public:
    bool validTree(int n, std::vector<std::vector<int>> &edges)
    {
        std::unordered_set<int> set({0});

        for (auto edge : edges)
        {
            set.insert(edge[1]);
            set.insert(edge[0]);
        }
        int count = set.size();

        return count + 1 == edges.size();
    }
};
