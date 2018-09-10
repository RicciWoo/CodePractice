#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Courese Schedule-1, use Topology Sort
class Solution {
public:
    bool canFinish(int numCourses, 
                   vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> preNum(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            graph[prerequisites[i].second].push_back(
                prerequisites[i].first);
            preNum[prerequisites[i].first]++;
        }
        for (int i = 0; i < numCourses; i++) {
            bool availableCourse = false;
            for (int j = 0; j < numCourses; j++) {
                if (preNum[j] == 0) {
                    for (int k : graph[j]) preNum[k]--;
                    availableCourse = true;
                    preNum[j] = -1;
                    break;
                }
            }
            if (!availableCourse) return false;
        }
        return true;
    }
};

int main(int argc, char **argv) {
    vector<pair<int, int>> prerequisites{{1, 0}};
    int numCourses = 2;

    bool result;
    Solution *solution = new Solution;
    result = solution->canFinish(numCourses, prerequisites);
    cout << "number of courses: " << numCourses << endl;
    cout << "prerequisites: [";
    for (pair<int, int> pre : prerequisites)
        cout << "[" << pre.first << ", " << pre.second << "], ";
    cout << "]" << endl;
    cout << "can finish courses: " << boolalpha << result;

    prerequisites.push_back({0, 1});
    result = solution->canFinish(numCourses, prerequisites);
    cout << "number of courses: " << numCourses << endl;
    cout << "prerequisites: [";
    for (pair<int, int> pre : prerequisites)
        cout << "[" << pre.first << ", " << pre.second << "], ";
    cout << "]" << endl;
    cout << "can finish courses: " << boolalpha << result;
}
