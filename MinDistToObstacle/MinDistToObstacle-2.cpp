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
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> distances(m, vector<int>(n, -1));
        queue<int> q;
        q.push(0);
        visited[0][0] = true;
        distances[0][0] = 0;
        vector<int> dx{0, 1, 0, -1};
        vector<int> dy{1, 0, -1, 0};

        while (!q.empty()) {
            int p = q.front();
            q.pop();
            int x = p / n, y = p % n;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                if (visited[nx][ny] || lot[nx][ny] == 0) {
                    continue;
                }
                if (lot[nx][ny] == 9) {
                    return distances[x][y] + 1;
                }
                visited[nx][ny] = true;
                distances[nx][ny] = distances[x][y] + 1;
                q.push(nx * n + ny);
            }
        }

        return -1;
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