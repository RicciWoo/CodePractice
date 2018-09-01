#include <vector>
#include <iostream>
using namespace std;

// Remove Duplicate Letters
class Solution {
public:
    string removeDuplicateLetters(string s) {
        if (s.size() == 0) return s;
        vector<int> cnt(26);
        for (int i = 0; i < s.size(); i++)
            cnt[s[i] - 'a']++;
        int pos = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < s[pos]) pos = i;
            if (--cnt[s[i] - 'a'] == 0) break;
        }
        return s[pos] + removeDuplicateLetters(
            s.substr(pos + 1).replaceAll("" + s[pos]), "");
        // no replaceAll in C++
    }
};

int main(int argc, char **argv) {

}
