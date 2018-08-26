#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Balanced Binary Tree, Recursion, 20180818
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode *> curr, next;
        curr.push(root);
        int leftVal = 0;
        bool isFirst = false;
        while (!curr.empty()) {
            isFirst = true;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                if (isFirst) {
                    leftVal = node->val;
                    isFirst = false;
                }
                if (node->left == NULL && node->right == NULL)
                    continue;
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
            swap(curr, next);
        }
        return leftVal;
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
    result = solution->findBottomLeftValue(root);
    cout << result << endl;
}
