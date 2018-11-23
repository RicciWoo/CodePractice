#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// LeetCode 647 - Palindromic Substrings, Dynamic Programming
class Solution {
public:
    int countSubstrings(string s) {
        if (s.size() == 1) {
            return 1;
        }
        
        int n = s.size(), result = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        unordered_set<string> exist;
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            if (!exist.count(s.substr(i, 1))) {
                exist.insert(s.substr(i, 1));
                result++;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                if (!exist.count(s.substr(i, 2))) {
                    exist.insert(s.substr(i, 2));
                    result++;
                }
            }
        }
        
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                if (dp[i + 1][j - 1] && s[i] == s[j]) {
                    dp[i][j] = true;
                    if (!exist.count(s.substr(i, j - i + 1))) {
                        exist.insert(s.substr(i, j - i + 1));
                        result++;
                    }
                }
            }
        }
        
        return result;
    }
};

int main(int argc, char **argv) {
    string s = "aabaa";

    int result;
    Solution *solution = new Solution;
    result = solution->countSubstrings(s);
    cout << "the string s: \"" << s << "\"" << endl;
    cout << "# of palindromic substring: " << result << endl;
}