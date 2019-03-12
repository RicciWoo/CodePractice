/******************** DFS on Permutation ********************/

// LeetCode 46 - Permutations, Depth-first Search, 20190123
class Solution {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.size() <= 1) {
            results.push_back(nums);
            return results;
        }
        
        vector<int> permutation;
        vector<bool> used(nums.size(), false);
        _permute(nums, used, permutation, results);
        return results;
    }
    
private:
    void _permute(vector<int> &nums, vector<bool> &used, 
                  vector<int> &permutation, 
                  vector<vector<int>> &results) {
        if (permutation.size() == nums.size()) {
            results.push_back(permutation);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            permutation.push_back(nums[i]);
            _permute(nums, used, permutation, results);
            used[i] = false;
            permutation.pop_back();
        }
    }
};

// LeetCode 47 - Permutations II, Depth-first Search, 20190123
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.size() <= 1) {
            results.push_back(nums);
            return results;
        }
        
        sort(nums.begin(), nums.end());
        vector<int> permutation;
        vector<bool> used(nums.size(), false);
        _permute(nums, used, permutation, results);
        return results;
    }
    
private:
    void _permute(vector<int> &nums, vector<bool> &used, 
                  vector<int> &permutation,
                  vector<vector<int>> &results) {
        if (permutation.size() == nums.size()) {
            results.push_back(permutation);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }
            if (i > 0 && 
                nums[i] == nums[i - 1] && !used[i - 1]) {
                continue;
            }
            
            used[i] = true;
            permutation.push_back(nums[i]);
            _permute(nums, used, permutation, results);
            used[i] = false;
            permutation.pop_back();
        }
    }
};

// LintCode 10 - String Permutation II, Depth-first Search, 20190123
class Solution {
public:
    vector<string> stringPermutation2(string &str) {
        vector<string> results;
        if (str.size() <= 1) {
            results.push_back(str);
            return results;
        }
        
        sort(str.begin(), str.end());
        string permutation;
        vector<bool> used(str.size(), false);
        _permute(str, permutation, used, results);
        return results;
    }
    
private:
    void _permute(string &s, string &permutation, 
                  vector<bool> &used, 
                  vector<string> &results) {
        if (permutation.size() == s.size()) {
            results.push_back(permutation);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            if (used[i]) {
                continue;
            }
            if (i > 0 && 
                s[i] == s[i - 1] && !used[i - 1]) {
                continue;
            }
            used[i] = true;
            permutation.push_back(s[i]);
            _permute(s, permutation, used, results);
            used[i] = false;
            permutation.pop_back();
        }
    }
};

// LintCode 211 - String Permutation, Sort, 20190301
class Solution {
public:
    bool Permutation(string &A, string &B) {
        if (A.size() != B.size()) {
            return false;
        }
        
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        return A == B;
    }
};

// LeetCode 51 - N-Queens, Depth-first Search, 20190123
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        if (n <= 0) {
            return results;
        }
        
        vector<int> cols;
        _placeQueens(n, cols, results);
        return results;
    }
    
private:
    void _placeQueens(int n, vector<int> &cols, 
                      vector<vector<string>> &results) {
        if (cols.size() == n) {
            _drawChessboard(cols, results);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (!_isValid(cols, col)) {
                continue;
            }
            
            cols.push_back(col);
            _placeQueens(n, cols, results);
            cols.pop_back();
        }
    }
    
    void _drawChessboard(vector<int> &cols, 
                         vector<vector<string>> &results) {
        vector<string> chessboard;
        for (int row = 0; row < cols.size(); row++) {
            string qInRow;
            for (int col = 0; col < cols.size(); col++) {
                qInRow += (col == cols[row] ? 'Q' : '.');
            }
            chessboard.push_back(qInRow);
        }
        results.push_back(chessboard);
    }
    
    bool _isValid(vector<int> &cols, int currCol) {
        int currRow = cols.size();
        for (int row = 0; row < cols.size(); row++) {
            if (cols[row] == currCol) {
                return false;
            }
            if (row + cols[row] == currRow + currCol) {
                return false;
            }
            if (row - cols[row] == currRow - currCol) {
                return false;
            }
        }
        return true;
    }
};

// LeetCode 52 - N Queens II, Depth-first Search, 20190123
class Solution {
public:
    int totalNQueens(int n) {
        if (n <= 0) {
            return 0;
        }
        
        int total = 0;
        vector<int> cols;
        _placeQueens(n, cols, total);
        return total;
    }
    
private:
    void _placeQueens(int n, vector<int> &cols, int &total) {
        if (cols.size() == n) {
            total++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (!_isValid(cols, col)) {
                continue;
            }
            
            cols.push_back(col);
            _placeQueens(n, cols, total);
            cols.pop_back();
        }
    }
    
    bool _isValid(vector<int> &cols, int currCol) {
        int currRow = cols.size();
        for (int row = 0; row < cols.size(); row++) {
            if (cols[row] == currCol) {
                return false;
            }
            if (row + cols[row] == currRow + currCol) {
                return false;
            }
            if (row - cols[row] == currRow - currCol) {
                return false;
            }
        }
        return true;
    }
};

// LeetCode 31 - Next Permutation, Depth-first Search, 20190123
class Solution {
public:
    void nextPermutation(vector<int> &nums) {
        if (nums.size() <= 1) {
            return;
        }
        if (nums.size() == 2) {
            swap(nums[0], nums[1]);
            return;
        }
        
        int pivot = nums.size() - 2;
        while (pivot >= 0 && nums[pivot] >= nums[pivot + 1]) {
            pivot--;
        }
        if (pivot == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        
        int index = nums.size() - 1;
        while (index > pivot && nums[index] <= nums[pivot]) {
            index--;
        }
        swap(nums[pivot], nums[index]);
        reverse(nums.begin() + pivot + 1, nums.end());
    }
};

// LintCode 52 - Next Permutation, Depth-first Search, 20190123
class Solution {
public:
    vector<int> nextPermutation(vector<int> &nums) {
        if (nums.size() <= 1) {
            return nums;
        }
        if (nums.size() == 2) {
            swap(nums[0], nums[1]);
            return nums;
        }
        
        int pivot = nums.size() - 2;
        while (pivot >= 0 && nums[pivot] >= nums[pivot + 1]) {
            pivot--;
        }
        if (pivot == -1) {
            reverse(nums.begin(), nums.end());
            return nums;
        }
        
        int index = nums.size() - 1;
        while (index > pivot && nums[index] <= nums[pivot]) {
            index--;
        }
        swap(nums[pivot], nums[index]);
        reverse(nums.begin() + pivot + 1, nums.end());
        return nums;
    }
};

// LeetCode 17 - Letter Combinations of a Phone Number, 
// Depth-first Search, 20190125
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> results;
        if (digits.empty()) {
            return results;
        }
        
        string combination;
        _letterComb(digits, 0, combination, results);
        return results;
    }
    
private:
    vector<string> keyboard{" ", "", "abc", "def", 
                            "ghi", "jkl", "mno", 
                            "pqrs", "tuv", "wxyz"};
    
    void _letterComb(string &digits, int index, 
                     string &combination, 
                     vector<string> &results) {
        if (index == digits.size()) {
            results.push_back(combination);
            return;
        }
        
        string keys = keyboard[digits[index] - '0'];
        for (int i = 0; i < keys.size(); i++) {
            combination.push_back(keys[i]);
            _letterComb(digits, index + 1, combination, results);
            combination.pop_back();
        }
    }
};

// LeetCode 291 - Word Pattern II, Depth-first Search, 20190125
class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        if (pattern.empty()) {
            return str.empty();
        }
        
        unordered_map<char, string> hashmap;
        unordered_set<string> hashset;
        return _match(pattern, 0, str, 0, hashmap, hashset);
    }
    
private:
    bool _match(string &pattern, int i, string &str, int j, 
                unordered_map<char, string> &hashmap, 
                unordered_set<string> &hashset) {
        if (i == pattern.size() && j == str.size()) {
            return true;
        }
        if (i >= pattern.size() || j >= str.size()) {
            return false;
        }
        
        char c = pattern[i];
        if (hashmap.count(c)) {
            string word = hashmap[c];
            if (str.compare(j, word.size(), word)) {
                return false;
            }
            return _match(pattern, i + 1, str, 
                          j + word.size(), hashmap, hashset);
        }
        
        for (int k = j; k < str.size(); k++) {
            string sub = str.substr(j, k - j + 1);
            if (hashset.count(sub)) {
                continue;
            }
            hashmap[c] = sub;
            hashset.insert(sub);
            if (_match(pattern, i + 1, str, k + 1, 
                       hashmap, hashset)) {
                return true;
            }
            hashmap.erase(c);
            hashset.erase(sub);
        }
        
        return false;
    }
};

// LeetCode 290 - Word Pattern, Hash Table, 20190301
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> words;
        _split(str, words);
        if (pattern.size() != words.size()) {
            return false;
        }
        
        unordered_map<char, string> hashmap1;
        unordered_map<string, char> hashmap2;
        for (int i = 0; i < pattern.size(); i++) {
            char a = pattern[i];
            string b = words[i];
            if (hashmap1.count(a) && hashmap1[a] != b) {
                return false;
            }
            hashmap1[a] = b;

            if (hashmap2.count(b) && hashmap2[b] != a) {
                return false;
            }
            hashmap2[b] = a;
        }
        
        return true;
    }
    
private:
    void _split(string &s, vector<string> &words) {
        for (int i = 0, j = 0; i <= s.size(); i++) {
            if (i == s.size() || s[i] == ' ') {
                string word = s.substr(j, i - j);
                words.push_back(word);
                j = i + 1;
            }
        }
    }
};

// LeetCode 212 - Word Search II, Depth-first Search, 20190125
class Solution {
public:
    vector<string> findWords(vector<vector<char>> &board, 
                             vector<string> &words) {
        vector<string> results;
        if (board.empty() || board[0].empty()) {
            return results;
        }
        if (words.empty()) {
            return results;
        }
        
        unordered_map<string, bool> prefix;
        _getPrefix(words, prefix);
        
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> used(m, vector<bool>(n, false));
        unordered_set<string> wordSet;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                used[i][j] = true;
                string word = string(1, board[i][j]);
                _wordSearch(board, used, i, j, word, 
                            prefix, wordSet);
                used[i][j] = false;
            }
        }
        
        results.insert(results.begin(), 
                       wordSet.begin(), wordSet.end());
        return results;
    }
    
private:
    void _getPrefix(vector<string> &words, 
                    unordered_map<string, bool> &prefix) {
        for (string &word : words) {
            for (int len = 1; len < word.size(); len++) {
                string pref = word.substr(0, len);
                if (!prefix.count(pref)) {
                    prefix[pref] = false;
                }
            }
            prefix[word] = true;
        }
    }
    
    void _wordSearch(vector<vector<char>> &board, 
                     vector<vector<bool>> &used, 
                     int x, int y, string &word, 
                     unordered_map<string, bool> &prefix, 
                     unordered_set<string> &wordSet) {
        if (!prefix.count(word)) {
            return;
        }
        if (prefix[word]) {
            wordSet.insert(word);
        }
        
        vector<int> dx{0, 1, 0, -1};
        vector<int> dy{1, 0, -1, 0};
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }
            if (used[nx][ny]) {
                continue;
            }
            used[nx][ny] = true;
            word.push_back(board[nx][ny]);
            _wordSearch(board, used, nx, ny, word, 
                        prefix, wordSet);
            used[nx][ny] = false;
            word.pop_back();
        }
    }
};

// LeetCode 79 - Word Search, Depth-first Search, 20190301
class Solution {
public:
    bool exist(vector<vector<char>> &board, string word) {
        if (board.empty() || board[0].empty()) {
            return word.empty();
        }
        if (word.empty()) {
            return true;
        }
        
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (_exist(board, i, j, word, 0, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    bool _exist(vector<vector<char>> &board, int x, int y,
                string &word, int index, 
                vector<vector<bool>> &visited) {
        if (index == word.size()) {
            return true;
        }
        int m = board.size(), n = board[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n) {
            return false;
        }
        if (visited[x][y]) {
            return false;
        }
        if (board[x][y] != word[index]) {
            return false;
        }
        
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            visited[x][y] = true;
            if (_exist(board, nx, ny, word, index + 1, visited)) {
                return true;
            }
            visited[x][y] = false;
        }
        
        return false;
    }
};

// LeetCode 126 - Word Ladder II, Depth-first Search, 20190126
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, 
                                       string endWord, 
                                       vector<string> &wordList) {
        vector<vector<string>> ladders;
        if (wordList.empty()) {
            return ladders;
        }
        
        unordered_set<string> dict(wordList.begin(), 
                                   wordList.end());
        if (!dict.count(endWord)) {
            return ladders;
        }
        dict.insert(beginWord);
        
        unordered_map<string, vector<string>> nextWords;
        unordered_map<string, int> distances;
        _bfs(dict, endWord, nextWords, distances);
        
        vector<string> path{beginWord};
        _dfs(nextWords, distances, 
             beginWord, endWord, path, ladders);
        return ladders;
    }
    
private:
    void _bfs(unordered_set<string> &dict, string &end, 
              unordered_map<string, vector<string>> &nextWords, 
              unordered_map<string, int> &distances) {
        queue<string> q;
        q.push(end);
        distances[end] = 0;
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            
            vector<string> prevWords;
            _getPrevWords(dict, curr, prevWords);
            for (string &prev : prevWords) {
                if (!nextWords.count(prev)) {
                    nextWords[prev] = vector<string>();
                }
                nextWords[prev].push_back(curr);
                if (!distances.count(prev)) {
                    distances[prev] = distances[curr] + 1;
                    q.push(prev);
                }
            }
        }
    }
    
    void _getPrevWords(unordered_set<string> &dict, string &word, 
                       vector<string> &prevWords) {
        for (int i = 0; i < word.size(); i++) {
            char oldChar = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == oldChar) {
                    continue;
                }
                word[i] = c;
                if (dict.count(word)) {
                    prevWords.push_back(word);
                }
            }
            word[i] = oldChar;
        }
    }
    
    void _dfs(unordered_map<string, vector<string>> &nextWords, 
              unordered_map<string, int> &distances, 
              string &curr, string &end, vector<string> &path, 
              vector<vector<string>> &ladders) {
        if (curr == end) {
            ladders.push_back(path);
            return;
        }
        
        for (string &next : nextWords[curr]) {
            if (distances[curr] != distances[next] + 1) {
                continue;
            }
            
            path.push_back(next);
            _dfs(nextWords, distances, next, end, path, ladders);
            path.pop_back();
        }
    }
};

// LintCode 121 - Word Ladder II, Depth-first Search, 20190126
class Solution {
public:
    vector<vector<string>> findLadders(string &start, 
                                       string &end, 
                                       unordered_set<string> &dict) {
        vector<vector<string>> ladders;
        if (dict.empty()) {
            return ladders;
        }
        
        dict.insert(start);
        dict.insert(end);
        
        unordered_map<string, vector<string>> nextWords;
        unordered_map<string, int> distances;
        _bfs(dict, end, nextWords, distances);
        
        vector<string> path{start};
        _dfs(nextWords, distances, start, end, path, ladders);
        return ladders;
    }
    
private:
    void _bfs(unordered_set<string> &dict, string &end, 
              unordered_map<string, vector<string>> &nextWords, 
              unordered_map<string, int> &distances) {
        queue<string> q;
        q.push(end);
        distances[end] = 0;
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            
            vector<string> prevWords;
            _getPrevWords(dict, curr, prevWords);
            for (string &prev : prevWords) {
                if (!nextWords.count(prev)) {
                    nextWords[prev] = vector<string>();
                }
                nextWords[prev].push_back(curr);
                if (!distances.count(prev)) {
                    distances[prev] = distances[curr] + 1;
                    q.push(prev);
                }
            }
        }
    }
    
    void _getPrevWords(unordered_set<string> &dict, 
                       string &curr, vector<string> &prevWords) {
        for (int i = 0; i < curr.size(); i++) {
            char oldCh = curr[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == oldCh) {
                    continue;
                }
                curr[i] = ch;
                if (dict.count(curr)) {
                    prevWords.push_back(curr);
                }
            }
            curr[i] = oldCh;
        }
    }
    
    void _dfs(unordered_map<string, vector<string>> &nextWords, 
              unordered_map<string, int> &distances, 
              string &curr, string &end, vector<string> &path, 
              vector<vector<string>> &ladders) {
        if (curr == end) {
            ladders.push_back(path);
            return;
        }
        
        for (string &next : nextWords[curr]) {
            if (distances[curr] != distances[next] + 1) {
                continue;
            }
            
            path.push_back(next);
            _dfs(nextWords, distances, next, end, path, ladders);
            path.pop_back();
        }
    }
};

// LeetCode 127 - Word Ladder, Breadth-first Search, 20190302
class Solution {
public:
    int ladderLength(string beginWord, string endWord, 
                     vector<string> &wordList) {
        if (wordList.empty()) {
            return 0;
        }
        
        unordered_set<string> dict(wordList.begin(), 
                                      wordList.end());
        if (!dict.count(endWord)) {
            return 0;
        }
        if (beginWord == endWord) {
            return 1;
        }
        
        queue<string> curr, next;
        curr.push(beginWord);
        dict.erase(beginWord);
        int length = 2;
        
        while (!curr.empty()) {
            while (!curr.empty()) {
                string word = curr.front();
                curr.pop();
                for (int i = 0; i < word.size(); i++) {
                    char oldChar = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == oldChar) {
                            continue;
                        }
                        word[i] = c;
                        if (word == endWord) {
                            return length;
                        }
                        if (dict.count(word)) {
                            next.push(word);
                            dict.erase(word);
                        }
                    }
                    word[i] = oldChar;
                }
            }
            length++;
            swap(curr, next);
        }
        
        return 0;
    }
};

// LintCode 120 - Word Ladder, Breadth-first Search, 20190302
class Solution {
public:
    int ladderLength(string &start, string &end, 
                     unordered_set<string> &dict) {
        if (dict.empty()) {
            return 0;
        }
        if (start == end) {
            return 1;
        }
        
        queue<string> curr, next;
        curr.push(start);
        dict.erase(start);
        int length = 2;
        
        while (!curr.empty()) {
            while (!curr.empty()) {
                string word = curr.front();
                curr.pop();
                for (int i = 0; i < word.size(); i++) {
                    char oldChar = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == oldChar) {
                            continue;
                        }
                        word[i] = c;
                        if (word == end) {
                            return length;
                        }
                        if (dict.count(word)) {
                            next.push(word);
                            dict.erase(word);
                        }
                    }
                    word[i] = oldChar;
                }
            }
            length++;
            swap(curr, next);
        }
        
        return 0;
    }
};
