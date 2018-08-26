#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Knapsack, Recursion, 20180816
class Solution {
public:
    vector<vector<int>> knapsack(vector<int> &candidates, int target) {
        // sort(candidate.begin(), candidates.end());
        vector<vector<int>> results;
        vector<int> temp;
        _knapsack(candidates, target, 0, temp, results);
        return results;
    }

private:
    void _knapsack(vector<int> &candidates, int target, int index, 
                   vector<int> &temp, vector<vector<int>> &results) {
        if (target == 0) {
            results.push_back(temp);
            return;
        }
        if (target < 0 || index == candidates.size()) {
            return;
        }
        temp.push_back(candidates[index]);
        _knapsack(candidates, target - candidates[index], index, 
                  temp, results);
        temp.pop_back();
        _knapsack(candidates, target, index + 1, temp, results);
    }
};

int main(int argc, char **argv) {
    int target = 20;
    vector<int> candidates{5, 7, 8, 3};
    vector<vector<int>> result;
    Solution *solution = new Solution;
    result = solution->knapsack(candidates, target);
    cout << "target: " << target << endl;
    cout << "candidates: [";
    for (int c : candidates) {
        cout << c << ", ";
    }
    cout << ']' << endl;
    for (vector<int> res : result) {
        cout << '[';
        for (int x : res) {
            cout << x << ", ";
        }
        cout << ']' << endl;
    }
    cout << endl;

    target = 7;
    candidates.clear();
    candidates.push_back(6);
    candidates.push_back(3);
    candidates.push_back(2);
    candidates.push_back(7);
    result.clear();
    result = solution->knapsack(candidates, target);
    cout << "target: " << target << endl;
    cout << "candidates: [";
    for (int c : candidates) {
        cout << c << ", ";
    }
    cout << ']' << endl;
    for (vector<int> res : result) {
        cout << '[';
        for (int x : res) {
            cout << x << ", ";
        }
        cout << ']' << endl;
    }
}