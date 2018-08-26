#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Depth of Binary Tree, Recursion, 20180818
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    int minDepth(TreeNode *root) {
        if (root == NULL) return 0;
        int leftDepth = minDepth(root->left);
        int rightDepth = minDepth(root->right);
        if (leftDepth == 0) {
            return rightDepth + 1;
        } else if (rightDepth == 0) {
            return leftDepth + 1;
        }
        return min(leftDepth, rightDepth) + 1;
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
    TreeNode *right2 = new TreeNode(4);
    left1->right = right2;

    TreeNode *left3 = new TreeNode(4);
    right1->left = left3;
    TreeNode *right3 = new TreeNode(3);
    right1->right = right3;

    int result;
    Solution *solution = new Solution;
    result = solution->minDepth(root);
    cout << "minimum depth of tree #1: " << result << endl;

    right1->left = NULL;
    free(left3);
    right1->right = NULL;
    free(right3);
    result = solution->minDepth(root);
    cout << "minimum depth of tree #2: " << result << endl;

    left1->right = NULL;
    free(right2);
    left3 = new TreeNode(3);
    right1->left = left3;
    result = solution->minDepth(root);
    cout << "minimum depth of tree #3: " << result << endl;
}
