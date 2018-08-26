#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Combination, Recursion, 20180817
class Solution {
public:
    vector<vector<int>> combination(vector<int> nums) {
        sort(nums.begin(), nums.end()); //unnecessary
        vector<int> items;
        vector<vector<int>> results;
        _combination(nums, 0, items, results);
        return results;
    }

private:
    void _combination(vector<int> &nums, int index, vector<int> &items, 
                      vector<vector<int>> &results) {
        for (int i = index; i < nums.size(); i++) {
            items.push_back(nums[i]);
            _combination(nums, i + 1, items, results);
            items.pop_back();
        }
        results.push_back(items);
    }
};

int main(int argc, char **argv) {
    vector<int> nums{2, 3, 1};
    vector<vector<int>> results;
    Solution *solution = new Solution;
    results = solution->combination(nums);
    cout << "nums: [";
    for (int c : nums) {
        cout << c << ", ";
    }
    cout << ']' << endl;
    for (vector<int> res : results) {
        cout << '[';
        for (int x : res) {
            cout << x << ", ";
        }
        cout << ']' << endl;
    }
    cout << endl;
}