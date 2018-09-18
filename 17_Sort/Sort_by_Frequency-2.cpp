#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

// Sort by Frequency, use Sort
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};

class Solution {
public:
    vector<int> frequencySort(vector<int> &array) {
        unordered_map<int, int> cm;
        for (int i = 0; i < array.size(); i++) {
            cm.insert({array[i], 0});
            cm[array[i]]++;
        }
        multimap<int, int, myComp()> rm;
        cout << "items in unordered_map:" << endl;
        for (pair<const int, int> &item : cm) {
            cout << "  " << item.first << ", " << item.second << endl;
            rm.insert({item.second, item.first});
        }
        vector<int> result;
        cout << "items in multimap:" << endl;
        for (pair<const int, int> &item : rm) {
            cout << "  " << item.first << ", " << item.second << endl;
            result.push_back(item.second);
        }
        return result;
    }
};

int main(int argc, char **argv) {
    vector<int> array{1, 4, 5, 5, 7, 8, 1, 3, 4, 5, 8, 11, 
                    2, 5, 6, 6, 7, 10, 2, 3, 5, 8, 10, 13};
    cout << "Input: [";
    for (int a : array) cout << a << ", ";
    cout << "]" << endl;

    vector<int> result;
    Solution *solution = new Solution;
    result = solution->frequencySort(array);

    cout << "Output: [";
    for (int r : result) cout << r << ", ";
    cout << "]" << endl;
}
