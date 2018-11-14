#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Unique Array Sum, 20181114
class Solution {
public:
    int getMinimumUniqueSum(vector<int> &arr) {
        if (arr.empty()) {
            return 0;
        }

        sort(arr.begin(), arr.end());
        int sum = arr[0], prev = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] <= prev) {
                prev++;
            } else {
                prev = arr[i];
            }
            sum += prev;
        }

        return sum;
    }
};

int main(int argc, char **argv) {
    vector<int> arr{3, 2, 1, 2, 7};

    int result;
    Solution *solution = new Solution;
    result = solution->getMinimumUniqueSum(arr);
    cout << "array: [";
    for (int &a : arr) {
        cout << a << ", ";
    }
    cout << "]" << endl;
    cout << "minimum Sum: " << result << endl;
}