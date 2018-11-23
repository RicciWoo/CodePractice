#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

// LeetCode 239 - Sliding Window Maximum, Sliding Window, 20181123
class Solution {
public:
    int segment(vector<int> &nums, int k) {
        if (nums.empty()) {
            return 0;
        }
        
        int n = nums.size();
        deque<int> dq;
        int maxNum = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            
            while (!dq.empty() && nums[dq.back()] > nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            if (i >= k - 1) {
                maxNum = max(maxNum, nums[dq.front()]);
            }
        }
        
        return maxNum;
    }
};

int main(int argc, char **argv) {
    vector<int> nums{1, 2, 3, 1, 2};
    int k = 1;

    int result;
    Solution *solution = new Solution;
    result = solution->segment(nums, k);
    cout << "numbers = [";
    for (int n : nums) {
        cout << n << ", ";
    }
    cout << "]" << endl;
    cout << "length of subarray: " << k << endl;
    cout << "maximum of minimums" << result << endl;

    nums = vector<int>{1, 1, 1};
    k = 2;
    result = solution->segment(nums, k);
    cout << "numbers = [";
    for (int n : nums) {
        cout << n << ", ";
    }
    cout << "]" << endl;
    cout << "length of subarray: " << k << endl;
    cout << "maximum of minimums" << result << endl;
}