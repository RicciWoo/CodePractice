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

    vector<int> getFinalRoots() {
        for (int i = 0; i < father.size(); i++) {
            _find(i);
        }

        return father;
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
    vector<int> countGroups(vector<vector<int>> &grid, vector<int> &t) {
        vector<int> results;
        if (grid.empty() || grid[0].empty()) {
            return results;
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

        vector<int> roots = unionFind->getFinalRoots();

        unordered_map<int, int> sizes;
        for (int i = 0; i < roots.size(); i++) {
            int root = roots[i];
            int x = root / n, y = root % n;
            if (grid[x][y] == 0) {
                continue;
            }

            if (!sizes.count(root)) {
                sizes[root] = 1;
            } else {
                sizes[root]++;
            }
        }

        unordered_map<int, int> counts;
        for (auto &p : sizes) {
            if (!counts.count(p.second)) {
                counts[p.second] = 1;
            } else {
                counts[p.second]++;
            }
        }

        for (int &i : t) {
            if (counts.count(i)) {
                results.push_back(counts[i]);
            } else {
                results.push_back(0);
            }
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
    
    vector<int> t{1, 10, 20, 2, 6};

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

    vector<int> results;
    Solution *solution = new Solution;
    results = solution->countGroups(m, t);
    cout << "# of groups: ";
    for (int &i : results) {
        cout << i << ", ";
    }
    cout << endl;
}