#include <vector>
#include <iostream>
using namespace std;

// 0-1 Knapsack-1, Dynamic Programming, 20180829
class Solution {
public:
    int knapsack(int capacity, vector<int> &weights, vector<int> &values) {
        int length = weights.size();
        if (capacity == 0 || length == 0) return 0;
        // vector<vector<int>> w(length + 1, vector<int>(capacity + 1, 0));
        vector<int> preLine(capacity + 1, 0);
        vector<int> curLine(capacity + 1, 0);
        for (int i = 1; i <= length; i++) {
            int index = i - 1;
            for (int j = 1; j <= capacity; j++) {
                if (weights[index] > j)
                    curLine[j] = preLine[j];
                else
                    curLine[j] = max(preLine[j], 
                            preLine[j - weights[index]] + values[index]);
            }
            swap(curLine, preLine);
        }
        return preLine[capacity];
    }
};

int main(int argc, char **argv) {
    int capacity = 7;
    vector<int> weights{1, 3, 4, 5};
    vector<int> values{3, 8, 4, 7};
    int result;
    Solution *solution = new Solution;
    result = solution->knapsack(capacity, weights, values);
    cout << "capacity: " << capacity << endl;
    cout << "weights: [";
    for (int w : weights) {
        cout << w << ", ";
    }
    cout << ']' << endl;
        cout << "values: [";
    for (int v : values) {
        cout << v << ", ";
    }
    cout << ']' << endl;
    cout << "The most value allowed: " << result << endl;
}