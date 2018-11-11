#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Cutting Metals, Brute Force, 20181111
class myComp {
public:
    bool operator() (const vector<int> &a, const vector<int> &b) {
        return a[0] >= b[0];
    }
};

class Solution {
public:
    int countNonDomin(vector<vector<int>> &entities) {
        if (entities.empty()) {
            return 0;
        }

        sort(entities.begin(), entities.end(), myComp());
        int count = 1, maximum = entities[0][1];
        for (int i = 1; i < entities.size(); i++) {
            if (entities[i][1] >= maximum) {
                maximum = entities[i][1];
                count++;
            }
        }

        return count;
    }
};

int main(int argc, char **argv) {
    vector<vector<int>> entities{{2, 4}, {4, 1}, {8, 8}, {3, 5}};

    int result;
    Solution *solution = new Solution;
    result = solution->countNonDomin(entities);
    cout << "entities: {" << endl;
    for (vector<int> &entity : entities) {
        cout << "  {";
        for (int en : entity) {
            cout << en << ", ";
        }
        cout << "}" << endl;
    }
    cout << "}" << endl;

    cout << "# of Non-dominatable entities: " << result << endl;
}