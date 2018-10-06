#include <vector>
#include <iostream>
using namespace std;

// Maze, Recursion, 20180815
class Solution {
public:
    bool solveMaze(vector<vector<char>> &maze, int startX, int startY, 
                   int targetX, int targetY) {
        if (startX < 0 || startX >= maze.size() || 
            startY < 0 || startY >= maze[0].size() || 
            maze[startX][startY] == 'X') {
            return false;
        }
        if (startX == targetX && startY == targetY) {
            return true;
        }
        maze[startX][startY] = 'X';
        if (solveMaze(maze, startX + 1, startY, targetX, targetY) || 
            solveMaze(maze, startX, startY + 1, targetX, targetY) || 
            solveMaze(maze, startX - 1, startY, targetX, targetY) || 
            solveMaze(maze, startX, startY - 1, targetX, targetY)) {
            return true;
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
    result = solution->solveMaze(maze, 0, 0, maze.size() - 1, maze[0].size() - 1);
    cout << boolalpha << result << endl;
}