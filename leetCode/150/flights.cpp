#include <vector>
#include <queue>

class Solution
{
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src, int dst, int k)
    {
        std::vector<std::vector<std::pair<int, int>>> adjacent(n);
        std::vector<int> mins(n, INT32_MAX);
        std::deque<std::pair<int, int>> que;

        for (auto flight : flights)
        {
            adjacent[flight[0]].push_back({flight[1], flight[2]});
        }

        int it = 0;
        que.push_back({src, 0});
        mins[src] = 0;
        while (it <= k)
        {
            it++;
            int len = que.size();

            for (int i = 0; i < len; i++)
            {
                auto rout = que.front();
                que.pop_front();

                if (rout.first != dst)
                {
                    for (auto nei : adjacent[rout.first])
                    {
                        int newCost = nei.second + rout.second;
                        if (mins[nei.first] > newCost)
                        {
                            mins[nei.first] = newCost;
                            que.push_back({nei.first, newCost});
                        }
                    }
                }
            }
        }

        return mins[dst] != INT32_MAX ? mins[dst] : -1;
    }
};
