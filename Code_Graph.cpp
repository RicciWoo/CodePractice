/******************** Graph ********************/

// Course Schedule-1, use Topology Sort
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















