#include <vector>
#include <limits.h>
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
    int maxPathSum(TreeNode* root) {
        if (root == NULL) return 0;
        int maxSum = INT_MIN;
        _maxBranchSum(root, maxSum);
        return maxSum;
    }
    
private:
    int _maxBranchSum(TreeNode *root, int &maxSum) {
        if (root == NULL) return 0;
        int leftSum = _maxBranchSum(root->left, maxSum);
        int rightSum = _maxBranchSum(root->right, maxSum);
        int maxBranchSum = root->val + max(0, max(leftSum, rightSum));
        maxSum = max(maxSum, max(maxBranchSum, 
                                 leftSum + root->val + rightSum));
        return maxBranchSum;
    }
};

int main(int argc, char **argv) {
    TreeNode *root = new TreeNode(5);

    TreeNode *left1 = new TreeNode(4);
    root->left = left1;
    TreeNode *right1 = new TreeNode(8);
    root->right = right1;

    TreeNode *left2 = new TreeNode(11);
    left1->left = left2;

    TreeNode *left3 = new TreeNode(13);
    right1->left = left3;
    TreeNode *right3 = new TreeNode(4);
    right1->right = right3;

    TreeNode *left4 = new TreeNode(7);
    left2->left = left4;
    TreeNode *right4 = new TreeNode(2);
    left2->right = right4;

    TreeNode *right5 = new TreeNode(1);
    right3->right = right5;

    int result;
    Solution *solution = new Solution;
    result = solution->maxPathSum(root);
    cout << "Maximum path sum on Tree #1: " << result << endl;

    left1->left = NULL;
    right1->left = NULL;
    right1->right = NULL;
    result = solution->maxPathSum(root);
    cout << "Maximum path sum on Tree #2: " << result << endl;

    right1->val = -8;
    result = solution->maxPathSum(root);
    cout << "Maximum path sum on Tree #3: " << result << endl;

    left1->val = -4;
    result = solution->maxPathSum(root);
    cout << "Maximum path sum on Tree #4: " << result << endl;

    right1->val = 8;
    result = solution->maxPathSum(root);
    cout << "Maximum path sum on Tree #5: " << result << endl;
}
