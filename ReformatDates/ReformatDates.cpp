#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Cutting Metal Surplus/Metals, Brute Force, 20181111
class Solution {
public:
    vector<string> reformatDates(vector<string> &dates) {
        if (dates.empty()) {
            return dates;
        }

        unordered_map<string, string> monDict{{"Jan", "01"}, 
                                              {"Feb", "02"}, 
                                              {"Mar", "03"}, 
                                              {"Apr", "04"}, 
                                              {"May", "05"}, 
                                              {"Jun", "06"}, 
                                              {"Jul", "07"}, 
                                              {"Aug", "08"}, 
                                              {"Sep", "09"}, 
                                              {"Oct", "10"}, 
                                              {"Nov", "11"}, 
                                              {"Dec", "12"}};

        for (string &str : dates) {
            vector<string> strs;
            for (int i = 0, j = 0; i <= str.size(); i++) {
                if (i == str.size() || str[i] == ' ') {
                    strs.push_back(str.substr(j, i - j));
                    j = i + 1;
                }
            }

            string day;
            if (isdigit(strs[0][0])) {
                day += strs[0][0];
            }
            if (isdigit(strs[0][1])) {
                day += strs[0][1];
            }
            if (day.size() == 1) {
                day = "0" + day;
            }

            cout << "day: " << day << endl;

        }

        return dates;
    }
};

int main(int argc, char **argv) {
    vector<string> dates{"20th Oct 2052", 
                         "6th Jun 1933", 
                         "26th May 1960", 
                         "20th Sep 1958", 
                         "16th Mar 2068", 
                         "25th May 1912", 
                         "16th Dec 2018", 
                         "26th Dec 2061", 
                         "4th Nov 2030", 
                         "28th Jul 1963"};
    vector<string> results;
    Solution *solution = new Solution;
    results = solution->reformatDates(dates);
    cout << "Original dates:" << endl;
    for (string &d : dates) {
        cout << "  \"" << d << "\"" << endl;
    }
    cout << "Reformated dates:" << endl;
    for (string &d : results) {
        cout << "  \"" << d << "\"" << endl;
    }
}