#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Permutation, Recursion, 20180816
class Solution {
public:
    vector<vector<int>> permute(vector<int> num) {
        // sort(num.begin(), num.end());
        vector<vector<int>> results;
        vector<int> cur;
        _permute(num, cur, results);
        return results;
    }

private:
    void _permute(vector<int> &num, vector<int> &cur, 
                  vector<vector<int>> &results) {
        if (num.size() == 0) {
            results.push_back(cur);
            return;
        }
        for (int i = 0; i < num.size(); i++) {
            vector<int> newCur(cur);
            newCur.push_back(num[i]);
            vector<int> newNum(num);
            newNum.erase(newNum.begin() + i);
            _permute(newNum, newCur, results);
        }
    }
};

int main(int argc, char **argv) {
    vector<int> num{2, 3, 1};
    vector<vector<int>> result;
    Solution *solution = new Solution;
    result = solution->permute(num);
    cout << "num: [";
    for (int c : num) {
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
}