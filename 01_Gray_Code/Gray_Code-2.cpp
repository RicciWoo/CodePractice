#include <vector>
#include <iostream>
using namespace std;

// Gray Code, Tail Recursion, 20180815
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        _grayCode(n, result);
        return result;
    }

private:
    void _grayCode(int n, vector<int> &result) {
        if (n == 0) {
            result.push_back(0);
            return;
        }
        _grayCode(n - 1, result);
        int k = 1 << (n - 1);
        for (int i = result.size() - 1; i >= 0; i--) {
            result.push_back(result[i] + k);
        }
    }
};

// // Gray Code, Iteration, 20180815
// class Solution {
// public:
//     vector<int> grayCode(int n) {
//         vector<int> result;
//         result.push_back(0);
//         for (int i = 0; i < n; i++) {
//             int k = 1 << i;
//             int size = result.size();
//             for (int j = size - 1; j >= 0; j--) {
//                 result.push_back(result[j] + k);
//             }
//         }
//         return result;
//     }
// };

int main(int argc, char **argv) {
    int n = 3;
    vector<int> result;
    Solution *solution = new Solution;
    result = solution->grayCode(n);
    for (int x : result) {
        cout << x << endl;
    }
}