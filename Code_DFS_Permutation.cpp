/******************** DFS on Permutation ********************/

// Permutations
class Solution {
public:
    /*
     * @param nums: A list of integers.
     * @return: A list of permutations.
     */
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> results;
        vector<int> permutation;
        vector<bool> visited(nums.size(), false);
        _permute(nums, visited, permutation, results);
        return results;
    }
    
    void _permute(vector<int> &nums, 
                  vector<bool> &visited, 
                  vector<int> &permutation, 
                  vector<vector<int>> &results) {
        if (permutation.size() == nums.size()) {
            results.push_back(permutation);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) {
                continue;
            }
            visited[i] = true;
            permutation.push_back(nums[i]);
            _permute(nums, visited, permutation, results);
            visited[i] = false;
            permutation.pop_back();
        }
    }
};

// Permutations II
class Solution {
public:
    /*
     * @param :  A list of integers
     * @return: A list of unique permutations
     */
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());
        vector<int> permutation;
        vector<bool> visited(nums.size(), false);
        _permute(nums, visited, permutation, results);
        return results;
    }
    
    void _permute(vector<int> &nums, 
                  vector<bool> &visited, 
                  vector<int> &permutation, 
                  vector<vector<int>> &results) {
        if (permutation.size() == nums.size()) {
            results.push_back(permutation);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] || i > 0 && 
                nums[i] == nums[i - 1] && visited[i - 1]) {
                continue;
            }
            visited[i] = true;
            permutation.push_back(nums[i]);
            _permute(nums, visited, permutation, results);
            visited[i] = false;
            permutation.pop_back();
        }
    }
};

// String Permutation II
class Solution {
public:
    /**
     * @param str: A string
     * @return: all permutations
     */
    vector<string> stringPermutation2(string &str) {
        vector<string> results;
        sort(str.begin(), str.end());
        string permutation;
        vector<bool> visited(str.size(), false);
        _strPermute(str, permutation, visited, results);
        return results;
    }
    
private:
    void _strPermute(string &s, string &permutation, 
                     vector<bool> &visited, 
                     vector<string> &results) {
        if (permutation.size() == s.size()) {
            results.push_back(permutation);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            if (visited[i] || i > 0 && 
                s[i] == s[i - 1] && !visited[i - 1]) {
                continue;
            }
            visited[i] = true;
            permutation.push_back(s[i]);
            _strPermute(s, permutation, visited, results);
            visited[i] = false;
            permutation.pop_back();
        }
    }
};

// N Queens
class Solution {
public:
    /*
     * @param n: The number of queens
     * @return: All distinct solutions
     */
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        if (n <= 0) {
            return results;
        }
        
        vector<int> cols;
        _solveNQueens(n, cols, results);
        return results;
    }
    
private:
    void _solveNQueens(int n, vector<int> &cols, 
                       vector<vector<string>> &results) {
        if (cols.size() == n) {
            _drawChessboard(cols, results);
            return;
        }
        
        for (int colIndex = 0; colIndex < n; colIndex++) {
            if (!_isValid(cols, colIndex)) {
                continue;
            }
            cols.push_back(colIndex);
            _solveNQueens(n, cols, results);
            cols.pop_back();
        }
    }
    
    void _drawChessboard(vector<int> &cols, 
                         vector<vector<string>> &results) {
        vector<string> chessboard;
        for (int i = 0; i < cols.size(); i++) {
            string row = "";
            for (int j = 0; j < cols.size(); j++) {
                row += j == cols[i] ? 'Q' : '.';
            }
            chessboard.push_back(row);
        }
        results.push_back(chessboard);
    }
    
    bool _isValid(vector<int> &cols, int colIndex) {
        int rows = cols.size();
        for (int rowIndex = 0; rowIndex < cols.size(); rowIndex++) {
            if (cols[rowIndex] == colIndex) {
                return false;
            }
            if (rowIndex + cols[rowIndex] == rows + colIndex) {
                return false;
            }
            if (rowIndex - cols[rowIndex] == rows - colIndex) {
                return false;
            }
        }
        return true;
    }
};

// N Queens II
class Solution {
public:
    /**
     * @param n: The number of queens.
     * @return: The total number of distinct solutions.
     */
    int totalNQueens(int n) {
        int sum = 0;
        vector<int> usedCols(n, -1);
        _placeQueen(n, 0, usedCols, sum);
        return sum;
    }
    
private:
    void _placeQueen(int n, int row, 
                     vector<int> &usedCols, int &sum) {
        if (row == n) {
            sum++;
            return;
        }
        
        for (int i = 0; i < n; i++) {
            if (_isValid(usedCols, row, i)) {
                usedCols[row] = i;
                _placeQueen(n, row + 1, usedCols, sum);
                //usedCols[row] = -1;
            }
        }
    }
    
    bool _isValid(vector<int> &usedCols, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (usedCols[i] == col) {
                return false;
            }
            if (i + usedCols[i] == row + col) {
                return false;
            }
            if (i - usedCols[i] == row - col) {
                return false;
            }
        }
        return true;
    }
};

// Next Permutation

// Next Permutation II

// Permutation Index

// Permutation Index II

// Letter Combinations of a Phone Number
class Solution {
public:
    /**
     * @param digits: A digital string
     * @return: all posible letter combinations
     */
    vector<string> letterCombinations(string &digits) {
        vector<string> results;
        if (digits.empty()) {
            return results;
        }
        string combination;
        _letComb(digits, 0, combination, results);
        return results;
    }
    
private:
    vector<string> keyboard{" ", "", "abc", "def", 
        "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    void _letComb(string &digits, int index, 
                  string &combination, 
                  vector<string> &results) {
        if (index == digits.size()) {
            results.push_back(combination);
        }
        string keys = keyboard[digits[index] - '0'];
        for (int i = 0; i < keys.size(); i++) {
            combination.push_back(keys[i]);
            _letComb(digits, index + 1, combination, results);
            combination.pop_back();
        }
    }
};

// Word Pattern II
class Solution {
public:
    /**
     * @param pattern: a string,denote pattern string
     * @param str: a string, denote matching string
     * @return: a boolean
     */
    bool wordPatternMatch(string &pattern, string &str) {
        if (pattern.empty()) {
            return str.empty();
        }
        unordered_map<char, string> map;
        unordered_set<string> set;
        return _wordPatternMatch(pattern, str, map, set);
    }
    
private:
    bool _wordPatternMatch(string pattern, string str, 
                           unordered_map<char, string> &map, 
                           unordered_set<string> &set) {
        if (pattern.empty()) {
            return str.empty();
        }
        
        char c = pattern[0];
        if (map.count(c)) {
            string word = map[c];
            if (str.compare(0, word.size(), word)) {
                return false;
            }
            string subPat = pattern.substr(1);
            string subStr = str.substr(word.size());
            return _wordPatternMatch(subPat, subStr, map, set);
        }
        
        for (int i = 0; i < str.size(); i++) {
            string word = str.substr(0, i + 1);
            if (set.count(word)) {
                continue;
            }
            map.insert({c, word});
            set.insert(word);
            string subPat = pattern.substr(1);
            string subStr = str.substr(i + 1);
            if (_wordPatternMatch(subPat, subStr, map, set)) {
                return true;
            }
            map.erase(c);
            set.erase(word);
        }
        
        return false;
    }
};

// Word Search II
class Solution {
public:
    /**
     * @param board: A list of lists of character
     * @param words: A list of string
     * @return: A list of string
     */
    vector<string> wordSearchII(vector<vector<char>> &board, 
                                vector<string> &words) {
        if (board.empty() || board[0].empty()) {
            return vector<string>();
        }
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        unordered_map<string, bool> prefixIsWord;
        _getPrefixSet(words, prefixIsWord);
        unordered_set<string> wordSet;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j <n; j++) {
                visited[i][j] = true;
                string word = string(1, board[i][j]);
                _wordSearch(board, visited, i, j, 
                            word, prefixIsWord, wordSet);
                visited[i][j] = false;
            }
        }
        
        vector<string> results(wordSet.begin(), wordSet.end());
        return results;
    }
    
private:
    void _getPrefixSet(vector<string> &words, 
                       unordered_map<string, bool> &prefixIsWord) {
        for (string word : words) {
            for (int i = 0; i < word.size() - 1; i++) {
                string prefix = word.substr(0, i + 1);
                if (!prefixIsWord.count(prefix)) {
                    prefixIsWord.insert({prefix, false});
                }
            }
            prefixIsWord[word] = true; // force insert
        }
    }
    
    void _wordSearch(vector<vector<char>> &board, 
                     vector<vector<bool>> &visited, 
                     int x, int y, string word, 
                     unordered_map<string, bool> &prefixIsWord, 
                     unordered_set<string> &wordSet) {
        if (!prefixIsWord.count(word)) {
            return;
        }
        
        if (prefixIsWord[word]) {
            wordSet.insert(word);
        }
        
        vector<int> dx{0, 1, -1, 0};
        vector<int> dy{1, 0, 0, -1};
        for (int i = 0; i < 4; i++) {
            int adjX = x + dx[i];
            int adjY = y + dy[i];
            
            if (!_inside(board, adjX, adjY) || visited[adjX][adjY]) {
                continue;
            }
            
            visited[adjX][adjY] = true;
            _wordSearch(board, visited, adjX, adjY, 
                        word + board[adjX][adjY], prefixIsWord, wordSet);
            visited[adjX][adjY] = false;
        }
    }
    
    bool _inside(vector<vector<char>> &board, int x, int y) {
        return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
    }
};

// Word Ladder II
class Solution {
public:
    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: a list of lists of string
     */
    vector<vector<string>> findLadders(string &start, string &end, 
                                       unordered_set<string> &dict) {
        vector<vector<string>> ladders;
        unordered_map<string, vector<string>> map;
        unordered_map<string, int> distance;
        
        dict.insert(start);
        dict.insert(end);
        
        _bfs(dict, end, start, map, distance);
        
        vector<string> path;
        _dfs(map, distance, start, end, path, ladders);
        
        return ladders;
    }
    
private:
    void _dfs(unordered_map<string, vector<string>> &map, 
              unordered_map<string, int> &distance, 
              string curr, string end, vector<string> &path, 
              vector<vector<string>> &ladders) {
        path.push_back(curr);
        if (curr == end) {
            ladders.push_back(path);
        } else {
            for (string next : map[curr]) {
                if (distance.count(next) && 
                    distance[curr] == distance[next] + 1) {
                    _dfs(map, distance, next, end, path, ladders);
                }
            }
        }
        path.pop_back();
    }
    
    void _bfs(unordered_set<string> &dict, string end, string start, 
              unordered_map<string, vector<string>> &map, 
              unordered_map<string, int> &distance) {
        queue<string> q;
        q.push(end);
        distance.insert({end, 0});
        for (string s : dict) {
            map.insert({s, vector<string>()});
        }
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            
            vector<string> prevWords;
            _expand(dict, curr, prevWords);
            for (string prev : prevWords) {
                map[prev].push_back(curr);
                if (!distance.count(prev)) {
                    distance.insert({prev, distance[curr] + 1});
                    q.push(prev);
                }
            }
        }
    }
    
    void _expand(unordered_set<string> &dict, 
                 string curr, vector<string> &prevWords) {
        for (int i = 0; i < curr.size(); i++) {
            char chOld = curr[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == chOld) {
                    continue;
                }
                curr[i] = ch;
                if (dict.count(curr)) {
                    prevWords.push_back(curr);
                }
            }
            curr[i] = chOld;
        }
    }
};

