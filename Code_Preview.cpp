/******************** Tree ********************/

// Binary Tree Preorder Traversal-1, use recursion
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        _preorder(root, result);
        return result;
    }
    
private:
    void _preorder(TreeNode *root, vector<int> &result) {
        if (root == NULL) return;
        result.push_back(root->val);
        _preorder(root->left, result);
        _preorder(root->right, result);
    }
};

// Binary Tree Preorder Traversal-2, use stack
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == NULL) return result;
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode *node = s.top();
            s.pop();
            result.push_back(node->val);
            if (node->right != NULL)
                s.push(node->right);
            if (node->left != NULL)
                s.push(node->left);
        }
        return result;
    }
};

// Binary Tree Preorder Traversal-3, use stack
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == NULL) return result;
        stack<TreeNode *> s;
        s.push(root);
        TreeNode *node = root;
        while (!s.empty()) {
            result.push_back(node->val);
            if (node->right != NULL)
                s.push(node->right);
            if (node->left != NULL)
                node = node->left;
            else {
                node = s.top();
                s.pop();
            }
        }
        return result;
    }
};

// Binary Tree Preorder Traversal-4, use stack
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == NULL) return result;
        stack<TreeNode *> s;
        TreeNode *node = root;
        while (!s.empty() || node != NULL) {
            if (node != NULL) {
                result.push_back(node->val);
                if (node->right != NULL)
                    s.push(node->right);
                node = node->left;
            } else {
                node = s.top();
                s.pop();
            }
        }
        return result;
    }
};

// Binary Tree Inorder Traversal-1, use recursion
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        _inorder(root, result);
        return result;
    }
    
private:
    void _inorder(TreeNode *root, vector<int> &result) {
        if (root == NULL) return;
        _inorder(root->left, result);
        result.push_back(root->val);
        _inorder(root->right, result);
    }
};

// Binary Tree Inorder Traversal-2, use stack
class Solution {
public:
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
};

// Binary Tree Postorder Traversal-1, use recursion
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        _postorder(root, result);
        return result;
    }
    
private:
    void _postorder(TreeNode *root, vector<int> &result) {
        if (root == NULL) return;
        _postorder(root->left, result);
        _postorder(root->right, result);
        result.push_back(root->val);
    }
};

// Binary Tree Postorder Traversal-2, use stack with flag
struct NodeWithFlag {
    TreeNode *node;
    bool flag;
    NodeWithFlag(TreeNode *n, bool f) : node(n), flag(f) {}
};
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == NULL) return result;
        TreeNode *node = root;
        NodeWithFlag *fNode;
        stack<NodeWithFlag *> s;
        while (!s.empty() || node != NULL) {
            while (node != NULL) {
                fNode = new NodeWithFlag(node, false);
                s.push(fNode);
                node = node->left;
            }
            fNode = s.top();
            s.pop();
            node = fNode->node;
            if (!fNode->flag) {
                fNode->flag = true;
                s.push(fNode);
                node = node->right;
            } else {
                result.push_back(node->val);
                node = NULL;
            }
        }
        return result;
    }
};

// Binary Tree Postorder Traversal-3, use stack and reverse
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode *> s;
        TreeNode *node = root;
        while (!s.empty() || node != NULL) {
            if (node != NULL) {
                result.push_back(node->val);
                if (node->left)
                    s.push(node->left);
                node = node->right;
            } else {
                node = s.top();
                s.pop();
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// Construct Binary Tree from Preorder and Inorder Traversal
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int preSt = 0, preEnd = preorder.size() - 1;
        int inSt = 0, inEnd = inorder.size() - 1;
        return _build(preorder, preSt, preEnd, inorder, inSt, inEnd);
    }
    
private:
    TreeNode *_build(vector<int> &preorder, int preSt, int preEnd, 
                     vector<int> &inorder, int inSt, int inEnd) {
        if (preSt > preEnd || inSt > inEnd) return NULL;
        int rootVal = preorder[preSt];
        int k = 0;
        for (int i = inSt; i <= inEnd; i++) {
            if (rootVal == inorder[i]) {
                k = i;
                break;
            }
        }
        TreeNode *root = new TreeNode(rootVal);
        root->left = _build(preorder, preSt + 1, preSt + (k - inSt), 
                            inorder, inSt, k - 1);
        root->right = _build(preorder, preSt + (k - inSt) + 1, preEnd, 
                             inorder, k + 1, inEnd);
        return root;
    }
};

// Construct Binary Tree from Preorder and Inorder Traversal
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int inSt = 0, inEnd = inorder.size() - 1;
        int poSt = 0, poEnd = postorder.size() - 1;
        return _build(inorder, inSt, inEnd, postorder, poSt, poEnd);
    }
    
private:
    TreeNode *_build(vector<int> &inorder, int inSt, int inEnd, 
                     vector<int> &postorder, int poSt, int poEnd) {
        if (inSt > inEnd || poSt > poEnd) return NULL;
        int rootVal = postorder[poEnd];
        int k = 0;
        for (int i = inSt; i <= inEnd; i++) {
            if (rootVal == inorder[i]) {
                k = i;
                break;
            }
        }
        TreeNode *root = new TreeNode(rootVal);
        root->left = _build(inorder, inSt, k - 1, 
                            postorder, poSt, poSt + (k - inSt) - 1);
        root->right = _build(inorder, k + 1, inEnd, 
                             postorder, poSt + (k - inSt), poEnd - 1);
        return root;
    }
};

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

// Trie Tree
struct TrieNode {
    bool isWord;
    vector<TrieNode *> children;
    TrieNode() {
        isWord = false;
        children = vector<TrieNode *>(26, NULL);
    }
};
class Trie {
private:
    TrieNode *root;
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.size() == 0) return;
        TrieNode *pNode = root;
        for (int i = 0; i < word.size(); i++) {
            if (pNode->children[word[i] - 'a'] == NULL)
                pNode->children[word[i] - 'a'] = new TrieNode();
            pNode = pNode->children[word[i] - 'a'];
        }
        pNode->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        if (word.size() == 0) return true;
        TrieNode *pNode = root;
        for (int i = 0; i < word.size(); i++) {
            pNode = pNode->children[word[i] - 'a'];
            if (pNode == NULL) return false;
        }
        return pNode->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if (prefix.size() == 0) return true;
        TrieNode *pNode = root;
        for (int i = 0; i < prefix.size(); i++) {
            pNode = pNode->children[prefix[i] - 'a'];
            if (pNode == NULL) return false;
        }
        return true;
    }
};
