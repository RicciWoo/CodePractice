#include <vector>
#include <iostream>
#include <sys/time.h>
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
    cout << "Use time_t time() in second" << endl;
    time_t curr = time(nullptr);
    cout << curr << endl;

    cout << endl;
    cout << "Use gettimeofday() in second" << endl;
    struct timeval tp;
    gettimeofday(&tp, nullptr);
    long long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << ms << endl;

    cout << endl;
    int n = 3;
    vector<int> result;
    Solution *solution = new Solution;
    result = solution->grayCode(n);
    for (int x : result) {
        cout << x << endl;
    }
}