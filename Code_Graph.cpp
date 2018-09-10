/******************** Graph ********************/

// Courses Schedule, use Topology Sort
class Solution {
public:
    bool canFinish(int numCourses, 
                   vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> preNum(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            graph[prerequisites[i].second].push_back(
                prerequisites[i].first);
            preNum[prerequisites[i].first]++;
        }
        for (int i = 0; i < numCourses; i++) {
            bool availableCourse = false;
            for (int j = 0; j < numCourses; j++) {
                if (preNum[j] == 0) {
                    for (int k : graph[j]) preNum[k]--;
                    availableCourse = true;
                    preNum[j] = -1;
                    break;
                }
            }
            if (!availableCourse) return false;
        }
        return true;
    }
};

// Alien Dictionary, use Topology Sort
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> hm;
        unordered_set<char> hs;
        queue<char> q;
        string result = "";
        for (string word : words)
            for (char c : word) hs.insert(c);
        for (char c : hs) hm.insert({c, unordered_set<char>()});
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
            if (j == minLen && 
                words[i].size() > words[i + 1].size())
                return "";
        }
        for (pair<const char, unordered_set<char>> &entry : hm) {
            if (entry.second.empty()) {
                q.push(entry.first);
                result.push_back(entry.first);
            }
        }
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
        if (result.size() == hs.size())
            return result;
        else return "";
    }
};


// Clone Graph, use Topology Sort
// Definition for undirected graph.
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> hm;
        queue<UndirectedGraphNode *> q;
        UndirectedGraphNode *head = new UndirectedGraphNode(node->label);
        hm.insert({node, head});
        q.push(node);
        while (!q.empty()) {
            UndirectedGraphNode *curNode = q.front();
            q.pop();
            for (UndirectedGraphNode *neighbor : curNode->neighbors) {
                if (!hm.count(neighbor)) {
                    q.push(neighbor);
                    UndirectedGraphNode *newNeighbor = 
                        new UndirectedGraphNode(neighbor->label);
                    hm.insert({neighbor, newNeighbor});
                }
                hm[curNode]->neighbors.push_back(hm[neighbor]);
            }
        }
        return head;
    }
};

// Minimum Height Trees, use Topology Sort
class Solution {
public:
    vector<int> findMinHeightTrees(int n, 
                    vector<pair<int, int>>& edges) {
        vector<int> result;
        if (n < 1) return result;
        vector<unordered_set<int>> graph;
        for (int i = 0; i < n; i++) 
            graph.push_back(unordered_set<int>());
        for (int i = 0; i < edges.size(); i++) {
            graph[edges[i].first].insert(edges[i].second);
            graph[edges[i].second].insert(edges[i].first);
        }
        queue<int> leaves;
        for (int i = 0; i < n; i++)
            if (graph[i].size() <= 1) leaves.push(i);
        while (n > 2) {
            n -= leaves.size();
            queue<int> newLeaves;
            while (!leaves.empty()) {
                int leaf = leaves.front();
                leaves.pop();
                int neighbor = *graph[leaf].begin();
                graph[neighbor].erase(leaf);
                if (graph[neighbor].size() == 1)
                    newLeaves.push(neighbor);
            }
            leaves = newLeaves;
        }
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }
        return result;
    }
};








