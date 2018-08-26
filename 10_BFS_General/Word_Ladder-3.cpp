#include <queue>
#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// Word Ladder, BFS, 20180827
class Solution {
public:
    int ladderLength(string beginWord, string endWord, 
                     vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        // if (!wordSet.count(endWord)) return 0;
        queue<pair<string, int>> q;
        q.push(make_pair(beginWord, 1));
        while (!q.empty()) {
            string s = q.front().first;
            int len = q.front().second;
            q.pop();
            if (s == endWord) return len;
            vector<string> wordsInDist = 
                _getWordsInDist(s, wordSet);
            for (string word : wordsInDist)
                q.push(make_pair(word, len + 1));
        }
        return 0;
    }
    
private:
    vector<string> _getWordsInDist(
        string s, unordered_set<string>& wordSet) {
        vector<string> results;
        for (int i = 0; i < s.size(); i++) {
            char cOri = s[i];
            for (int c = 'a'; c <= 'z'; c++) {
                if (c == cOri) continue;
                s[i] = c;
                if (wordSet.count(s)) {
                    results.push_back(s);
                    wordSet.erase(s);
                }
            }
            s[i] = cOri;
        }
        return results;
    }
};

int main(int argc, char **argv) {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot", "dot", "dog", "lot", "log"};

    int result;
    Solution *solution = new Solution;
    result = solution->ladderLength(beginWord, endWord, wordList);
    cout << "beginWord = " << beginWord << endl;
    cout << "endWord = " << endWord << endl;
    cout << "wordList = [";
    for (string word : wordList) {
        cout << "\"" << word << "\", ";
    }
    cout << "]" << endl;
    cout << "shortest transformation: " << result << endl;
}
