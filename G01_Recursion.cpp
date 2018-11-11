/******************** Recursion ********************/

// LeetCode 89 - Gray Code, Recursion
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        if (n < 0) return result;
        _grayCode(n, result);
        return result;
    }
    
private:
    void _grayCode(int n, vector<int> &result) {
        if (n == 0) {
            result.push_back(0);
            return;
        }
        _grayCode(n - 1, result);
        int highBit = 1 << (n - 1);
        int currSize = result.size();
        for (int i = currSize - 1; i >= 0; i--) {
            result.push_back(result[i] + highBit);
        }
    }
};

// LeetCode 717 - 1-bit and 2-bit Characters, Recursion
class Solution {
public:
    bool isOneBitCharacter(vector<int> &bits) {
        if (bits.empty()) {
            return false;
        }
        
        return _isOneBitChar(bits, 0);
    }
    
private:
    bool _isOneBitChar(vector<int> &bits, int index) {
        if (index >= bits.size()) {
            return false;
        }
        if (index == bits.size() - 1) {
            return true;
        }
        
        if (bits[index] == 0) {
            return _isOneBitChar(bits, index + 1);
        }
        return _isOneBitChar(bits, index + 2);
    }
};

// Maze, Recursion
class Solution {
public:
    bool solveMaze(vector<vector<char>> &maze, int startX, int startY, 
                   int targetX, int targetY) {
        if (startX == targetX && startY == targetY) {
            return true;
        }

        maze[startX][startY] = 'X';
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int newX = startX + dx[i], newY = startY + dy[i];
            if (newX < 0 || newX >= maze.size() || 
                newY < 0 || newY >= maze[0].size() || 
                maze[newX][newY] == 'X') {
                continue;
            }
            if (solveMaze(maze, newX, newY, targetX, targetY)) {
                return true;
            }
        }
        return false;
    }
};

// LeetCode 39 - Combination Sum, Knapsack, Recursion, 
class Solution {
public:
    vector<vector<int>> combinationSum(
                    vector<int> &candidates, int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        
        vector<int> combination;
        _combination(candidates, target, 0, combination, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int target, 
                      int index, vector<int> &combination, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }
        
        for (int i = index; i < candidates.size(); i++) {
            if (target < condidates[i]) {
                continue;  // unsorted, need to check following 
            }
            
            combination.push_back(candidates[i]);
            _combination(candidates, target - candidates[i], 
                         i, combination, results);
            combination.pop_back();
        }
    }
};

// LeetCode 40 - Combination Sum II, Knapsack II, Recursion
class Solution {
public:
    vector<vector<int>> combinationSum2(
                    vector<int>& candidates, int target) {
        vector<vector<int>> results;
        if (candidates.empty()) {
            return results;
        }
        
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        _combination(candidates, target, 0, combination, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int target, 
                      int index, vector<int> &combination, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(combination);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            if (target < candidates[i]) {
                break;  // for sorted candidates, pruning
            }
            
            combination.push_back(candidates[i]);
            _combination(candidates, target - candidates[i], 
                         i + 1, combination, results);
            combination.pop_back();
        }
    }
};

// LeetCode 216 - Combination Sum III, Recursion
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> results;
        vector<int> combination;
        _combination(k, n, 1, combination, results);
        return results;
    }
    
private:
    void _combination(int k, int n, int index, 
                      vector<int> &combination, 
                      vector<vector<int>> &results) {
        if (n == 0 && combination.size() == k) {
            results.push_back(combination);
            return;
        }
        if (combination.size() >= k) {
            return;
        }
            
        for (int i = index; i <= 9; i++) {
            if (n < i) {
                break;  // sorted, pruning
            }
            
            combination.push_back(i);
            _combination(k, n - i, i + 1, combination, results);
            combination.pop_back();
        }
    }
};

// LeetCode 377 - Combination Sum IV, Dynamic Programming
class Solution {
public:
    int combinationSum4(vector<int> &nums, int target) {
        if (nums.empty()) {
            return 0;
        }
        
        vector<int> combs(target + 1, 0);
        combs[0] = 1;  // not 0
        for (int i = 1; i <= target; i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i - nums[j] >= 0) {
                    combs[i] += combs[i - nums[j]];
                }
            }
        }
        
        return combs[target];
    }
};

// LeetCode 77. Combinations, Recursion
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

// LeetCode 254. Factor Combinations, Recursion
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> results;
        if (n <= 1) {
            return results;
        }
        
        vector<int> factors;
        _getFactores(n, n, 2, factors, results);
        return results;
    }
    
private:
    void _getFactores(int n, int r, int index, 
                     vector<int> &factors, 
                     vector<vector<int>> &results) {
        if (r == 1) {
            results.push_back(factors);
            return;
        }

        for (int i = index; i < n; i++) {
            if (r < i) {
                break;  // sorted, pruning
            }
            
            if (r % i == 0) {
                factors.push_back(i);
                _getFactores(n, r / i, i, factors, results);
                factors.pop_back();
            }
        }
    }
};

// 0-1 Knapsack, Recursion
class Solution {
public:
    bool knapsack(int s, vector<int> &weights) {
        return _knapsack(s, weights, 0);
    }

private:
	bool _knapsack(int s, vector<int> &weights, int index) {
		if (s == 0) {
            return true;
        }
		if (s < 0 || index == weights.size()) {
            return false;
        }

		return _knapsack(s, weights, index + 1) ||
		       _knapsack(s - weights[index], weights, index + 1);
	}
};

// 0-1 Knapsack II, Recursion
class Solution {
public:
    int knapsack(int s, vector<int> &weights) {
        return _knapsack(s, weights, 0);
    }

private:
    int _knapsack(int s, vector<int> &weights, int index) {
        if (s == 0 || index == weights.size()) {
            return 0;
        }
        if (s < weights[index]) {
            return _knapsack(s, weights, index + 1);
        }

        return max(_knapsack(s, weights, index + 1), weights[index] + 
                   _knapsack(s - weights[index], weights, index + 1));
    }
};

// LeetCode 46 - Permutations, Recursion
class Solution {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> result;
        if (nums.size() <= 1) {
            result.push_back(nums);
            return result;
        }
        
        vector<int> permutation;
        vector<bool> visited(nums.size(), false);
        _permute(nums, visited, permutation, result);
        return result;
    }
    
private:
    void _permute(vector<int> &nums, vector<bool> &visited, 
                  vector<int> &permutation, 
                  vector<vector<int>> &result) {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) {
                continue;
            }
            
            visited[i] = true;
            permutation.push_back(nums[i]);
            _permute(nums, visited, permutation, result);
            visited[i] = false;
            permutation.pop_back();
        }
    }
};

// LeetCode 46 - Permutations, Recursion and Swap
class Solution {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.size() <= 1) {
            results.push_back(nums);
            return results;
        }
        
        _permute(nums, 0, results);
        return results;
    }
    
private:
    void _permute(vector<int> &nums, int index, 
                  vector<vector<int>> &results) {
        if (index == nums.size()) {
            results.push_back(nums);
            return;
        }
        
        for (int i = index; i < nums.size(); i++) {
            swap(nums[index], nums[i]);
            _permute(nums, index + 1, results);
            swap(nums[index], nums[i]);
        }
    }
};

// LeetCode 47 - Permutation II, Recursion
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> result;
        if (nums.size() <= 1) {
            result.push_back(nums);
            return result;
        }
        
        sort(nums.begin(), nums.end());
        vector<int> permutation;
        vector<bool> visited(nums.size(), false);
        _permute(nums, visited, permutation, result);
        return result;
    }
    
private:
    void _permute(vector<int> &nums, vector<bool> &visited, 
                  vector<int> &permutation,
                  vector<vector<int>> &result) {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) {
                continue;
            }
            if (i > 0 && nums[i] == nums[i - 1] && 
                                !visited[i - 1]) {
                continue;
            }
            
            visited[i] = true;
            permutation.push_back(nums[i]);
            _permute(nums, visited, permutation, result);
            visited[i] = false;
            permutation.pop_back();
        }
    }
};

// LeetCode 78 - Subsets, Combination, Recursion
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
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

// LeetCode 90 - Subsets II, Combination II, Recursion
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
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

// Lucky Number, Recursion, 20180818
class Solution {
public:
    vector<string> luckyNumbers(string num, int target) {
        vector<string> results;
        string temp;
        _luckyNumber(num, target, 0, 0, 0, temp, results);
        return results;
    }

private:
    void _luckyNumber(string &num, int target, int index, int curr,
                      int last, string temp, vector<string> &results) {
        if (index == num.size()) {
            if (curr == target) {
                results.push_back(temp);
            }
            return;
        }
        for (int i = index; i < num.size(); i++) {
            if (num[index] == '0' && i != index) {
                return;
            }
            string m = num.substr(index, i - index + 1);
            long n = stol(m);
            if (index == 0) {
                _luckyNumber(num, target, i + 1, n, n, temp + m, results);
            }
            else {
                _luckyNumber(num, target, i + 1, curr + n, n, 
                                                temp + "+" + m, results);
                _luckyNumber(num, target, i + 1, curr - n, -n, 
                                                temp + "-" + m, results);
                _luckyNumber(num, target, i + 1, curr - last + last * n, 
                                        last * n, temp + "*" + m, results);
                if (n != 0 && last % n == 0) {
                    _luckyNumber(num, target, i + 1, curr - last + last / n, 
                                        last / n, temp + "/" + m, results);
                }
            }
        }
    }
};

// LeetCode 17 - Letter Combinations of a Phone Number, Recursion
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> results;
        if (digits.empty()) {
            return results;
        }
        
        string comb;
        _letterComb(digits, 0, comb, results);
        return results;
    }
    
private:
    vector<string> dict{" ", "", "abc", "def", "ghi", 
                        "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    void _letterComb(string &digits, int index, 
                     string &comb, vector<string> &results) {
        if (index == digits.size()) {
            results.push_back(comb);
            return;
        }
        
        int k = digits[index] - '0';
        for (int i = 0; i < dict[k].size(); i++) {
            comb.push_back(dict[k][i]);
            _letterComb(digits, index + 1, comb, results);
            comb.pop_back();
        }
    }
};

// LeetCode 51 - N-Queens, Depth-first Search
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        if (n <= 0) {
            return results;
        }
        
        vector<int> cols;
        _placeQueens(n, cols, results);
        return results;
    }
    
private:
    void _placeQueens(int n, vector<int> &cols, 
                      vector<vector<string>> &results) {
        if (cols.size() == n) {
            _drawChessboard(cols, results);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (!_isValid(cols, col)) {
                continue;
            }
            
            cols.push_back(col);
            _placeQueens(n, cols, results);
            cols.pop_back();
        }
    }
    
    void _drawChessboard(vector<int> &cols, 
                         vector<vector<string>> &results) {
        vector<string> chessboard;
        for (int row = 0; row < cols.size(); row++) {
            string qInRow;
            for (int col = 0; col < cols.size(); col++) {
                qInRow += (col == cols[row] ? 'Q' : '.');
            }
            chessboard.push_back(qInRow);
        }
        results.push_back(chessboard);
    }
    
    bool _isValid(vector<int> &cols, int currCol) {
        int currRow = cols.size();
        for (int row = 0; row < cols.size(); row++) {
            if (cols[row] == currCol) {
                return false;
            }
            if (row + cols[row] == currRow + currCol) {
                return false;
            }
            if (row - cols[row] == currRow - currCol) {
                return false;
            }
        }
        return true;
    }
};

// LeetCode 52 - N-Queens II, Depth-first Search
class Solution {
public:
    int totalNQueens(int n) {
        if (n <= 0) {
            return 0;
        }
        
        int total = 0;
        vector<int> cols;
        _placeQueens(n, cols, total);
        return total;
    }
    
private:
    void _placeQueens(int n, vector<int> &cols, int &total) {
        if (cols.size() == n) {
            total++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (!_isValid(cols, col)) {
                continue;
            }
            
            cols.push_back(col);
            _placeQueens(n, cols, total);
            cols.pop_back();
        }
    }
    
    bool _isValid(vector<int> &cols, int currCol) {
        int currRow = cols.size();
        for (int row = 0; row < cols.size(); row++) {
            if (cols[row] == currCol) {
                return false;
            }
            if (row + cols[row] == currRow + currCol) {
                return false;
            }
            if (row - cols[row] == currRow - currCol) {
                return false;
            }
        }
        return true;
    }
};

// LeetCode 131. Palindrome Partitioning
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<string> parts;
        if (s.size() <= 1) {
            parts.push_back(s);
            results.push_back(parts);
            return results;
        }
        
        _partition(s, 0, parts, results);
        return results;
    }
    
private:
    void _partition(string &s, int index, 
                    vector<string> &parts, 
                    vector<vector<string>> &results) {
        if (index == s.size()) {
            results.push_back(parts);
            return;
        }
        
        for (int i = index; i < s.size(); i++) {
            string sub = s.substr(index, i - index + 1);
            if (!_isPalindrome(sub)) {
                continue;
            }
            
            parts.push_back(sub);
            _partition(s, i + 1, parts, results);
            parts.pop_back();
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

// LeetCode 131. Palindrome Partitioning
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<string> parts;
        if (s.size() <= 1) {
            parts.push_back(s);
            results.push_back(parts);
            return results;
        }
        
        int n = s.size();
        vector<vector<bool>> isPalindr(n, 
                        vector<bool>(n, false));
        _getIsPalindr(s, isPalindr);
        
        _partition(s, 0, isPalindr, parts, results);
        return results;
    }
    
private:
    void _getIsPalindr(string &s, 
                       vector<vector<bool>> &isPalindr) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            isPalindr[i][i] = true;
        }
        for (int i = 0; i < n - 1; i++) {
            isPalindr[i][i + 1] = (s[i] == s[i + 1]);
        }
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                isPalindr[i][j] = s[i] == s[j] && 
                                  isPalindr[i + 1][j - 1];
            }
        }
    }
    
    void _partition(string &s, int index, 
                    vector<vector<bool>> &isPalindr, 
                    vector<string> &parts, 
                    vector<vector<string>> &results) {
        if (index == s.size()) {
            results.push_back(parts);
            return;
        }
        
        for (int i = index; i < s.size(); i++) {
            if (!isPalindr[index][i]) {
                continue;
            }
            
            string sub = s.substr(index, i - index + 1);
            parts.push_back(sub);
            _partition(s, i + 1, isPalindr, parts, results);
            parts.pop_back();
        }
    }
};

// LeetCode 132. Palindrome Partitioning II
class Solution {
public:
    int minCut(string s) {
        if (s.size() <= 1) {
            return 0;
        }
        
        int n = s.size();
        vector<vector<bool>> isPalindr(n, vector<bool>(n, false));
        _getIsPalindr(s, isPalindr);
        
        vector<int> parts(n + 1, INT_MAX);
        parts[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (isPalindr[j][i - 1]) {
                    parts[i] = min(parts[i], parts[j] + 1);
                }
            }
        }
        
        return parts[n] - 1;
    }
    
private:
    void _getIsPalindr(string &s, 
                       vector<vector<bool>> &isPalindr) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            isPalindr[i][i] = true;
        }

        for (int i = 0; i < n - 1; i++) {
            isPalindr[i][i + 1] = (s[i] == s[i + 1]);
        }

        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                isPalindr[i][j] = (s[i] == s[j]) && 
                                  isPalindr[i + 1][j - 1];
            }
        }
    }
};

// LeetCode 36 -  Valid Sudoku
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<bool> used(9);
        
        // check rows
        for (int i = 0; i < 9; i++) {
            fill(used.begin(), used.end(), false);
            for (int j = 0; j < 9; j++) {
                if (!_isValid(used, board[i][j])) {
                    return false;
                }
            }
        }
        
        // check columns
        for (int i = 0; i < 9; i++) {
            fill(used.begin(), used.end(), false);
            for (int j = 0; j < 9; j++) {
                if (!_isValid(used, board[j][i])) {
                    return false;
                }
            }
        }
        
        // check sub-boxes
        for (int i = 0; i < 9; i++) {
            fill(used.begin(), used.end(), false);
            int r = (i / 3) * 3, c = (i % 3) * 3;
            for (int j = 0; j < 9; j++) {
                int x = r + j / 3, y = c + j % 3;
                if (!_isValid(used, board[x][y])) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
private:
    bool _isValid(vector<bool> &used, char digit) {
        if (digit == '.') {
            return true;
        }

        if (used[digit - '1']) {
            return false;
        }

        used[digit - '1'] = true;
        return true;
    }
};

// LeetCode 37 - Sudoku Solver
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        _solveSudoku(board);
    }
    
private:
    bool _solveSudoku(vector<vector<char>> &board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    continue;
                }
                
                for (int k = 0; k < 9; k++) {
                    board[i][j] = '1' + k;
                    if (_isValidSudoku(board, i, j) && 
                                _solveSudoku(board)) {
                        return true;
                    }
                    board[i][j] = '.';
                }
                return false;
            }
        }
        return true;
    }
    
private:
    bool _isValidSudoku(vector<vector<char>> &board, 
                                        int x, int y) {
        vector<bool> used(9, false);
        
        // check rows
        for (int j = 0; j < 9; j++) {
            if (!_isValid(used, board[x][j])) {
                return false;
            }
        }
        
        // check columns
        fill(used.begin(), used.end(), false);
        for (int i = 0; i < 9; i++) {
            if (!_isValid(used, board[i][y])) {
                return false;
            }
        }
        
        // check sub-boxes
        fill(used.begin(), used.end(), false);
        int r = (x / 3) * 3, c = (y / 3) * 3;
        for (int k = 0; k < 9; k++) {
            int i = r + k / 3, j = c + k % 3;
            if (!_isValid(used, board[i][j])) {
                return false;
            }
        }
        
        return true;
    }
    
    bool _isValid(vector<bool> &used, char digit) {
        if (digit == '.') {
            return true;
        }

        if (used[digit - '1']) {
            return false;
        }

        used[digit - '1'] = true;
        return true;
    }
};

// Restore IP Addresses - LeetCode 93
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> results;
        if (s.empty()) {
            return results;
        }
        
        vector<string> ip;
        _restoreIP(s, 0, ip, results);
        return results;
    }
    
private:
    void _restoreIP(string &s, int index, 
                    vector<string> &ip, 
                    vector<string> &results) {
        if (index == s.size() && ip.size() == 4) {
            results.push_back(ip[0] + '.' + ip[1] + 
                        '.' + ip[2] + '.' + ip[3]);
            return;
        }
        
        if (s.size() - index > (4 - ip.size()) * 3) {
            return;
        }
        if (s.size() - index < 4 - ip.size()) {
            return;
        }
        
        int num = 0;
        for (int i = index; i < index + 3; i++) {
            num = num * 10 + (s[i] - '0');
            if (num < 0 || num > 255) {
                return;
            }
            
            string sub = s.substr(index, i - index + 1);
            ip.push_back(sub);
            _restoreIP(s, i + 1, ip, results);
            ip.pop_back();
            
            if (i == index && s[i] == '0') {
                break;
            }
        }
    }
};

// LeetCode 468. Valid IP Address [string]
class Solution {
public:
    string validIPAddress(string IP) {
        if (IP.find(".") < IP.size()) {
            return _validIPv4(IP);
        }
        if (IP.find(":") < IP.size()) {
            return _validIPv6(IP);
        }
        return "Neither";
    }
    
private:
    string _validIPv4(string &ip) {
        vector<string> strs;
        for (int i = 0, j = 0; i <= ip.size(); i++) {
            if (ip[i] == '.' || i == ip.size()) {
                strs.push_back(ip.substr(j, i - j));
                j = i + 1;
            }
        } 
            
        if (strs.size() != 4) {
            return "Neither";
        }
        
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].empty() || strs[i].size() > 3) {
                return "Neither";
            }
            if (strs[i].size() > 1 && strs[i][0] == '0') {
                return "Neither";
            }
            int num = 0;
            for (int j = 0; j < strs[i].size(); j++) {
                if (!isdigit(strs[i][j])) {
                    return "Neither";
                }
                num = num * 10 + (strs[i][j] - '0');
                if (num > 255) {
                    return "Neither";
                }
            }
        }
        return "IPv4";
    }
    
    string _validIPv6(string &ip) {
        vector<string> strs;
        for (int i = 0, j = 0; i <= ip.size(); i++) {
            if (ip[i] == ':' || i == ip.size()) {
                strs.push_back(ip.substr(j, i - j));
                j = i + 1;
            }
        }
        
        if (strs.size() != 8) {
            return "Neither";
        }
        
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].empty() || strs[i].size() > 4) {
                return "Neither";
            }
            for (int j = 0; j < strs[i].size(); j++) {
                if (!isalnum(strs[i][j])) {
                    return "Neither";
                }
                if (islower(strs[i][j]) && strs[i][j] > 'f') {
                    return "Neither";
                }
                if (isupper(strs[i][j]) && strs[i][j] > 'F') {
                    return "Neither";
                }
            }
        }
        return "IPv6";
    }
};
