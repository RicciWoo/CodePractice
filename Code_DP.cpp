/******************** DFS ********************/

// Binary Tree Level Order Traversal-1, BFS, use two queues
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (root == NULL) return results;
        queue<TreeNode *> curr, next;
        curr.push(root);
        while (!curr.empty()) {
            vector<int> level;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                level.push_back(node->val);
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
            results.push_back(level);
            swap(curr, next);
        }
        return results;
    }
};

// Binary Tree Level Order Traversal-2, BFS, use NULL pointer
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (root == NULL) return results;
        vector<int> level;
        queue<TreeNode *> next;
        next.push(root);
        next.push(NULL);
        while (!next.empty()) {
            TreeNode *node = next.front();
            next.pop();
            if (node == NULL) {
                results.push_back(level);
                level.clear();
                if (!next.empty())
                    next.push(NULL);
            } else {
                level.push_back(node->val);
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
        }
        return results;
    }
};

// Binary Tree Zigzag Level Order Traversal-1, BFS, use two queues and list
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (root == NULL) return results;
        queue<TreeNode *> curr, next;
        curr.push(root);
        bool isOdd = true;
        while (!curr.empty()) {
            list<int> level;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                if (isOdd) level.push_back(node->val);
                else       level.push_front(node->val);
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
            vector<int> res(level.begin(), level.end());
            results.push_back(res);
            swap(curr, next);
            isOdd = !isOdd;
        }
        return results;
    }
};

// Binary Tree Zigzag Level Order Traversal-2, BFS, use two stacks
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (root == NULL) return results;
        stack<TreeNode *> curr, next;
        curr.push(root);
        bool isOdd = false;
        while (!curr.empty()) {
            vector<int> level;
            while (!curr.empty()) {
                TreeNode *node = curr.top();
                curr.pop();
                level.push_back(node->val);
                if (!isOdd) {
                    if (node->left != NULL)
                        next.push(node->left);
                    if (node->right != NULL)
                        next.push(node->right);
                } else {
                    if (node->right != NULL)
                        next.push(node->right);
                    if (node->left != NULL)
                        next.push(node->left);
                }
            }
            results.push_back(level);
            swap(curr, next);
            isOdd = !isOdd;
        }
        return results;
    }
};

// Find Bottom Left Tree Value, BFS, use two queues
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode *> curr, next;
        curr.push(root);
        int leftVal = 0;
        bool isFirst = false;
        while (!curr.empty()) {
            isFirst = true;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                if (isFirst) {
                    leftVal = node->val;
                    isFirst = false;
                }
                if (node->left == NULL && node->right == NULL)
                    continue;
                if (node->left != NULL)
                    next.push(node->left);
                if (node->right != NULL)
                    next.push(node->right);
            }
            swap(curr, next);
        }
        return leftVal;
    }
};

// The Maze, Breadth-first Search
struct Pair {
    int x;
    int y;
    Pair(int a, int b) : x(a), y(b) {}
};
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, 
                 vector<int>& dest) {
        int m = maze.size();
        int n = maze[0].size();
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        vector<int> dx{1, 0, 0, -1};
        vector<int> dy{0, -1, 1, 0};
        queue<Pair> grid;
        grid.push(Pair(start[0], start[1]));
        distance[start[0]][start[1]] = 0;
        while (!grid.empty()) {
            Pair curPnt = grid.front();
            grid.pop();
            for (int i = 0; i < 4; i++) {
                int x = curPnt.x, y = curPnt.y;
                int dist = distance[x][y];
                while (x >= 0 && x < m && y >= 0 && y < n && 
                       maze[x][y] == 0) {
                    x += dx[i];
                    y += dy[i];
                    dist++;
                }
                x -= dx[i];
                y -= dy[i];
                dist--;
                if (dist < distance[x][y]) {
                    distance[x][y] = dist;
                    if (x != dest[0] || y != dest[1])
                        grid.push(Pair(x, y));
                }
            }
        }
        int result = distance[dest[0]][dest[1]];
        return result == INT_MAX ? false : true;
    }
};

// The Maze II, Breadth-first Search
struct Pair {
    int x;
    int y;
    Pair(int a, int b) : x(a), y(b) {}
};
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, 
                         vector<int>& dest) {
        int m = maze.size();
        int n = maze[0].size();
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        vector<int> dx{1, 0, 0, -1};
        vector<int> dy{0, -1, 1, 0};
        queue<Pair> grid;
        grid.push(Pair(start[0], start[1]));
        distance[start[0]][start[1]] = 0;
        while (!grid.empty()) {
            Pair curPnt = grid.front();
            grid.pop();
            for (int i = 0; i < 4; i++) {
                int x = curPnt.x, y = curPnt.y;
                int dist = distance[x][y];
                while (x >= 0 && x < m && y >= 0 && y < n && 
                       maze[x][y] == 0) {
                    x += dx[i];
                    y += dy[i];
                    dist++;
                }
                x -= dx[i];
                y -= dy[i];
                dist--;
                if (dist < distance[x][y]) {
                    distance[x][y] = dist;
                    if (x != dest[0] || y != dest[1])
                        grid.push(Pair(x, y));
                }
            }
        }
        int result = distance[dest[0]][dest[1]];
        return result == INT_MAX ? -1 : result;
    }
};

// The Maze III, Breadth-first Search
struct Pair {
    int x;
    int y;
    Pair(int a, int b) : x(a), y(b) {}
};
class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, 
                           vector<int>& hole) {
        int m = maze.size();
        int n = maze[0].size();
        vector<int> dx{1, 0, 0, -1};
        vector<int> dy{0, -1, 1, 0};
        vector<string> dir{"d", "l", "r", "u"};
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        vector<vector<string>> path(m, vector<string>(n, ""));
        queue<Pair> grid;
        grid.push(Pair(ball[0], ball[1]));
        distance[ball[0]][ball[1]] = 0;
        // path[ball[0]][ball[1]] = "";
        while (!grid.empty()) {
            Pair curPnt = grid.front();
            grid.pop();
            for (int i = 0; i < 4; i++) {
                int x = curPnt.x, y = curPnt.y;
                int dist = distance[x][y];
                string curPath = path[x][y];
                while (x >= 0 && x < m && y >= 0 && y < n && 
                       maze[x][y] == 0 && 
                       (x != hole[0] || y != hole[1])) {
                    x += dx[i];
                    y += dy[i];
                    dist++;
                }
                if (x != hole[0] || y != hole[1]) {
                    x -= dx[i];
                    y -= dy[i];
                    dist--;
                }
                string newPath = curPath + dir[i];
                if (dist < distance[x][y] || (dist == distance[x][y] && 
                                    newPath.compare(path[x][y]) < 0)) {
                    distance[x][y] = dist;
                    path[x][y] = newPath;
                    if (x != hole[0] || y != hole[1])
                        grid.push(Pair(x, y));
                }
            }
        }
        string result = path[hole[0]][hole[1]];
        return distance[hole[0]][hole[1]] == INT_MAX ? 
               "impossible" : result;
    }
};

// Word Ladder-1, Breadth-first Search
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

// Word Ladder-2, Breadth-first Search
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

// Word Ladder-3, BFS, 20180827
class Solution {
public:
    int ladderLength(string beginWord, string endWord, 
                     vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        queue<pair<string, int>> curr;
        curr.push(make_pair(beginWord, 1));
        while (!curr.empty()) {
            string str = curr.front().first;
            int dist = curr.front().second;
            curr.pop();
            unordered_set<string> wordsInDist = 
                _getWordsInDist(wordSet, str);
            if (wordsInDist.count(endWord))
                return dist + 1;
            for (string word : wordsInDist)
                curr.push(make_pair(word, dist + 1));
        }
        return 0;
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

// Word Ladder II-1, BFS, 20180828
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
                    }
                }
            }
            visited.insert(next.begin(), next.end());
            if (isFinished) {
                vector<string> temp;
                _getPaths(results, preList, temp, endWord);
                break;
            }
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
            curPath.pop_back();
        }
    }
};

// Surrounded region-1, BFS
class Solution {
public:
    void solve(vector<vector<char>> &board) {
        if (board.size() <= 2 || board[0].size() <= 2)
            return;
        for (int i = 0; i < board.size(); i++) {
            _search(board, i, 0);
            _search(board, i, board[0].size() - 1);
        }
        for (int j = 0; j < board[0].size(); j++) {
            _search(board, 0, j);
            _search(board, board.size() - 1, j);
        }
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                board[i][j] = board[i][j] == '+' ? 'O' : 'X';
    }
    
private:
    void _search(vector<vector<char>> &board, int x, int y) {
        if (board[x][y] != 'O') return;
        board[x][y] = '+';
        int m = board.size(), n = board[0].size();
        queue<int> q;
        q.push(x * n + y);
        vector<int> dx{-1, 0, 1, 0};
        vector<int> dy{0, 1, 0, -1};
        while (!q.empty()) {
            int temp = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = temp / n + dx[i], ny = temp % n + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    board[nx][ny] == 'O') {
                    board[nx][ny] = '+';
                    q.push(nx * n + ny);
                }
            }
        }
    }
};

// Surrounded region-2, DFS
class Solution {
public:
    void solve(vector<vector<char>> &board) {
        if (board.size() <= 2 || board[0].size() <= 2)
            return;
        for (int i = 0; i < board.size(); i++) {
            _search(board, i, 0);
            _search(board, i, board[0].size() - 1);
        }
        for (int j = 0; j < board[0].size(); j++) {
            _search(board, 0, j);
            _search(board, board.size() - 1, j);
        }
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                board[i][j] = board[i][j] == '+' ? 'O' : 'X';
    }
    
private:
    void _search(vector<vector<char>> &board, int x, int y) {
        if (board[x][y] != 'O') return;
        board[x][y] = '+';
        if (x > 1)
            _search(board, x - 1, y);
        if (x < board.size() - 2)
            _search(board, x + 1, y);
        if (y > 1)
            _search(board, x, y - 1);
        if (y < board[0].size() - 2)
            _search(board, x, y + 1);
    }
};

// Remove Invalid Parentheses, BFS
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> results;
        queue<string> q;
        q.push(s);
        unordered_set<string> checked;
        bool found = false;
        int max = 0;
        while (!q.empty()) {
            string t = q.front();
            q.pop();
            if (_isValid(t)) {
                found = true;
                if (t.size() >= max) {
                    max = t.size();
                    results.push_back(t);
                }
            }
            if (found) continue;
            for (int i = 0; i < t.size(); i++) {
                string sub = t.substr(0, i) + 
                    t.substr(i + 1, t.size() - i - 1);
                if (!checked.count(sub)) {
                    q.push(sub);
                    checked.insert(sub);
                }
            }
        }
        return results;
    }
    
private:
    bool _isValid(string s) {
        int count = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') count++;
            else if (s[i] == ')') {
                if (count == 0) return false;
                else count--;
            }
        }
        return count == 0;
    }
};
