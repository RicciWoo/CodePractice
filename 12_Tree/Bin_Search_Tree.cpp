#include <stack>
#include <vector>
#include <iostream>
using namespace std;

// Binary Search Tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool find(int value, TreeNode *root) {
        TreeNode *node = root;
        while (node != NULL) {
            if (value < node->val)
                node = node->left;
            else if (value > node->val)
                node = node->right;
            else return true;
        }
        return false;
    }

    bool add(int value, TreeNode *root) {
        if (root == NULL) {
            root = new TreeNode(value);
            return true;
        }
        TreeNode *node = root;
        while (node != NULL) {
            if (value < node->val) {
                if (node->left != NULL)
                    node = node->left;
                else {
                    node->left = new TreeNode(value);
                    return true;
                }
            } else if (value > node->val) {
                if (node->right != NULL)
                    node = node->right;
                else {
                    node->right = new TreeNode(value);
                    return true;
                }
            } else return false;
        }
        return false;
    }

    bool remove(int value, TreeNode *root) {
        if (root == NULL) return false;
        if (value == root->val) {
            root = _removeNode(root);
            return true;
        }
        TreeNode *node = root;
        while (node != NULL) {
            if (value < node->val) {
                if (node->left != NULL && value != node->left->val) 
                    node = node->left;
                else if (node->left == NULL) return false;
                else {
                    node->left = _removeNode(node->left);
                    return true;
                }
            } else if (node->val < value) {
                if (node->right != NULL && value != node->right->val)
                    node = node->right;
                else if (node->right == NULL) return false;
                else {
                    node->right = _removeNode(node->right);
                    return true;
                }
            } else return false;
        }
        return false;
    }

private:
    TreeNode *_removeNode(TreeNode *node) {
        if (node->left == NULL && node->right == NULL)
            return NULL;
        else if (node->left == NULL)
            return node->right;
        else if (node->right == NULL)
            return node->left;
        else {
            node->val = _findAndRemove(node);
            return node;
        }
    }

    int _findAndRemove(TreeNode *node) {
        int result;
        if (node->left->right == NULL) {
            result = node->left->val;
            node->left = node->left->left;
            return result;
        }
        node = node->left;
        while (node->right->right != NULL)
            node = node->right;
        result = node->right->val;
        node->right = node->right->left;
        return result;
    }
};

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    if (root == NULL) return result;
    stack<TreeNode *> s;
    TreeNode *node = root;
    while (!s.empty() || node != NULL) {
        if (node != NULL) {
            s.push(node);
            node = node->left;
        } else {
            node = s.top();
            s.pop();
            result.push_back(node->val);
            node = node->right;
        }
    }
    return result;
}

int main(int argc, char **argv) {
    TreeNode *root = new TreeNode(30);

    TreeNode *left1 = new TreeNode(18);
    TreeNode *right1 = new TreeNode(34);
    root->left = left1;
    root->right = right1;

    TreeNode *left2 = new TreeNode(13);
    TreeNode *right2 = new TreeNode(24);
    left1->left = left2;
    left1->right = right2;

    TreeNode *left3 = new TreeNode(31);
    TreeNode *right3 = new TreeNode(40);
    right1->left = left3;
    right1->right = right3;

    TreeNode *left4 = new TreeNode(22);
    TreeNode *right4 = new TreeNode(27);
    right2->left = left4;
    right2->right = right4;

    TreeNode *right5 = new TreeNode(47);
    right3->right = right5;

    vector<int> inorder;
    inorder = inorderTraversal(root);
    cout << "inoder traversal of Tree: [";
    for (int i : inorder) cout << i << ", ";
    cout << "]" << endl;

    bool findRes = false;
    Solution *solution = new Solution;
    findRes = solution->find(24, root);
    cout << "find element 24, result is: " << findRes << endl;
    findRes = solution->find(24, root);
    cout << "find element 42, result is: " << findRes << endl;

    bool addRes = false;
    addRes = solution->add(42, root);
    cout << "add element 42, result is: " << addRes << endl;
    if (addRes) {
        inorder = inorderTraversal(root);
        cout << "inoder traversal of Tree: [";
        for (int i : inorder) cout << i << ", ";
        cout << "]" << endl;
    }

    bool rmRes = false;
    rmRes = solution->remove(27, root);
    cout << "remove element 27, result is: " << rmRes << endl;
    if (rmRes) {
        inorder = inorderTraversal(root);
        cout << "inoder traversal of Tree: [";
        for (int i : inorder) cout << i << ", ";
        cout << "]" << endl;
    }

    rmRes = solution->remove(30, root);
    cout << "remove element 30, result is: " << rmRes << endl;
    if (rmRes) {
        inorder = inorderTraversal(root);
        cout << "inoder traversal of Tree: [";
        for (int i : inorder) cout << i << ", ";
        cout << "]" << endl;
    }
}





















