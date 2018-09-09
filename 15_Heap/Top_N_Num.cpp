#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Top N Numbers, use Heap
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};

class Solution {
public:
    vector<int> topNumbers(vector<vector<int>> &nums) {
        int m = nums.size();
        int n = nums[0].size();
        priority_queue<int, vector<int>, myComp> minHeap;
        for (int i : nums[0]) minHeap.push(i);
        vector<int> list(n, 0);
        for (int i = 1; i < m; i++) {
            for (int j = n - 1; j >= 0; j--) {
                list[j] = minHeap.top();
                minHeap.pop();
            }
            vector<int> curr = nums[i];
            sort(curr.begin(), curr.end(), greater<int>());
            int largest = curr[0];
            for (int j = 0; j < n; j++)
                minHeap.push(largest + list[j]);
            for (int j = 1; j < n; j++) {
                for (int r = 0; r < n; r++) {
                    if (curr[j] + list[r] < minHeap.top())
                        break;
                    minHeap.pop();
                    minHeap.push(curr[j] + list[r]);
                }
            }
        }
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        sort(result.begin(), result.end(), greater<int>());
        return result;
    }
};

int main(int argc, char **argv) {
    vector<vector<int>> nums{{5, 8, 7}, {2, 9, 5}, {0, 2, 3}};

    vector<int> result;
    Solution *solution = new Solution;
    result = solution->topNumbers(nums);
    cout << "numbers:" << endl;
    cout << "[" << endl;
    for (vector<int> &num : nums) {
        cout << "   [";
        for (int n : num) cout << n << ", ";
        cout << "]," << endl;
    }
    cout << "]" << endl;
    cout << "result: [";
    for (int r : result) cout << r << ", ";
    cout << "]" << endl;
}
