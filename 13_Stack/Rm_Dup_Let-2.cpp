#include <vector>
#include <iostream>
using namespace std;

// Remove Duplicate Letters-2
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> freqs(26, 0);
        for (int i = 0; i < s.size(); i++)
            freqs[s[i] - 'a']++;
        vector<bool> visited(26, false);
        stack<char> charSt;
        for (int i = 0; i < s.size(); i++) {
            freqs[s[i] - 'a']--;
            if (visited[s[i] - 'a']) continue;
            while (!charSt.empty() && s[i] < charSt.top() && 
                   freqs[charSt.top() - 'a'] > 0) {
                visited[charSt.top() - 'a'] = false;
                charSt.pop();
            }
            charSt.push(s[i]);
            visited[s[i] - 'a'] = true;
        }
        string result = "";
        while (!charSt.empty()) {
            result += charSt.top();
            charSt.pop();
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
