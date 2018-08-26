#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Palindrome Partitioning, Depth-first Search, 20180821
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

int main(int argc, char **argv) {
    string s = "aab";

    vector<vector<string> > result;
    Solution *solution = new Solution;
    result = solution->partition(s);
    cout << "input: \"" << s << "\"" << endl;
    cout << "output: [ ";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << "\"" << result[i][j] << "\", ";
        }
        cout << "], ";
    }
    cout << "]" << endl;
}
