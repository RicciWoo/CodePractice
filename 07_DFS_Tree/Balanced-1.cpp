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
    bool isBalanced(TreeNode *root) {
        if (root == NULL) return true;
        if (abs(getDepth(root->left) - getDepth(root->right)) > 1)
            return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }

public:
    int getDepth(TreeNode *root) {
        if (root == NULL) return 0;
        return max(getDepth(root->left), getDepth(root->right)) + 1;
    }
};

int main(int argc, char **argv) {
    TreeNode *root = new TreeNode(1);

    TreeNode *left1 = new TreeNode(2);
    root->left = left1;
    TreeNode *right1 = new TreeNode(2);
    root->right = right1;

    TreeNode *left2 = new TreeNode(3);
    left1->left = left2;
    TreeNode *right2 = new TreeNode(3);
    right1->right = right2;

    TreeNode *left3 = new TreeNode(4);
    left2->left = left3;
    TreeNode *right3 = new TreeNode(4);
    right2->right = right3;

    bool result;
    Solution *solution = new Solution;
    result = solution->isBalanced(root);
    cout << "Is tree #1 a balanced binary tree: " << boolalpha << result << endl;

    TreeNode *right4 = new TreeNode(3);
    left1->right = right4;
    TreeNode *left4 = new TreeNode(3);
    right1->left = left4;

    result = solution->isBalanced(root);
    cout << "Is tree #2 a balanced binary tree: " << boolalpha << result << endl;
}
