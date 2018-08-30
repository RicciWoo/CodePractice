#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Matrix Multiplication, Dynamic Programming, 20180830
class Solution {
public:
    int matrixChain(vector<int> &p) {
        int n = p.size() - 1;
        vector<vector<int>> m(n, vector<int>(n, 0));
        // for (int i = 0; i < n; i++) m[i][i] = 0;
        for (int r = 2; r <= n; r++) { // the length of matrix chain
            for (int i = 0; i < n - r + 1; i++) {
                int j = i + r - 1;
                m[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                    if (t < m[i][j]) m[i][j] = t;
                }
            }
        }
        return m[0][n - 1];
    }
};

int main(int argc, char **argv) {
    vector<int> p{100, 10, 100, 5};
    Solution *solution = new Solution;
    int result = solution->matrixChain(p);
    cout << "sizes of matrix: ";
    for (int n : p) cout << n << ", ";
    cout << endl;
    cout << "min # of multiplication: " << result << endl;
}
