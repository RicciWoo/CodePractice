#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Array Reduction, Heap, 20181114
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};

class Solution {
public:
    int reductionCost(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }

        priority_queue<int, vector<int>, myComp> heap;
        for (int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
        }

        int cost = 0;
        while (heap.size() >= 2) {
            int num1 = heap.top();
            heap.pop();
            int num2 = heap.top();
            heap.pop();
            int sum = num1 + num2;
            cost += sum;
            heap.push(sum);
        }

        return cost;
    }
};

int main(int argc, char **argv) {
    vector<int> nums{1, 2, 3};

    int result;
    Solution *solution = new Solution;
    result = solution->reductionCost(nums);
    cout << "numbers: [";
    for (int &i : num) {
        cout << i << ", ";
    }
    cout << endl;
    cout << "minimum cost: " << result << endl;
}