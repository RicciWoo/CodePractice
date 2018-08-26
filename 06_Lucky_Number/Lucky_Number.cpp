#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// Lucky Number, Recursion, 20180818
class Solution {
public:
    vector<string> luckyNumbers(string num, int target) {
        vector<string> results;
        string temp;
        _luckyNumber(num, target, 0, 0, 0, temp, results);
        return results;
    }

private:
    void _luckyNumber(string &num, int target, int index, int current, 
                      int last, string temp, vector<string> &results) {
        if (index == num.size()) {
            if (current == target) {
                results.push_back(temp);
                return;
            }
        }
        for (int i = index; i < num.size(); i++) {
            if (num[index] == '0' && i != index) return;
            string m = num.substr(index, i - index + 1);
            char *pEnd;
            long n = strtol(m.c_str(), &pEnd, 10);
            if (index == 0)
                _luckyNumber(num, target, i + 1, n, n, temp + m, results);
            else {
                _luckyNumber(num, target, i + 1, current + n, n, 
                             temp + "+" + m, results);
                _luckyNumber(num, target, i + 1, current - n, -n, 
                             temp + "-" + m, results);
                _luckyNumber(num, target, i + 1, current - last + last * n, 
                             last * n, temp + "*" + m, results);
                if (n != 0 && last % n == 0) {
                    _luckyNumber(num, target, i + 1, current - last + last / n, 
                                 last / n, temp + "/" + m, results);
                }
            }
        }
    }
};

int main(int argc, char **argv) {
    int target = 888;
    string num = "8123910806";
    vector<string> results;
    Solution *solution = new Solution;
    results = solution->luckyNumbers(num, target);

    cout << "target: " << target << endl;
    cout << "number: " << num << endl;
    cout << "lucky numbers: " << endl;
    for (int i = 0; i < results.size(); i++) {
        cout << "  " << results[i] << " = " << target << endl;
    }
}
