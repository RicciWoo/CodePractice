#include <stack>
#include <vector>
#include <iostream>
using namespace std;

// Bad Hair Day, see cows
class Solution {
public:
    int seeCows(vector<int> &cow) {
        int totalNum = 0;
        stack<int> cowStack;
        for (int i = 0; i < cow.size(); i++) {
            if (cowStack.empty() || cow[i] < cowStack.top())
                cowStack.push(cow[i]);
            else {
                while (!cowStack.empty() && cow[i] >= cowStack.top()) {
                    cowStack.pop();
                    totalNum += cowStack.size();
                }
                cowStack.push(cow[i]);
            }
        }
        while (!cowStack.empty()) {
            cowStack.pop();
            totalNum += cowStack.size();
        }
        return totalNum;
    }
};

int main(int argc, char **argv) {
    vector<int> cow{6, 2, 3, 1, 7, 4};
    int result;

    Solution *solution = new Solution;
    result = solution->seeCows(cow);
    cout << "cow's heights: [";
    for (int h : cow) cout << h << ", ";
    cout << "]" << endl;
    cout << "# of cows can be seen: " << result << endl;
}
