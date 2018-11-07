#include <vector>
#include <iostream>
using namespace std;

// Maze, Recursion, 20180815
class Solution {
public:
    bool solveMaze(vector<vector<char>> &maze, int startX, int startY, 
                   int targetX, int targetY) {
        if (startX == targetX && startY == targetY) {
            return true;
        }
        maze[startX][startY] = 'X';
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int newX = startX + dx[i], newY = startY + dy[i];
            if (newX < 0 || newX >= maze.size() || 
                newY < 0 || newY >= maze[0].size() || 
                maze[newX][newY] == 'X') {
                continue;
            }
            if (solveMaze(maze, newX, newY, targetX, targetY)) {
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
    bool result = false;
    Solution *solution = new Solution;
    result = solution->solveMaze(maze, 0, 0, maze.size() - 1, 
                                 maze[0].size() - 1);
    cout << boolalpha << result << endl;
}