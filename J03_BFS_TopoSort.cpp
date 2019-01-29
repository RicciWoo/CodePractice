/******************** BFS and Topology Sort ********************/

// LeetCode 102 - Binary Tree Level Order Traversal, 
// Breadth-first Search, 20181205
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        
        queue<TreeNode *> curr, next;
        curr.push(root);
        while (!curr.empty()) {
            vector<int> level;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                level.push_back(node->val);
                if (node->left != nullptr) {
                    next.push(node->left);
                }
                if (node->right != nullptr) {
                    next.push(node->right);
                }
            }
            swap(curr, next);
            result.push_back(level);
        }
        
        return result;
    }
};

// LeetCode 297 - Serialize and Deserialize Binary Tree, 
// Breadth-first Search, 20181205
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "{}";
        }
        
        queue<TreeNode *> q;
        q.push(root);
        vector<TreeNode *> nodes;
        while (!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            nodes.push_back(node);
            if (node == nullptr) {
                continue;
            }
            q.push(node->left);
            q.push(node->right);
        }
        
        stringstream ss;
        ss << "{" << nodes[0]->val;
        for (int i = 1; i < nodes.size(); i++) {
            if (nodes[i] != nullptr) {
                ss << "," << nodes[i]->val;
            } else {
                ss << ",#";
            }
        }
        ss << "}";
        
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() < 2 || data == "{}") {
            return nullptr;
        }
        
        string sub = data.substr(1, data.size() - 2);
        vector<string> vals;
        _split(sub, ",", vals);
        
        TreeNode *root = new TreeNode(stoi(vals[0]));
        queue<TreeNode *> q;
        q.push(root);
        
        bool isLeftChild = true;
        for (int i = 1; i < vals.size(); i++) {
            if (vals[i] != "#") {
                TreeNode *node = new TreeNode(stoi(vals[i]));
                if (isLeftChild) {
                    q.front()->left = node;
                } else {
                    q.front()->right = node;
                }
                q.push(node);
            }
            
            if (!isLeftChild) {
                q.pop();
            }
            
            isLeftChild = !isLeftChild;
        }
        
        return root;
    }
    
private:
    void _split(string &str, string delim, 
                vector<string> &results) {
        for (int i = 0, j = 0; i <= str.size(); i++) {
            if (str[i] == delim[0] || i == str.size()) {
                results.push_back(str.substr(j, i - j));
                j = i + 1;
            }
        }
    }
};

// LeetCode 107 - Binary Tree Level Order Traversal II, 
// Breadth-first Search, 20181209
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        
        queue<TreeNode*> curr, next;
        curr.push(root);
        while (!curr.empty()) {
            vector<int> level;
            while (!curr.empty()) {
                TreeNode* node = curr.front();
                curr.pop();
                level.push_back(node->val);
                if (node->left != nullptr) {
                    next.push(node->left);
                }
                if (node->right != nullptr) {
                    next.push(node->right);
                }
            }
            swap(next, curr);
            result.push_back(level);
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};

// LeetCode 103 - Binary Tree Zigzag Level Order Traversal, 
// Breadth-first Search, 20181209
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if (root == nullptr) {
            return results;
        }
        
        queue<TreeNode *> curr, next;
        curr.push(root);
        bool isOdd = true;
        while (!curr.empty()) {
            deque<int> level;
            while (!curr.empty()) {
                TreeNode *node = curr.front();
                curr.pop();
                if (isOdd) {
                    level.push_back(node->val);
                } else {
                    level.push_front(node->val);
                }
                if (node->left != nullptr) {
                    next.push(node->left);
                }
                if (node->right != nullptr) {
                    next.push(node->right);
                }
            }
            isOdd = !isOdd;
            swap(curr, next);
            vector<int> result(level.begin(), level.end());
            results.push_back(result);

        }
        
        return results;
    }
};

// LintCode 242 - Convert Binary Tree to Linked List by Depth, 
// Breadth-first Search, 20181209
class Solution {
public:
    vector<ListNode *> binaryTreeToLists(TreeNode *root) {
        vector<ListNode *> results;
        if (root == nullptr) {
            return results;
        }
        
        queue<TreeNode *> curr, next;
        curr.push(root);
        while (!curr.empty()) {
            ListNode dummy(-1);
            ListNode *node = &dummy;
            while (!curr.empty()) {
                TreeNode *head = curr.front();
                curr.pop();
                node->next = new ListNode(head->val);
                node = node->next;
                if (head->left != nullptr) {
                    next.push(head->left);
                }
                if (head->right != nullptr) {
                    next.push(head->right);
                }
            }
            swap(curr, next);
            results.push_back(dummy.next);
        }
        
        return results;
    }
};

// LeetCode 133 - Clone Graph, Breadth-first Search, 20181217.
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        UndirectedGraphNode *n1 = node;
        UndirectedGraphNode *n2 = new UndirectedGraphNode(n1->label);
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> hm;
        hm.insert({n1, n2});
        queue<UndirectedGraphNode *> q;
        q.push(n1);
        
        while (!q.empty()) {
            n1 = q.front();
            q.pop();
            n2 = hm[n1];
            for (UndirectedGraphNode *nb1 : n1->neighbors) {
                if (hm.count(nb1)) {
                    n2->neighbors.push_back(hm[nb1]);
                } else {
                    UndirectedGraphNode *nb2 = 
                        new UndirectedGraphNode(nb1->label);
                    n2->neighbors.push_back(nb2);
                    hm.insert({nb1, nb2});
                    q.push(nb1);
                }
            }
        }
        
        return hm[node];
    }
};

// LeetCode 127 - Word Ladder, Breadth-first Search, 20181217.
// endWord is included in wordList
class Solution {
public:
    int ladderLength(string beginWord, string endWord, 
                     vector<string> &wordList) {
        unordered_set<string> wordSet(wordList.begin(), 
                                      wordList.end());
        if (!wordSet.count(endWord)) {
            return 0;
        }
        if (beginWord == endWord) {
            return 1;
        }
        
        queue<string> curr, next;
        curr.push(beginWord);
        wordSet.erase(beginWord);
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
                        if (wordSet.count(word)) {
                            next.push(word);
                            wordSet.erase(word);
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

// LintCode 120 - Word Ladder, Breadth-first Search, 20181217.
// end is not included in dict
class Solution {
public:
    int ladderLength(string &start, string &end, 
                     unordered_set<string> &dict) {
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

// LeetCode 200 - Number of Islands, Breadth-first Search, 20181217.
class Solution {
public:
    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int islands = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    _bfs(grid, i, j);
                    islands++;
                }
            }
        }
        
        return islands;
    }
    
private:
    void _bfs(vector<vector<char>> &grid, int x, int y) {
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        
        int m = grid.size(), n = grid[0].size();
        queue<int> q;
        q.push(x * n + y);
        grid[x][y] = '0';
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            x = curr / n;
            y = curr % n;
            for (int k = 0; k < 4; k++) {
                int i = x + dx[k], j = y + dy[k];
                if (i < 0 || i >= m || j < 0 || j >= n) {
                    continue;
                }
                if (grid[i][j] == '1') {
                    grid[i][j] = '0';
                    q.push(i * n + j);
                }
            }
        }
    }
};

// LeetCode 200 - Number of Islands, Union-Find, 20181217.
class UnionFind {
private:
    vector<int> father;
    int count = 0;
    
public:
    UnionFind(int n) {
        father = vector<int>(n, 0);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }
    }
    
    void setCount(int total) {
        count = total;
    }
    
    int getCount() {
        return count;
    }
    
    void connect(int a, int b) {
        int rootA = _find(a);
        int rootB = _find(b);
        if (rootA != rootB) {
            father[rootA] = rootB;
            count--;
        }
    }
    
private:
    int _find(int x) {
        if (father[x] == x) {
            return x;
        }
        
        return father[x] = _find(father[x]);
    }
};
class Solution {
public:
    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        UnionFind *unionFind = new UnionFind(m * n);
        
        int total = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    total++;
                }
            }
        }
        unionFind->setCount(total);
        
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '0') {
                    continue;
                }
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x < 0 || x >= m || y < 0 || y >= n) {
                        continue;
                    }
                    if (grid[x][y] == '1') {
                        unionFind->connect(i * n + j, x * n + y);
                    }
                }
            }
        }
        
        return unionFind->getCount();
    }
};

// LintCode 611 - Knight Shortest Path, Breadth-first Search, 20181218.
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int shortestPath(vector<vector<bool>> &grid, 
                     Point &source, Point &destination) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        if (grid[source.x][source.y] || 
            grid[destination.x][destination.y]) {
            return -1;
        }
        
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[source.x][source.y] = 0;
        vector<int> dx{1, 1, -1, -1, 2, 2, -2, -2};
        vector<int> dy{2, -2, 2, -2, 1, -1, 1, -1};
        
        queue<Point> q;
        q.push(source);
        while (!q.empty()) {
            Point curr = q.front();
            q.pop();
            for (int i = 0; i < 8; i++) {
                int x = curr.x + dx[i];
                int y = curr.y + dy[i];
                if (x < 0 || x >= n || y < 0 || y >= m || 
                    grid[x][y]) {
                    continue;
                }
                if (dist[curr.x][curr.y] + 1 < dist[x][y]) {
                    dist[x][y] = dist[curr.x][curr.y] + 1;
                    q.push(Point(x, y));
                }
            }
        }
        
        if (dist[destination.x][destination.y] == INT_MAX) {
            return -1;
        }
        return dist[destination.x][destination.y];
    }
};

// LintCode 630 - Knight Shortest Path II, Breadth-first Search, 20181218.
class Solution {
public:
    int shortestPath2(vector<vector<bool>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        int n = grid.size(), m = grid[0].size();
        if (grid[0][0] || grid[n - 1][m - 1]) {
            return -1;
        }
        
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;
        vector<int> dx{1, -1, 2, -2};
        vector<int> dy{2,  2, 1,  1};
        
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            int x = curr / m, y = curr % m;
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i], newY = y + dy[i];
                if (newX < 0 || newX >= n || 
                    newY < 0 || newY >= m || grid[x][y]) {
                    continue;
                }
                if (dist[x][y] + 1 < dist[newX][newY]) {
                    dist[newX][newY] = dist[x][y] + 1;
                    q.push(newX * m + newY);
                }
            }
        }
        
        if (dist[n - 1][m - 1] == INT_MAX) {
            return -1;
        }
        return dist[n - 1][m - 1];
    }
};

// LintCode 127 - Topological Sorting, Topological Sorting, 20181218.
/**
 * Definition for Directed graph.
 * struct DirectedGraphNode {
 *     int label;
 *     vector<DirectedGraphNode *> neighbors;
 *     DirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    vector<DirectedGraphNode *> topSort(
                    vector<DirectedGraphNode *> &graph) {
        vector<DirectedGraphNode *> result;
        if (graph.empty()) {
            return result;
        }
        
        unordered_map<DirectedGraphNode *, int> hm;
        for (DirectedGraphNode *node : graph) {
            for (DirectedGraphNode *nb : node->neighbors) {
                if (hm.count(nb)) {
                    hm[nb]++;
                } else {
                    hm[nb] = 1;
                }
            }
        }
        
        queue<DirectedGraphNode *> q;
        for (DirectedGraphNode *node : graph) {
            if (!hm.count(node)) {
                q.push(node);
                result.push_back(node);
            }
        }
        
        while (!q.empty()) {
            DirectedGraphNode *node = q.front();
            q.pop();
            for (DirectedGraphNode *nb : node->neighbors) {
                hm[nb]--;
                if (hm[nb] == 0) {
                    hm.erase(nb);
                    q.push(nb);
                    result.push_back(nb);
                }
            }
        }
        
        return result;
    }
};

// LeetCode 207 - Course Schedule, 
// Topological Sort, Breadth-first Search, 20181219.
class Solution {
public:
    bool canFinish(int numCourses, 
                   vector<pair<int, int>> &prerequisites) {
        if (numCourses <= 1 || prerequisites.empty()) {
            return true;
        }
        
        vector<vector<int>> graph(numCourses);
        vector<int> degree(numCourses, 0);
        for (pair<int, int> p : prerequisites) {
            graph[p.second].push_back(p.first);
            degree[p.first]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0;
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            count++;
            for (int i : graph[n]) {
                degree[i]--;
                if (degree[i] == 0) {
                    q.push(i);
                }
            }
        }
        
        return count == numCourses;
    }
};

// LeetCode 210 - Course Schedule II, 
// Topological Sort, Breadth-first Search, 20181219.
class Solution {
public:
    vector<int> findOrder(int numCourses, 
                          vector<pair<int, int>> &prerequisites) {
        vector<int> result;
        if (numCourses <= 1 || prerequisites.empty()) {
            for (int i = 0; i < numCourses; i ++) {
                result.push_back(i);
            }
            return result;
        }
        
        vector<vector<int>> graph(numCourses);
        vector<int> degree(numCourses, 0);
        for (pair<int, int> p : prerequisites) {
            graph[p.second].push_back(p.first);
            degree[p.first]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            result.push_back(n);
            for (int i : graph[n]) {
                degree[i]--;
                if (degree[i] == 0) {
                    q.push(i);
                }
            }
        }
        
        if (result.size() < numCourses) {
            return vector<int>();
        }
        return result;
    }
};

// LeetCode 269 - Alien Dictionary, 
// Topological Sort, Breadth-first Search, 20181219.
class Solution {
public:
    string alienOrder(vector<string> &words) {
        if (words.empty()) {
            return "";
        }
        
        unordered_map<char, int> degree;
        for (string word : words) {
            for (char c : word) {
                degree[c] = 0;
            }
        }
        
        unordered_map<char, vector<char>> graph;
        for (int i = 0; i < words.size() - 1; i++) {
            int minLen = min(words[i].size(), words[i + 1].size());
            for (int j = 0; j < minLen; j++) {
                if (words[i][j] != words[i + 1][j]) {
                    graph[words[i][j]].push_back(words[i + 1][j]);
                    break;
                }
            }
        }
        
        for (pair<const char, vector<char>> g : graph) {
            for (char c : g.second) {
                degree[c]++;
            }
        }
        
        queue<char> q;
        for (pair<const char, int> d : degree) {
            if (d.second == 0) {
                q.push(d.first);
            }
        }
        
        string result;
        while (!q.empty()) {
            char ch = q.front();
            q.pop();
            result.push_back(ch);
            for (char c : graph[ch]) {
                degree[c]--;
                if (degree[c] == 0) {
                    q.push(c);
                }
            }
        }
        
        if (result.size() != degree.size()) {
            return "";
        }
        return result;
    }
};

// LeetCode 261 - Graph Valid Tree, 
// Topological Sort, Breadth-first Search, 20181219.
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>> &edges) {
        if (n <= 0) {
            return false;
        }
        if (edges.size() != n - 1) {
            return false;
        }
        
        vector<vector<int>> graph(n);
        for (pair<int, int> p : edges) {
            int u = p.first;
            int v = p.second;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        queue<int> q;
        q.push(0);
        unordered_set<int> visited;
        visited.insert(0);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int nb : graph[node]) {
                if (visited.count(nb)) {
                    continue;
                }
                visited.insert(nb);
                q.push(nb);
            }
        }
        
        return visited.size() == n;
    }
};

// LintCode 618 - Search Graph Nodes, 
// Topological Sort, Breadth-first Search, 20181219.
/**
 * Definition for Undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
     UndirectedGraphNode *searchNode(vector<UndirectedGraphNode *> &graph,
                                     map<UndirectedGraphNode *, int> &values,
                                     UndirectedGraphNode *node,
                                     int target) {
        if (graph.empty()) {
            return nullptr;
        }
        if (values[node] == target) {
            return node;
        }
        
        queue<UndirectedGraphNode *> q;
        q.push(node);
        unordered_set<UndirectedGraphNode *> visited;
        visited.insert(node);
        while (!q.empty()) {
            node = q.front();
            q.pop();
            for (UndirectedGraphNode *nb : node->neighbors) {
                if (visited.count(nb)) {
                    continue;
                }
                if (values[nb] == target) {
                    return nb;
                }
                visited.insert(nb);
                q.push(nb);
            }
        }
        
        return nullptr;
    }
};

// LeetCode 323 - Number of Connected Components in an Undirected Graph, 
// Topological Sort, Breadth-first Search, 20181219.
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>> &edges) {
        if (n == 0 || edges.empty()) {
            return n;
        }
        
        vector<vector<int>> graph(n);
        for (pair<int, int> p : edges) {
            int u = p.first;
            int v = p.second;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        int count = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                _bfs(graph, visited, i);
                count++;
            }
        }
        
        return count;
    }
    
private:
    void _bfs(vector<vector<int>> &graph, 
              vector<bool> &visited, int index) {
        queue<int> q;
        q.push(index);
        visited[index] = true;
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            for (int nb : graph[n]) {
                if (visited[nb]) {
                    continue;
                }
                visited[nb] = true;
                q.push(nb);
            }
        }
    }
};

// LeetCode 323 - Number of Connected Components in an Undirected Graph, 
// Union Find, 20181219.
class UnionFind {
private:
    vector<int> father;
    int count;
    
    int _find(int x) {
        if (father[x] == x) {
            return x;
        }
        return father[x] = _find(father[x]);
    }
    
public:
    UnionFind(int n) {
        count = n;
        father = vector<int>(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }
    }
    
    int getCount() {
        return count;
    }
    
    void connect(int a, int b) {
        int rootA = _find(a);
        int rootB = _find(b);
        if (rootA != rootB) {
            father[rootA] = rootB;
            count--;
        }
    }
};

class Solution {
public:
    int countComponents(int n, vector<pair<int, int>> &edges) {
        if (n == 0 || edges.empty()) {
            return n;
        }
        
        UnionFind *unionFind = new UnionFind(n);
        for (pair<int, int> e : edges) {
            unionFind->connect(e.first, e.second);
        }
        
        return unionFind->getCount();
    }
};

// LintCode 431 - Connected Component in Undirected Graph, 
// Topological Sort, Breadth-first Search, 20181219.
/**
 * Definition for Undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    vector<vector<int>> connectedSet(
                vector<UndirectedGraphNode *> nodes) {
        vector<vector<int>> results;
        if (nodes.empty()) {
            return results;
        }
        
        int n = nodes.size();
        unordered_set<UndirectedGraphNode *> visited;
        for (UndirectedGraphNode *node : nodes) {
            if (!visited.count(node)) {
                _bfs(nodes, node, visited, results);
            }
        }
        
        return results;
    }
    
private:
    void _bfs(vector<UndirectedGraphNode *> &nodes, 
              UndirectedGraphNode *node, 
              unordered_set<UndirectedGraphNode *> &visited, 
              vector<vector<int>> &results) {
        vector<int> result;
        queue<UndirectedGraphNode *> q;
        q.push(node);
        visited.insert(node);
        while (!q.empty()) {
            node = q.front();
            q.pop();
            result.push_back(node->label);
            for (UndirectedGraphNode *nb : node->neighbors) {
                if (visited.count(nb)) {
                    continue;
                }
                visited.insert(nb);
                q.push(nb);
            }
        }
        sort(result.begin(), result.end());
        results.push_back(result);
    }
};

// LintCode 431 - Connected Component in Undirected Graph, 
// Union Find, 20181220.
/**
 * Definition for Undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class UnionFind {
private:
    unordered_map<int, int> father;

public:
    UnionFind(unordered_set<int> &nodes) {
        for (int node : nodes) {
            father.insert({node, node});
        }
    }
    
    int find(int x) {
        if (father[x] == x) {
            return x;
        }
        return father[x] = find(father[x]);
    }
    
    void connect(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            father[rootA] = rootB;
        }
    }
};
class Solution {
public:
    vector<vector<int>> connectedSet(
                    vector<UndirectedGraphNode *> nodes) {
        vector<vector<int>> result;
        if (nodes.empty()) {
            return result;
        }
        
        unordered_set<int> nodeSet;
        for (UndirectedGraphNode *node : nodes) {
            nodeSet.insert(node->label);
            for (UndirectedGraphNode *nb : node->neighbors) {
                nodeSet.insert(nb->label);
            }
        }
        
        UnionFind *unionFind = new UnionFind(nodeSet);
        for (UndirectedGraphNode *node : nodes) {
            for (UndirectedGraphNode *nb : node->neighbors) {
                unionFind->connect(node->label, nb->label);
            }
        }
        
        unordered_map<int, vector<int>> hashMap;
        for (int node : nodeSet) {
            int root = unionFind->find(node);
            hashMap[root].push_back(node);
        }
        for (pair<const int, vector<int>> &p : hashMap) {
            sort(p.second.begin(), p.second.end());
            result.push_back(p.second);
        }
        
        return result;
    }
};

// LeetCode 444 - Sequence Reconstruction, 
// Topological Sort, Breadth-first Search, 20181224
class Solution {
public:
    bool sequenceReconstruction(vector<int> &org, 
                                vector<vector<int>> &seqs) {
        if (org.empty() && seqs.empty()) {
            return true;
        }
        if (org.empty() || seqs.empty()) {
            return false;
        }
        
        unordered_map<int, unordered_set<int>> graph;
        unordered_map<int, int> degree;
        for (int e : org) {
            graph[e] = unordered_set<int>();
            degree[e] = 0;
        }
        
        int n = org.size();
        int count = 0;
        for (vector<int> &seq : seqs) {
            count += seq.size();
            if (seq.size() > 0 && (seq[0] <= 0 || seq[0] > n)) {
                return false;
            }
            for (int i = 1; i < seq.size(); i++) {
                if (seq[i] <= 0 || seq[i] > n) {
                    return false;
                }
                if (!graph[seq[i - 1]].count(seq[i])) {
                    graph[seq[i - 1]].insert(seq[i]);
                    degree[seq[i]]++;
                }
            }
        }
        
        if (count < n) {
            return false;
        }
        
        queue<int> q;
        for (pair<const int, int> &p : degree) {
            if (p.second == 0) {
                q.push(p.first);
            }
        }
        
        count = 0;
        while (q.size() == 1) {
            int curr = q.front();
            q.pop();
            if (curr != org[count]) {
                return false;
            }
            count++;
            for (int next : graph[curr]) {
                degree[next]--;
                if (degree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return count == org.size();
    }
};

// LintCode 598 - Zombie in Matrix, 
// Topological Sort, Breadth-first Search
class Solution {
public:
    int zombie(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        queue<int> curr, next;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    curr.push(i * n + j);
                }
            }
        }
        
        int dist = 0;
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        while (!curr.empty()) {
            while (!curr.empty()) {
                int x = curr.front() / n;
                int y = curr.front() % n;
                curr.pop();
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx < 0 || nx >= m || 
                        ny < 0 || ny >= n || 
                        grid[nx][ny] != 0) {
                        continue;
                    }
                    grid[nx][ny] = 1;
                    next.push(nx * n + ny);
                }
            }
            dist++;
            swap(curr, next);
        }
        dist--;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    return -1;
                }
            }
        }
        
        return dist;
    }
};

// LeetCode 317 - Shortest Distance from All Buildings, 
// Topological Sort, Breadth-first Search, 20181226
class Solution {
public:
    int shortestDistance(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        
        vector<int> houses, empties;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    houses.push_back(i * n + j);
                } else if (grid[i][j] == 0) {
                    empties.push_back(i * n + j);
                }
            }
        }
        
        vector<vector<int>> dist(m, vector<int>(n, 0));
        vector<vector<int>> count(m, vector<int>(n, 0));
        for (int house : houses) {
            _bfs(grid, house, dist, count);
        }
        
        int minDist = INT_MAX;
        for (int empty : empties) {
            int x = empty / n, y = empty % n;
            if (count[x][y] != houses.size()) {
                continue;
            }
            minDist = min(minDist, dist[x][y]);
        }
        
        return minDist == INT_MAX ? -1 : minDist;
    }
    
private:
    void _bfs(vector<vector<int>> &grid, int start, 
              vector<vector<int>> &dist, 
              vector<vector<int>> &count) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<int> curr, next;
        curr.push(start);
        
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        
        int steps = 0;
        while (!curr.empty()) {
            steps++;
            while (!curr.empty()) {
                int x = curr.front() / n;
                int y = curr.front() % n;
                curr.pop();
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || 
                        grid[nx][ny] != 0 || visited[nx][ny]) {
                        continue;
                    }
                    next.push(nx * n + ny);
                    visited[nx][ny] = true;
                    dist[nx][ny] += steps;
                    count[nx][ny]++;
                }
            }
            swap(curr, next);
        }
    }
};

// LintCode 573 - Build Post Office II, 
// Topological Sort, Breadth-first Search, 20181226
class Solution {
public:
    int shortestDistance(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        
        int m = grid.size(), n = grid[0].size();
        vector<int> houses, empties;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    houses.push_back(i * n + j);
                } else if (grid[i][j] == 0) {
                    empties.push_back(i * n + j);
                }
            }
        }
        
        vector<vector<int>> dist(m, vector<int>(n, 0));
        vector<vector<int>> count(m, vector<int>(n, 0));
        for (int house : houses) {
            _bfs(grid, house, dist, count);
        }
        
        int minDist = INT_MAX;
        for (int empty : empties) {
            int x = empty / n, y = empty % n;
            if (count[x][y] != houses.size()) {
                continue;
            }
            minDist = min(minDist, dist[x][y]);
        }
        
        if (minDist == INT_MAX) {
            return -1;
        }
        return minDist;
    }
    
private:
    void _bfs(vector<vector<int>> &grid, int start, 
              vector<vector<int>> &dist, 
              vector<vector<int>> &count) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<int> curr, next;
        curr.push(start);
        
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        
        int steps = 0;
        while (!curr.empty()) {
            steps++;
            while (!curr.empty()) {
                int x = curr.front() / n;
                int y = curr.front() % n;
                curr.pop();
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || 
                        grid[nx][ny] != 0 || visited[nx][ny]) {
                        continue;
                    }
                    next.push(nx * n + ny);
                    visited[nx][ny] = true;
                    dist[nx][ny] += steps;
                    count[nx][ny]++;
                }
            }
            swap(curr, next);
        }
    }
};
