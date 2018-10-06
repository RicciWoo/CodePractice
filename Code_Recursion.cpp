/******************** Recursion ********************/

// Gray Code, Recursion, LeetCode 89
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
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
        int k = 1 << (n - 1);
        for (int i = result.size() - 1; i >= 0; i--)
            result.push_back(result[i] + k);
    }
};

// Maze, Recursion
class Solution {
public:
	bool solveMaze(vector<vector<char>> &maze, int startX, int startY, 
		            int targetX, int targetY) {
		if (startX < 0 || startX >= maze.size() || 
			startY < 0 || startY >= maze[0].size() || 
			maze[startX][startY] == 'X') {
			return false;
		}
		if (startX == targetX && startY == targetY) return true;
		maze[startX][startY] = 'X';
		vector<int> dx{1, 0, -1, 0};
		vector<int> dy{0, 1, 0, -1};
		for (int i = 0; i < 4; i++) {
			if (solveMaze(maze, startX + dx[i], startY + dy[i], 
				          targetX, targetY)) {
				return true;
			}
		}
		return false;
	}
};

// Knapsack, Recursion, LeetCode 39. Combination Sum
class Solution {
public:
    vector<vector<int>> combinationSum(
            vector<int> &candidates, int target) {
        vector<vector<int>> results;
        if (candidates.empty() || target <= 0) return results;
        vector<int> temp;
        _combination(candidates, target, 0, temp, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int target, 
                      int index, vector<int> &temp, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(temp);
            return;
        }
        if (target < 0) return;
        for (int i = index; i < candidates.size(); i++) {
            temp.push_back(candidates[i]);
            _combination(candidates, target - candidates[i], 
                         i, temp, results);
            temp.pop_back();
        }
    }
};

// Knapsack II, Recursion, LeetCode 40. Combination Sum II
class Solution {
public:
    vector<vector<int>> combinationSum2(
            vector<int>& candidates, int target) {
        vector<vector<int>> results;
        if (candidates.empty() || target <= 0) return results;
        sort(candidates.begin(), candidates.end());
        vector<int> temp;
        _combination(candidates, target, 0, temp, results);
        return results;
    }
    
private:
    void _combination(vector<int> &candidates, int target, 
                      int index, vector<int> &temp, 
                      vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(temp);
            return;
        }
        if (target < 0) return;
        for (int i = index; i < candidates.size(); i++) {
            temp.push_back(candidates[i]);
            _combination(candidates, target - candidates[i], 
                         i + 1, temp, results);
            temp.pop_back();
            while (i < candidates.size() - 1 && 
                   candidates[i + 1] == candidates[i]) i++;
        }
    }
};

// LeetCode 216. Combination Sum III, Recursion
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> results;
        if (k <= 0 || n <= 0) return results;
        vector<int> temp;
        _combination(k, n, 1, temp, results);
        return results;
    }
    
private:
    void _combination(int k, int n, int index, 
                      vector<int> &temp, 
                      vector<vector<int>> &results) {
        if (n == 0) {
            if (temp.size() == k) 
                results.push_back(temp);
            return;
        }
        if (n < 0)  return;
        for (int i = index; i <= 9; i++) {
            temp.push_back(i);
            _combination(k, n - i, i + 1, temp, results);
            temp.pop_back();
        }
    }
};

// LeetCode 377. Combination Sum IV, Dynamic Programming
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        if (nums.empty() || target <= 0) return 0;
        vector<int> opt(target + 1, 0);
        opt[0] = 1;
        for (int i = 1; i <= target; i++)
            for (int j = 0; j < nums.size(); j++)
                if (i - nums[j] >= 0)
                    opt[i] += opt[i - nums[j]];
        return opt[target];
    }
};

// LeetCode 77. Combinations, Recursion
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        if (n <= 0 || k <= 0 || n < k) return result;
        vector<int> temp;
        _combine(n, k, 1, temp, result);
        return result;
    }
    
private:
    void _combine(int n, int k, int index, 
                  vector<int> &temp, 
                  vector<vector<int>> &result) {
        if (temp.size() == k) {
            result.push_back(temp);
            return;
        }
        for (int i = index; i <= n; i++) {
            temp.push_back(i);
            _combine(n, k, i + 1, temp, result);
            temp.pop_back();
        }
    }
};

// LeetCode 254. Factor Combinations, Recursion
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> result;
        if (n <= 1) return result;
        vector<int> temp;
        _getFactores(n, n, 2, temp, result);
        return result;
    }
    
private:
    void _getFactores(int n, int r, int index, 
                     vector<int> &temp, 
                     vector<vector<int>> &result) {
        if (r == 1) {
            result.push_back(temp);
            return;
        }
        if (r < index) return;
        for (int i = index; i < n; i++) {
            if (r % i == 0) {
                temp.push_back(i);
                _getFactores(n, r / i, i, temp, result);
                temp.pop_back();
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
		if (s == 0) return true;
		if (s < 0 || index == weights.size()) return false;
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
        if (s == 0 || index == weights.size()) return 0;
        if (s < weights[index])
            return _knapsack(s, weights, index + 1);
        return max(_knapsack(s, weights, index + 1), weights[index] + 
                   _knapsack(s - weights[index], weights, index + 1));
    }
};

// Permutations, Recursion, LeetCode 46
class Solution {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> result;
        if (nums.size() <= 1) {
            result.push_back(nums);
            return result;
        }
        vector<int> temp;
        vector<bool> used(nums.size(), false);
        _permute(nums, used, temp, result);
        return result;
    }
    
private:
    void _permute(vector<int> &nums, vector<bool> &used, 
                  vector<int> &temp, 
                  vector<vector<int>> &result) {
        if (temp.size() == nums.size()) {
            result.push_back(temp);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            used[i] = true;
            temp.push_back(nums[i]);
            _permute(nums, used, temp, result);
            used[i] = false;
            temp.pop_back();
        }
    }
};

// Permutations, Recursion and Swap, LeetCode 46
class Solution {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> result;
        if (nums.size() <= 1) {
            result.push_back(nums);
            return result;
        }
        _permute(nums, 0, result);
        return result;
    }
    
private:
    void _permute(vector<int> &nums, int index, 
                  vector<vector<int>> &result) {
        if (index == nums.size()) {
            result.push_back(nums);
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            swap(nums[index], nums[i]);
            _permute(nums, index + 1, result);
            swap(nums[index], nums[i]);
        }
    }
};

// Permutation II, Recursion, LeetCode 47
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> result;
        if (nums.size() <= 1) {
            result.push_back(nums);
            return result;
        }
        sort(nums.begin(), nums.end());
        vector<int> temp;
        vector<bool> used(nums.size(), false);
        _permute(nums, used, temp, result);
        return result;
    }
    
private:
    void _permute(vector<int> &nums, vector<bool> &used, 
                  vector<int> &temp,
                  vector<vector<int>> &result) {
        if (temp.size() == nums.size()) {
            result.push_back(temp);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] || (i > 0 && 
                nums[i] == nums[i - 1] && !used[i - 1]))
                continue;
            used[i] = true;
            temp.push_back(nums[i]);
            _permute(nums, used, temp, result);
            used[i] = false;
            temp.pop_back();
        }
    }
};

// Combination-1, Recursion, return as parameter and new array
// LeetCode 78. Subsets
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        // sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        if (index == nums.size()) {
            results.push_back(items);
            return;
        }

        vector<int> newItems1(items);
        _combination(nums, index + 1, newItems1, results);

        vector<int> newItems2(items);
        newItems2.push_back(nums[index]);
        _combination(nums, index + 1, newItems2, results);
    }
};

// Combination-2, Recursion, return as parameter and share array
// LeetCode 78. Subsets
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        // sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        if (index == nums.size()) {
            results.push_back(items);
            return;
        }

        _combination(nums, index + 1, items, results);

        items.push_back(nums[index]);
        _combination(nums, index + 1, items, results);
        items.pop_back();
    }
};

// Combination-3, Recursion, always pick a element, add empty set in the loop
// LeetCode 78. Subsets
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        // sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        if (index == nums.size()) {
            results.push_back(items);
            return;
        }
        for (int i = index; i <= nums.size(); i++) {
            if (i == nums.size()) {
                _combination(nums, nums.size(), items, results);
            }
            items.push_back(nums[i]);
            _combination(nums, i + 1, items, results);
            items.pop_back();
        }
    }
};

// Combination-4, Recursion, always pick a element, add empty set at the end
// LeetCode 78. Subsets
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        // sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        if (index == nums.size()) {
            results.push_back(items);
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            items.push_back(nums[i]);
            _combination(nums, i + 1, items, results);
            items.pop_back();
        }
        _combination(nums, nums.size(), items, results);
    }
};

// Combination-5, Recursion, add empty set at first
// LeetCode 78. Subsets, !!! better method !!!
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        // sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        results.push_back(items);
        for (int i = index; i < nums.size(); i++) {
            items.push_back(nums[i]);
            _combination(nums, i + 1, items, results);
            items.pop_back();
        }
    }
};

// Combination-6, Recursion, add empty set at the end
// LeetCode 78. Subsets, !!! better method !!!
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        // sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        for (int i = index; i < nums.size(); i++) {
            items.push_back(nums[i]);
            _combination(nums, i + 1, items, results);
            items.pop_back();
        }
        results.push_back(items);
    }
};

// Combination II, Recursion, LeetCode 90. Subsets II
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> results;
        vector<int> temp;
        _subsets(nums, 0, temp, results);
        return results;
    }
    
private:
    void _subsets(vector<int> &nums, int index, 
                  vector<int> &temp, 
                  vector<vector<int>> &results) {
        results.push_back(temp);
        for (int i = index; i < nums.size(); i++) {
            if (i > index && nums[i] == nums[i - 1])
                continue;
            temp.push_back(nums[i]);
            _subsets(nums, i + 1, temp, results);
            temp.pop_back();
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
            if (num[index] == '0' && i != index) return;
            string m = num.substr(index, i - index + 1);
            long n = stol(m);
            if (index == 0)
                _luckyNumber(num, target, i + 1, n, n, temp + m, results);
            else {
                _luckyNumber(num, target, i + 1, curr + n, n, 
                             temp + "+" + m, results);
                _luckyNumber(num, target, i + 1, curr - n, -n, 
                             temp + "-" + m, results);
                _luckyNumber(num, target, i + 1, curr - last + last * n, 
                             last * n, temp + "*" + m, results);
                if (n != 0 && last % n == 0)
                    _luckyNumber(num, target, i + 1, curr - last + last / n, 
                                 last / n, temp + "/" + m, results);
            }
        }
    }
};

// Letter Combinations of a Phone Number - LeetCode 17
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> results;
        if (digits.empty()) return results;
        _letterComb(digits, 0, "", results);
        return results;
    }
    
private:
    vector<string> dict{" ", "", "abc", "def", "ghi", "jkl", 
                        "mno", "pqrs", "tuv", "wxyz"};
    void _letterComb(string &digits, int index, 
                     string temp, vector<string> &results) {
        if (index == digits.size()) {
            results.push_back(temp);
            return;
        }
        int k = digits[index] - '0';
        for (int i = 0; i < dict[k].size(); i++)
            _letterComb(digits, index + 1, temp + dict[k][i], 
                        results);
    }
};

// N-Queens - LeetCode 51
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        vector<string> temp(n, string(n, '.'));
        vector<bool> c(n, false);  // flags of columns
        vector<bool> d1(2 * n - 1, false); // main diag
        vector<bool> d2(2 * n - 1, false); // anti diag
        _solveNQ(n, 0, c, d1, d2, temp, results);
        return results;
    }
    
private:
    void _solveNQ(int n, int i, vector<bool> &c, 
                  vector<bool> &d1, vector<bool> &d2, 
                  vector<string> &temp, 
                  vector<vector<string>> &results) {
        if (i == n) {
            results.push_back(temp);
            return;
        }
        for (int j = 0; j < n; j++) {
            if (!c[j] && !d1[i - j + n - 1] && !d2[i + j]) {
                c[j] = d1[i - j + n - 1] = d2[i + j] = true;
                temp[i][j] = 'Q';
                _solveNQ(n, i + 1, c, d1, d2, temp, results);
                temp[i][j] = '.';
                c[j] = d1[i - j + n - 1] = d2[i + j] = false;
            }
        }
    }
};

// LeetCode 52. N-Queens II
class Solution {
public:
    int totalNQueens(int n) {
        int result = 0;
        vector<bool> c(n, false);  // flags of columns
        vector<bool> d1(2 * n - 1, false); // main diag
        vector<bool> d2(2 * n - 1, false); // anti diag
        _solveNQ(n, 0, c, d1, d2, result);
        return result;
    }
    
private:
    void _solveNQ(int n, int i, vector<bool> &c, 
                  vector<bool> &d1, vector<bool> &d2, 
                  int &result) {
        if (i == n) {
            result++;
            return;
        }
        for (int j = 0; j < n; j++) {
            if (!c[j] && !d1[i - j + n - 1] && !d2[i + j]) {
                c[j] = d1[i - j + n - 1] = d2[i + j] = true;
                _solveNQ(n, i + 1, c, d1, d2, result);
                c[j] = d1[i - j + n - 1] = d2[i + j] = false;
            }
        }
    }
};

// LeetCode 131. Palindrome Partitioning
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

// LeetCode 36. Valid Sudoku [Hash Table]
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> used;
        for (int i = 0; i < 9; i++) {
            used.clear();
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                if (used.count(board[i][j])) return false;
                else used.insert(board[i][j]);
            }
            used.clear();
            for (int j = 0; j < 9; j++) {
                if (board[j][i] == '.') continue;
                if (used.count(board[j][i])) return false;
                else used.insert(board[j][i]);
            }
            used.clear();
            int r = (i / 3) * 3, c = (i % 3) * 3;
            for (int j = 0; j < 9; j++) {
                int x = r + j / 3, y = c + j % 3;
                if (board[x][y] == '.') continue;
                if (used.count(board[x][y])) return false;
                else used.insert(board[x][y]);
            }
        }
        return true;
    }
};

// Sudoku Solver - LeetCode 37
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        _solveSudoku(board);
    }
    
private:
    bool _solveSudoku(vector<vector<char>> &board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (int k = 0; k < 9; k++) {
                        board[i][j] = '1' + k;
                        if (_isValid(board, i, j) && 
                            _solveSudoku(board))
                            return true;
                        board[i][j] = '.';
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
private:
    bool _isValid(vector<vector<char>> &board, int x, int y) {
        unordered_set<char> used;
        for (int j = 0; j < 9; j++) {
            if (board[x][j] == '.') continue;
            if (used.count(board[x][j])) return false;
            else used.insert(board[x][j]);
        }
        used.clear();
        for (int i = 0; i < 9; i++) {
            if (board[i][y] == '.') continue;
            if (used.count(board[i][y])) return false;
            else used.insert(board[i][y]);
        }
        used.clear();
        int r = (x / 3) * 3, c = (y / 3) * 3;
        for (int k = 0; k < 9; k++) {
            int i = r + k / 3, j = c + k % 3;
            if (board[i][j] == '.') continue;
            if (used.count(board[i][j])) return false;
            else used.insert(board[i][j]);
        }
        return true;
    }
};

// Restore IP Addresses - LeetCode 93
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> results;
        vector<string> ip;
        _restoreIP(s, 0, ip, results);
        return results;
    }
    
private:
    void _restoreIP(string &s, int index, 
                    vector<string> &ip, 
                    vector<string> &results) {
        if (index == s.size() && ip.size() == 4) {
            results.push_back(ip[0] + '.' + ip[1] + '.' + 
                              ip[2] + '.' + ip[3]);
            return;
        }
        if (s.size() - index > (4 - ip.size()) * 3)
            return;
        if (s.size() - index < 4 - ip.size())
            return;
        int num = 0;
        for (int i = index; i < index + 3; i++) {
            num = num * 10 + (s[i] - '0');
            if (num < 0 || num > 255) return;
            string sub = s.substr(index, i - index + 1);
            ip.push_back(sub);
            _restoreIP(s, i + 1, ip, results);
            ip.pop_back();
            if (num == 0) return;
        }
    }
};

// LeetCode 468. Valid IP Address [string]
class Solution {
public:
    string validIPAddress(string IP) {
        if (IP.find(".") < IP.size())
            return _validIPv4(IP);
        else if (IP.find(":") < IP.size())
            return _validIPv6(IP);
        else return "Neither";
    }
    
private:
    string _validIPv4(string &ip) {
        vector<string> strs;
        int start = 0, end = 0;
        while (end < ip.size()) {
            end = ip.find(".", start);
            strs.push_back(ip.substr(start, end - start));
            start = end + 1;
        }
        if (strs.size() != 4) return "Neither";
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].empty() || strs[i].size() > 3)
                return "Neither";
            if (strs[i].size() > 1 && strs[i][0] == '0')
                return "Neither";
            int num = 0;
            for (int j = 0; j < strs[i].size(); j++) {
                if (!isdigit(strs[i][j])) return "Neither";
                num = num * 10 + (strs[i][j] - '0');
                if (num > 255) return "Neither";
            }
        }
        return "IPv4";
    }
    
    string _validIPv6(string &ip) {
        vector<string> strs;
        int start = 0, end = 0;
        while (end < ip.size()) {
            end = ip.find(":", start);
            strs.push_back(ip.substr(start, end - start));
            start = end + 1;
        }
        if (strs.size() != 8) return "Neither";
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].empty() || strs[i].size() > 4)
                return "Neither";
            for (int j = 0; j < strs[i].size(); j++) {
                if (!isdigit(strs[i][j]) && !isalpha(strs[i][j]))
                    return "Neither";
                if (islower(strs[i][j]) && strs[i][j] > 'f')
                    return "Neither";
                if (isupper(strs[i][j]) && strs[i][j] > 'F')
                    return "Neither";
            }
        }
        return "IPv6";
    }
};



