#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

int maxLength(vector<int> &a, int k) {
    int sum = 0, maxLen = 0;
    for (int i = 0, j = 0; i < a.size(); i++) {
        sum += a[i];
        if (sum <= k) {
            maxLen = max(maxLen, i - j + 1);
        } else {
            while (j <= i) {
                sum -= a[j];
                j++;
                if (sum <= k) {
                    break;
                }
            }
        }
    }
    return maxCount;
}

int main(int argc, char **argv) {

    // ofstream fout("result.txt");

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

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    int result = maxLength(a, k);
    cout << "output: "<< result << endl;

    // fout << result << "\n";
    // fout.close();

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
