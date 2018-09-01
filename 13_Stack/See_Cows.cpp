#include <vector>
#include <iostream>
using namespace std;

// Bad Hair Day
class Solution {
public:
    int seeCows(vector<int> &cow) {
        int length = cow.size();
        int totalNum = 0;
        stack<int> cowStack;
        for (int i = 0; i <length; i++) {
            if (cowStack.size() == 0 || cowStack.top() > cow[i])
                cowStack.push(cow[i]);
            else {
                while (cowStack.size() > 0 && cowStack.top() <= cow[i]) {
                    cowStack.pop();
                    totalNum += cowStack.size();
                }
                cowStack.push(cow[i]);
            }
        }
        while (cowStack.size() > 0) {
            cowStack.pop();
            totalNum += cowStack.size();
        }
        return totalNum;
    }
};

int main(int argc, char **argv) {

}
