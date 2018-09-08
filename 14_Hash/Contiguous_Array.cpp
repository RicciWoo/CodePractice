#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Contiguous Array, use Hash Map
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int result = 0;
        vector<int> diff(nums.size() + 1, 0);
        unordered_map<int, int> hm;
        hm[0] = 0;
        for (int i = 1; i <= nums.size(); i++) {
            diff[i] = diff[i - 1] + (nums[i - 1] == 0 ? -1 : 1);
            if (!hm.count(diff[i])) hm[diff[i]] = i;
            else result = max(result, i - hm[diff[i]]);
        }
        return result;
    }
};

int main(int argc, char **argv) {
    vector<int> nums{0, 1};
    int result;
    Solution *solution = new Solution;
    result = solution->findMaxLength(nums);
    cout << "numbers: [";
    for (int &n : nums) cout << n << ", ";
    cout << "]"<< endl;
    cout << "max length of contiguous array: " << result << endl;

    nums.push_back(0);
    result = solution->findMaxLength(nums);
    cout << "numbers: [";
    for (int &n : nums) cout << n << ", ";
    cout << "]"<< endl;
    cout << "max length of contiguous array: " << result << endl;
}
