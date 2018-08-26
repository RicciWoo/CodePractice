#include <list>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (root == NULL) return results;
        queue<TreeNode *> curr, next;
        curr.push(root);
        bool isOdd = true;
        while (!curr.empty()) {
            list<int> level;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                if (isOdd) level.push_back(node->val);
                else       level.push_front(node->val);
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
            vector<int> res(level.begin(), level.end());
            results.push_back(res);
            swap(curr, next);
            isOdd = !isOdd;
        }
        return results;
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

    vector<vector<int>> results;
    Solution *solution = new Solution;
    results = solution->zigzagLevelOrder(root);
    cout << "[ ";
    for (vector<int> vec : results) {
        cout << "[";
        for (int val : vec) {
            cout << val << ",";
        }
        cout << "], ";
    }
    cout << "], " << endl;
}
