#include <queue>
#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// The Maze II, BFS, 20180825
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

int main(int argc, char **argv) {
    vector<vector<int>> maze{{0, 0, 1, 0, 0},
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 1, 0},
                             {1, 1, 0, 1, 1},
                             {0, 0, 0, 0, 0}};
    vector<int> start{0, 4};
    vector<int> dest{4, 4};

    int result;
    Solution *solution = new Solution;
    result = solution->shortestDistance(maze, start, dest);
    cout << "Maze: " << endl;
    for (vector<int> maz : maze) {
        for (int m : maz)
            cout << m << " ";
        cout << endl;
    }
    cout << "Start: (" << start[0] << ", " << start[1] << ")" << endl;
    cout << "Destination: (" << dest[0] << ", " << dest[1] << ")" <<endl;
    cout << "Shortest distance: " << result << endl;
}
