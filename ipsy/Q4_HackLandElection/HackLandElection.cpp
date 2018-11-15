#include <vector>
#include <climits>
//#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// HackLand Electtion, 20181115
class myComp {
public:
    bool operator() (const pair<string, int> &a, 
                     const pair<string, int> &b) {
        if (a.second == b.second) {
            return a.first > b.first;
        }
        return a.second > b.second;
    }
};

string electionWinner(vector<string> votes) {
    if (votes.empty()) {
        return "";
    }

    unordered_map<string, int> counts;
    for (int i = 0; i < votes.size(); i++) {
        if (counts.count(votes[i])) {
            counts[votes[i]]++;
        } else {
            counts[votes[i]] = 1;
        }
    }

    vector<pair<string, int>> cntVec;
    for (pair<const string, int> &item : counts) {
        string name = item.first;
        int count = item.second;
        cntVec.push_back(make_pair(name, count));
    }

    sort(cntVec.begin(), cntVec.end(), myComp());

    return cntVec[0].first;
}

int main(int argc, char **argv) {

    // ofstream fout(getenv("OUTPUT_PATH"));

    string votes_count_temp;
    getline(cin, votes_count_temp);

    int votes_count = stoi(ltrim(rtrim(votes_count_temp)));

    vector<string> votes(votes_count);

    for (int i = 0; i < votes_count; i++) {
        string votes_item_temp;
        getline(cin, votes_item_temp);

        string votes_item = ltrim(rtrim(votes_item_temp));

        votes[i] = votes_item;
    }

    string res = electionWinner(votes);

    // fout << res << "\n";

    // fout.close();

    cout << "winner: " << res << "\n";

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
