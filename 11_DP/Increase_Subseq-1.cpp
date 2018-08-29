#include <vector>
#include <iostream>
using namespace std;

// Longest Increasing Subsquence-1, Dynamic Programming
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> lis(nums.size(), 0);
        int maxLen = 0;
        for (int i = 0; i < nums.size(); i++) {
            int localMax = 0;
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i] && lis[j] > localMax)
                    localMax = lis[j];
            lis[i] = localMax + 1;
            maxLen = max(maxLen, lis[i]);
        }
        return maxLen;
    }
};

int main(int argc, char **argv) {
    vector<int> nums{3, 1, 4, 5, 7, 6, 8, 2};
    int result;
    Solution *solution = new Solution;
    result = solution->lengthOfLIS(nums);
    cout << "numbers: [";
    for (int n : nums) {
        cout << n << ", ";
    }
    cout << ']' << endl;
    cout << "length of longest increasing subsquence: " << result << endl;
}