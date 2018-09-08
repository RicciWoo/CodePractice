#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Longest_Substring Without Repeating Characters-3, use Hash Map
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        vector<int> cache(256, 0);
        for (int i = 0, j = 0; i < s.size(); i++) {
            j = max(j, cache[s[i]]);
            cache[s[i]] = i + 1;
            result = max(result, i - j + 1);
        }
        return result;
    }
};

int main(int argc, char **argv) {
    string s = "abcabcbb";
    int result;
    Solution *solution = new Solution;
    result = solution->lengthOfLongestSubstring(s);
    cout << "string: \"" << s << "\"" << endl;
    cout << "max length substring without repating: " << result << endl;

    s = "bbbbb";
    result = solution->lengthOfLongestSubstring(s);
    cout << "string: \"" << s << "\"" << endl;
    cout << "max length substring without repating: " << result << endl;

    s = "pwwkew";
    result = solution->lengthOfLongestSubstring(s);
    cout << "string: \"" << s << "\"" << endl;
    cout << "max length substring without repating: " << result << endl;

    s = "abbcdefdgh";
    result = solution->lengthOfLongestSubstring(s);
    cout << "string: \"" << s << "\"" << endl;
    cout << "max length substring without repating: " << result << endl;
}
