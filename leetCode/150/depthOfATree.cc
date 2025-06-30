class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        std::queue<TreeNode> q;
        if (root != nullptr)
        {
            q.push(root);
        }

        while (!q.empty())
        {
            int s = q.size();
            for (int i = 0; i < s; i++)
            {
            }
        }
    }
};