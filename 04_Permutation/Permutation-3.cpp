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
        _permute(num, 0, results);
        return results;
    }

private:
    void _permute(vector<int> &num, int index, 
                  vector<vector<int>> &results) {
        if (index == num.size()) {
            results.push_back(num);
            return;
        }
        for (int i = index; i < num.size(); i++) {
            swap(num[index], num[i]);
            _permute(num, index + 1, results);
            swap(num[index], num[i]);
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