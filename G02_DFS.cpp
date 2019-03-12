/******************** DFS ********************/

// Depth of Tree, Depth-first Search
class Solution {
public:
	int depth(TreeNode *root) {
		if (root == NULL) return 0;
		return max(depth(root->left), depth(root->right)) + 1;
	}
};

// Balanced Binary Tree-1, Depth-first Search
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        if (root == NULL) return true;
        if (abs(getDepth(root->left) - getDepth(root->right)) > 1)
            return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
    
    int getDepth(TreeNode *root) {
        if (root == NULL) return 0;
        return max(getDepth(root->left), getDepth(root->right)) + 1;
    }
};

// Balanced Binary Tree-2, Depth-first Search, with special number -1
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return _depth(root) != -1;
    }
    
private:
    int _depth(TreeNode *root) {
        if (root == NULL) return 0;
        int leftDepth = _depth(root->left);
        int rightDepth = _depth(root->right);
        if (abs(leftDepth - rightDepth) > 1 || 
            leftDepth == -1 || rightDepth == -1) {
            return -1;
        }
        return max(leftDepth, rightDepth) + 1;
    }
};

// Symmetric Tree, Depth_first Search
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        return _isSymmetric(root->left, root->right);
    }
    
private:
    bool _isSymmetric(TreeNode *left, TreeNode *right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        if (left->val != right->val) return false;
        return _isSymmetric(left->left, right->right) && 
               _isSymmetric(left->right, right->left);
    }
};

// Minimum Depth of Binary Tree, Depth-first Search
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int leftDepth = minDepth(root->left);
        int rightDepth = minDepth(root->right);
        if (leftDepth == 0)
            return rightDepth + 1;
        else if (rightDepth == 0)
            return leftDepth + 1;
        return min(leftDepth, rightDepth) + 1;
    }
};

// Path Sum, Depth-first Search
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == NULL) return false;
        if (root->left == NULL && root->right == NULL) {
            if (root->val == sum)
                return true;
            else
                return false;
        }
        return hasPathSum(root->left, sum - root->val) ||
               hasPathSum(root->right, sum - root->val);
    }
};

// Binary Tree Maximum Path Sum, Depth-first Search
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

// Word Search, Depth-first Search
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0 || board[0].size() == 0)
            return false;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> flags(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (_exist(board, word, i, j, 0, flags))
                    return true;
        return false;
    }
    
private:
    bool _exist(vector<vector<char>> &board, string &word, int x, 
                int y, int index, vector<vector<bool>> &flags) {
        if (index == word.size()) return true;
        if (x < 0 || x >= board.size() || 
            y < 0 || y >= board[0].size() || 
            flags[x][y] || board[x][y] != word[index])
            return false;
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            flags[x][y] = true;
            if (_exist(board, word, x + dx[i], y + dy[i], 
                       index + 1, flags))
                return true;
            flags[x][y] = false;
        }
        return false;
    }
};

// Palindrome Partitioning, Depth-first Search
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<string> temp;
        _partition(s, 0, temp, results);
        return results;
    }
    
private:
    void _partition(string &s, int index, vector<string> &temp, 
                    vector<vector<string>> &results) {
        if (index == s.size()) {
            results.push_back(temp);
            return;
        }
        for (int i = index; i < s.size(); i++) {
            string sub = s.substr(index, i - index + 1);
            if (_isPalindrome(sub)) {
                temp.push_back(sub);
                _partition(s, i + 1, temp, results);
                temp.pop_back();
            }
        }
    }
    
    bool _isPalindrome(string s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--)
            if (s[i] != s[j]) return false;
        return true;
    }
};

// Remove Invalid Parentheses-1, Depth-first Search
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> results;
        int maxLen = 0;
        _dfs(s, "", 0, 0, maxLen, results);
        return results;
    }
    
private:
    void _dfs(string s, string sub, int left, int temMax, 
              int &maxLen, vector<string> &results) {
        if (s.size() == 0) {
            if (left == 0) {
                if (temMax > maxLen) {
                    maxLen = temMax;
                    results.clear();
                }
                if (temMax == maxLen && find(results.begin(), 
                    results.end(), sub) == results.end())
                    results.insert(results.end(), sub);
            }
            return;
        }
        if (s[0] == '(') {
            _dfs(s.substr(1), sub + "(", left + 1, temMax + 1, 
                 maxLen, results);
            _dfs(s.substr(1), sub, left, temMax, maxLen, results);
        } else if (s[0] == ')') {
            if (left > 0)
                _dfs(s.substr(1), sub + ")", left - 1, temMax, 
                     maxLen, results);
            _dfs(s.substr(1), sub, left, temMax, maxLen, results);
        } else {
            string letter = s.substr(0, 1);
            _dfs(s.substr(1), sub + letter, left, temMax, maxLen, 
                 results);
        }
    }
};

// Remove Invalid Parentheses-2, Depth-first Search, 20180821
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> resSet;
        int maxLen = 0;
        _dfs(s, "", 0, 0, maxLen, resSet);
        vector<string> results(resSet.begin(), resSet.end());
        return results;
    }
    
private:
    void _dfs(string s, string sub, int left, int temMax, 
              int &maxLen, unordered_set<string> &resSet) {
        if (s.size() == 0) {
            if (left == 0) {
                if (temMax > maxLen) {
                    maxLen = temMax;
                    resSet.clear();
                }
                if (temMax == maxLen)
                    resSet.insert(resSet.end(), sub);
            }
            return;
        }
        if (s[0] == '(') {
            _dfs(s.substr(1), sub + "(", left + 1, temMax + 1, 
                 maxLen, resSet);
            _dfs(s.substr(1), sub, left, temMax, maxLen, resSet);
        } else if (s[0] == ')') {
            if (left > 0)
                _dfs(s.substr(1), sub + ")", left - 1, temMax, 
                     maxLen, resSet);
            _dfs(s.substr(1), sub, left, temMax, maxLen, resSet);
        } else {
            string letter = s.substr(0, 1);
            _dfs(s.substr(1), sub + letter, left, temMax, maxLen, 
                 resSet);
        }
    }
};

// Coin Change, Depth-first Search
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        int minCnt = INT_MAX;
        if (_coinChange(coins, amount, 
                        coins.size() - 1, 0, minCnt))
            return minCnt;
        return -1;
    }
    
private:
    bool _coinChange(vector<int> &coins, int rest, 
                     int index, int cnt, int &minCnt) {
        if (rest < 0) return false;
        if (rest == 0) {
            if (cnt < minCnt) minCnt = cnt;
            return true;
        }
        if (cnt >= minCnt) return false;  // pruning
        for (int i = index; i >= 0; i--)
            if (_coinChange(coins, rest - coins[i], i, 
                            cnt + 1, minCnt))
                return true;
        return false;
    }
};
