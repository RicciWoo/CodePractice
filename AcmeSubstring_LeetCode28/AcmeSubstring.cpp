#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Acme Substring, Sliding Window, 20181110
class Solution {
public:
    int firstOccurrence(string &A, string &X) {
        if (A.empty() || X.empty()) {
            return -1;
        }

        for (int i = 0, j = 0; i < A.size() - X.size() + 1; i++) {
            for (j = 0; j < X.size(); j++) {
                if (X[j] == '*') {
                    continue;
                }
                if (A[i + j] != X[j]) {
                    break;
                }
            }
            if (j == X.size()) {
                return i;
            }
        }

        return -1;
    }
};

int main(int argc, char **argv) {
    string A = "thisisatest";
    string X = "this";

    int result;
    Solution *solution = new Solution;
    result = solution->firstOccurrence(A, X);
    cout << "String A:       \"" << A << "\"" << endl;
    cout << "Query String X: \"" << X << "\"" << endl;
    cout << "First Occurrence: " << result << endl << endl;

    A = "thisisanotheratest";
    X = "ano*her";
    result = solution->firstOccurrence(A, X);
    cout << "String A:       \"" << A << "\"" << endl;
    cout << "Query String X: \"" << X << "\"" << endl;
    cout << "First Occurrence: " << result << endl;
}