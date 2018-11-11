#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Aprroximate Matching, Trie, 20181110
class TrieNode {
public:
    char val;
    TrieNode *child;
    TrieNode(char val) {
        this->val = val;
        this->child = nullptr;
    }
};

class Solution {
public:
    string approxMatching(string text, string prefix, string suffix) {
        // build Trie Tree for prefix
        reverse(prefix.begin(), prefix.end());
        TrieNode *prefixRoot = _buildTrieTree(prefix);
        
        // build Trie Tree for suffix
        TrieNode *suffixRoot = _buildTrieTree(suffix);

        // search matching for substring of text
        int maxScore = 0;
        string result;
        for (int i = 0; i < text.size(); i++) {
            for (int j = i; j < text.size(); j++) {
                string sub = text.substr(i, j - i + 1);

                // calculate prefixScore
                int prefixScore = 0;
                for (int k = 1; k <= sub.size(); k++) {
                    string prefixSub = sub.substr(0, k);
                    reverse(prefixSub.begin(), prefixSub.end());
                    int score = _searchPrefix(prefixRoot, prefixSub);
                    prefixScore = max(prefixScore, score);
                }

                // calculate suffixScore
                int suffixScore = 0;
                for (int k = sub.size() - 1; k >= 0; k--) {
                    string suffixSub = sub.substr(k);
                    int score = _searchPrefix(suffixRoot, suffixSub);
                    suffixScore = max(suffixScore, score);
                }

                int textScore = prefixScore + suffixScore;
                if (textScore > maxScore) {
                    maxScore = textScore;
                    result = word;
                }
            }
        }

        return result;
    }

private:
    // build Trie Tree for the string
    TrieNode *_buildTrieTree(string &prefix) {
        TrieNode *root = new TrieNode(prefix[0]);
        TrieNode *node = root;
        for (int i = 1; i < prefix.size(); i++) {
            TrieNode *newNode = new TrieNode(prefix[i]);
            node->child = newNode;
            node = node->child;
        }
        return root;
    }

    // search for prefix
    int _searchPrefix(TrieNode *root, string &word) {
        int length = 0;
        for (int i = 0; i < word.size(); i++) {
            if (root == nullptr || word[i] != root->val) {
                return length;
            }
            length++;
            root = root->child;
        }
        return length;
    }
};

int main(int argc, char **argv) {
    string text = "nothing";
    string prefix = "bruno";
    string suffix = "ingenious";

    string result;
    Solution *solution = new Solution;
    result = solution->approxMatching(text, prefix, suffix);
    cout << "text: \"" << text << "\"" << endl;
    cout << "prefix: \"" << prefix << "\"" << endl;
    cout << "suffix: \"" << suffix << "\"" << endl;

    cout << "output: \"" << result << "\"" << endl;
}