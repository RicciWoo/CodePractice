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
        // if (find(wordSet.begin(), wordSet.end(), 
        //          endWord) == wordSet.end())
        //     return 0;
        queue<string> curr, next;
        curr.push(beginWord);
        int distance = 1;
        while (!curr.empty() && !wordSet.empty()) {
            distance++;
            while (!curr.empty()) {
                string node = curr.front();
                curr.pop();
                vector<string> wordsWithinDistance = 
                    _getWordsWithinDistance(wordSet, node);
                if (find(wordsWithinDistance.begin(), 
                         wordsWithinDistance.end(), 
                         endWord) != wordsWithinDistance.end())
                    return distance;
                for (string word : wordsWithinDistance)
                    next.push(word);
            }
            swap(curr, next);
        }
        return distance == 2 ? 0 : distance;
    }
    
private:
    vector<string> _getWordsWithinDistance(
        unordered_set<string> &wordSet, string word) {
        vector<string> results;
        for (int i = 0; i < word.size(); i++) {
            char oriChar = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == oriChar)
                    continue;
                word[i] = c;
                if (find(wordSet.begin(), wordSet.end(), 
                         word) != wordSet.end()) {
                    results.push_back(word);
                    wordSet.erase(word);
                }
            }
            word[i] = oriChar;
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
