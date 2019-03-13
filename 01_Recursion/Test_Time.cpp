#include <vector>
#include <iostream>
using namespace std;

// Test Time, 20190313
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

int main(int argc, char **argv) {
    int n = 3;
    vector<int> result;
    Solution *solution = new Solution;
    result = solution->grayCode(n);
    for (int x : result) {
        cout << x << endl;
    }
    cout << endl;
    cout << time(null) << endl;
}