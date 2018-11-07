/******************** Tree based DFS ********************/

// Maximum Depth of Binary Tree
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

// Balanced Binary Tree
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
     * @return: True if this Binary tree is Balanced, or false.
     */
    bool isBalanced(TreeNode *root) {
        bool isBalanced = true;
        int depth = _maxDepth(root, isBalanced);
        return isBalanced;
    }
    
private:
    int _maxDepth(TreeNode *root, bool &isBalanced) {
        if (root == nullptr) {
            isBalanced = true;
            return 0;
        }
        
        bool leftBalanced = true;
        int leftDepth = _maxDepth(root->left, leftBalanced);
        bool rightBalanced = true;
        int rightDepth = _maxDepth(root->right, rightBalanced);
        
        if (!leftBalanced || !rightBalanced) {
            isBalanced = false;
            return -1;
        }
        
        if (abs(leftDepth - rightDepth) > 1) {
            isBalanced = false;
            return -1;
        }
        
        isBalanced = true;
        return max(leftDepth, rightDepth) + 1;
    }
};

// Subtree with Maximum Average

// Invert Binary Tree

// Validate Binary Search Tree
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
     * @return: True if the binary tree is BST, or false
     */
    bool isValidBST(TreeNode *root) {
        TreeNode *lastNode = nullptr;
        bool isValid = true;
        _inorder(root, lastNode, isValid);
        
        return isValid;
    }
    
private:
    void _inorder(TreeNode *root, TreeNode *&lastNode, bool &isValid) {
        if (root == nullptr) {
            return;
        }
        
        _inorder(root->left, lastNode, isValid);
        if (lastNode != nullptr && lastNode->val >= root->val) {
            isValid = false;
            return;
        }
        lastNode = root;
        _inorder(root->right, lastNode, isValid);
    }
};

// Minimum Subtree
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
     * @param root: the root of binary tree
     * @return: the root of the minimum subtree
     */
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
        
        int leftSum = _findSubtree(root->left, subtree, minSum);
        int rightSum = _findSubtree(root->right, subtree, minSum);
        
        int sum = leftSum + rightSum + root->val;
        if (sum < minSum) {
            minSum = sum;
            subtree = root;
        }
        return sum;
    }
};

// Binary Tree Paths
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
     * @param root: the root of the binary tree
     * @return: all root-to-leaf paths
     */
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

// Lowest Common Ancestor II
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
    /*
     * @param root: The root of the tree
     * @param A: node in the tree
     * @param B: node in the tree
     * @return: The lowest common ancestor of A and B
     */
    ParentTreeNode *lowestCommonAncestorII(ParentTreeNode *root, 
                                           ParentTreeNode *A, 
                                           ParentTreeNode *B) {
        vector<ParentTreeNode *> pathA = _getPath2Root(A);
        vector<ParentTreeNode *> pathB = _getPath2Root(B);
        
        int indexA = pathA.size() - 1;
        int indexB = pathB.size() - 1;
        
        ParentTreeNode *lowestAncestor = nullptr;
        while (indexA >= 0 && indexB >= 0) {
            if (pathA[indexA] != pathB[indexB]) {
                break;
            }
            lowestAncestor = pathA[indexA];
            indexA--;
            indexB--;
        }
        
        return lowestAncestor;
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

// Lowest Common Ancestor
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
    /*
     * @param root: The root of the binary search tree.
     * @param A: A TreeNode in a Binary.
     * @param B: A TreeNode in a Binary.
     * @return: Return the least common ancestor(LCA) of the two nodes.
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, 
                                   TreeNode *A, 
                                   TreeNode *B) {
        if (root == nullptr || root == A || root == B) {
            return root;
        }
        
        TreeNode *left = lowestCommonAncestor(root->left, A, B);
        TreeNode *right = lowestCommonAncestor(root->right, A, B);
        
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

// Lowest Common Ancestor III
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
class ResultType {
public:
    bool a_exist, b_exist;
    TreeNode *node;
    ResultType(bool a, bool b, TreeNode *n) {
        a_exist = a;
        b_exist = b;
        node = n;
    }
};
class Solution {
public:
    /*
     * @param root: The root of the binary tree.
     * @param A: A TreeNode
     * @param B: A TreeNode
     * @return: Return the LCA of the two nodes.
     */
    TreeNode *lowestCommonAncestor3(TreeNode *root, 
                                    TreeNode *A, TreeNode *B) {
        ResultType *rt = _lca(root, A, B);
        if (rt->a_exist && rt->b_exist) {
            return rt->node;
        } else {
            return nullptr;
        }
    }
    
private:
    ResultType *_lca(TreeNode *root, TreeNode *A, TreeNode *B) {
        if (root == nullptr) {
            return new ResultType(false, false, nullptr);
        }
        
        ResultType *left_rt = _lca(root->left, A, B);
        ResultType *right_rt = _lca(root->right, A, B);
        
        bool a_exist = left_rt->a_exist || right_rt->a_exist || root == A;
        bool b_exist = left_rt->b_exist || right_rt->b_exist || root == B;
        
        if (root == A || root == B) {
            return new ResultType(a_exist, b_exist, root);
        }
        
        if (left_rt->node != nullptr && right_rt->node != nullptr) {
            return new ResultType(a_exist, b_exist, root);
        }
        if (left_rt->node != nullptr) {
            return new ResultType(a_exist, b_exist, left_rt->node);
        }
        if (right_rt->node != nullptr) {
            return new ResultType(a_exist, b_exist, right_rt->node);
        }
        
        return new ResultType(a_exist, b_exist, nullptr);
    }
};

// Flattern Binary Tree to Linked List
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
     * @param root: a TreeNode, the root of the binary tree
     * @return: nothing
     */
    void flatten(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        _flatten(root);
    }
    
private:
    // flatten root and return the last node
    TreeNode *_flatten(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }
        
        TreeNode *leftLast = _flatten(root->left);
        TreeNode *rightLast = _flatten(root->right);
        
        // connect leftLast to root.right
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

// Kth Smallest Element in BST
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
     * @param root: the given BST
     * @param k: the given k
     * @return: the kth smallest element in BST
     */
    int kthSmallest(TreeNode * root, int k) {
        stack<TreeNode *> myStack;
        
        while (root != nullptr) {
            myStack.push(root);
            root = root->left;
        }
        
        for (int i = 0; i < k - 1; i++) {
            TreeNode *node = myStack.top();
            
            if (node->right != nullptr) {
                node = node->right;
                while (node != nullptr) {
                    myStack.push(node);
                    node = node->left;
                }
            } else {
                node = myStack.top();
                myStack.pop();
                while (!myStack.empty() && myStack.top()->right == node) {
                    node = myStack.top();
                    myStack.pop();
                }
            }
        }
        
        return myStack.top()->val;
    }
};

// Kth Smallest Element in BST
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
     * @param root: the given BST
     * @param k: the given k
     * @return: the kth smallest element in BST
     */
    int kthSmallest(TreeNode *root, int k) {
        unordered_map<TreeNode *, int> numOfChildren;
        _countNodes(root, numOfChildren);
        return _quickSelectOnTree(root, k, numOfChildren);
    }
    
private:
    int _countNodes(TreeNode *root, 
                   unordered_map<TreeNode *, int> &numOfChildren) {
        if (root == nullptr) {
            return 0;
        }
        
        int left = _countNodes(root->left, numOfChildren);
        int right = _countNodes(root->right, numOfChildren);
        int numNodes = left + right + 1;
        numOfChildren[root] = numNodes;
        return numNodes;
    }
    
    int _quickSelectOnTree(TreeNode *root, int k, 
                           unordered_map<TreeNode *, int> &numOfChildren) {
        if (root == nullptr) {
            return -1;
        }
        
        int left = root->left == nullptr ? 0 : numOfChildren[root->left];
        if (left >= k) {
            return _quickSelectOnTree(root->left, k, numOfChildren);
        }
        if (left + 1 == k) {
            return root->val;
        }
        
        return _quickSelectOnTree(root->right, k - left - 1, numOfChildren);
    }
};

// Binary Search Tree Iterator
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
public:
    /*
    * @param root: The root of binary tree.
    */BSTIterator(TreeNode *root) {
        while (root != nullptr) {
            myStack.push(root);
            root = root->left;
        }
    }

    /*
     * @return: True if there has next node, or false
     */
    bool hasNext() {
        return !myStack.empty();
    }

    /*
     * @return: return next node
     */
    TreeNode *next() {
        TreeNode *curr = myStack.top();
        if (curr->right != nullptr) {
            TreeNode *node = curr->right;
            while (node != nullptr) {
                myStack.push(node);
                node = node->left;
            }
        } else {
            TreeNode *node = myStack.top();
            myStack.pop();
            while (!myStack.empty() && myStack.top()->right == node) {
                node = myStack.top();
                myStack.pop();
            }
        }
        
        return curr;
    }
    
private:
    stack<TreeNode *> myStack;
};

// Inorder Successor in Binary Search Tree
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
    /*
     * @param root: The root of the BST.
     * @param p: You need find the successor node of p.
     * @return: Successor of p.
     */
    TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
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

// Validate Binary Search Tree (Iteration)

// Binary Tree Inorder Traversal (Iteration)
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
     * @param root: A Tree
     * @return: Inorder in ArrayList which contains node values.
     */
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        TreeNode *node = root;
        stack<TreeNode *> nStack;
        while (!nStack.empty() || node != nullptr) {
            if (node != nullptr) {
                nStack.push(node);
                node = node->left;
            } else {
                node = nStack.top();
                nStack.pop();
                result.push_back(node->val);
                node = node->right;
            }
        }
        
        return result;
    }
};

// Binary Tree Inorder Traversal (Iteration)
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
     * @param root: A Tree
     * @return: Inorder in ArrayList which contains node values.
     */
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> nStack;
        while (root != nullptr) {
            nStack.push(root);
            root = root->left;
        }
        
        while (!nStack.empty()) {
            TreeNode *node = nStack.top();
            result.push_back(node->val);
            
            if (node->right != nullptr) {
                node = node->right;
                while (node != nullptr) {
                    nStack.push(node);
                    node = node->left;
                }
            } else {
                node = nStack.top();
                nStack.pop();
                while (!nStack.empty() && nStack.top()->right == node) {
                    node = nStack.top();
                    nStack.pop();
                }
            }
        }
        
        return result;
    }
};

// Binary Tree Preorder Traversal (Iteration)
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
     * @param root: A Tree
     * @return: Preorder in ArrayList which contains node values.
     */
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        TreeNode *node = root;
        stack<TreeNode *> nStack;
        while (!nStack.empty() || node != nullptr) {
            if (node != nullptr) {
                result.push_back(node->val);
                if (node->right != nullptr) {
                    nStack.push(node->right);
                }
                node = node->left;
            } else {
                node = nStack.top();
                nStack.pop();
            }
        }
        
        return result;
    }
};

// Binary Tree Preorder Traversal (Iteration)
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
     * @param root: A Tree
     * @return: Preorder in ArrayList which contains node values.
     */
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> nStack;
        nStack.push(root);
        while (!nStack.empty()) {
            TreeNode *node = nStack.top();
            nStack.pop();
            result.push_back(node->val);
            if (node->right != nullptr) {
                nStack.push(node->right);
            }
            if (node->left != nullptr) {
                nStack.push(node->left);
            }
        }
        
        return result;
    }
};

// Binary Tree Postorder Traversal (Iteration)
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
     * @param root: A Tree
     * @return: Postorder in ArrayList which contains node values.
     */
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        TreeNode *prev = nullptr;
        TreeNode *curr = root;
        stack<TreeNode *> nStack;
        nStack.push(root);
        while (!nStack.empty()) {
            curr = nStack.top();
            if (prev == nullptr || prev->left == curr || prev->right == curr) {
                // traverse down the tree
                if (curr->left != nullptr) {
                    nStack.push(curr->left);
                } else if (curr->right != nullptr) {
                    nStack.push(curr->right);
                }
            } else if (curr->left == prev) {
                // traverse up the tree from the left
                if (curr->right != nullptr) {
                    nStack.push(curr->right);
                }
            } else {
                // traverse up the tree from the right
                result.push_back(curr->val);
                nStack.pop();
            }
            prev = curr;
        }
        
        return result;
    }
};

// Closest Binary Search Tree Value
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
     * @param root: the given BST
     * @param target: the given target
     * @return: the value in the BST that is closest to the target
     */
    int closestValue(TreeNode * root, double target) {
        if (root == nullptr) {
            return 0;
        }
        
        TreeNode *lowerNode = _lowerBound(root, target);
        TreeNode *upperNode = _upperBound(root, target);
        
        if (lowerNode == nullptr) {
            return upperNode->val;
        }
        if (upperNode == nullptr) {
            return lowerNode->val;
        }
        
        if (target - lowerNode->val > upperNode->val - target) {
            return upperNode->val;
        }
        return lowerNode->val;
    }
    
private:
    TreeNode *_lowerBound(TreeNode *root, double target) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (target <= root->val) {
            return _lowerBound(root->left, target);
        }
        
        // target > root->val
        TreeNode *lowerNode = _lowerBound(root->right, target);
        if (lowerNode != nullptr) {
            return lowerNode;
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
        
        // target <= root.val
        TreeNode *upperNode = _upperBound(root->left, target);
        if (upperNode != nullptr) {
            return upperNode;
        }
        
        return root;
    }
};

// Closest Binary Search Tree Value II
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
     * @param root: the given BST
     * @param target: the given target
     * @param k: the given k
     * @return: k values in the BST that are closest to the target
     */
    vector<int> closestKValues(TreeNode *root, double target, int k) {
        vector<int> result;
        if (k == 0 || root == nullptr) {
            return result;
        }
        
        stack<TreeNode *> lowerStack;
        _getStack(root, target, lowerStack);
        stack<TreeNode *> upperStack(lowerStack);
        
        if (target < lowerStack.top()->val) {
            _moveLower(lowerStack);
        } else {
            _moveUpper(upperStack);
        }
        
        for (int i = 0; i < k; i++) {
            if (lowerStack.empty() || !upperStack.empty() && 
                target - lowerStack.top()->val > upperStack.top()->val - target) {
                result.push_back(upperStack.top()->val);
                _moveUpper(upperStack);
            } else {
                result.push_back(lowerStack.top()->val);
                _moveLower(lowerStack);
            }
        }
        
        return result;
    }
    
private:
    void _getStack(TreeNode *root, double target, stack<TreeNode *> &nStack) {
        while (root != nullptr) {
            nStack.push(root);
            
            if (target < root->val) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
    }
    
    void _moveUpper(stack<TreeNode *> &nStack) {
        TreeNode *node = nStack.top();
        if (node->right == nullptr) {
            node = nStack.top();
            nStack.pop();
            while (!nStack.empty() && nStack.top()->right == node) {
                node = nStack.top();
                nStack.pop();
            }
            return;
        }
        
        node = node->right;
        while (node != nullptr) {
            nStack.push(node);
            node = node->left;
        }
    }
    
    void _moveLower(stack<TreeNode *> &nStack) {
        TreeNode *node = nStack.top();
        if (node->left == nullptr) {
            node = nStack.top();
            nStack.pop();
            while (!nStack.empty() && nStack.top()->left == node) {
                node = nStack.top();
                nStack.pop();
            }
            return;
        }
        
        node = node->left;
        while (node != nullptr) {
            nStack.push(node);
            node = node->right;
        }
    }
};

// Search Range in Binary Search Tree

// Insert Node in a Binary Search Tree

// Remove Node in Binary Search Tree

