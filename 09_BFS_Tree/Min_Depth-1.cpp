#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Depth of Binary Tree-1, BFS, 20180825
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        queue<TreeNode *> curr, next;
        curr.push(root);
        int minDepth = 1;
        while (!curr.empty()) {
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                if (node->left == NULL && node->right == NULL)
                    return minDepth;
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
            minDepth++;
            swap(curr, next);
        }
        return minDepth;
    }
};

int main(int argc, char **argv) {
    TreeNode *root = new TreeNode(3);

    TreeNode *left1 = new TreeNode(9);
    root->left = left1;
    TreeNode *right1 = new TreeNode(20);
    root->right = right1;

    TreeNode *left2 = new TreeNode(15);
    right1->left = left2;
    TreeNode *right2 = new TreeNode(7);
    right1->right = right2;

    int result;
    Solution *solution = new Solution;
    result = solution->minDepth(root);
    cout << result << endl;
}
