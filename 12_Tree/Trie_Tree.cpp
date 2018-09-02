#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Trie Tree
struct TrieNode {
    bool isWord;
    char var;
    vector<TrieNode *> children;
    TrieNode() {
        children = vector<TrieNode *>(26, NULL);
        var = 0;
        isWord = false;
    }
};

class Trie {
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie.
    void insert(string word) {
        if (word.size() == 0) return;
        TrieNode *pNode = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            int index = c - 'a';
            if (pNode->children[index] == NULL) {
                TrieNode *newNode = new TrieNode();
                pNode->children[index] = newNode;
            }
            pNode = pNode->children[index];
        }
        pNode->isWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *pNode = root;
        if (word.size() == 0) return true;
        for (int i = 0; i < word.size(); i++) {
            int index = word[i] - 'a';
            pNode = pNode->children[index];
            if (pNode == NULL) return false;
        }
        return pNode->isWord;
    }

    // Returns if there is any word in the trie 
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *pNode = root;
        if (prefix.size() == 0) return true;
        for (int i = 0; i < prefix.size(); i++) {
            int index = prefix[i] - 'a';
            pNode = pNode->children[index];
            if (pNode == NULL) return false;
        }
        return true;
    }
};

int main(int argc, char **argv) {
    Trie *trie = new Trie;
    trie->insert("validate");
    cout << "inserted word 'validate'." << endl;
    trie->insert("binary");
    cout << "inserted word 'binary'." << endl;
    trie->insert("search");
    cout << "inserted word 'search'." << endl;
    trie->insert("tree");
    cout << "inserted word 'tree'." << endl;

    bool schRes = false;
    schRes = trie->search("tree");
    cout << "search for word 'tree': " << boolalpha << schRes << endl;
    schRes = trie->search("trees");
    cout << "search for word 'trees': " << boolalpha << schRes << endl;

    bool stwRes = false;
    stwRes = trie->startsWith("val");
    cout << "starts with word 'val': " << boolalpha << stwRes << endl;
}
