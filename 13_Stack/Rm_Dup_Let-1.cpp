#include <vector>
#include <iostream>
using namespace std;

// Remove Duplicate Letters-1
class Solution {
public:
    string removeDuplicateLetters(string s) {
        if (s.size() == 0) return s;
        vector<int> cnt(26, 0);
        for (int i = 0; i < s.size(); i++)
            cnt[s[i] - 'a']++;
        int pos = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < s[pos]) pos = i;
            if (--cnt[s[i] - 'a'] == 0) break;
        }
        string sub = "";
        for (int i = pos + 1; i < s.size(); i++)
            if (s[i] != s[pos]) sub += s.substr(i, 1);
        return s[pos] + removeDuplicateLetters(sub);
    }
};

int main(int argc, char **argv) {
    string s = "bcabc";
    string result;
    Solution *solution = new Solution;
    result = solution->removeDuplicateLetters(s);
    cout << "string with duplicate letters: " << s << endl;
    cout << "    removed duplicate letters: " << result << endl;

    s = "cbacdcbc";
    result = solution->removeDuplicateLetters(s);
    cout << "string with duplicate letters: " << s << endl;
    cout << "    removed duplicate letters: " << result << endl;
}
