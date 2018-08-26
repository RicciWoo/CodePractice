#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Remove Invalid Parentheses, Depth-first Search, 20180821
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> results;
        int max = 0;
        _dfs(s, "", 0, 0, max, results);
        if (results.size() == 0) results.push_back("");
        return results;
    }
    
private:
    void _dfs(string s, string sub, int left, int temp, 
              int &max, vector<string> &results) {
        if (s.size() == 0) {
            if (left == 0 && sub.size() != 0) {
                if (temp > max) {
                    max = temp;
                    results.clear();
                }
                if (temp == max && find(results.begin(), 
                        results.end(), sub) == results.end()) {
                    results.push_back(sub);
                }
            }
            return;
        }
        if (s[0] == '(') {
            _dfs(s.substr(1), sub + "(", left + 1, temp + 1, max, results);
            _dfs(s.substr(1), sub, left, temp, max, results);
        } else if (s[0] == ')') {
            if (left > 0)
                _dfs(s.substr(1), sub + ")", left - 1, temp, max, results);
            _dfs(s.substr(1), sub, left, temp, max, results);
        } else {
            string letter = s.substr(0, 1);
            _dfs(s.substr(1), sub + letter, left, temp, max, results);
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
