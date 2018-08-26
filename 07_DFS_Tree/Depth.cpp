#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Depth of Tree, Recursion, 20180818
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    int depth(TreeNode *root) {
        if (root == NULL) return 0;
        return max(depth(root->left), depth(root->right)) + 1;
    }
};

int main(int argc, char **argv) {
    TreeNode *root = new TreeNode(1);
    TreeNode *left = new TreeNode(2);
    root->left = left;
    TreeNode *left2 = new TreeNode(3);
    left->left = left2;

    int result;
    Solution *solution = new Solution;
    result = solution->depth(root);
    cout << "depth of tree #1: " << result << endl;

    TreeNode *left3 = new TreeNode(4);
    left2->left = left3;
    TreeNode *right = new TreeNode(2);
    root->right = right;
    result = solution->depth(root);
    cout << "depth of tree #2: " << result << endl;

    TreeNode *right2 = new TreeNode(3);
    left->right = right2;
    TreeNode *left4 = new TreeNode(3);
    right->left = left4;
    TreeNode *right4 = new TreeNode(3);
    right->right = right4;
    TreeNode *right5 = new TreeNode(4);
    right4->right = right5;
    result = solution->depth(root);
    cout << "depth of tree #3: " << result << endl;
}
