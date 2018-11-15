#include <vector>
#include <climits>
//#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

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

    string a_count_temp;
    getline(cin, a_count_temp);

    int a_count = stoi(ltrim(rtrim(a_count_temp)));

    vector<int> a(a_count);

    for (int i = 0; i < a_count; i++) {
        string a_item_temp;
        getline(cin, a_item_temp);

        int a_item = stoi(ltrim(rtrim(a_item_temp)));

        a[i] = a_item;
    }

    int res = maxDifference(a);

    // fout << res << "\n";

    // fout.close();

    cout << res << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(), 
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
