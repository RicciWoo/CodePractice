#include <stack>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Word Pattern II, use Hash Map
class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        unordered_map<char, string> hm;
        unordered_set<string> hs;
        return _isMatch(str, 0, pattern, 0, hm, hs);
    }
    
private:
    bool _isMatch(string str, int i, string pattern, int j, 
                  unordered_map<char, string> &hm, 
                  unordered_set<string> &hs) {
        if (i == str.size() && j == pattern.size()) 
            return true;
        if (i == str.size() || j == pattern.size())
            return false;
        char c = pattern[j];
        if (hm.count(c)) {
            string s = hm[c];
            if (str.compare(i, s.size(), s)) return false;
            else return _isMatch(str, i + s.size(), 
                                 pattern, j + 1, hm, hs);
        }
        for (int k = i; k < str.size(); k++) {
            string p = str.substr(i, k - i + 1);
            if (hs.count(p)) continue;
            hm[c] = p;
            hs.insert(p);
            if (_isMatch(str, k + 1, pattern, j + 1, hm, hs))
                return true;
            hm.erase(c);
            hs.erase(p);
        }
        return false;
    }
};

int main(int argc, char **argv) {
    string pattern = "abab";
    string str = "redblueredblue";
    bool result;
    Solution *solution = new Solution;
    result = solution->wordPatternMatch(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl << endl;

    pattern = "aaaa";
    str = "asdasdasdasd";
    result = solution->wordPatternMatch(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl << endl;

    pattern = "aabb";
    str = "xyzabcxyzabc";
    result = solution->wordPatternMatch(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl;
}
