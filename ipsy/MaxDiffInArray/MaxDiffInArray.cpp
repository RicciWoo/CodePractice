#include <vector>
#include <climits>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Maximum Difference in an Array, 20181115
int maxDifference(vector<int> a) {
    if (a.empty()) {
        return -1;
    }

    int minNum = INT_MAX, maxDiff = -1;
    for (int i = 0; i < a.size(); i++) {
        minNum = min(minNum, a[i]);
        if (a[i] > minNum) {
            maxDiff = max(maxDiff, a[i] - minNum);
        }
    }

    return maxDiff;
}

int main(int argc, char **argv) {

    // ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limites<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int i = 0; i < a_count; i++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limites<streamsize>::max(), '\n');

        a[i] = a_item;
    }

    int res = maxDifference(a);

    // fout << res << "\n";

    // fout.close();

    cout << res << "\n";

    return 0;
}
