#include <vector>
#include <iostream>
using namespace std;

// 0-1 Knapsack II, Recursion, 20180816
class Solution {
public:
    int knapsack(int s, vector<int> &weights) {
        vector<vector<int>> opt(s + 1, vector<int>(weights.size() + 1, 0));
        // for (int j = 0; j <= weights.size(); j++) opt[0][j] = 0;
        // for (int i = 0; i <= s; i++) opt[i][0] = 0;
        for (int i = 1; i <= s; i++) {
            for (int j = 1; j <= weights.size(); j++) {
                if (weights[j - 1] > i - opt[i][j - 1])
                    opt[i][j] = opt[i][j - 1];
                else
                    opt[i][j] = max(opt[i][j - 1], opt[i][j - 1] + weights[j - 1]);
            }
        }
        return opt[s][weights.size()];
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