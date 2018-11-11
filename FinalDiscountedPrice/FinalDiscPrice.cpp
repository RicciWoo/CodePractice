#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

void finalPrice(vector<int> prices) {
    if (prices.empty()) {
        return;
    }

    stack<pair<int, int>> st;
    //st.push(make_pair(prices[0], 0));

    int cost = 0;
    for (int i = 0; i < prices.size(); i++) {
        if (st.empty() || prices[i] >= st.top().first) {
            st.push(make_pair(prices[i], i));
        } else {
            while (!st.empty() && prices[i] < st.top().first) {
                price = st.top().first;
                cost += (price - prices[i]);
                st.pop();
            }
        }
    }

    vector<int> result;
    while (!st.empty()) {
        int price = st.top().first;
        cost += price;
        result.push_back(st.top().second);
        st.pop();
    }

    cout << cost << endl;
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
}

int main(int argc, char **argv) {
    string prices_count_temp;
    getline(cin, prices_count_temp);

    int prices_count = stoi(ltrim(rtrim(prices_count_temp)));

    vector<int> prices(prices_count);

    for (int i = 0; i < prices_count; i++) {
        string prices_item_temp;
        getline(cin, prices_item_temp);

        int prices_item = stoi(ltrim(rtrim(prices_item_temp)));

        prices[i] = prices_item;
    }

    finalPrice(prices);

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
        s.begin()
    );

    return s;
}
