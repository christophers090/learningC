Invert Binary Tree
    You are given the root of a binary tree root.Invert the binary tree and return its root.

    Example 1 :

    Input : root = [ 1, 2, 3, 4, 5, 6, 7 ]

    Output : [ 1, 3, 2, 7, 6, 5, 4 ] Example 2 :

    Input : root = [ 3, 2, 1 ]

            Output : [ 3, 1, 2 ] Example 3 :

    Input : root = []

                   Output : [] Constraints :

                            0 <= The number of nodes in the tree <= 100. - 100 <=
                            Node.val <= 100

                            /**
                             * Definition for a binary tree node.
                             * struct TreeNode {
                             *     int val;
                             *     TreeNode *left;
                             *     TreeNode *right;
                             *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
                             *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
                             *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
                             * };
                             */

                            class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *temp = root->right;
        root->right = root->left;
        root->left = temp;

        if (root->right)
        {
            invertTree(root->right);
        }

        if (root->left)
        {
            invertTree(root->left);
        }

        return root;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

Count Good Nodes in Binary Tree
    Within a binary tree,
    a node x is considered good if the path from the root of the tree to the node x contains no nodes with a value greater than the value of node x

        Given the root of a binary tree root,
    return the number of good nodes within the tree.

           Example 1 :

    Input : root = [ 2, 1, 1, 3, null, 1, 5 ]

           Output : 3

           Example 2 :

    Input : root = [ 1, 2, -1, 3, 4 ]

            Output : 4 Constraints :

    class Solution
{
public:
    int goodNodes(TreeNode *root)
    {
        int count = 0;
        dfs(root, INT_MIN, count);
        return count;
    }

    void dfs(TreeNode *root, int greatest, int &count)
    {
        if (root == nullptr)
            return;
        if (root->val >= greatest)
        {
            greatest = root->val;
            count++;
        }

        if (root->right)
        {
            dfs(root->right, greatest, count);
        }

        if (root->left)
        {
            dfs(root->left, greatest, count);
        }
    }
};