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
bool _myComp(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0])
        return a[a.size() - 1] < b[b.size() - 1];
    else return a[0] < b[0];
}

vector<vector<int>> findSubArrays(vector<int> arr) {
    vector<vector<int>> results;
    vector<int> diff(arr.size() + 1, 0);
    unordered_map<int, vector<int>> hm;
    hm[0] = vector<int>{0};
    for (int i = 1; i <= arr.size(); i++) {
        diff[i] = diff[i - 1] + arr[i - 1];
        if (!hm.count(diff[i]))
            hm[diff[i]] = vector<int>{i};
        else {
            for (int j : hm[diff[i]])
                results.push_back(vector<int>{j, i - 1});
            hm[diff[i]].push_back(i);
        }
    }
    sort(results.begin(), results.end(), _myComp);
    return results;
}
/******************************结束写代码******************************/


int main() {
    vector<vector<int>> res;

    // int _arr_size = 0;
    // cin >> _arr_size;
    // cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    // vector<int> _arr;
    // int _arr_item;
    // for(int _arr_i=0; _arr_i<_arr_size; _arr_i++) {
    //     cin >> _arr_item;
    //     cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    //     _arr.push_back(_arr_item);
    // }

    vector<int> _arr{6, 3, -1, -3, 4, -2, 2, 4, 6, -12, -7};
    cout << "Array: [";
    for (int i : _arr) cout << i << ", ";
    cout << "]" << endl;
    
    res = findSubArrays(_arr);

    cout << "All sum 0 subarrays:" << endl;
    cout << "[" <<endl;
    for(int res_i=0; res_i < res.size(); res_i++) {
        cout << "   [";
        for(int res_j=0; res_j < res[res_i].size(); res_j++) {
            cout << res[res_i][res_j] << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
    
    return 0;

}
