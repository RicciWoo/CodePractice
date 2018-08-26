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
                     vector<string>& wordList) {
        if (find(wordList.begin(), wordList.end(), 
                 endWord) == wordList.end())
            return 0;
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        queue<string> curr, next;
        curr.push(beginWord);
        unordered_set<string> visited;
        visited.insert(beginWord);
        int distance = 1;
        while (!curr.empty()) {
            distance++;
            while (!curr.empty()) {
                string node = curr.front();
                curr.pop();
                vector<string> wordsWithinDistance = 
                    _getWordsWithinDistance(wordSet, node);
                for (string word : wordsWithinDistance) {
                    if (word == endWord)
                        return distance;
                    if (find(visited.begin(), visited.end(), 
                             word) == visited.end()) {
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
                         word) != wordSet.end())
                    results.push_back(word);
            }
            word[i] = oriChar;
        }
        return results;
    }
};

// Word Ladder-2, Breadth-first Search
class Solution {
public:
    int ladderLength(string beginWord, string endWord, 
                     vector<string>& wordList) {
        if (find(wordList.begin(), wordList.end(), 
                 endWord) == wordList.end())
            return 0;
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        queue<string> curr, next;
        curr.push(beginWord);
        unordered_set<string> visited;
        visited.insert(beginWord);
        int distance = 1;
        while (!curr.empty()) {
            distance++;
            while (!curr.empty()) {
                string node = curr.front();
                curr.pop();
                vector<string> wordsWithinDistance = 
                    _getWordsWithinDistance(wordSet, node);
                for (string word : wordsWithinDistance) {
                    if (word == endWord)
                        return distance;
                    if (find(visited.begin(), visited.end(), 
                             word) == visited.end()) {
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
                         word) != wordSet.end())
                    results.push_back(word);
            }
            word[i] = oriChar;
        }
        return results;
    }
};













