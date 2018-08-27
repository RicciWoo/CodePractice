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
                     vector<string> &wordList) {
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        // if (!wordSet.count(endWord)) return 0;
        queue<string> curr, next;
        curr.push(beginWord);
        unordered_set<string> visited;
        visited.insert(beginWord);
        int distance = 1;
        while (!curr.empty()) {
            distance++;
            while (!curr.empty()) {
                string str = curr.front();
                curr.pop();
                vector<string> wordsInDist = 
                    _getWordsInDist(wordSet, str);
                for (string word : wordsInDist) {
                    if (word == endWord) return distance;
                    if (!visited.count(word)) {
                        next.push(word);
                        visited.insert(word);
                    }
                }
            }
            swap(curr, next);
        }
        return distance == 2 ? 0 : distance;
    }
    
private:
    vector<string> _getWordsInDist(
        unordered_set<string> &wordSet, string word) {
        vector<string> results;
        for (int i = 0; i < word.size(); i++) {
            char cOri = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == cOri) continue;
                word[i] = c;
                if (wordSet.count(word))
                    results.push_back(word);
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
