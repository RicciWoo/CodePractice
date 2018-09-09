#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Sliding Window Maximum, use Heap
// Definition for singly-linked list.
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty()) return nums;
        vector<int> result(nums.size() - k + 1, 0);
        deque<int> dq;
        for (int i = 0; i < nums.size(); i++) {
            if (!dq.empty() && dq.front() == i - k)
                dq.pop_front();
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) result[i - k + 1] = nums[dq.front()];
        }
        return result;
    }
};

int main(int argc, char **argv) {
    vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> result;
    Solution *solution = new Solution;
    result = solution->maxSlidingWindow(lists);
    cout << "numbers: [";
    for (int n : nums) cout << n << ", ";
    cout << "]" << endl;
    cout << "k: " << k << endl;
    cout << "result: [";
    for (int r : result) cout << r << ", ";
    cout << "]" << endl;
}
