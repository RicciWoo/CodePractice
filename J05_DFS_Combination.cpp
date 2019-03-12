/******************** DFS on Combination ********************/

// LeetCode 78 - Subsets, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.empty()) {
            return results;
        }
        
        vector<int> subset;
        _subsets(nums, 0, subset, results);
        return results;
    }
    
private:
    void _subsets(vector<int> &nums, int index, 
                  vector<int> &subset, 
                  vector<vector<int>> &results) {
        results.push_back(subset);
        
        for (int i = index; i < nums.size(); i++) {
            subset.push_back(nums[i]);
            _subsets(nums, i + 1, subset, results);
            subset.pop_back();
        }
    }
};

// LintCode 17 - Subsets, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.empty()) {
            results.push_back(vector<int>());
            return results;
        }
        
        sort(nums.begin(), nums.end());
        vector<int> subset;
        _subsets(nums, 0, subset, results);
        return results;
    }
    
private:
    void _subsets(vector<int> &nums, int index, 
                  vector<int> &subset, 
                  vector<vector<int>> &results) {
        results.push_back(subset);
        
        for (int i = index; i < nums.size(); i++) {
            subset.push_back(nums[i]);
            _subsets(nums, i + 1, subset, results);
            subset.pop_back();
        }
    }
};

// LeetCode 90 - Subsets II, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.empty()) {
            return results;
        }
        
        sort(nums.begin(), nums.end());
        vector<int> subset;
        _subsets(nums, 0, subset, results);
        return results;
    }
    
private:
    void _subsets(vector<int> &nums, int index, 
                  vector<int> &subset, 
                  vector<vector<int>> &results) {
        results.push_back(subset);
        
        for (int i = index; i < nums.size(); i++) {
            if (i > index && nums[i] == nums[i - 1]) {
                continue;
            }
            
            subset.push_back(nums[i]);
            _subsets(nums, i + 1, subset, results);
            subset.pop_back();
        }
    }
};

// LeetCode 77 - Combinations, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> results;
        if (n <= 0 || k <= 0 || n < k) {
            return results;
        }
        
        vector<int> combination;
        _combine(n, k, 1, combination, results);
        return results;
    }
    
private:
    void _combine(int n, int k, int index, 
                  vector<int> &combination, 
                  vector<vector<int>> &results) {
        if (combination.size() == k) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i <= n; i++) {
            combination.push_back(i);
            _combine(n, k, i + 1, combination, results);
            combination.pop_back();
        }
    }
};

// LeetCode 39 - Combination Sum, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, 
                                       int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        
        vector<int> combination;
        _combination(candidates, 0, target, combination, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int index, 
                      int target, vector<int> &combination, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i < candidates.size(); i++) {
            if (target < candidates[i]) {
                continue;  // unsorted, need to check the next
            }
            
            combination.push_back(candidates[i]);
            _combination(candidates, i, target - candidates[i], 
                         combination, results);
            combination.pop_back();
        }
    }
};

// LintCode 135 - Combination Sum, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, 
                                       int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        _combination(candidates, 0, target, combination, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int index, 
                      int target, vector<int> &combination, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i < candidates.size(); i++) {
            if (target < candidates[i]) {
                break;  // for sorted candidates, pruning
            }
            
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            combination.push_back(candidates[i]);
            _combination(candidates, i, target - candidates[i], 
                         combination, results);
            combination.pop_back();
        }
    }
};

// LeetCode 40 - Combination Sum II, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, 
                                        int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        _combination(candidates, 0, target, combination, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int index, 
                      int target, vector<int> &combination, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i < candidates.size(); i++) {
            if (target < candidates[i]) {
                break;  // for sorted candidates, pruning
            }
            
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            combination.push_back(candidates[i]);
            _combination(candidates, i + 1, target - candidates[i], 
                         combination, results);
            combination.pop_back();
        }
    }
};

// LintCode 90 - k Sum II, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<int>> kSumII(vector<int> &A, int k, int target) {
        vector<vector<int>> results;
        if (A.empty()) {
            return results;
        }
        
        vector<int> combination;
        _kSum(A, 0, k, target, combination, results);
        return results;
    }
    
private:
    void _kSum(vector<int> &A, int index, int k, int target, 
               vector<int> &combination, 
               vector<vector<int>> &results) {
        if (k == 0 && target == 0) {
            results.push_back(combination);
            return;
        }
        
        if (k < 0 || target < 0 || index == A.size()) {
            return;
        }
        
        _kSum(A, index + 1, k, target, combination, results);
        combination.push_back(A[index]);
        _kSum(A, index + 1, k - 1, target - A[index], 
              combination, results);
        combination.pop_back();
    }
};

// LeetCode 131 - Palindrome Partitioning, Depth-first Search, 20190118
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        if (s.empty()) {
            return results;
        }
        
        vector<string> partition;
        _partition(s, 0, partition, results);
        return results;
    }
    
private:
    void _partition(string &s, int index, vector<string> &partition, 
                    vector<vector<string>> &results) {
        if (index == s.size()) {
            results.push_back(partition);
            return;
        }
        
        for (int i = index; i < s.size(); i++) {
            string sub = s.substr(index, i - index + 1);
            if (!_isPalindrome(sub)) {
                continue;
            }
            
            partition.push_back(sub);
            _partition(s, i + 1, partition, results);
            partition.pop_back();
        }
    }
    
    bool _isPalindrome(string &s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        
        return true;
    }
};

// LeetCode 131 - Palindrome Partitioning, 
// Depth-first Search and preprocess, 20190119
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        if (s.empty()) {
            return results;
        }
        
        int n = s.size();
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        _getIsPalindrome(s, isPalindrome);
        
        vector<string> partition;
        _partition(s, 0, isPalindrome, partition, results);
        return results;
    }
    
private:
    void _getIsPalindrome(string &s, 
                          vector<vector<bool>> &isPalindrome) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = s[i] == s[i + 1];
        }
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                isPalindrome[i][j] = s[i] == s[j] && 
                                     isPalindrome[i + 1][j - 1];
            }
        }
    }
    
    void _partition(string &s, int index, 
                    vector<vector<bool>> &isPalindrome, 
                    vector<string> &partition, 
                    vector<vector<string>> &results) {
        if (index == s.size()) {
            results.push_back(partition);
            return;
        }
        
        for (int i = index; i < s.size(); i++) {
            if (!isPalindrome[index][i]) {
                continue;
            }
            
            string sub = s.substr(index, i - index + 1);
            partition.push_back(sub);
            _partition(s, i + 1, isPalindrome, partition, results);
            partition.pop_back();
        }
    }
};

// LeetCode 132 - Palindrome Partitioning II, 
// Dynamic Programming and preprocess, 20190119
class Solution {
public:
    int minCut(string s) {
        if (s.size() <= 1) {
            return 0;
        }
        
        int n = s.size();
        vector<vector<bool>> isPalindr(n, vector<bool>(n, false));
        _getIsPalindr(s, isPalindr);
        
        vector<int> segs(n + 1, INT_MAX);
        segs[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (isPalindr[j][i - 1]) {
                    segs[i] = min(segs[i], segs[j] + 1);
                }
            }
        }
        
        return segs[n] - 1;
    }
    
private:
    void _getIsPalindr(string &s, vector<vector<bool>> &isPalindr) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            isPalindr[i][i] = true;
        }
        for (int i = 0; i < n - 1; i++) {
            isPalindr[i][i + 1] = s[i] == s[i + 1];
        }
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                isPalindr[i][j] = s[i] == s[j] && 
                                  isPalindr[i + 1][j - 1];
            }
        }
    }
};

// LeetCode 44 - Wildcard Matching, 
// Depth-first Search and memoization, 20190119
class Solution {
public:
    bool isMatch(string s, string p) {
        if (s.empty()) {
            return _allStars(p, 0);
        }
        if (p.empty()) {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> memo(m, vector<bool>(n, false));
        vector<vector<bool>> done(m, vector<bool>(n, false));
        return _isMatch(s, 0, p, 0, memo, done);
    }
    
private:
    bool _allStars(string &p, int j) {
        for (int i = j; i < p.size(); i++) {
            if (p[i] != '*') {
                return false;
            }
        }
        return true;
    }
    
    bool _isMatch(string &s, int i, string &p, int j, 
                  vector<vector<bool>> &memo, 
                  vector<vector<bool>> &done) {
        if (i == s.size()) {
            return _allStars(p, j);
        }
        if (j == p.size()) {
            return false;
        }
        if (done[i][j]) {
            return memo[i][j];
        }
        
        char a = s[i], b = p[j];
        bool match = false;
        if (b == '*') {
            match = _isMatch(s, i + 1, p, j, memo, done) ||
                    _isMatch(s, i, p, j + 1, memo, done);
        } else {
            match = (a == b || b == '?') && 
                    _isMatch(s, i + 1, p, j + 1, memo, done);
        }
        
        done[i][j] = true;
        memo[i][j] = match;
        return match;
    }
};

// LeetCode 44 - Wildcard Matching, Dynamic Programming, 20190121
class Solution {
public:
    bool isMatch(string s, string p) {
        if (s.empty()) {
            return _allStars(p);
        }
        if (p.empty()) {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> opt(m + 1, 
                                 vector<bool>(n + 1, false));
        opt[0][0] = true;
        for (int j = 1; j <= n; j++) {
            opt[0][j] = opt[0][j - 1] && p[j - 1] == '*';
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    opt[i][j] = opt[i - 1][j] || opt[i][j - 1];
                } else {
                    opt[i][j] = opt[i - 1][j - 1] && 
                        (s[i - 1] == p[j - 1] || p[j - 1] == '?');
                }
            }
        }
        
        return opt[m][n];
    }
    
private:
    bool _allStars(string &p) {
        for (int i = 0; i < p.size(); i++) {
            if (p[i] != '*') {
                return false;
            }
        }
        return true;
    }
};

// LeetCode 10 - Regular Expression Matching, 
// Depth-first Search and Memoization, 20190121
class Solution {
public:
    bool isMatch(string s, string p) {
        if (s.empty()) {
            return _isEmpty(p, 0);
        }
        if (p.empty()) {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> memo(m, vector<bool>(n, false));
        vector<vector<bool>> done(m, vector<bool>(n, false));
        return _isMatch(s, 0, p, 0, memo, done);
    }
    
private:
    bool _isEmpty(string &p, int j) {
        for (int i = j; i < p.size(); i += 2) {
            if (i + 1 >= p.size() || p[i + 1] != '*') {
                return false;
            }
        }
        return true;
    }
    
    bool _isMatch(string &s, int i, string &p, int j, 
                  vector<vector<bool>> &memo, 
                  vector<vector<bool>> &done) {
        if (i == s.size()) {
            return _isEmpty(p, j);
        }
        if (j == p.size()) {
            return false;
        }
        if (done[i][j]) {
            return memo[i][j];
        }
        
        char a = s[i], b = p[j];
        bool match = false;
        if (j + 1 < p.size() && p[j + 1] == '*') {
            match = _isMatch(s, i, p, j + 2, memo, done) || 
                    _charMatch(a, b) && 
                    _isMatch(s, i + 1, p, j, memo, done);
        } else {
            match = _charMatch(a, b) && 
                    _isMatch(s, i + 1, p, j + 1, memo, done);
        }
        
        done[i][j] = true;
        memo[i][j] = match;
        return match;
    }
    
    bool _charMatch(char &a, char &b) {
        return a == b || b == '.';
    }
};

// LeetCode 10 - Regular Expression Matching, 
// Dynamic Programming, 20190121
class Solution {
public:
    bool isMatch(string s, string p) {
        if (s.empty()) {
            return _isEmpty(p);
        }
        if (p.empty() || p[0] == '*') {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> opt(m + 1, 
                                 vector<bool>(n + 1, false));
        opt[0][0] = true;
        for (int j = 2; j <= n; j++) {
            opt[0][j] = opt[0][j - 2] && p[j - 1] == '*';
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (j > 1 && p[j - 1] == '*') {
                    opt[i][j] = opt[i][j - 2] || opt[i - 1][j] && 
                        _charMatch(s[i - 1], p[j - 2]);
                } else {
                    opt[i][j] = opt[i - 1][j - 1] && 
                        _charMatch(s[i - 1], p[j - 1]);
                }
            }
        }
        
        return opt[m][n];
    }
    
private:
    bool _isEmpty(string &p) {
        for (int i = 0; i < p.size(); i += 2) {
            if (i + 1 >= p.size() || p[i + 1] != '*') {
                return false;
            }
        }
        return true;
    }
    
    bool _charMatch(char a, char b) {
        return a == b || b == '.';
    }
};

// LeetCode 10 - Regular Expression Matching, 
// Dynamic Programming, 20190121
class Solution {
public:
    bool isMatch(string s, string p) {
        if (s.empty()) {
            return _isEmpty(p);
        }
        if (p.empty() || p[0] == '*') {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> opt(m + 1, 
                                 vector<bool>(n + 1, false));
        opt[m][n] = true;
        for (int j = n - 2; j >= 0; j--) {
            opt[m][j] = opt[m][j + 2] && p[j + 1] == '*';
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                bool match = s[i] == p[j] || p[j] == '.';
                if (j + 1 < n && p[j + 1] == '*') {
                    opt[i][j] = opt[i][j + 2] || 
                                opt[i + 1][j] && match;
                } else {
                    opt[i][j] = opt[i + 1][j + 1] && match;
                }
            }
        }
        
        return opt[0][0];
    }
    
private:
    bool _isEmpty(string &p) {
        for (int i = 0; i < p.size(); i += 2) {
            if (i + 1 >= p.size() || p[i + 1] != '*') {
                return false;
            }
        }
        return true;
    }
};

// LintCode 680 - Split String, Depth-first Search, 20190122
class Solution {
public:
    vector<vector<string>> splitString(string& s) {
        vector<vector<string>> results;
        vector<string> path;
        _splitString(s, 0, path, results);
        return results;
    }
    
private:
    void _splitString(string &s, int index, vector<string> &path, 
                      vector<vector<string>> &results) {
        if (index == s.size()) {
            results.push_back(path);
            return;
        }
        
        for (int i = 1; i <= 2; i++) {
            if (index + i > s.size()) {
                break;
            }
            path.push_back(s.substr(index, i));
            _splitString(s, index + i, path, results);
            path.pop_back();
        }
    }
};

// LeetCode 140 - Word Break II, 
// Depth-first Search and Memoization, 20190123
class Solution {
public:
    vector<string> wordBreak(string s, 
                             vector<string> &wordDict) {
        vector<string> results;
        if (s.empty() || wordDict.empty()) {
            return results;
        }
        
        unordered_set<string> dict(wordDict.begin(), 
                                   wordDict.end());
        unordered_map<string, vector<string>> memo;
        return _wordBreak(s, dict, memo);
    }
    
private:
    vector<string> _wordBreak(string &s, 
            unordered_set<string> &dict, 
            unordered_map<string, vector<string>> &memo) {
        vector<string> results;
        if (s.empty()) {
            return results;
        }
        if (memo.count(s)) {
            return memo[s];
        }
        if (dict.count(s)) {
            results.push_back(s);
        }
        
        for (int len = 1; len <= s.size(); len++) {
            string sub = s.substr(0, len);
            if (!dict.count(sub)) {
                continue;
            }
            
            string suf = s.substr(len);
            vector<string> segs = _wordBreak(suf, dict, memo);
            for (string &seg : segs) {
                results.push_back(sub + " " + seg);
            }
        }
        
        memo[s] = results;
        return results;
    }
};

// LintCode 582 - Word Break II, 
// Depth-first Search and Memoization, 20190123
class Solution {
public:
    vector<string> wordBreak(string &s, 
                             unordered_set<string> &wordDict) {
        vector<string> results;
        if (s.empty() || wordDict.empty()) {
            return results;
        }
        
        unordered_map<string, vector<string>> memo;
        return _wordBreak(s, wordDict, memo);
    }
    
private:
    vector<string> _wordBreak(string &s, 
            unordered_set<string> &dict, 
            unordered_map<string, vector<string>> &memo) {
        vector<string> results;
        if (s.empty()) {
            return results;
        }
        if (memo.count(s)) {
            return memo[s];
        }
        if (dict.count(s)) {
            results.push_back(s);
        }
        
        for (int len = 1; len <= s.size(); len++) {
            string sub = s.substr(0, len);
            if (!dict.count(sub)) {
                continue;
            }
            
            string suf = s.substr(len);
            vector<string> segs = _wordBreak(suf, dict, memo);
            for (string &seg : segs) {
                results.push_back(sub + " " + seg);
            }
        }
        
        memo[s] = results;
        return results;
    }
};

// LeetCode 139 - Word Break, Dynamic Programming, 20190228
class Solution {
public:
    bool wordBreak(string s, vector<string> &wordDict) {
        if (s.empty()) {
            return true;
        }
        if (wordDict.empty()) {
            return false;
        }
        
        unordered_set<string> dict(wordDict.begin(),
                                      wordDict.end());
        int n = s.size();
        vector<bool> opt(n + 1);
        opt[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (opt[j] && 
                        dict.count(s.substr(j, i - j))) {
                    opt[i] = true;
                    break;
                }
            }
        }
        
        return opt[n];
    }
};

// LintCode 107 - Word Break, Dynamic Programming, 20190228
class Solution {
public:
    bool wordBreak(string &s, unordered_set<string> &dict) {
        if (s.empty()) {
            return true;
        }
        if (dict.empty()) {
            return false;
        }
        
        int n = s.size();
        vector<bool> opt(n + 1);
        opt[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (opt[j] && 
                        dict.count(s.substr(j, i - j))) {
                    opt[i] = true;
                    break;
                }
            }
        }
        
        return opt[n];
    }
};
