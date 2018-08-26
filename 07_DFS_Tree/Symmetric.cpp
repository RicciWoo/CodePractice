#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Symmetric Tree, Recursion, 20180818
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == NULL) return true;
        return _isSymmetric(root->left, root->right);
    }

private:
    bool _isSymmetric(TreeNode *left, TreeNode *right) {
        if (left == NULL && right == NULL) 
            return true;
        if (left == NULL && right != NULL) 
            return false;
        if (left != NULL && right == NULL) 
            return false;
        if (left->val != right->val) 
            return false;
        return _isSymmetric(left->left, right->right) && 
               _isSymmetric(left->right, right->left);
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

    bool result;
    Solution *solution = new Solution;
    result = solution->isSymmetric(root);
    cout << "Is tree #1 a Symmetric tree: " << boolalpha << result << endl;

    left2->val = 4;
    right2->val = 3;
    result = solution->isSymmetric(root);
    cout << "Is tree #2 a Symmetric tree: " << boolalpha << result << endl;

    left1->left = NULL;
    free(left2);
    right1->left = NULL;
    free(left3);
    result = solution->isSymmetric(root);
    cout << "Is tree #3 a Symmetric tree: " << boolalpha << result << endl;

    left1->right = NULL;
    free(right2);
    left2 = new TreeNode(3);
    left1->left = left2;
    result = solution->isSymmetric(root);
    cout << "Is tree #4 a Symmetric tree: " << boolalpha << result << endl;
}
