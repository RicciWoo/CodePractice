#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Word Search, Depth-first Search, 20180821
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0 || board[0].size() == 0)
            return false;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> flags(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (_exist(board, word, i, j, 0, flags))
                    return true;
        return false;
    }
    
private:
    bool _exist(vector<vector<char>> &board, string &word, int x, 
                int y, int index, vector<vector<bool>> &flags) {
        if (index == word.size()) return true;
        if (x < 0 || x >= board.size() || 
            y < 0 || y >= board[0].size() || 
            flags[x][y] || board[x][y] != word[index])
            return false;
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            flags[x][y] = true;
            if (_exist(board, word, x + dx[i], y + dy[i], 
                       index + 1, flags))
                return true;
            flags[x][y] = false;
        }
        return false;
    }
};

int main(int argc, char **argv) {
    vector<vector<char>> board{{'A', 'B', 'C', 'E'}, 
                               {'S', 'F', 'C', 'S'}, 
                               {'S', 'D', 'E', 'E'}};
    string word1 = "ABCCED";

    bool result;
    Solution *solution = new Solution;
    result = solution->exist(board, word1);
    cout << "Word #1 exist in board: " << boolalpha << result << endl;

    string word2 = "SEE";
    result = solution->exist(board, word2);
    cout << "Word #2 exist in board: " << boolalpha << result << endl;

    string word3 = "ABCB";
    result = solution->exist(board, word3);
    cout << "Word #3 exist in board: " << boolalpha << result << endl;
}
