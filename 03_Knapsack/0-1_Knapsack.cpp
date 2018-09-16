#include <vector>
#include <iostream>
using namespace std;

// 0-1 knapsack, Recursion, 20180816
class Solution {
public:
    bool knapsack(int s, vector<int> &weights) {
        return _knapsack(s, weights, 0);
    }

private:
    bool _knapsack(int s, vector<int> &weights, int index) {
        if (s == 0) return true;
        if (s < 0 || index == weights.size()) return false;
        return _knapsack(s, weights, index + 1) ||
               _knapsack(s - weights[index], weights, index + 1);
    }
};

int main(int argc, char **argv) {
    int s = 20;
    vector<int> w{14, 8, 7, 5, 3};
    bool result = false;
    Solution *solution = new Solution;
    result = solution->knapsack(s, w);
    cout << boolalpha << result << endl;

    w.erase(w.begin() + 3); // remove '5'
    result = solution->knapsack(s, w);
    cout << boolalpha << result << endl;
}