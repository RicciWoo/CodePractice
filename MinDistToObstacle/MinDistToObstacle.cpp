#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Distance to Obstacle, Breadth-first Search, 20181130
class Solution {
public:
    int MinDistToObstacle(vector<vector<int>> &lot) {
        if (lot.empty() || lot[0].empty()) {
            return -1;
        }

        int m = lot.size(), n = lot[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        int minDist = INT_MAX;
        _bfs(lot, dist, 0, 0, 1, minDist);

        return minDist;
    }

private:
    void _bfs(vector<vector<int>> &lot, vector<vector<int>> &dist, 
             int x, int y, int currDist, int &minDist) {
        if (lot[x][y] == 9) {
            dist[x][y] = min(dist[x][y], currDist);
            minDist = min(minDist, currDist);
            return;
        }

        lot[x][y] = 0;
        dist[x][y] = min(dist[x][y], currDist);

        int m = lot.size(), n = lot[0].size();
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i], newY = y + dy[i];
            if (newX < 0 || newX >= m || newY < 0 || newY >= n || 
                lot[newX][newY] == 0) {
                continue;
            }

            _bfs(lot, dist, newX, newY, currDist + 1, minDist);
        }
    }
};

int main(int argc, char **argv) {
    vector<vector<int>> lot{{1, 0, 0}, {1, 0, 0}, {1, 9, 1}};
    cout << "the lot: [" << endl;
    for (vector<int> vec : lot) {
        cout << "  [";
        for (int v : vec) {
            cout << v << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
    int result;
    Solution *solution = new Solution;
    result = solution->MinDistToObstacle(lot);
    cout << "minimum distance to obstacle: " << result << endl << endl;

    lot = vector<vector<int>>{{1, 1, 1, 1}, 
                              {0, 1, 1, 1}, 
                              {0, 1, 0, 1}, 
                              {1, 1, 9, 1}, 
                              {0, 0, 1, 1}};
    cout << "the lot: [" << endl;
    for (vector<int> vec : lot) {
        cout << "  [";
        for (int v : vec) {
            cout << v << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
    result = solution->MinDistToObstacle(lot);
    cout << "minimum distance to obstacle: " << result << endl;
}