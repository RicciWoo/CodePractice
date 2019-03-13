// LeetCode 684 - Redundant Connection, Union-Find, 20190311
class Solution {
public:
    vector<int> findRedundantConnection(
                vector<vector<int>> &edges) {
        vector<int> result;
        if (edges.empty() || edges[0].empty()) {
            return result;
        }
        
        int n = edges.size();
        UnionFind *uf = new UnionFind(n);
        for (vector<int> &e : edges) {
            int father_u = uf->find(e[0]);
            int father_v = uf->find(e[1]);
            if (father_u == father_v) {
                result.push_back(e[0]);
                result.push_back(e[1]);
                return result;
            }
            uf->connect(father_u, father_v);
        }
        
        return result;
    }
    
private:
    struct UnionFind {
        vector<int> fathers;
        UnionFind(int n) {
            fathers = vector<int>(n + 1);
            for (int i = 0; i <= n; i++) {
                fathers[i] = i;
            }
        }
        
        void connect(int father_u, int father_v) {
            fathers[father_u] = father_v;
        }

        int find(int x) {
            if (fathers[x] == x) {
                return x;
            }
            return fathers[x] = find(fathers[x]);
        }
    };
};

// LeetCode 685 - Redundant Connection IIu78u, Union-Find, 20190311
class Solution {
public:
    vector<int> findRedundantDirectedConnection(
                    vector<vector<int>> &edges) {
        vector<int> result;
        if (edges.empty() || edges[0].empty()) {
            return result;
        }
        
        unordered_map<int, int> parents;
        vector<int> candidate;
        for (vector<int> &edge : edges) {
            int u = edge[0], v = edge[1];
            if(!parents.count(v)) {
                parents[v] = u;
                continue;
            }
            
            candidate = {parents[v], v};
            result = {u, v};
        }
        
        int n = edges.size();
        UnionFind *uf = new UnionFind(n);
        for (vector<int> &edge : edges) {
            int u = edge[0], v = edge[1];
            if (!result.empty() && 
                    u == result[0] && 
                    v == result[1]) {
                continue;
            }
            
            int father_u = uf->find(u);
            int father_v = uf->find(v);
            // there is a circle
            if (father_u == father_v) {
                // no multiple fathers
                if (candidate.empty()) {
                    return edge;
                }
                
                // still has circle, after deleting edge
                return candidate;
            }
            uf->connect(father_u, father_v);
        }
        
        return result;
    }
    
private:
    struct UnionFind {
        vector<int> fathers;
        UnionFind(int n) {
            fathers = vector<int>(n + 1);
            for (int i = 0; i <= n; i++) {
                fathers[i] = i;
            }
        }
        
        void connect(int father_u, int father_v) {
            fathers[father_u] = father_v;
        }

        int find(int x) {
            if (fathers[x] == x) {
                return x;
            }
            return fathers[x] = find(fathers[x]);
        }
    };
};

// LeetCode 98 - Validate Binary Search Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }
        bool isBST = true;
        root = _isValidBST(root, nullptr, nullptr, isBST);
        return isBST;
    }
    
private:
    TreeNode *_isValidBST(TreeNode *root, TreeNode *minNode, 
                          TreeNode *maxNode, bool &isBST) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (minNode != nullptr && minNode->val >= root->val) {
            isBST = false;
            return nullptr;
        }
        if (maxNode != nullptr && root->val >= maxNode->val) {
            isBST = false;
            return nullptr;
        }
        
        root->left = _isValidBST(root->left, minNode, root, isBST);
        root->right = _isValidBST(root->right, root, maxNode, isBST);
        return root;
    }
};

// LeetCode 62 - Unique Paths, Dynamic Programming, 20190311
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m <= 0 || n <= 0) {
            return 0;
        }
        
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        
        return dp[m - 1][n - 1];
    }
};

// LeetCode 62 - Unique Paths, Dynamic Programming and rolling array, 20190311
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m <= 0 || n <= 0) {
            return 0;
        }
        
        if (m < n) {
            return uniquePaths(n, m);
        }
        
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j - 1] + dp[j - 1];
            }
        }
        
        return dp[n - 1];
    }
};

// LeetCode 63 - Unique Paths II, Depth-first Search and Memoization, 20190311
class Solution {
public:
    int uniquePathsWithObstacles(
                vector<vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
            return 0;
        }
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) {
            return 0;
        }
        
        vector<vector<int>> paths(m, vector<int>(n, 0));
        paths[0][0] = 1;
        return _dfs(obstacleGrid, paths, m - 1, n - 1);
    }
    
private:
    int _dfs(vector<vector<int>> &obstacleGrid, 
             vector<vector<int>> &paths, 
             int x, int y) {
        if (x < 0 || y < 0) {
            return 0;
        }
        if (obstacleGrid[x][y]) {
            return 0;
        }
        if (x == 0 && y == 0) {
            return paths[0][0] = 1;
        }
        if (paths[x][y] > 0) {
            return paths[x][y];
        }
        paths[x][y] = _dfs(obstacleGrid, paths, x - 1, y) + 
                      _dfs(obstacleGrid, paths, x, y - 1);
        return paths[x][y];
    }
};

// LeetCode 63 - Unique Paths II, Dynamic Programming, 20190311
class Solution {
public:
    int uniquePathsWithObstacles(
                vector<vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty() || 
                        obstacleGrid[0].empty()) {
            return 0;
        }
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) {
            return 0;
        }
        
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        dp[0][0] = 1;
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j] == 0) {
                dp[0][j] = dp[0][j - 1];
            }
        }
        for (int i = 1; i < m; i++) {
            if (obstacleGrid[i][0] == 0) {
                dp[i][0] = dp[i - 1][0];
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        
        return dp[m - 1][n - 1];
    }
};

// LeetCode 63 - Unique Paths II, Dynamic Programming and rolling array, 20190311
class Solution {
public:
    int uniquePathsWithObstacles(
                vector<vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty() || 
                        obstacleGrid[0].empty()) {
            return 0;
        }
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) {
            return 0;
        }
        
        vector<long long> dp(n, 0);
        dp[0] = 1;
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j] == 0) {
                dp[j] = dp[j - 1];
            }
        }
        for (int i = 1; i < m; i++) {
            if (obstacleGrid[i][0] == 1) {
                dp[0] = 0;
            }
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 0) {
                    dp[j] = dp[j] + dp[j - 1];
                } else {
                    dp[j] = 0;
                }
            }
        }
        
        return dp[n - 1];
    }
};

// LintCode 679 - Unique Paths III, Dynamic Programming and Hash Table, 20190312
class Solution {
public:
    int uniqueWeightedPaths(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        unordered_map<int, unordered_set<int>> dp;
        dp[0].insert(grid[0][0]);
        for (int i = 0; i < m; i++) {
            int curr = i * n, prev = (i - 1) * n;
            for (const int &dis : dp[prev]) {
                dp[curr].insert(dis + grid[i][0]);
            }
        }
        for (int j = 0; j < n; j++) {
            int curr = j, prev = j - 1;
            for (const int &dis : dp[prev]) {
                dp[curr].insert(dis + grid[0][j]);
            }
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                int curr = i * n + j;
                int left = i * n + j - 1;
                int up = (i - 1) * n + j;
                for (const int &dis : dp[left]) {
                    dp[curr].insert(dis + grid[i][j]);
                }
                for (const int &dis : dp[up]) {
                    dp[curr].insert(dis + grid[i][j]);
                }
            }
        }
        
        int result = 0;
        int index = (m - 1) * n + n - 1;
        for (const int &dis : dp[index]) {
            result += dis;
        }
        return result;
    }
};

// Unique Paths, Google, follow up 1: O(m) space
// 3 directions: right, right up, right down
// start from left top, end at right top
class Solution {
public:
    int uniquePaths(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int m = grid.size(), n = grid[0].size();
        vector<int> prev(m, 0), curr(m, 0);
        prev[0] = 1;
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < m; i++) {
                curr[i] = prev[i] + 
                          (i - 1 >= 0 ? prev[i - 1] : 0) + 
                          (i + 1 < m ? prev[i + 1] : 0);
            }
            swap(curr, prev);
        }

        return prev[0];
    }
}

// follow up 2: can reach 3 points
class Solution {
public:
    bool canReach(vector<vector<int>> &points) {
        if (points.empty()) {
            return true;
        }

        sort(points.begin(), points.end(), myComp());
        for (int i = 1; i < points.size(); i++) {
            vector<int> &prev = points[i - 1];
            vector<int> &curr = points[i];
            if (curr[1] == prev[1]) {
                return false;
            }
            int len = curr[1] - prev[1];
            int lower = prev[0] - len;
            int upper = prev[0] + len;
            if (curr[0] < lower || curr[0] > upper) {
                return false;
            }
        }

        return true;
    }

private:
    struct myComp {
        bool operator() (const vector<int> &a, 
                         const vector<int> &b) {
            return a[1] < b[1];
        }
    };
}

// follow up 3: unique paths through points
class Solution {
public:
    int uniquePaths(int rows, int cols, 
                    vector<vector<int>> &points) {
        if (rows <= 0 || cols <= 0 || points.empty()) {
            return 0;
        }

        unordered_map<int, int> hashmap;
        for (vector<int> &point : points) {
            if (!hashmap.count(point[1])) {
                return 0;
            }
            hashmap[point[1]] = point[0];
        }

        vector<int> curr(rows, 0), prev(rows, 0);
        prev[0] = 1;
        int result = 0;
        for (int j = 1; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                curr[i] = prev[i] + 
                          (i - 1 >= 0 ? prev[i - 1] : 0) + 
                          (i + 1 < rows ? prev[i + 1] : 0);
            }
            swap(curr, prev);
            if (hashmap.count(j)) {
                int row = hashmap[j];
                for (int i = 0; i < rows; i++) {
                    if (i != row) {
                        prev[i] = 0;
                    } else {
                        result = prev[i];
                    }
                }
            }
        }

        return result;
    }
}

// follow up 4: given lower bound (x == H)
int uniquePaths(int rows, int cols, int H) {
    return uniquePaths(rows, cols) - uniquePaths(H, cols);
}

// follow up 5: 
// 3 directions: down, left down, right down
// start from left top, end at left bottom
class Solution {
public:
    int uniquePaths(int rows, int cols) {
        if (rows <= 0 || cols <= 0) {
            return 0;
        }

        vector<int> prev(cols, 0), curr(cols, 0);
        prev[0] = 1;
        for (int i = 1; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                curr[j] = prev[j] + 
                          (j - 1 >= 0 ? prev[j - 1] : 0) + 
                          (j + 1 < cols ? prev[j + 1] : 0);
            }
            swap(curr, prev);
        }

        return prev[0];
    }
}

// LeetCode 64 - Minimum Path Sum, Dynamic Programming, 20190312
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        vector<int> line(n, 0);
        line[0] = grid[0][0];
        for (int j = 1; j < n; j++) {
            line[j] = line[j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; i++) {
            line[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                line[j] = min(line[j], 
                              line[j - 1]) + grid[i][j];
            }
        }
        
        return line[n - 1];
    }
};

// Maximum Path Sum, Dynamic Programming, 20190312
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        vector<int> line(n, 0);
        line[0] = grid[0][0];
        for (int j = 1; j < n; j++) {
            line[j] = line[j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; i++) {
            line[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                line[j] = max(line[j], 
                              line[j - 1]) + grid[i][j];
            }
        }
        
        return line[n - 1];
    }
};

// follow up 2: O(1) space
class Solution {
public:
    int minPathSum(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        for (int j = 1; j < n; j++) {
            grid[0][j] = grid[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; i++) {
            grid[i][0] = grid[i - 1][0] + grid[i][0];
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                grid[i][j] = max(grid[i - 1][j], 
                                 grid[i][j - 1]) + 
                             grid[i][j];
            }
        }
        
        vector<vector<int>> path;
        path.push_back({m - 1, n - 1});
        int x = m - 1, y = n - 1;
        while (x > 0 || y > 0) {
            if (x == 0) {
                y--;
            } else if (y == 0) {
                x--;
            } else {
                if (grid[x - 1][y] > grid[x][y - 1]) {
                    x--;
                } else {
                    y--;
                }
            }
            path.push_back({x, y});
        }
        reverse(path.begin(), path.end());

        return grid[m - 1][n - 1];
    }
};

// LeetCode 205 - Isomorphic Strings, Hash Table, 20190312
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        
        unordered_map<char, char> st;
        for (int i = 0; i < s.size(); i++) {
            if (!st.count(s[i])) {
                st[s[i]] = t[i];
            } else {
                if (st[s[i]] != t[i]) {
                    return false;
                }
            }
        }
        
        unordered_map<char, char> ts;
        for (int i = 0; i < t.size(); i++) {
            if (!ts.count(t[i])) {
                ts[t[i]] = s[i];
            } else {
                if (ts[t[i]] != s[i]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// LeetCode 890 - Find and Replace Pattern, Hash Table, 20190312
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string> &words, 
                                         string pattern) {
        vector<string> results;
        if (words.empty() || pattern.empty()) {
            return results;
        }
        
        for (string &word : words) {
            if (_isIsomorphic(word, pattern)) {
                results.push_back(word);
            }
        }
        
        return results;
    }
    
private:
    bool _isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        
        unordered_map<char, char> st;
        for (int i = 0; i < s.size(); i++) {
            if (!st.count(s[i])) {
                st[s[i]] = t[i];
            } else {
                if (st[s[i]] != t[i]) {
                    return false;
                }
            }
        }
        
        unordered_map<char, char> ts;
        for (int i = 0; i < t.size(); i++) {
            if (!ts.count(t[i])) {
                ts[t[i]] = s[i];
            } else {
                if (ts[t[i]] != s[i]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// LeetCode 489 - Robot Room Cleaner, Depth-first Search, 20190313
class Solution {
public:
    void cleanRoom(Robot &robot) {
        unordered_set<string> visited;
        _dfs(visited, 0, 0, 0, robot);
    }
    
private:
    void _dfs(unordered_set<string> &visited, 
              int i, int j, int currDir, Robot &r) {
        string index = to_string(i) + "," + to_string(j);
        if (visited.count(index)) {
            return;
        }
        visited.insert(index);
        r.clean();
        for (int k = 0; k < 4; k++) {
            if (r.move()) {
                int x = i, y = j;
                switch(currDir) {
                    case 0: 
                        x -= 1;  // up
                        break;
                    case 1: 
                        y += 1;  // right
                        break;
                    case 2: 
                        x += 1;  // down
                        break;
                    case 3: 
                        y -= 1;  // left
                        break;
                    default:
                        break;
                }
                _dfs(visited, x, y, currDir, r);
                r.turnRight();
                r.turnRight();
                r.move();
                r.turnRight();
                r.turnRight();
            }
            r.turnRight();
            currDir += 1;
            currDir %= 4;
        }
    }
};

// LeetCode 855 - Exam Room, Tree Set and Hash Table, 20190313
class ExamRoom {
private:
    struct myComp {
        int N;
        myComp(int N) {this->N = N;}
        bool operator() (const pair<int, int> &lhs, 
                         const pair<int, int> &rhs) const {
            int a = lhs.first, b = lhs.second;
            int c = rhs.first, d = rhs.second;
            int dist1 = (a == -1 || b == N) ? 
                        (b - a) - 1 : (b - a) / 2;
            int dist2 = (c == -1 || d == N) ? 
                        (d - c) - 1 : (d - c) / 2;
            return dist1 < dist2 || (dist1 == dist2 && a > c);
        }
    };
    
    set<pair<int, int>, myComp> s;
    unordered_map<int, int> left;
    unordered_map<int, int> right;
    int N;
public:
    ExamRoom(int N) : s(myComp(N)) {
        this->N = N;
        s.insert({-1, N});
    }
    
    int seat() {
        pair<int, int> p = *prev(s.end());
        s.erase(prev(s.end()));
        int pos = (p.first == -1) ?
                0 : (p.second == N) ?
                N - 1 : p.first + (p.second - p.first) / 2;
        
        right[p.first] = pos;
        left[p.second] = pos;
        left[pos] = p.first;
        right[pos] = p.second;
        
        s.insert({p.first, pos});
        s.insert({pos, p.second});

        return pos;
    }
    
    void leave(int p) {
        s.erase({left[p], p});
        s.erase({p, right[p]});
        
        right[left[p]] = right[p];
        left[right[p]] = left[p];
        
        s.insert({left[p], right[p]});
        left.erase(p);
        right.erase(p);
    }
};



