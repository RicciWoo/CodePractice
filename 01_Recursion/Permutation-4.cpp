#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Permutation, Recursion, 20180816
class Solution {
public:
    vector<vector<int>> permute(vector<int> num) {
        // sort(num.begin(), num.end());
        vector<int> cur;
        vector<vector<int>> results;
        vector<bool> visited(num.size(), false);
        _permute(num, cur, visited, results);
        return results;
    }

private:
    void _permute(vector<int> &num, vector<int> &cur, 
                  vector<bool> &visited, 
                  vector<vector<int>> &results) {
        if (cur.size() == num.size()) {
            results.push_back(cur);
            return;
        }
        for (int i = 0; i < num.size(); i++) {
            if (visited[i]) continue;
            visited[i] = true;
            cur.push_back(num[i]);
            _permute(num, cur, visited, results);
            cur.pop_back();
            visited[i] = false;
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