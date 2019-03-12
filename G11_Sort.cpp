/******************** Sort ********************/

// Largest Number, use sort
class myComp {
public:
    bool operator() (const string &a, const string &b) {
        string str1 = a + b, str2 = b + a;
        return str1.compare(str2) > 0;
    }
};
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if (nums.empty()) return "";
        vector<string> strs;
        for (int i = 0; i < nums.size(); i++)
            strs.push_back(to_string(nums[i]));
        sort(strs.begin(), strs.end(), myComp());
        if (strs[0][0] == '0') return "0";
        string result = "";
        for (int i = 0; i < strs.size(); i++)
            result += strs[i];
        return result;
    }
};

// Best Meeting Point, use Sort
class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        vector<int> ipos;
        vector<int> jpos;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    ipos.push_back(i);
                    jpos.push_back(j);
                }
            }
        }
        sort(ipos.begin(), ipos.end());
        sort(jpos.begin(), jpos.end());
        int lo = 0, hi = ipos.size() - 1;
        int sum = 0;
        while (lo < hi) {
            sum += ipos[hi] - ipos[lo];
            sum += jpos[hi] - jpos[lo];
            lo++;
            hi--;
        }
        return sum;
    }
};

// Merge Intervals, use Sort
// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
class myComp {
public:
    bool operator() (const Interval &a, const Interval &b) {
        return a.start < b.start;
    }
};
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
        if (intervals.empty()) return result;
        sort(intervals.begin(), intervals.end(), myComp());
        int start = intervals[0].start;
        int end = intervals[0].end;
        for (int i = 1; i < intervals.size(); i++) {
            if (end < intervals[i].start) {
                result.push_back(Interval(start, end));
                start = intervals[i].start;
                end = intervals[i].end;
            }
            else end = max(end, intervals[i].end);
        }
        result.push_back(Interval(start, end));
        return result;
    }
};

// Maximum Gap, use Sort
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.empty()) return 0;
        int minNum = nums[0];
        int maxNum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            minNum = min(minNum, nums[i]);
            maxNum = max(maxNum, nums[i]);
        }
        int bucketLen = (maxNum - minNum) / nums.size() + 1;
        int bucketNum = (maxNum - minNum) / bucketLen + 1;
        vector<vector<int>> buckets(bucketNum);
        for (int i = 0; i < nums.size(); i++) {
            int k = (nums[i] - minNum) / bucketLen;
            if (buckets[k].empty()) {
                buckets[k].push_back(nums[i]);
                buckets[k].push_back(nums[i]);
            } else {
                if (nums[i] < buckets[k][0]) buckets[k][0] = nums[i];
                if (nums[i] > buckets[k][1]) buckets[k][1] = nums[i];
            }
        }
        int gap = 0, prev = 0;
        for (int i = 1; i < bucketNum; i++) {
            if (buckets[i].empty()) continue;
            gap = max(gap, buckets[i][0] - buckets[prev][1]);
            prev = i;
        }
        return gap;
    }
};




















