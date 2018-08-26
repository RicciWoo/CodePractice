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
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL) return false;
        if (root->left == NULL && root->right == NULL) {
            if (sum == root->val) return true;
            return false;
        }
        return hasPathSum(root->left, sum - root->val) || 
               hasPathSum(root->right, sum - root->val);
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

    int sum = 22;
    bool result;
    Solution *solution = new Solution;
    result = solution->hasPathSum(root, sum);
    cout << "has path sum to " << sum << " on tree #1: ";
    cout << boolalpha << result << endl;

    root->val = 3;
    left1->val = 2;
    right1->val = 6;
    left2->val = 9;
    left3->val = 22;
    right3->val = 9;
    sum = 31;
    result = solution->hasPathSum(root, sum);
    cout << "has path sum to " << sum << " on tree #1: ";
    cout << boolalpha << result << endl;
}
