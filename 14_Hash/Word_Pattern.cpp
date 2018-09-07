#include <stack>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Word Pattern, use Hash Map
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> hm;
        unordered_map<string, char> hm_r;
        istringstream iss(str);
        vector<string> words(istream_iterator<string>{iss}, 
                             istream_iterator<string>());
        if (pattern.size() != words.size()) return false;
        for (int i = 0; i < pattern.size(); i++) {
            char a = pattern[i];
            string b = words[i];
            if (!hm.count(a)) hm[a] = b;
            else if (hm[a] != b) return false;
            if (!hm_r.count(b)) hm_r[b] = a;
            else if (hm_r[b] != a) return false;
        }
        return true;
    }
};

int main(int argc, char **argv) {
    string pattern = "abba";
    string str = "dog cat cat dog";
    bool result;
    Solution *solution = new Solution;
    result = solution->wordPattern(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl << endl;

    pattern = "abba";
    str = "dog cat cat fish";
    result = solution->wordPattern(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl << endl;

    pattern = "aaaa";
    str = "dog cat cat dog";
    result = solution->wordPattern(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl << endl;

    pattern = "abba";
    str = "dog dog dog dog";
    result = solution->wordPattern(pattern, str);
    cout << "pattern: \"" << pattern << "\"" << endl;
    cout << "strings: \"" << str << "\"" << endl;
    cout << "strings follow the same pattern: " << boolalpha << result;
    cout << endl;
}
