#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Counting Groups, 20181114
class UnionFind {
public:
    UnionFind(int n) {
        father = vector<int>(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }
    }
    
    void connect(int a, int b) {
        int root_a = _find(a);
        int root_b = _find(b);
        if (root_a != root_b) {
            father[root_a] = root_b;
            count--;
        }
    }
    
    int getCount() {
        return count;
    }
    
    void setCount(int total) {
        count = total;
    }
    
    unordered_map<int, int> calculateSizes() {
        unordered_map<int, int> sizes;
        for (int i = 0; i < father.size(); i++) {
            int root = _find(i);
            if (root != i) {
                sizes[root]++;
            }
        }

        unordered_map<int, int> counts;
        for (auto &p : sizes) {
            counts[p.second]++;
        }

        return counts;
    }

private:
    vector<int> father;
    int count;
    
    int _find(int x) {
        if (father[x] == x) {
            return x;
        }
        
        return father[x] = _find(father[x]);
    }
};
class Solution {
public:
    int numIslands(vector<vector<int>> &grid, vector<int> &t) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        UnionFind *unionFind = new UnionFind(m * n);
        
        int total = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    total++;
                }
            }
        }
        
        unionFind->setCount(total);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int curr = i * n + j;
                    if (i > 0 && grid[i - 1][j] == 1) {
                        unionFind->connect(curr, (i - 1) * n + j);
                    }
                    if (i < m - 1 && grid[i + 1][j] == 1) {
                        unionFind->connect(curr, (i + 1) * n + j);
                    }
                    if (j > 0 && grid[i][j - 1] == 1) {
                        unionFind->connect(curr, i * n + (j - 1));
                    }
                    if (j < n - 1 && grid[i][j + 1] == 1) {
                        unionFind->connect(curr, i * n + (j + 1));
                    }
                }
            }
        }

        unordered_map<int, int> counts;
        counts = unionFind->calculateSizes();
        vector<int> results;
        for (int &i : t) {
            results.push_back(counts[i]);
        }

        return results;
    }
};

int main(int argc, char **argv) {
    vector<vector<int>> m{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
                          {1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, 
                          {1, 1, 1, 0, 0, 0, 0, 1, 1, 1}, 
                          {1, 1, 0, 0, 1, 0, 0, 1, 1, 1}, 
                          {1, 0, 1, 0, 0, 1, 1, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
                          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
                          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    
    vector<int> t{5, 1, 10, 20, 2, 6};

    cout << "the grid: " << endl;
    for (vector<int> &n : m) {
        cout << "    ";
        for (int &i : n) {
            cout << i << ", ";
        }
        cout << endl;
    }
    cout << "search size: ";
    for (int &i : t) {
        cout << i << ", ";
    }
    cout << endl;

    // Solution *solution = new Solution;
    // int num = solution->numIslands(m);
    // cout << "# of Islands: " << num << endl;

    vector<int> result;
    Solution *solution = new Solution;
    result = solution->countGroups(m, t);
    cout << "# of groups: ";
    for (int &i : result) {
        cout << i << ", ";
    }
    cout << endl;
}