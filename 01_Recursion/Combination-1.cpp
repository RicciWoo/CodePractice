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
        if (index == nums.size()) {
            results.push_back(items);
            return;
        }

        vector<int> newItems1(items);
        _combination(nums, index + 1, newItems1, results);

        vector<int> newItems2(items);
        newItems2.push_back(nums[index]);
        _combination(nums, index + 1, newItems2, results);
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