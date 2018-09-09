#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Kth Largest Element in an Array, use Heap
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, myComp> minHeap;
        for (int i = 0; i < k; i++)
            minHeap.push(nums[i]);
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] >= minHeap.top()) {
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }
        return minHeap.top();
    }
};

int main(int argc, char **argv) {
    vector<int> nums{3, 2, 1, 5, 6, 4};
    int k = 2;

    int result;
    Solution *solution = new Solution;
    result = solution->findKthLargest(nums, k);
    cout << "numbers: [";
    for (int n : nums) cout << n << ", ";
    cout << "]" << endl;
    cout << "k: " << k << endl;
    cout << "result: " << result << endl << endl;

    nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    k = 4;
    result = solution->findKthLargest(nums, k);
    cout << "numbers: [";
    for (int n : nums) cout << n << ", ";
    cout << "]" << endl;
    cout << "k: " << k << endl;
    cout << "result: " << result << endl << endl;
}
