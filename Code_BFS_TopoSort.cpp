/******************** BFS and Topology Sort ********************/

// Binary Tree Level Order Traversal
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    /**
     * @param root: A Tree
     * @return: Level order a list of lists of integer
     */
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        if (root == NULL) {
            return result;
        }
        
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            vector<int> level;
            int size = q.size();
            for (int i = 0; i < size; i++)  {
                TreeNode *node = q.front();
                q.pop();
                level.push_back(node->val);
                if (node->left != NULL) {
                    q.push(node->left);
                }
                if (node->right != NULL) {
                    q.push(node->right);
                }
            }
            result.push_back(level);
        }
    }
};

// Binary Tree Serialization
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    /**
     * This method will be invoked first, you should design your own algorithm 
     * to serialize a binary tree which denote by a root node to a string which
     * can be easily deserialized by your own "deserialize" method later.
     */
    string serialize(TreeNode *root) {
        if (root == nullptr) {
            return "{}";
        }
        
        vector<TreeNode *> q;
        q.push_back(root);
        
        for (int i = 0; i < q.size(); i++) {
            TreeNode *node = q[i];
            if (node == nullptr) {
                continue;
            }
            q.push_back(node->left);
            q.push_back(node->right);
        }
        
        while (!q.empty() && q[q.size() - 1] == nullptr) {
            q.pop_back();
        }
        
        if (q.empty()){
            return "{}";
        }
        
        stringstream ss;
        ss << "{" << q[0]->val;
        for (int i = 1; i < q.size(); i++) {
            if (q[i] == nullptr) {
                ss << ",#";
            } else {
                ss << "," << q[i]->val;
            }
        }
        ss << "}";
        
        return ss.str();
    }

    /**
     * This method will be invoked second, the argument data is what exactly
     * you serialized at method "serialize", that means the data is not given by
     * system, it's given by your own serialize method. So the format of data is
     * designed by yourself, and deserialize it here as you serialize it in 
     * "serialize" method.
     */
    TreeNode * deserialize(string &data) {
        if (data == "{}") {
            return nullptr;
        }
        
        vector<string> vals = _split(data.substr(1, data.size() - 2), ",");
        TreeNode *root = new TreeNode(atoi(vals[0].c_str()));
        queue<TreeNode *> q;
        q.push(root);
        
        bool isLeftChild = true;
        for (int i = 1; i < vals.size(); i++) {
            if (vals[i] != "#") {
                TreeNode *node = new TreeNode(atoi(vals[i].c_str()));
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
    vector<string> _split(const string &str, string delim) {
        vector<string> results;
        int lastIndex = 0, index;
        while ((index = str.find(delim, lastIndex)) != string::npos) {
            results.push_back(str.substr(lastIndex, index - lastIndex));
            lastIndex = index + delim.size();
        }
        
        if (lastIndex != str.size()) {
            results.push_back(str.substr(lastIndex, str.size() - lastIndex));
        }
        
        return results;
    }
};

// Binary Tree Level Order Traversal II

// Binary Tree Zigzag Level Order Traversal

// Convert Binary Tree to Linked List by Depth

// Clone Graph
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
    /*
     * @param node: A undirected graph node
     * @return: A undirected graph node
     */
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        UndirectedGraphNode *p1 = node;
        UndirectedGraphNode *p2 = new UndirectedGraphNode(p1->label);
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> map;
        map[p1] = p2;
        queue<UndirectedGraphNode *> q;
        q.push(node);
        
        while (!q.empty()) {
            p1 = q.front();
            p2 = map[p1];
            q.pop();
            for (int i = 0; i < p1->neighbors.size(); i++) {
                UndirectedGraphNode *nb = p1->neighbors[i];
                if (map.count(nb)) {
                    p2->neighbors.push_back(map[nb]);
                } else {
                    UndirectedGraphNode *temp = new UndirectedGraphNode(nb->label);
                    p2->neighbors.push_back(temp);
                    map[nb] = temp;
                    q.push(nb);
                }
            }
        }
        
        return map[node];
    }
};

// Word Ladder
class Solution {
public:
    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: An integer
     */
    int ladderLength(string &start, string &end, unordered_set<string> &dict) {
        if (start == end) {
            return 1;
        }
        int n = start.size(); 
        if (n < 1 || n != end.size()) {
            return 0;
        }
        
        queue<string> q;
        q.push(start);
        dict.erase(start);
        int length = 2;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                for (int i = 0; i < n; i++) {
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
                            q.push(word);
                            dict.erase(word);
                        }
                    }
                    word[i] = oldChar;
                }
            }
            length++;
        }
        return 0;
    }
};

// Number of Islands
class Solution {
public:
    /**
     * @param grid: a boolean 2D matrix
     * @return: an integer
     */
    int numIslands(vector<vector<bool>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int n = grid.size(), m = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j]) {
                    _bfs(grid, i, j);
                    count++;
                }
            }
        }
        
        return count;
    }
    
private:
    void _bfs(vector<vector<bool>> &grid, int x, int y) {
        vector<int> dirX{0, 1, -1, 0};
        vector<int> dirY{1, 0, 0, -1};
        
        queue<vector<int>> q;
        q.push({x, y});
        grid[x][y] = false;
        
        while (!q.empty()) {
            x = q.front()[0];
            y = q.front()[1];
            q.pop();
            for (int i = 0; i < 4; i++) {
                int newX = x + dirX[i];
                int newY = y + dirY[i];
                if (!_inBound(grid, newX, newY)) {
                    continue;
                }
                if (grid[newX][newY]) {
                    grid[newX][newY] = false;
                    q.push({newX, newY});
                }
            }
        }
    }
    
    bool _inBound(vector<vector<bool>> &grid, int x, int y) {
        int n = grid.size(), m = grid[0].size();
        
        return x >= 0 && x < n && y >= 0 && y < m;
    }
};

// Knight Shortest Path
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
    /**
     * @param grid: a chessboard included 0 (false) and 1 (true)
     * @param source: a point
     * @param destination: a point
     * @return: the shortest path 
     */
    int shortestPath(vector<vector<bool>> &grid, Point &source, Point &destination) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        if (grid[source.x][source.y] || 
            grid[destination.x][destination.y]) {
            return -1;
        }
        
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> record(n, vector<int>(m, INT_MAX));
        record[source.x][source.y] = 0;
        
        vector<int> dx{1, 1, -1, -1, 2, 2, -2, -2};
        vector<int> dy{2, -2, 2, -2, 1, -1, 1, -1};
        
        queue<Point> q;
        q.push(source);
        
        while (!q.empty()) {
            Point head = q.front();
            q.pop();
            for (int k = 0; k < 8; k++) {
                int x = head.x + dx[k];
                int y = head.y + dy[k];
                if (x >= 0 && x < n && y >= 0 && y < m && !grid[x][y] && 
                    record[head.x][head.y] + 1 < record[x][y]) {
                    record[x][y] = record[head.x][head.y] + 1;
                    q.push(Point(x, y));
                }
            }
        }
        
        if (record[destination.x][destination.y] == INT_MAX) {
            return -1;
        }
        return record[destination.x][destination.y];
    }
};

// Topological Sorting
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
    /*
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */
    vector<DirectedGraphNode *> topSort(vector<DirectedGraphNode *> &graph) {
        vector<DirectedGraphNode *> result;
        unordered_map<DirectedGraphNode *, int> map;
        for (DirectedGraphNode *node : graph) {
            for (DirectedGraphNode *nb : node->neighbors) {
                if (map.count(nb)) {
                    map[nb]++;
                } else {
                    map[nb] = 1;
                }
            }
        }
        
        queue<DirectedGraphNode *> q;
        for (DirectedGraphNode *node : graph) {
            if (!map.count(node)) {
                q.push(node);
                result.push_back(node);
            }
        }
        
        while (!q.empty()) {
            DirectedGraphNode *node = q.front();
            q.pop();
            for (DirectedGraphNode *n : node->neighbors) {
                map[n]--;
                if (map[n] == 0) {
                    result.push_back(n);
                    q.push(n);
                }
            }
        }
        
        return result;
    }
};

// Course Schedule I
class Solution {
public:
    /*
     * @param numCourses: a total of n courses
     * @param prerequisites: a list of prerequisite pairs
     * @return: true if can finish all courses or false
     */
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (numCourses <= 0) {
            return false;
        }
        if (prerequisites.empty()) {
            return true;
        }
        
        // use multiset because test case has duplicate [1,9]
        vector<unordered_multiset<int>> edges(numCourses);
        vector<int> degree(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            edges[prerequisites[i].second].insert(prerequisites[i].first);
            degree[prerequisites[i].first]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        
        int node = 0;
        while (!q.empty()) {
            int x = q.front(); 
            q.pop();
            node++;
            for (int i : edges[x]) {
                degree[i]--;
                if (degree[i] == 0) {
                    q.push(i);
                }
            }
        }
        
        return node == numCourses;
    }
};

// Course Schedule II
class Solution {
public:
    /*
     * @param numCourses: a total of n courses
     * @param prerequisites: a list of prerequisite pairs
     * @return: the course order
     */
    vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites) {
        vector<int> result;
        if (numCourses <= 0) {
            return result;
        }
        if (prerequisites.empty()) {
            for (int i = 0; i < numCourses; i++) {
                result.push_back(i);
            }
            return result;
        }
        
        // use multiset because test case has duplicate [1,9]
        vector<unordered_multiset<int>> edges(numCourses);
        vector<int> degree(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            edges[prerequisites[i].second].insert(prerequisites[i].first);
            degree[prerequisites[i].first]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int x = q.front(); 
            q.pop();
            result.push_back(x);
            for (int i : edges[x]) {
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

// Alien Dictionary, LintCode 892
class Solution {
public:
    /**
     * @param words: a list of words
     * @return: a string which is correct order
     */
    string alienOrder(vector<string> &words) {
        unordered_map<char, unordered_set<char>> graph;
        _constructGraph(words, graph);
        return _topologicalSorting(graph);
    }
    
private:
    void _constructGraph(vector<string> &words, 
        unordered_map<char, unordered_set<char>> &graph) {
        // create node
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j <words[i].size(); j++) {
                char c = words[i][j];
                if (!graph.count(c)) {
                    graph[c] = unordered_set<char>();
                }
            }
        }
        
        // create edges
        for (int i = 0; i < words.size() - 1; i++) {
            int index = 0;
            while (index < words[i].size() && index < words[i + 1].size()) {
                if (words[i][index] != words[i + 1][index]) {
                    graph[words[i][index]].insert(words[i + 1][index]);
                    break;
                }
                index++;
            }
        }
    }
    
    string _topologicalSorting(unordered_map<char, unordered_set<char>> &graph) {
        unordered_map<char, int> indegree;
        _getIndegree(graph, indegree);
        queue<char> pq;
        
        for (pair<const char, int> item : indegree) {
            if (item.second == 0) {
                pq.push(item.first);
            }
        }
        
        string result;
        while (!pq.empty()) {
            char head = pq.front();
            pq.pop();
            result.push_back(head);
            for (char nb : graph[head]) {
                indegree[nb]--;
                if (indegree[nb] == 0) {
                    pq.push(nb);
                }
            }
        }
        
        if (result.size() != indegree.size()) {
            return "";
        }
        return result;
    }
    
    void _getIndegree(unordered_map<char, unordered_set<char>> &graph, 
        unordered_map<char, int> &indegree) {
        for (pair<const char, unordered_set<char>> item : graph) {
            indegree[item.first] = 0;
        }
        
        for (pair<const char, unordered_set<char>> item : graph) {
            for (char v : item.second) {
                indegree[v]++;
            }
        }
    }
};

// Alien Dictionary-2, LintCode 892
class Node {
public:
    int degree;
    vector<int> neighbors;
    Node() {
        degree = 0;
    }
};
class Solution {
public:
    /**
     * @param words: a list of words
     * @return: a string which is correct order
     */
    string alienOrder(vector<string> &words) {
        vector<Node> nodes(26);
        vector<bool> exist(26, false);
        
        for (int i = 0; i < words.size(); i++) {
            int startPoint = 0, endPoint = 0;
            for (int j = 0; j < words[i].size(); j++) {
                exist[words[i][j] - 'a'] = true;
            }
            
            if (i != words.size() - 1) {
                for (int j = 0; j < min(words[i].size(), 
                                        words[i + 1].size()); j++) {
                    if (words[i][j] != words[i + 1][j]) {
                        startPoint = words[i][j] - 'a';
                        endPoint = words[i + 1][j] - 'a';
                        break;
                    }
                }
            }
            if (startPoint != endPoint) {
                nodes[startPoint].neighbors.push_back(endPoint);
                nodes[endPoint].degree++;
            }
        }
        
        // Topological Sorting
        queue<int> q;
        string result = "";
        for (int i = 0; i < 26; i++) {
            if (nodes[i].degree == 0 && exist[i]) {
                q.push(i);
                result += (char)('a' + i);
            }
        }
        
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i : nodes[now].neighbors) {
                nodes[i].degree--;
                if (nodes[i].degree == 0) {
                    q.push(i);
                    result += (char)('a' + i);
                }
            }
        }
        
        for (int i = 0; i < 26; i++) {
            if (nodes[i].degree != 0) {
                return "";
            }
        }
        
        return result;
    }
};

// Alien Dictionary, LeetCode 269
class Solution {
public:
    string alienOrder(vector<string>& words) {
        string result = "";
        if (words.empty()) {
            return result;
        }
        
        unordered_map<char, unordered_set<char>> hm;
        unordered_set<char> hs;
        queue<char> q;
        
        // get all characters
        for (string word : words) {
            for (char c : word) {
                hs.insert(c);
            }
        }
        
        // create nodes
        for (char c : hs) {
            hm.insert({c, unordered_set<char>()});
        }
        
        // create edges
        for (int i = 0; i < words.size() - 1; i++) {
            int minLen = min(words[i].size(), 
                             words[i + 1].size());
            int j = 0; 
            for (j = 0; j < minLen; j++) {
                if (words[i][j] != words[i + 1][j]) {
                    hm[words[i + 1][j]].insert(words[i][j]);
                    break;
                }
            }
            // forming circle, not allowed, return ""
            if (j == minLen && 
                words[i].size() > words[i + 1].size())
                return "";
        }
        
        // put zero indegree into queue
        for (pair<const char, unordered_set<char>> &entry : hm) {
            if (entry.second.empty()) {
                q.push(entry.first);
                result.push_back(entry.first);
            }
        }
        
        // topological sorting
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            for (pair<const char, unordered_set<char>> &entry : hm) {
                if (entry.second.count(c)) {
                    entry.second.erase(c);
                    if (entry.second.empty()) {
                        q.push(entry.first);
                        result.push_back(entry.first);
                    }
                }
            }
        }
        
        // some nodes are missing
        if (result.size() != hs.size()) {
            return "";
        }
        return result;
    }
};

// Graph Valid Tree

// Search Graph Nodes

// Connected Component in Undirected Graph

// Sequence Reconstruction
class Solution {
public:
    /**
     * @param org: a permutation of the integers from 1 to n
     * @param seqs: a list of sequences
     * @return: true if it can be reconstructed only one or false
     */
    bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
        unordered_map<int, int> pos, pre;
        
        for (int i = 0; i < org.size(); i++) {
            pos[org[i]] = i;
        }
        
        for (auto &seq : seqs) {
            for (int i = 0; i < seq.size(); i++) {
                if (!pos.count(seq[i])) {
                    return false;
                }
                if (i > 0 && pos[seq[i - 1]] >= pos[seq[i]]) {
                    return false;
                }
                if (!pre.count(seq[i])) {
                    pre[seq[i]] = (i > 0) ? pos[seq[i - 1]] : -1;
                } else {
                    pre[seq[i]] = max(pre[seq[i]], (i > 0) ? pos[seq[i - 1]] : -1);
                }
            }
        }
        
        for (int i = 0; i < org.size(); i++) {
            if (pre[org[i]] != i - 1) {
                return false;
            }
        }
        return true;
    }
};

// Zombie in Matrix

// Build Post Office II
