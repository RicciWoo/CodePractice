#include <vector>
#include <iostream>
using namespace std;

// Maze, Recursion, 20180815
class Solution {
public:
    bool solveMaze(vector<vector<char>> &maze, int startX, int startY, 
                    int targetX, int targetY) {
        string path;
        return _solveMaze(maze, startX, startY, targetX, targetY, path);
    }

private:
    bool _solveMaze(vector<vector<char>> &maze, int startX, int startY, 
                    int targetX, int targetY, string path) {
        if (startX < 0 || startX >= maze.size() || 
            startY < 0 || startY >= maze[0].size() || 
            maze[startX][startY] == 'X') {
            return false;
        }
        if (startX == targetX && startY == targetY) {
            cout << path << endl;
            return true;
        }
        maze[startX][startY] = 'X';
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        vector<string> direction{"D", "R", "U", "L"};
        for (int i = 0; i < 4; i++) {
            string newPath = path + direction[i];
            if (_solveMaze(maze, startX + dx[i], startY + dy[i], 
                           targetX, targetY, newPath)) {
                return true;
            }
        }
        return false;
    }
};

int main(int argc, char **argv) {
    vector<vector<char>> maze{{'.', 'X', '.', '.', '.', 'X'},
                              {'.', '.', '.', 'X', '.', 'X'},
                              {'X', 'X', '.', 'X', '.', '.'},
                              {'.', 'X', 'X', 'X', '.', 'X'},
                              {'.', '.', '.', '.', '.', 'X'},
                              {'.', '.', '.', '.', '.', '.'}};
    vector<char> path;
    bool result = false;
    Solution *solution = new Solution;
    result = solution->solveMaze(maze, 0, 0, maze.size() - 1, 
                                 maze[0].size() - 1);
    cout << boolalpha << result << endl;
}