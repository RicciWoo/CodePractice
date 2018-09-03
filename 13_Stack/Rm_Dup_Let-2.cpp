#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Remove Duplicate Letters-2
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> cnt(26, 0);
        for (int i = 0; i < s.size(); i++)
            cnt[s[i] - 'a']++;
        stack<char> chStack;
        vector<bool> visited(26, false);
        for (int i = 0; i < s.size(); i++) {
            cnt[s[i] - 'a']--;
            if (visited[s[i] - 'a']) continue;
            while (!chStack.empty() && s[i] < chStack.top() && 
                   cnt[chStack.top() - 'a'] > 0) {
                visited[chStack.top() - 'a'] = false;
                chStack.pop();
            }
            chStack.push(s[i]);
            visited[s[i] - 'a'] = true;
        }
        string result = "";
        while (!chStack.empty()) {
            result += chStack.top();
            chStack.pop();
        }
        reverse(begin(result), end(result));
        return result;
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
