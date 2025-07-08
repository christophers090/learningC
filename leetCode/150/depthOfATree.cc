class Solution {
public:
  int maxDepth(TreeNode *root) {
    queue<TreeNode *> q;
    if (root != nullptr) {
      q.push(root);
    }

    int level = 0;

    while (!q.empty()) {
      int s = q.size();
      for (int i = 0; i < s; i++) {
        TreeNode *n = q.front();
        if (n->left != nullptr) {
          q.push(n->left);
        }
        if (n->right != nullptr) {
          q.push(n->right);
        }
        q.pop();
      }
      level++;
    }

    return level;
  }
};