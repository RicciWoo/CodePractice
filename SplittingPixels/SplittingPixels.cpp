#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Splitting Pixels, 20181123
class Solution {
public:
    vector<string> splitPixels(vector<string> &pixels) {
        vector<string> results;
        if (pixels.empty()) {
            return results;
        }

        map<int, string> colors;
        for (int i = 0; i < pixels.size(); i++) {
            colors.clear();

            string rStr = pixels[i].substr(0, 8);
            string gStr = pixels[i].substr(8, 8);
            string bStr = pixels[i].substr(16, 8);
            int rInt = 0, gInt = 0, bInt = 0;
            for (int j = 0; j < 8; j++) {
                rInt = (rInt + rStr[j] - '0') << 1;
                gInt = (gInt + gStr[j] - '0') << 1;
                bInt = (bInt + bStr[j] - '0') << 1;
            }

            cout << rStr << endl;
            cout << gStr << endl;
            cout << bStr << endl;

            int rCom = rInt * rInt;
            int rRes = (255 - rInt) * (255 - rInt);
            int gCom = gInt * gInt;
            int gRes = (255 - gInt) * (255 - gInt);
            int bCom = bInt * bInt;
            int bRes = (255 - bInt) * (255 - bInt);
            
            int black = rCom + gCom + bCom;
            colors.insert({black, "Black"});
            int white = rRes + gRes + bRes;
            colors.insert({white, "White"});
            int red = rRes + gCom + bCom;
            colors.insert({red, "Red"});
            int green = rCom + gRes + bCom;
            colors.insert({green, "Green"});
            int blue = rCom + gCom + bRes;
            colors.insert({green, "Blue"});

            if (colors.size() < 5) {
                results.push_back("Ambiguous");
            } else {
                results.push_back(colors.begin()->second);
            }
        }

        return results;
    }
};

int main(int argc, char **argv) {
    vector<string> pixels{"101111010110011011100100", 
                          "110000010101011111101111", 
                          "100110101100111111101101", 
                          "010111011010010110000011", 
                          "000000001111111111111111"};
    vector<string> results;
    Solution *solution = new Solution;
    results = solution->splitPixels(pixels);
    cout << "binary string of pixels:" << endl;
    for (string &str : pixels) {
        cout << "\"" << str << "\"" << endl;
    }
    cout << "Closest Colors:" << endl;
    for (string &str : results) {
        cout << "\"" << str << "\"" << endl;
    }
}