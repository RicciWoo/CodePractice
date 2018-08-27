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
        queue<string> curr, next;
        curr.push(beginWord);
        int distance = 1;
        while (!curr.empty()) {
            distance++;
            while (!curr.empty()) {
                string str = curr.front();
                curr.pop();
                unordered_set<string> wordsInDist = 
                    _getWordsInDist(wordSet, str);
                if (wordsInDist.count(endWord))
                    return distance;
                for (string word : wordsInDist)
                    next.push(word);
            }
            swap(curr, next);
        }
        return distance == 2 ? 0 : distance;
    }
    
private:
    unordered_set<string> _getWordsInDist(
        unordered_set<string> &wordSet, string word) {
        unordered_set<string> results;
        for (int i = 0; i < word.size(); i++) {
            char cOri = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == cOri) continue;
                word[i] = c;
                if (wordSet.count(word)) {
                    results.insert(word);
                    wordSet.erase(word);
                }
            }
            word[i] = cOri;
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
