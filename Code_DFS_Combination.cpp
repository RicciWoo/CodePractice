/******************** DFS on Combination ********************/

// Subsets
class Solution {
public:
    /**
     * @param nums: A set of numbers
     * @return: A list of lists
     */
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> results;
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

// Subsets II
class Solution {
public:
    /**
     * @param nums: A set of numbers.
     * @return: A list of lists. All valid subsets.
     */
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());
        vector<int> subset;
        _subsetsWithDup(nums, 0, subset, results);
        return results;
    }
    
private:
    void _subsetsWithDup(vector<int> &nums, int index, 
                         vector<int> &subset, 
                         vector<vector<int>> &results) {
        results.push_back(subset);
        
        for (int i = index; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1] && i > index) {
                continue;
            }
            subset.push_back(nums[i]);
            _subsetsWithDup(nums, i + 1, subset, results);
            subset.pop_back();
        }
    }
};

// Combinations
class Solution {
public:
    /**
     * @param n: Given the range of numbers
     * @param k: Given the numbers of combinations
     * @return: All the combinations of k numbers out of 1..n
     */
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> results;
        vector<int> combination;
        _combine(n, k, 1, combination, results);
        return results;
    }
    
private:
    void _combine(int n, int k, int index, vector<int> combination, 
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

// Combination Sum
class Solution {
public:
    /**
     * @param candidates: A list of integers
     * @param target: An integer
     * @return: A list of lists of integers
     */
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        _combinationSum(candidates, 0, target, combination, results);
        return results;
    }
    
private:
    void _combinationSum(vector<int> &candidates, int index, int target, 
                         vector<int> &combination, vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] > target) {
                break;
            }
            
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            combination.push_back(candidates[i]);
            _combinationSum(candidates, i, target - candidates[i], combination, results);
            combination.pop_back();
        }
    }
};

// Combination Sum II
class Solution {
public:
    /**
     * @param candidates: Given the candidate numbers
     * @param target: Given the target number
     * @return: All the combinations that sum to target
     */
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        _combinationSum(candidates, 0, target, combination, results);
        return results;
    }
    
private:
    void _combinationSum(vector<int> &candidates, int index, int target, 
                         vector<int> &combination, vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] > target) {
                break;
            }
            
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            combination.push_back(candidates[i]);
            _combinationSum(candidates, i + 1, target - candidates[i], combination, results);
            combination.pop_back();
        }
    }
};

// k Sum II
class Solution {
public:
    /*
     * @param A: an integer array
     * @param k: a postive integer <= length(A)
     * @param target: an integer
     * @return: A list of lists of integer
     */
    vector<vector<int>> kSumII(vector<int> &A, int k, int target) {
        vector<vector<int>> results;
        vector<int> combination;
        _kSumII(A, k, target, 0, combination, results);
        return results;
    }
    
private:
    void _kSumII(vector<int> &A, int k, int target, int index, 
                 vector<int> &combination, 
                 vector<vector<int>> &results) {
        if (k == 0 && target == 0) {
            results.push_back(combination);
            return;
        }
        
        if (k < 0 || target < 0 || index == A.size()) {
            return;
        }
        
        _kSumII(A, k, target, index + 1, combination, results);
        combination.push_back(A[index]);
        _kSumII(A, k - 1, target - A[index], index + 1, combination, results);
        combination.pop_back();
    }
};

// Palindrome Partitioning
class Solution {
public:
    /*
     * @param s: A string
     * @return: A list of lists of string
     */
    vector<vector<string>> partition(string &s) {
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
            string subString = s.substr(index, i - index + 1);
            if (!_isPalindrome(subString)) {
                continue;
            }
            partition.push_back(subString);
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

// Palindrome Partitioning
class Solution {
public:
    /*
     * @param s: A string
     * @return: A list of lists of string
     */
    vector<vector<string>> partition(string &s) {
        vector<vector<string>> results;
        if (s.empty()) {
            return results;
        }
        
        int n = s.size();
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        _getIsPalindrome(s, isPalindrome);
        
        vector<int> partition;
        _partition(s, 0, partition, isPalindrome, results);
        return results;
    }
    
private:
    void _getIsPalindrome(string s, vector<vector<bool>> &isPalindrome) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
        }
        
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1] && 
                                     s[i] == s[j];
            }
        }
    }

    void _partition(string &s, int index, vector<int> &partition, 
                    vector<vector<bool>> &isPalindrome, 
                    vector<vector<string>> &results) {
        if (index == s.size()) {
            _addResult(s, partition, results);
            return;
        }
        
        for (int i = index; i < s.size(); i++) {
            string subString = s.substr(index, i - index + 1);
            if (!isPalindrome[index][i]) {
                continue;
            }
            partition.push_back(i);
            _partition(s, i + 1, partition, isPalindrome, results);
            partition.pop_back();
        }
    }
    
    void _addResult(string &s, vector<int> &partition, 
                    vector<vector<string>> &results) {
        vector<string> result;
        int index = 0;
        for (int i = 0; i < partition.size(); i++) {
            result.push_back(s.substr(index, partition[i] - index + 1));
            index = partition[i] + 1;
        }
        results.push_back(result);
    }
};

// Wildcard Matching
class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    bool isMatch(string &s, string &p) {
        if (s.empty()) {
            return _allStar(p, 0);
        }
        if (p.empty()) {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> memo(m, vector<bool>(n, false));
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        return _isMatch(s, 0, p, 0, memo, visited);
    }
    
private:
    bool _isMatch(string &s, int sIndex, string &p, int pIndex, 
                  vector<vector<bool>> &memo, 
                  vector<vector<bool>> &visited) {
        if (sIndex == s.size()) {
            return _allStar(p, pIndex);
        }
        
        if (pIndex == p.size()) {
            return false;
        }
        
        if (visited[sIndex][pIndex]) {
            return memo[sIndex][pIndex];
        }
        
        char sChar = s[sIndex];
        char pChar = p[pIndex];
        bool match = false;
        
        if (pChar == '*') {
            match = _isMatch(s, sIndex, p, pIndex + 1, memo, visited) || 
                    _isMatch(s, sIndex + 1, p, pIndex, memo, visited);
        } else {
            match = _charMatch(sChar, pChar) && 
                    _isMatch(s, sIndex + 1, p, pIndex + 1, memo, visited);
        }
        
        visited[sIndex][pIndex] = true;
        memo[sIndex][pIndex] = match;
        return match;
    }
    
    bool _charMatch(char &sChar, char pChar) {
        return (sChar == pChar || pChar == '?');
    }
    
    bool _allStar(string &p, int pIndex) {
        for (int i = pIndex; i < p.size(); i++) {
            if (p[i] != '*') {
                return false;
            }
        }
        return true;
    }
};

// Regular Expression Matching
class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "." and "*"
     * @return: A boolean
     */
    bool isMatch(string &s, string &p) {
        if (s.empty()) {
            return _isEmpty(p, 0);
        }
        if (p.empty()) {
            return false;
        }
        
        int m = s.size(), n = p.size();
        vector<vector<bool>> memo(m, vector<bool>(n, false));
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        return _isMatch(s, 0, p, 0, memo, visited);
    }
    
private:
    bool _isMatch(string &s, int sIndex, string &p, int pIndex, 
                  vector<vector<bool>> &memo, 
                  vector<vector<bool>> &visited) {
        if (sIndex == s.size()) {
            return _isEmpty(p, pIndex);
        }
        
        if (pIndex == p.size()) {
            return false;
        }
        
        if (visited[sIndex][pIndex]) {
            return memo[sIndex][pIndex];
        }
        
        char sChar = s[sIndex];
        char pChar = p[pIndex];
        bool match = false;
        
        if (pIndex + 1 < p.size() && p[pIndex + 1] == '*') {
            match = _isMatch(s, sIndex, p, pIndex + 2, memo, visited) || 
                    _charMatch(sChar, pChar) && 
                    _isMatch(s, sIndex + 1, p, pIndex, memo, visited);
        } else {
            match = _charMatch(sChar, pChar) && 
                    _isMatch(s, sIndex + 1, p, pIndex + 1, memo, visited);
        }
        
        visited[sIndex][pIndex] = true;
        memo[sIndex][pIndex] = match;
        return match;
    }
    
    bool _charMatch(char &sChar, char pChar) {
        return (sChar == pChar || pChar == '.');
    }
    
    bool _isEmpty(string &p, int pIndex) {
        for (int i = pIndex; i < p.size(); i += 2) {
            if (i + 1 > p.size() || p[i + 1] != '*') {
                return false;
            }
        }
        return true;
    }
};

// Split String
class Solution {
public:
    /*
     * @param : a string to be split
     * @return: all possible split string array
     */
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

// Word Break II
class Solution {
public:
    /*
     * @param s: A string
     * @param wordDict: A set of words.
     * @return: All possible sentences.
     */
    vector<string> wordBreak(string &s, unordered_set<string> &wordDict) {
        unordered_map<string, vector<string>> memo;
        return _wordBreak(s, wordDict, memo);
    }
    
private:
    vector<string> _wordBreak(string s, unordered_set<string> &dict, 
                              unordered_map<string, vector<string>> &memo) {
        if (memo.count(s)) {
            return memo[s];
        }
        
        vector<string> results;
        
        if (s.empty()) {
            return results;
        }
        
        if (dict.count(s)) {
            results.push_back(s);
        }
        
        for (int len = 1; len < s.size(); len++) {
            string word = s.substr(0, len);
            if (!dict.count(word)) {
                continue;
            }
            
            string suffix = s.substr(len);
            vector<string> segmentations = _wordBreak(suffix, dict, memo);
            
            for (string segmentation : segmentations) {
                results.push_back(word + " " + segmentation);
            }
        }
        
        memo[s] = results;
        return results;
    }
};
