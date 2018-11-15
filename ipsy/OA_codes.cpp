#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Difference in Array, 20181115
class Solution {
public:
    int maxDifference(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }

        int minNum = INT_MAX, maxDiff = 0;
        for (int i = 0; i < nums.size(); i++) {
            minNum = min(minNum, nums[i]);
            maxDiff = max(maxDiff, max(nums[i] - minNum, 0));
        }

        return maxDiff;
    }
};

int main(int argc, char **argv) {
    vector<int> nums{1, 5, 3, 19, 18, 25};
    cout << "numbers: [";
    for (int &n : nums) {
        cout << n << ", ";
    }
    cout << "]" << endl;

    Solution *solution = new Solution;
    int maxDiff = solution->maxDifference(nums);
    cout << "max difference: " << maxDiff << endl << endl;


}