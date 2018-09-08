#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Window Substring, use Hash Map
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> pattern(256, 0);
        vector<int> text(256, 0);
        for (int i = 0; i < t.size(); i++)
            pattern[t[i]]++;
        int start = 0, end = 0, minStart = 0;
        int minLen = s.size() + 1;
        int count = t.size();
        bool isIncluded = false;
        while (true) {
            if (count == 0) {
                isIncluded = true;
                while (text[s[start]] > pattern[s[start]])
                    text[s[start++]]--;
                if (end - start < minLen) {
                    minLen = end - start;
                    minStart = start;
                }
            }
            if (end < s.size()) {
                text[s[end]]++;
                if (text[s[end]] <= pattern[s[end]])
                    count--;
                end++;
            } else break;
        }
        if (isIncluded)
            return s.substr(minStart, minLen);
        else return "";
    }
};

int main(int argc, char **argv) {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string result;
    Solution *solution = new Solution;
    result = solution->minWindow(s, t);
    cout << "string s: \"" << s << "\"" << endl;
    cout << "string t: \"" << t << "\"" << endl;
    cout << "min window substring: \"" << result << "\"" << endl << endl;

    t = "ABCC";
    result = solution->minWindow(s, t);
    cout << "string s: \"" << s << "\"" << endl;
    cout << "string t: \"" << t << "\"" << endl;
    cout << "min window substring: \"" << result << "\"" << endl;
}
