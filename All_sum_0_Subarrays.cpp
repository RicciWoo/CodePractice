#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*请完成下面这个函数，实现题目要求的功能
当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^ 
******************************开始写代码******************************/
void _combination(vector<int> &nums, int index, vector<int> &items, 
                  int k, vector<vector<int>> &results) {
    for (int i = index; i < nums.size(); i++) {
        items.push_back(nums[i]);
        _combination(nums, i + 1, items, k, results);
        items.pop_back();
    }
    if (items.size() == k)
        results.push_back(items);
}

vector<vector<int>> combination(vector<int> &nums, int k) {
    vector<int> items;
    vector<vector<int>> results;
    _combination(nums, 0, items, k, results);
    return results;
}

bool _myComp(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0])
        return a[a.size() - 1] < b[b.size() - 1];
    else return a[0] < b[0];
}

vector<vector<int>> findSubArrays(vector<int> arr) {
    vector<int> diff(arr.size() + 1, 0);
    unordered_map<int, vector<int>> hm;
    hm[0] = vector<int>{0};
    for (int i = 0; i < arr.size(); i++) {
        diff[i + 1] = diff[i] + arr[i];
        if (!hm.count(diff[i + 1]))
            hm[diff[i + 1]] = vector<int>{i};
        else {
            hm[diff[i + 1]].push_back(i);
        }
    }
    vector<vector<int>> results;
    if (hm.empty()) return results;
    for (auto &entry : hm) {
        if (entry.second.size() == 2) 
            results.push_back(entry.second);
        else if (entry.second.size() >= 3) {
            vector<vector<int>> temp = combination(entry.second, 2);
            results.insert(results.end(), temp.begin(), temp.end());
        }
    }
    sort(results.begin(), results.end(), _myComp);
    return results;
}
/******************************结束写代码******************************/


int main() {
    vector < vector < int > > res;

    int _arr_size = 0;
    cin >> _arr_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> _arr;
    int _arr_item;
    for(int _arr_i=0; _arr_i<_arr_size; _arr_i++) {
        cin >> _arr_item;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        _arr.push_back(_arr_item);
    }


    
    res = findSubArrays(_arr);
    for(int res_i=0; res_i < res.size(); res_i++) {
        for(int res_j=0; res_j < res[res_i].size(); res_j++) {
            cout << res[res_i][res_j] << " ";
        }
        cout << endl;
    }
    
    return 0;

}
