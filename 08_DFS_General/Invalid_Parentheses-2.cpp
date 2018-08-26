#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// Remove Invalid Parentheses-2, Depth-first Search, 20180821
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> results;
        int maxLen = 0;
        _dfs(s, "", 0, 0, maxLen, results);
        if (results.size() == 0)
            results.insert(results.end(), "");
        vector<string> res(results.begin(), results.end());
        return res;
    }
    
private:
    void _dfs(string s, string sub, int left, int tempMax, 
              int &maxLen, unordered_set<string> &results) {
        if (s.size() == 0) {
            if (left == 0 && sub.size() != 0) {
                if (tempMax > maxLen) {
                    maxLen = tempMax;
                    results.clear();
                }
                if (maxLen == tempMax)
                    results.insert(results.end(), sub);
            }
            return;
        }
        if (s[0] == '(') {
            _dfs(s.substr(1), sub + "(", left + 1, tempMax + 1, 
                 maxLen, results);
            _dfs(s.substr(1), sub, left, tempMax, maxLen, results);
        } else if (s[0] == ')') {
            if (left > 0)
                _dfs(s.substr(1), sub + ")", left - 1, tempMax, 
                     maxLen, results);
            _dfs(s.substr(1), sub, left, tempMax, maxLen, results);
        } else {
            string letter = s.substr(0, 1);
            _dfs(s.substr(1), sub + letter, left, tempMax, maxLen, 
                 results);
        }
    }
};

int main(int argc, char **argv) {
    string s = "()())()";

    vector<string> result;
    Solution *solution = new Solution;
    result = solution->removeInvalidParentheses(s);
    cout << "input: \"" << s << "\"" << endl;
    cout << "output: [ ";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << "\"" << result[i][j] << "\",";
        }
        cout << "], ";
    }
    cout << "]" << endl;
}
