#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <unordered_set>

using namespace std;


/*请完成下面这个函数，实现题目要求的功能
当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^ 
******************************开始写代码******************************/
void _removeChar(string str, int index, int count, int min, 
                 unordered_set<string> &dict) {
    if (index == str.size()) {
        if (count < min) min = count;
        return;
    }
    if (count >= min) return;
    for (int i = index; i < str.size(); i++) {
        string sub = str.substr(index, i - index + 1);
        if (dict.count(sub)) 
            _removeChar(str, i + 1, count, min, dict);
        else 
            _removeChar(str, i + 1, count + i - index + 1, min, dict);
    }
}

int removeCharacters(string str, vector<string> dict) {
    unordered_set<string> dictSet(dict.begin(), dict.end());
    int min = str.size();
    _removeChar(str, 0, 0, min, dictSet);
	return min;
}
/******************************结束写代码******************************/


int main() {
    int res;

    string _str;
    getline(cin, _str);
    int _dict_size = 0;
    cin >> _dict_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<string> _dict;
    string _dict_item;
    for(int _dict_i=0; _dict_i<_dict_size; _dict_i++) {
        getline(cin, _dict_item);
        _dict.push_back(_dict_item);
    }
    
    res = removeCharacters(_str, _dict);
    cout << res << endl;
    
    return 0;

}
