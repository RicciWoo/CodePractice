#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Largest Rectangle in Histogram, use stack
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int area = 0;
        stack<int> hStack;
        for (int i = 0; i < heights.size(); i++) {
            if (hStack.empty() || heights[i] > heights[hStack.top()])
                hStack.push(i);
            else {
                int start = hStack.top();
                hStack.pop();
                int width = hStack.empty() ? i : i - hStack.top() - 1;
                area = max(area, heights[start] * width);
                i--;
            }
        }
        while (!hStack.empty()) {
            int start = hStack.top();
            hStack.pop();
            int width = hStack.empty() ? heights.size() : 
                        heights.size() - hStack.top() - 1;
            area = max(area, heights[start] * width);
        }
        return area;
    }
};

int main(int argc, char **argv) {
    vector<int> heights{2, 1, 5, 6, 2, 3};
    string result;
    Solution *solution = new Solution;
    result = solution->largestRectangleArea(heights);
    cout << "heights: [";
    for (int h : heights) cout << h << ", ";
    cout << "]" << endl;
    cout << "Largest Rectangle in Histogram: " << result << endl;
}
