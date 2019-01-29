/******************** Tree based DFS ********************/

// LeetCode 104 - Maximum Depth of Binary Tree, 
// Depth-first Search, Preorder Traversal, 20181227
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        
        int maxDepth = INT_MIN;
        _traverse(root, 1, maxDepth);
        return maxDepth;
    }
    
private:
    void _traverse(TreeNode *node, int depth, int &maxDepth) {
        if (node == nullptr) {
            return;
        }
        
        maxDepth = max(maxDepth, depth);
        _traverse(node->left, depth + 1, maxDepth);
        _traverse(node->right, depth + 1, maxDepth);
    }
};

// LeetCode 104 - Maximum Depth of Binary Tree, 
// Depth-first Search, Divide and Conquer, 20181227
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    /**
     * @param root: The root of binary tree.
     * @return: An integer
     */
    int maxDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(left, right) + 1;
    }
};

// LeetCode 110 - Balanced Binary Tree, 
// Depth-first Search, Divide and Conquer, 20181227
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return _depth(root) != -1;
    }
    
private:
    int _depth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        
        int leftDepth = _depth(root->left);
        int rightDepth = _depth(root->right);
        if (abs(leftDepth - rightDepth) > 1 ||
            leftDepth == -1 || rightDepth == -1) {
            return -1;
        }
        
        return max(leftDepth, rightDepth) + 1;
    }
};

// LeetCode 98 - Validate Binary Search Tree, 
// Depth-first Search, Inorder Traversal, 20181227
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        bool valid = true;
        TreeNode *prev = nullptr;
        _traverse(root, prev, valid);
        return valid;
    }
    
private:
    void _traverse(TreeNode *root, TreeNode *&prev, bool &valid) {
        if (root == nullptr) {
            return;
        }
        
        _traverse(root->left, prev, valid);
        if (prev != nullptr && prev->val >= root->val) {
            valid = false;
            return;
        }
        prev = root;
        _traverse(root->right, prev, valid);
    }
};

// LeetCode 98 - Validate Binary Search Tree, 
// Depth-first Search, Divide and Conquer, 20181227
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class ResultType {
public:
    bool isBST;
    int maxVal, minVal;
    ResultType(bool isBST, int maxVal, int minVal) {
        this->isBST = isBST;
        this->maxVal = maxVal;
        this->minVal = minVal;
    }
};

class Solution {
public:
    bool isValidBST(TreeNode *root) {
        return _isValid(root)->isBST;
    }
    
private:
    ResultType *_isValid(TreeNode *root) {
        if (root == nullptr) {
            return new ResultType(true, INT_MIN, INT_MAX);
        }
        
        ResultType *left = _isValid(root->left);
        ResultType *right = _isValid(root->right);
        if (!left->isBST || !right->isBST) {
            return new ResultType(false, 0, 0);
        }
        
        if (root->left != nullptr && left->maxVal >= root->val) {
            return new ResultType(false, 0, 0);
        }
        if (root->right != nullptr && right->minVal <= root->val) {
            return new ResultType(false, 0, 0);
        }
        
        ResultType *result = new ResultType(true, 0, 0);
        result->minVal = min(root->val, left->minVal);
        result->maxVal = max(root->val, right->maxVal);
        return result;
    }
};

// LeetCode 98 - Validate Binary Search Tree, 
// Depth-first Search, Divide and Conquer, 20181227
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class ResultType {
public:
    bool isBST;
    TreeNode *maxNode, *minNode;
    ResultType(bool isBST) {
        this->isBST = isBST;
        this->maxNode = this->minNode = nullptr;
    }
};
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        return _isValid(root)->isBST;
    }
    
private:
    ResultType *_isValid(TreeNode *root) {
        if (root == nullptr) {
            return new ResultType(true);
        }
        
        ResultType *left = _isValid(root->left);
        ResultType *right = _isValid(root->right);
        if (!left->isBST || !right->isBST) {
            return new ResultType(false);
        }
        
        if (left->maxNode != nullptr && left->maxNode->val >= root->val) {
            return new ResultType(false);
        }
        if (right->minNode != nullptr && right->minNode->val <= root->val) {
            return new ResultType(false);
        }
        
        ResultType *result = new ResultType(true);
        result->minNode = left->minNode != nullptr ? left->minNode : root;
        result->maxNode = right->maxNode != nullptr ? right->maxNode : root;
        return result;
    }
};

// LeetCode 98 - Validate Binary Search Tree, 
// Iteration, Inorder Traversal, 20190103
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        
        stack<TreeNode *> st;
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
        
        TreeNode *lastNode = nullptr;
        while (!st.empty()) {
            TreeNode *node = st.top();
            if (lastNode != nullptr && lastNode->val >= node->val) {
                return false;
            }
            lastNode = node;
            
            if (node->right != nullptr) {
                node = node->right;
                while (node != nullptr) {
                    st.push(node);
                    node = node->left;
                }
            } else {
                node = st.top();
                st.pop();
                while (!st.empty() && st.top()->right == node) {
                    node = st.top();
                    st.pop();
                }
            }
        }
        
        return true;
    }
};

// LeetCode 226 - Invert Binary Tree, 
// Depth-first Search, Preorder Traversal, 20181227
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }
        
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;
        
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

// LintCode 596 - Minimum Subtree, 
// Depth-first Search, Postorder Traversal, 20181227
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    TreeNode *findSubtree(TreeNode *root) {
        TreeNode *subtree = nullptr;
        int minSum = INT_MAX;
        _findSubtree(root, subtree, minSum);
        return subtree;
    }
    
private:
    int _findSubtree(TreeNode *root, 
                     TreeNode *&subtree, int &minSum) {
        if (root == nullptr) {
            return 0;
        }
        
        int left = _findSubtree(root->left, subtree, minSum);
        int right = _findSubtree(root->right, subtree, minSum);
        int sum = left + right + root->val;
        if (sum < minSum) {
            minSum = sum;
            subtree = root;
        }
        
        return sum;
    }
};

// LintCode 596 - Minimum Subtree, 
// Depth-first Search, Divide and Conquer, 20181227
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Result {
public:
    int sum, minSum;
    TreeNode *subtree;
    Result(int sum, int minSum, TreeNode *subtree) {
        this->sum = sum;
        this->minSum = minSum;
        this->subtree = subtree;
    }
};
class Solution {
public:
    TreeNode *findSubtree(TreeNode *root) {
        Result *result = _findSubtree(root);
        return result->subtree;
    }
    
private:
    Result *_findSubtree(TreeNode *root) {
        if (root == nullptr) {
            return new Result(0, INT_MAX, nullptr);
        }
        
        Result *left = _findSubtree(root->left);
        Result *right = _findSubtree(root->right);
        int sum = left->sum + right->sum + root->val;
        Result *result = new Result(sum, sum, root);
        
        if (left->minSum < result->minSum) {
            result->minSum = left->minSum;
            result->subtree = left->subtree;
        }
        if (right->minSum < result->minSum) {
            result->minSum = right->minSum;
            result->subtree = right->subtree;
        }
        
        return result;
    }
};

// LintCode 597 - Subtree with Maximum Average, 
// Depth-first Search, Divide and Conquer, 20181227
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Result {
public:
    int sum, size;
    Result(int sum, int size) {
        this->sum = sum;
        this->size = size;
    }
};

class Solution {
public:
    TreeNode *findSubtree2(TreeNode *root) {
        TreeNode *subtree = nullptr;
        Result *subResult = nullptr;
        _findSubtree(root, subtree, subResult);
        return subtree;
    }
    
private:
    Result *_findSubtree(TreeNode *root, 
                         TreeNode *&subtree, Result *&subResult) {
        if (root == nullptr) {
            return new Result(0, 0);
        }
        
        Result *left = _findSubtree(root->left, subtree, subResult);
        Result *right = _findSubtree(root->right, subtree, subResult);
        Result *result = new Result(
            left->sum + right->sum + root->val, 
            left->size + right->size + 1);
        if (subResult == nullptr || 
            result->sum * subResult->size > subResult->sum * result->size ) {
            subtree = root;
            subResult = result;
        }
        
        return result;
    }
};

// LeetCode 257 - Binary Tree Paths, 
// Depth-first Search, Inorder Traversal, 20181230
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> results;
        if (root == nullptr) {
            return results;
        }
        
        string path = to_string(root->val);
        _binaryTreePaths(root, path, results);
        return results;
    }
    
private:
    void _binaryTreePaths(TreeNode *root, string path, 
                          vector<string> &results) {
        if (root == nullptr) {
            return;
        }
        
        if (root->left == nullptr && root->right == nullptr) {
            results.push_back(path);
            return;
        }
        
        if (root->left != nullptr) {
            string newPath = path + "->" + to_string(root->left->val);
            _binaryTreePaths(root->left, newPath, results);
        }
        if (root->right != nullptr) {
            string newPath = path + "->" + to_string(root->right->val);
            _binaryTreePaths(root->right, newPath, results);
        }
    }
};

// LeetCode 235 - Lowest Common Ancestor of a Binary Search Tree, 
// Depth-first Search, Divide and Conquer, 20181230
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, 
                                   TreeNode *p, TreeNode *q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr) {
            return root;
        }
        if (left != nullptr) {
            return left;
        }
        if (right != nullptr) {
            return right;
        }
        
        return nullptr;
    }
};

// LeetCode 236 - Lowest Common Ancestor of a Binary Tree, 
// LintCode 88 - Lowest Common Ancester of a Binary Tree, 
// Depth-first Search, Divide and Conquer, 20181230
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, 
                                   TreeNode *p, TreeNode *q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr) {
            return root;
        }
        if (left != nullptr) {
            return left;
        }
        if (right != nullptr) {
            return right;
        }
        
        return nullptr;
    }
};

// LintCode 474 - Lowest Common Ancestor II, 20181231
/**
 * Definition of ParentTreeNode:
 * class ParentTreeNode {
 * public:
 *     int val;
 *     ParentTreeNode *parent, *left, *right;
 * }
 */
class Solution {
public:
    ParentTreeNode *lowestCommonAncestorII(ParentTreeNode *root, 
                                           ParentTreeNode *A, 
                                           ParentTreeNode *B) {
        if (root == nullptr) {
            return nullptr;
        }
        
        vector<ParentTreeNode *> pathA = _getPath2Root(A);
        vector<ParentTreeNode *> pathB = _getPath2Root(B);
        
        int indexA = pathA.size() - 1;
        int indexB = pathB.size() - 1;
        
        ParentTreeNode *result = nullptr;
        while (indexA >= 0 && indexB >= 0) {
            if (pathA[indexA] != pathB[indexB]) {
                break;
            }
            
            result = pathA[indexA];
            indexA--;
            indexB--;
        }
        
        return result;
    }
    
private:
    vector<ParentTreeNode *> _getPath2Root(ParentTreeNode *node) {
        vector<ParentTreeNode *> path;
        
        while (node != nullptr) {
            path.push_back(node);
            node = node->parent;
        }
        
        return path;
    }
};

// LintCode 578 - Lowest Common Ancestor III, 
// Depth-first Search, Divide and Conquer, 20181231
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Result {
public:
    bool aExist, bExist;
    TreeNode *node;
    Result(bool aExist, bool bExist, TreeNode *node) {
        this->aExist = aExist;
        this->bExist = bExist;
        this->node = node;
    }
};
class Solution {
public:
    TreeNode *lowestCommonAncestor3(TreeNode *root, 
                                    TreeNode *A, TreeNode *B) {
        if (root == nullptr) {
            return nullptr;
        }
        
        Result *result = _lca(root, A, B);
        if (result->aExist && result->bExist) {
            return result->node;
        }
        return nullptr;
    }

private:
    Result *_lca(TreeNode *root, TreeNode *A, TreeNode *B) {
        if (root == nullptr) {
            return new Result(false, false, nullptr);
        }
        
        Result *left = _lca(root->left, A, B);
        Result *right = _lca(root->right, A, B);
        bool aExist = left->aExist || right->aExist || root == A;
        bool bExist = left->bExist || right->bExist || root == B;
        
        if (root == A || root == B) {
            return new Result(aExist, bExist, root);
        }
        
        TreeNode *node = nullptr;
        if (left->node != nullptr && right->node != nullptr) {
            node = root;
        } else if (left->node != nullptr) {
            node = left->node;
        } else if (right->node != nullptr) {
            node = right->node;
        }
        return new Result(aExist, bExist, node);
    }
};

// LeetCode 114 - Flattern Binary Tree to Linked List, 
// Depth-first Search, Preorder Traversal, 20190102
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        TreeNode *lastNode = nullptr;
        _flatten(root, lastNode);
    }
    
private:
    void _flatten(TreeNode *root, TreeNode *&lastNode) {
        if (root == nullptr) {
            return;
        }
        
        if (lastNode != nullptr) {
            lastNode->left = nullptr;
            lastNode->right = root;
        }
        
        lastNode = root;
        // root->right will be changed
        TreeNode *right = root->right;
        _flatten(root->left, lastNode);
        _flatten(right, lastNode);
    }
};

// LeetCode 114 - Flattern Binary Tree to Linked List, 
// Depth-first Search, Divide and Conquer, 20190102
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        _flatten(root);
    }
    
private:
    TreeNode *_flatten(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }
        
        TreeNode *leftLast = _flatten(root->left);
        TreeNode *rightLast = _flatten(root->right);
        if (leftLast != nullptr) {
            leftLast->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        
        if (rightLast != nullptr) {
            return rightLast;
        }
        if (leftLast != nullptr) {
            return leftLast;
        }
        return root;
    }
};

// LeetCode 114 - Flattern Binary Tree to Linked List, 
// Iteration, Preorder Traversal, 20190102
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode *node = st.top();
            st.pop();
            if (node->right != nullptr) {
                st.push(node->right);
            }
            if (node->left != nullptr) {
                st.push(node->left);
            }
            
            node->left = nullptr;
            node->right = nullptr;
            if (!st.empty()) {
                node->right = st.top();
            }
        }
    }
};

// LeetCode 230 - Kth Smallest Element in a BST, 
// Iteration, Inorder Traversal, 20190103
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode *root, int k) {
        if (root == nullptr) {
            return -1;
        }
        
        stack<TreeNode *> st;
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
        
        for (int i = 0; i < k - 1; i++) {
            if (st.empty()) {
                return -1;
            }
            TreeNode *node = st.top();
            if (node->right != nullptr) {
                node = node->right;
                while (node != nullptr) {
                    st.push(node);
                    node = node->left;
                }
            } else {
                node = st.top();
                st.pop();
                while (!st.empty() && st.top()->right == node) {
                    node = st.top();
                    st.pop();
                }
            }
        }

        return st.empty() ? -1 : st.top()->val;
    }
};

// LeetCode 230 - Kth Smallest Element in a BST, 
// Depth-first Search, Divide and Conquer, 20190102
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode *root, int k) {
        if (root == nullptr) {
            return -1;
        }
        
        unordered_map<TreeNode *, int> numNodes;
        _countNodes(root, numNodes);
        return _quickSelect(root, k, numNodes);
    }
    
private:
    int _countNodes(TreeNode *root, 
                    unordered_map<TreeNode *, int> &numNodes) {
        if (root == nullptr) {
            return 0;
        }
        
        int left = _countNodes(root->left, numNodes);
        int right = _countNodes(root->right, numNodes);
        int sum = left + right + 1;
        numNodes[root] = sum;
        return sum;
    }
    
    int _quickSelect(TreeNode *root, int k, 
                     unordered_map<TreeNode *, int> &numNodes) {
        if (root == nullptr) {
            return -1;
        }
        
        int left = root->left == nullptr ? 0 : numNodes[root->left];
        if (left == k - 1) {
            return root->val;
        }
        if (left > k - 1) {
            return _quickSelect(root->left, k, numNodes);
        }
        return _quickSelect(root->right, k - left - 1, numNodes);
    }
};

// LeetCode 173 - Binary Search Tree Iterator, 
// Iteration, Inorder Traversal, 20190103
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
    stack<TreeNode *> st;
    
public:
    BSTIterator(TreeNode* root) {
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode *curr = st.top();
        if (curr->right != nullptr) {
            TreeNode *node = curr->right;
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
        } else {
            TreeNode *node = st.top();
            st.pop();
            while (!st.empty() && st.top()->right == node) {
                node = st.top();
                st.pop();
            }
        }
        
        return curr->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !st.empty();
    }
};

// LintCode 86 - Binary Search Tree Iterator, 
// Iteration, Inorder Traversal, 20190103
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 * Example of iterate a tree:
 * BSTIterator iterator = BSTIterator(root);
 * while (iterator.hasNext()) {
 *    TreeNode * node = iterator.next();
 *    do something for node
 */
class BSTIterator {
private:
    stack<TreeNode *> st;
    
public:
    BSTIterator(TreeNode *root) {
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
    }

    bool hasNext() {
        return !st.empty();
    }

    TreeNode *next() {
        TreeNode *curr = st.top();
        if (curr->right != nullptr) {
            TreeNode *node = curr->right;
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
        } else {
            TreeNode *node = st.top();
            st.pop();
            while (!st.empty() && st.top()->right == node) {
                node = st.top();
                st.pop();
            }
        }
        
        return curr;
    }
};

// LeetCode 285 - Inorder Successor in BST, 20190103
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
        if (root == nullptr) {
            return nullptr;
        }
        
        TreeNode *successor = nullptr;
        while (root != nullptr && root->val != p->val) {
            if (p->val < root->val) {
                successor = root;
                root = root->left;
            } else {
                root = root->right;
            }
        }
        
        if (root == nullptr) {
            return nullptr;
        }
        if (root->right == nullptr) {
            return successor;
        }
        root = root->right;
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }
};

// LeetCode 94 - Binary Tree Inorder Traversal, 
// Iteration, Inorder Traversal-1, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> st;
        while (!st.empty() || root != nullptr) {
            if (root != nullptr) {
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                st.pop();
                result.push_back(root->val);
                root = root->right;
            }
        }
        
        return result;
    }
};

// LeetCode 94 - Binary Tree Inorder Traversal, 
// Iteration, Inorder Traversal-2, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> st;
        while (!st.empty() || root != nullptr) {
            while (root != nullptr) {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            result.push_back(root->val);
            root = root->right;
        }
        
        return result;
    }
};

// LeetCode 94 - Binary Tree Inorder Traversal, 
// Iteration, Inorder Traversal-3, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> st;
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
        while (!st.empty()) {
            root = st.top();
            result.push_back(root->val);
            if (root->right != nullptr) {
                root = root->right;
                while (root != nullptr) {
                    st.push(root);
                    root = root->left;
                }
            } else {
                root = st.top();
                st.pop();
                while (!st.empty() && st.top()->right == root) {
                    root = st.top();
                    st.pop();
                }
            }
        }
        
        return result;
    }
};

// LeetCode 144 - Binary Tree Preorder Traversal, 
// Iteration, Preorder Traversal-1, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty()) {
            root = st.top();
            st.pop();
            result.push_back(root->val);
            if (root->right != nullptr) {
                st.push(root->right);
            }
            if (root->left != nullptr) {
                st.push(root->left);
            }
        }
        
        return result;
    }
};

// LeetCode 144 - Binary Tree Preorder Traversal, 
// Iteration, Preorder Traversal-2, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty()) {
            result.push_back(root->val);
            if (root->right != nullptr) {
                st.push(root->right);
            }
            if (root->left != nullptr) {
                root = root->left;
            } else {
                root = st.top();
                st.pop();
            }
        }
        
        return result;
    }
};

// LeetCode 145 - Binary Tree Postorder Traversal, 
// Iteration, Postorder Traversal, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> st;
        st.push(root);
        TreeNode *prev = nullptr, *curr = nullptr;
        while (!st.empty()) {
            curr = st.top();
            if (prev == nullptr || 
                prev->left == curr || prev->right == curr) {
                if (curr->left != nullptr) {
                    st.push(curr->left);
                } else if (curr->right != nullptr) {
                    st.push(curr->right);
                }
            } else if (curr->left == prev) {
                if (curr->right != nullptr) {
                    st.push(curr->right);
                }
            } else {
                result.push_back(curr->val);
                st.pop();
            }
            prev = curr;
        }
        
        return result;
    }
};

// LeetCode 270 - Closest Binary Search Tree Value, 
// Depth-first Search, Divide and Conquer, 20190110
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode *root, double target) {
        if (root == nullptr) {
            return -1;
        }
        
        TreeNode *lower = _lowerBound(root, target);
        TreeNode *upper = _upperBound(root, target);
        if (lower == nullptr && upper == nullptr) {
            return -1;
        }
        if (lower == nullptr) {
            return upper->val;
        }
        if (upper == nullptr) {
            return lower->val;
        }
        
        if (upper->val - target < target - lower->val) {
            return upper->val;
        }
        return lower->val;
    }
    
private:
    TreeNode *_lowerBound(TreeNode *root, double target) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (target <= root->val) {
            return _lowerBound(root->left, target);
        }
        
        TreeNode *lower = _lowerBound(root->right, target);
        if (lower != nullptr) {
            return lower;
        }
        
        return root;
    }
    
    TreeNode *_upperBound(TreeNode *root, double target) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (target > root->val) {
            return _upperBound(root->right, target);
        }
        
        TreeNode *upper = _upperBound(root->left, target);
        if (upper != nullptr) {
            return upper;
        }
        
        return root;
    }
};

// LeetCode 272 - Closest Binary Search Tree Value II, 
// Iteration, Inorder Traversal, 20190111
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> closestKValues(TreeNode *root, double target, int k) {
        vector<int> result;
        if (k == 0 || root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> lowerSt;
        _getStack(root, target, lowerSt);
        stack<TreeNode *> upperSt(lowerSt);
        if (target <= lowerSt.top()->val) {
            _moveLower(lowerSt);
        } else {
            _moveUpper(upperSt);
        }
        
        for (int i = 0; i < k; i++) {
            if (lowerSt.empty() || !upperSt.empty() && 
                upperSt.top()->val - target <= 
                target - lowerSt.top()->val) {
                result.push_back(upperSt.top()->val);
                _moveUpper(upperSt);
            } else {
                result.push_back(lowerSt.top()->val);
                _moveLower(lowerSt);
            }
        }
        
        return result;
    }
    
private:
    void _getStack(TreeNode *root, double target, 
                   stack<TreeNode *> &st) {
        while (root != nullptr) {
            st.push(root);
            
            if (target <= root->val) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
    }
    
    void _moveUpper(stack<TreeNode *> &st) {
        TreeNode *node = st.top();
        if (node->right != nullptr) {
            node = node->right;
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
        } else {
            node = st.top();
            st.pop();
            while (!st.empty() && st.top()->right == node) {
                node = st.top();
                st.pop();
            }
        }
    }
    
    void _moveLower(stack<TreeNode *> &st) {
        TreeNode *node = st.top();
        if (node->left != nullptr) {
            node = node->left;
            while (node != nullptr) {
                st.push(node);
                node = node->right;
            }
        } else {
            node = st.top();
            st.pop();
            while (!st.empty() && st.top()->left == node) {
                node = st.top();
                st.pop();
            }
        }
    }
};

// LeetCode 700 - Search in a Binary Search Tree, 20190111
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *searchBST(TreeNode *root, int val) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (val == root->val) {
            return root;
        }
        if (val < root->val) {
            return searchBST(root->left, val);
        }
        if (val > root->val) {
            return searchBST(root->right, val);
        }
    }
};

// LintCode 11 - Search Range in Binary Search Tree, 
// Depth-first Search, 20190111
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    vector<int> searchRange(TreeNode *root, int k1, int k2) {
        vector<int> results;
        if (root == nullptr || k1 > k2) {
            return results;
        }
        
        _searchRange(root, k1, k2, results);
        return results;
    }
    
private:
    void _searchRange(TreeNode *root, int k1, int k2, 
                      vector<int> &results) {
        if (root == nullptr) {
            return;
        }
        
        if (k1 < root->val) {
            _searchRange(root->left, k1, k2, results);
        }
        if (k1 <= root->val && root->val <= k2) {
            results.push_back(root->val);
        }
        if (k2 > root->val) {
            _searchRange(root->right, k1, k2, results);
        }
    }
};

// LeetCode 701 - Insert into a Binary Search Tree, 20190111
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        if (val <= root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            root->right = insertIntoBST(root->right, val);
        }
        
        return root;
    }
};

// LintCode 85 - Insert Node in a Binary Search Tree, 20190111
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    TreeNode *insertNode(TreeNode *root, TreeNode *node) {
        if (root == nullptr) {
            return node;
        }
        
        if (root->val > node->val) {
            root->left = insertNode(root->left, node);
        } else {
            root->right = insertNode(root->right, node);
        }
        
        return root;
    }
};

// LintCode 87 - Remove Node in Binary Search Tree, 20190111
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    TreeNode * removeNode(TreeNode * root, int value) {
        TreeNode *dummy = new TreeNode(0);
        dummy->left = root;
        
        TreeNode *parent = _findNode(dummy, root, value);
        TreeNode *node = nullptr;
        if (parent->left != nullptr && parent->left->val == value) {
            node = parent->left;
        } else if (parent->right != nullptr && parent->right->val == value) {
            node = parent->right;
        } else {
            return dummy->left;
        }
        
        _deleteNode(parent, node);
        
        return dummy->left;
    }
    
private:
    TreeNode *_findNode(TreeNode *parent, TreeNode *node, int value) {
        if (node == nullptr) {
            return parent;
        }
        
        if (node->val == value) {
            return parent;
        }
        if (value < node->val) {
            return _findNode(node, node->left, value);
        } else {
            return _findNode(node, node->right, value);
        }
    }
    
    void _deleteNode(TreeNode *parent, TreeNode *node) {
        if (node->right == nullptr) {
            if (parent->left == node) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
        } else {
            TreeNode *temp = node->right;
            TreeNode *father = node;
            
            while (temp->left != nullptr) {
                father = temp;
                temp = temp->left;
            }
            
            if (father->left == temp) {
                father->left = temp->right;
            } else {
                father->right = temp->right;
            }
            
            if (parent->left == node) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
            
            temp->left = node->left;
            temp->right = node->right;
        }
    }
};
