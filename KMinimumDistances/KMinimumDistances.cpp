#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

// Minimum Distance to Obstacle, Breadth-first Search, 20181130
class Solution {
public:
    vector<pair<int, int>> KMinDist(vector<pair<int, int>> &locations, 
                                    int k) {
        if (locations.empty()) {
            return locations;
        }

        _partition(locations, 0, locations.size() - 1, k);

        vector<pair<int, int>> results;
        for (int i = 0; i < k; i++) {
            results.push_back(locations[i]);
        }
        return results;
    }

private:
    void _partition(vector<pair<int, int>> &locations, 
                    int start, int end, int k) {
        if (start >= end) {
            return;
        }

        int left = start, right = end;
        int mid = start + (end - start) / 2;
        int pivote = _distance(locations[mid]);
        while (left < right) {
            while (left < right && _distance(locations[left]) < pivote) {
                left++;
            }
            while (left < right && _distance(locations[right]) > pivote) {
                right--;
            }

            if (left < right) {
                swap(locations[left], locations[right]);
                left++;
                right--;
            }
        }

        if (k <= right) {
            _quickSelect(locations, start, right, k);
            return;
        }
        if (k >= left) {
            _quickSelect(locations, left, end, k);
            return;
        }
    }

    int _distance(pair<int, int> &location) {
        return location.first * location.first + 
               location.second * location.second;
    }
};

int main(int argc, char **argv) {
    vector<pair<int, int>> locations{{1, 2}, {3, 4}, {1, -1}, 
                                     {4, 5}, {6, 2}, {-2, 2},
                                     {8, 3}, {3, 5}, {3, -2}};
    int k = 4;
    cout << "locations: [" << endl;
    for (pair<int, int> loc : locations) {
        cout << "  [" << loc.first << ", ";
        cout << loc.second << "]" << endl;
    }
    cout << "]" << endl;
    cout << "number of Steakhouses: " << k << endl;
    vector<pair<int, int>> results;
    Solution *solution = new Solution;
    results = solution->KMinDist(locations, k);
    cout << k << " minimum disttances: [" << endl;
    for (pair<int, int> res : results) {
        cout << "  [" << loc.first << ", ";
        cout << loc.second << "]" << endl;
    }
    cout << "]";
}