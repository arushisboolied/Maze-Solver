/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    unordered_map<int, int> inIdx;

    TreeNode* build(vector<int>& preorder, int& p, int l, int r) {
        if (l > r)
            return nullptr;
        int v = preorder[p++];
        TreeNode* n = new TreeNode(v);
        int m = inIdx[v];
        n->left = build(preorder, p, l, m - 1);
        n->right = build(preorder, p, m + 1, r);
        return n;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++)
            inIdx[inorder[i]] = i;
        int p = 0;
        return build(preorder, p, 0, inorder.size() - 1);
    }
};
