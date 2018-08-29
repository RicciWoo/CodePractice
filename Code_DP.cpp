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

// 0-1 Knapsack, Dynamic Programming, 20180829
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















