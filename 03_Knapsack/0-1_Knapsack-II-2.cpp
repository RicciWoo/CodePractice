#include <vector>
#include <iostream>
using namespace std;

// 0-1 Knapsack II, use DP, not correct!!!!!!!!
class Solution {
public:
    int knapsack(int s, vector<int> &weights) {
        vector<int> opt(weights.size() + 1, 0);
        for (int i = 1; i <= weights.size(); i++) {
            if (weights[i - 1] > s - opt[i - 1])
                opt[i] = opt[i - 1];
            else
                opt[i] = max(opt[i - 1], opt[i - 1] + weights[i - 1]);
        }
        return opt[weights.size()];
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