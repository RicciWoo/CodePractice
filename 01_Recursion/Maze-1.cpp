#include <vector>
#include <iostream>
using namespace std;

// Maze, Recursion, 20180815
class Solution {
public:
    bool solveMaze(vector<vector<char>> &maze, int startX, int startY,
                   int targetX, int targetY) {
        int sizeX = maze.size(), sizeY = maze[0].size();
        vector<vector<bool>> visited(sizeX, vector<bool>(sizeY, false));
        return _solveMaze(maze, startX, startY, targetX, targetY, 
                          visited);
    }

private:
    bool _solveMaze(vector<vector<char>> &maze, int startX, int startY, 
                    int targetX, int targetY, vector<vector<bool>> &visited) {
        if (startX < 0 || startX >= maze.size() || 
            startY < 0 || startY >= maze[0].size() || 
            maze[startX][startY] == 'X' || visited[startX][startY]) {
            return false;
        }
        if (startX == targetX && startY == targetY) {
            return true;
        }
        visited[startX][startY] = true;
        if (_solveMaze(maze, startX + 1, startY, targetX, targetY, visited) || 
            _solveMaze(maze, startX, startY + 1, targetX, targetY, visited) || 
            _solveMaze(maze, startX - 1, startY, targetX, targetY, visited) || 
            _solveMaze(maze, startX, startY - 1, targetX, targetY, visited)) {
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
    result = solution->solveMaze(maze, 0, 0, maze.size() - 1, 
                                 maze[0].size() - 1);
    cout << boolalpha << result << endl;
}