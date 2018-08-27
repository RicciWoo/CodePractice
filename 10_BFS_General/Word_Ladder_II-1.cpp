#include <queue>
#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Word Ladder II, BFS, 20180827
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, 
            string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        vector<vector<string>> results;
        if (!wordSet.count(endWord)) return results;
        unordered_map<string, vector<string>> preList;
        queue<string> curr;
        curr.push(beginWord);
        unordered_set<string> visited;
        visited.insert(beginWord);
        while (!curr.empty()) {
            unordered_set<string> next;
            bool isFinished = false;
            while (!curr.empty()) {
                string str = curr.front();
                curr.pop();
                unordered_set<string> wordsInDist = 
                    _getWordsInDist(wordSet, str);
                for (string word : wordsInDist) {
                    if (word == endWord) {
                        isFinished = true;
                    }
                    if (!visited.count(word)) {
                        _updatePreList(word, str, preList);
                        next.insert(word);
                        // visited.insert(word);
                    }
                }
            }
            visited.insert(next.begin(), next.end());
            if (isFinished) {
                vector<string> temp;
                _getPaths(results, preList, temp, endWord);
                break;
            }
            // swap(curr, next);
            for (auto it = next.begin(); it != next.end(); it++)
                curr.push(*it);
        }
        return results;
    }
    
private:
    void _updatePreList(string cur, string pre, 
        unordered_map<string, vector<string>> &preList) {
        if (!preList.count(cur)) {
            vector<string> temp;
            preList[cur] = temp;
        }
        preList[cur].push_back(pre);
    }
    
    unordered_set<string> _getWordsInDist(
        unordered_set<string> &wordSet, string word) {
        unordered_set<string> results;
        for (int i = 0; i < word.size(); i++) {
            char cOri = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == cOri) continue;
                word[i] = c;
                if (wordSet.count(word))
                    results.insert(word);
            }
            word[i] = cOri;
        }
        return results;
    }
    
    void _getPaths(vector<vector<string>> &paths, 
        unordered_map<string, vector<string>> &preList, 
        vector<string> curPath, string end) {
        if (!preList.count(end)) {
            curPath.push_back(end);
            reverse(curPath.begin(), curPath.end());
            paths.push_back(curPath);
            return;
        }
        for (string pre : preList[end]) {
            curPath.push_back(end);
            _getPaths(paths, preList, curPath, pre);
        }
    }
};

int main(int argc, char **argv) {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};

    vector<vector<string>> results;
    Solution *solution = new Solution;
    results = solution->findLadders(beginWord, endWord, wordList);
    cout << "beginWord = " << beginWord << endl;
    cout << "endWord = " << endWord << endl;
    cout << "wordList = [";
    for (string word : wordList) {
        cout << "\"" << word << "\", ";
    }
    cout << "]" << endl;
    cout << "paths: " << endl;
    for (vector<string> path : results) {
        cout << "[ ";
        for(string step : path) {
            cout << "\"" << step << "\", ";
        }
        cout << "]" << endl;
    }
}
