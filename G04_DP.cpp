/******************** DP ********************/

// Fibonacci Numbers, Dynamic Programming
class solution {
public:
    int fibonacci(int n) {
        if (n <= 1) return 1;
        vector<int> result(n + 1, 0);
        result[0] = 1;
        result[1] = 1;
        for (int i = 2; i <= n; i++)
            result[i] = result[i - 1] + result[i - 2];
        return result[n];
    }
}

// Unique Paths, Dynamic Programming
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> a(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
            a[i][0] = 1;
        for (int j = 0; j < n; j++)
            a[0][j] = 1;
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                a[i][j] = a[i - 1][j] + a[i][j - 1];
        return a[m - 1][n - 1];
    }
};

// Minimum Path Sum-1, Dynamic Programming, use 2D array
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++)
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int j = 1; j < n; j++)
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        return dp[m - 1][n - 1];
    }
};

// Minimum Path Sum-2, Dynamic Programming, use two 1D lines
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int m = grid.size(), n = grid[0].size();
        vector<int> newLine(n, 0);
        vector<int> oldLine(n, 0);
        oldLine[0] = grid[0][0];
        for (int j = 1; j < n; j++)
            oldLine[j] = oldLine[j - 1] + grid[0][j];
        for (int i = 1; i < m; i++) {
            newLine[0] = oldLine[0] + grid[i][0];
            for (int j = 1; j < n; j++) {
                newLine[j] = min(oldLine[j], newLine[j - 1]) + grid[i][j];
            }
            swap(oldLine, newLine);
        }
        return oldLine[n - 1];
    }
};

// Minimum Path Sum-3, Dynamic Programming, use one 1D line
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int m = grid.size(), n = grid[0].size();
        vector<int> line(n, 0);
        line[0] = grid[0][0];
        for (int j = 1; j < n; j++)
            line[j] = line[j - 1] + grid[0][j];
        for (int i = 1; i < m; i++) {
            line[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                line[j] = min(line[j], line[j - 1]) + grid[i][j];
            }
        }
        return line[n - 1];
    }
};

// 0-1 Knapsack-1, Dynamic Programming, use 2D array
class Solution {
public:
    int knapsack(int capacity, vector<int> &weights, vector<int> &values) {
        int length = weights.size();
        if (capacity == 0 || length == 0) return 0;
        vector<vector<int>> w(length + 1, vector<int>(capacity + 1, 0));
        for (int i = 1; i <= length; i++) {
            int index = i - 1;
            for (int j = 1; j <= capacity; j++) {
                if (weights[index] > j)
                    w[i][j] = w[i - 1][j];
                else
                    w[i][j] = max(w[i - 1][j], 
                                  w[i - 1][j - weights[index]] + values[index]);
            }
        }
        return w[length][capacity];
    }
};

// Coin Change-1, Dynamic Programming, use 2D array
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // sort(coins.begin(), coins.end());
        int length = coins.size();
        vector<vector<int>> dp(length, vector<int>(amount + 1, 0));
        for (int j = 0; j <= amount; j++)
            if (j % coins[0] == 0) dp[0][j] = j / coins[0];
            else dp[0][j] = -1;
        for (int i = 1; i < length; i++) {
            for (int j = 0; j <= amount; j++) {
                if (coins[i] > j)
                    dp[i][j] = dp[i - 1][j];
                else {
                    int temp = INT_MAX;
                    for (int k = 0; k <= j / coins[i]; k++) {
                        int remaining = j - coins[i] * k;
                        if (dp[i - 1][remaining] != -1)
                            temp = min(temp, dp[i - 1][remaining] + k);
                    }
                    dp[i][j] = temp == INT_MAX ? -1 : temp;
                }
            }
        }
        return dp[length - 1][amount];
    }
};

// Coin Change-2, Dynamic Programming, use two 1D rows
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // sort(coins.begin(), coins.end());
        int length = coins.size();
        vector<int> preRow(amount + 1, 0);
        vector<int> curRow(amount + 1, 0);
        for (int j = 0; j <= amount; j++)
            if (j % coins[0] == 0) preRow[j] = j / coins[0];
            else preRow[j] = -1;
        for (int i = 1; i < length; i++) {
            for (int j = 0; j <= amount; j++) {
                if (coins[i] > j)
                    curRow[j] = preRow[j];
                else {
                    int temp = INT_MAX;
                    for (int k = 0; k <= j / coins[i]; k++) {
                        int remaining = j - coins[i] * k;
                        if (preRow[remaining] != -1)
                            temp = min(temp, preRow[remaining] + k);
                    }
                    curRow[j] = temp == INT_MAX ? -1 : temp;
                }
            }
            swap(curRow, preRow);
        }
        return preRow[amount];
    }
};

// Longest Increasing Subsequence-1, Dynamic Programming
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> lis(nums.size(), 0);
        int maxLen = 0;
        for (int i = 0; i < nums.size(); i++) {
            int localMax = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && lis[j] > localMax)
                    localMax = lis[j];
            }
            lis[i] = localMax + 1;
            maxLen = max(maxLen, lis[i]);
        }
        return maxLen;
    }
};

// Longest Common Sequence, Dynamic Programming
class Solution {
public:
    int longestCommonString(string &a, string &b) {
        int m = a.size(), n = b.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};

int main(int argc, char **argv) {
    string a = "abcfbc";
    string b = "abfcab";

    int result;
    Solution *solution = new Solution;
    result = solution->longestCommonString(a, b);
    cout << "string a: " << a << endl;
    cout << "string b: " << b << endl;
    cout << "length of longest Common Sequence: " << result << endl;
}

// Matrix Multiplication, Dynamic Programming
class Solution {
public:
    int matrixChain(vector<int> &p) {
        int n = p.size() - 1;
        vector<vector<int>> m(n, vector<int>(n, 0));
        // for (int i = 0; i < n; i++) m[i][i] = 0;
        for (int r = 2; r <= n; r++) { // the length of matrix chain
            for (int i = 0; i < n - r + 1; i++) {
                int j = i + r - 1;
                m[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                    if (t < m[i][j]) m[i][j] = t;
                }
            }
        }
        return m[0][n - 1];
    }
};

// Scramble String-1, Recursion
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        if (s1 == s2) return true;
        string c1 = s1, c2 = s2;
        sort(begin(c1), end(c1));
        sort(begin(c2), end(c2));
        if (c1 != c2) return false;
        for (int i = 1; i < s1.size(); i++) {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && 
                isScramble(s1.substr(i), s2.substr(i)))
                return true;
            if (isScramble(s1.substr(0, i), s2.substr(s2.size() - i)) && 
                isScramble(s1.substr(i), s2.substr(0, s2.size() - i)))
                return true;
        }
        return false;
    }
};

// Scramble String-2, Dynamic Programming
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        if (s1 == s2) return true;
        string c1 = s1, c2 = s2;
        sort(begin(c1), end(c1));
        sort(begin(c2), end(c2));
        if (c1 != c2) return false;
        int n = s1.size();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(
                                n, vector<bool>(n + 1, false)));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dp[i][j][1] = s1[i] == s2[j];
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                for (int j = 0; j < n - len + 1; j++) {
                    for (int k = 1; k < len; k++) {
                        dp[i][j][len] = dp[i][j][len] || 
                            (dp[i][j][k] && dp[i + k][j + k][len - k] || 
                            dp[i][j + len - k][k] && dp[i + k][j][len - k]);
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
