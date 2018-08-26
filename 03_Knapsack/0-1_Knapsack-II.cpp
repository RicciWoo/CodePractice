#include <vector>
#include <iostream>
using namespace std;

// 0-1 Knapsack II, Recursion, 20180816
class Solution {
public:
    bool knapsack(int s, vector<int> &weights) {
        return _knapsack(s, weights, 0);
    }

private:
    int _knapsack(int s, vector<int> &weights, int index) {
        if (s == 0 || index >= weights.size()) return 0;
        if (weights[index] > s) 
            return _knapsack(s, weights, index + 1);
        return max(_knapsack(s, weights, index + 1), weights[index] + 
                   _knapsack(s - weights[index], weights, index + 1));
    }
};

int main(int argc, char **argv) {
    int s = 32;
    vector<int> w{5, 8, 7, 14, 3};
    int result;
    Solution *solution = new Solution;
    result = solution->knapsack(s, w);
    cout << "target: " << s << endl;
    cout << "candidates: [";
    for (int c : w) {
        cout << c << ", ";
    }
    cout << ']' << endl;
    cout << "max weight allowed: " << result << endl << endl;

    w.erase(w.begin() + 3); // remove '5'
    result = solution->knapsack(s, w);
    cout << "target: " << s << endl;
    cout << "candidates: [";
    for (int c : w) {
        cout << c << ", ";
    }
    cout << ']' << endl;
    cout << "max weight allowed: " << result << endl;
}