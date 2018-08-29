#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Longest Common Sequence, Dynamic Programming, 20180829
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
