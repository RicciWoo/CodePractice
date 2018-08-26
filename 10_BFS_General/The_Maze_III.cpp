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

int main(int argc, char **argv) {
    vector<vector<int>> maze{{0, 0, 0, 0, 0},
                             {1, 1, 0, 0, 1},
                             {0, 0, 0, 0, 0},
                             {0, 1, 0, 0, 1},
                             {0, 1, 0, 0, 0}};
    vector<int> start{4, 3};
    vector<int> dest{0, 1};

    string result;
    Solution *solution = new Solution;
    result = solution->findShortestWay(maze, start, dest);
    cout << "The path is: " << result << endl;
}
