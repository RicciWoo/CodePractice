#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Trie Tree
struct TrieNode {
    bool isWord;
    char var;
    vector<TrieNode *> children;
    TreeNode() {
        children = new TrieNode[26];
        var = 0;
        isWord = false;
    }
};

class Trie {
private:
    TrieNode root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie.
    void insert(string word) {
        if (word == NULL || word.size() == 0) return;
        TrieNode *pNode = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            int index = c - 'a';
            if (pNode->children[index] == NULL) {
                TrieNode newNode = new TrieNode();
                pNode->children[index] = newNode;
            }
            pNode = pNode->children[index];
        }
        pNode->isWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *pNode = root;
        if (word == NULL || word.size() == 0) return true;
        for (int i = 0; i < word.size(); i++) {
            int index = word[i] - 'a';
            pNode = pNode->children[index];
            if (pNode == NULL) return false;
        }
        return pNode->isWord;
    }

    // Returns if there is any word in the trie that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode pNode = root;
        if (prefix == NULL || prefix.size() == 0) return true;
        for (int i = 0; i < prefix.size(); i++) {
            int index = prefix[i] - 'a';
            pNode = pNode->children[index];
            if (pNode == NULL) return false;
        }
        return true;
    }
};

int main(int argc, char **argv) {

}
