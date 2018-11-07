/******************** Interval, Array, Matrix, Binary Indexed Tree ********************/

// Maximum Subarray
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int maxSum = INT_MIN, sum = 0, minSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        
        return maxSum;
    }
};

// Minimum Subarray
class Solution {
public:
    /*
     * @param nums: a list of integers
     * @return: A integer indicate the sum of minimum subarray
     */
    int minSubArray(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int maxSum = INT_MIN, sum = 0, minSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += -nums[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        
        return -maxSum;
    }
};

// Subarray Sum
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number and the index of the last number
     */
    vector<int> subarraySum(vector<int> &nums) {
        vector<int> result;
        if (nums.empty()) {
            return result;
        }
        
        unordered_map<int, int> map;
        map.insert({0, -1});
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            
            if (map.count(sum)) {
                result.push_back(map[sum] + 1);
                result.push_back(i);
                return result;
            }
            
            map.insert({sum, i});
        }
        return result;
    }
};

// Subarray Sum Closest

// Median of two Sorted Arrays
class Solution {
public:
    /*
     * @param A: An integer array
     * @param B: An integer array
     * @return: a double whose format is *.5 or *.0
     */
    double findMedianSortedArrays(vector<int> &A, vector<int> &B) {
        int n = A.size() + B.size();
        if (n % 2 == 0) {
            return ((double)_findKth(A, 0, B, 0, n / 2) + 
                    (double)_findKth(A, 0, B, 0, n / 2 + 1)) / 2.;
        }
        
        return _findKth(A, 0, B, 0, n / 2 + 1);
    }
    
private:
    int _findKth(vector<int> &A, int startOfA, 
                 vector<int> &B, int startOfB, int k) {
        if (startOfA >= A.size()) {
            return B[startOfB + k - 1];
        }
        if (startOfB >= B.size()) {
            return A[startOfA + k - 1];
        }
        
        if (k == 1) {
            return min(A[startOfA], B[startOfB]);
        }
        
        int halfKthOfA = startOfA + k / 2 - 1 < A.size() ?
            A[startOfA + k / 2 - 1] : INT_MAX;
        int halfKthOfB = startOfB + k / 2 - 1 < B.size() ?
            B[startOfB + k / 2 - 1] : INT_MAX;
        if (halfKthOfA < halfKthOfB) {
            return _findKth(A, startOfA + k / 2, B, startOfB, k - k / 2);
        } else {
            return _findKth(A, startOfA, B, startOfB + k / 2, k - k / 2);
        }
    }
};

// Merge Two Sorted Arrays
class Solution {
public:
    /**
     * @param A: sorted integer array A
     * @param B: sorted integer array B
     * @return: A new sorted integer array
     */
    vector<int> mergeSortedArray(vector<int> &A, vector<int> &B) {
        if (A.empty() || B.empty()) {
            return vector<int>();
        }
        
        vector<int> result(A.size() + B.size());
        int i = 0, j = 0, index = 0;
        while (i < A.size() && j < B.size()) {
            if (A[i] < B[j]) {
                result[index++] = A[i++];
            } else {
                result[index++] = B[j++];
            }
        }
        
        while (i < A.size()) {
            result[index++] = A[i++];
        }
        while (j < B.size()) {
            result[index++] = B[j++];
        }
        
        return result;
    }
};

// Merge Sorted Array
class Solution {
public:
    /*
     * @param A: sorted integer array A which has m elements, but size of A is m+n
     * @param m: An integer
     * @param B: sorted integer array B which has n elements
     * @param n: An integer
     * @return: nothing
     */
    void mergeSortedArray(int A[], int m, int B[], int n) {
        int i = m - 1, j = n - 1, index = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (A[i] > B[j]) {
                A[index--] = A[i--];
            } else {
                A[index--] = B[j--];
            }
        }
        
        while (i >= 0) {
            A[index--] = A[i--];
        }
        while (j >= 0) {
            A[index--] = B[j--];
        }
    }
};

// Merge Two Sorted Interval Lists
/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */
class Solution {
public:
    /**
     * @param list1: one of the given list
     * @param list2: another list
     * @return: the new sorted list of interval
     */
    vector<Interval> mergeTwoInterval(vector<Interval> &list1, vector<Interval> &list2) {
        vector<Interval> results;
        if (list1.empty() && list2.empty()) {
            return results;
        }
        Interval *last = nullptr, *curr = nullptr;
        int i = 0, j = 0;
        while (i < list1.size() && j < list2.size()) {
            if (list1[i].start < list2[j].start) {
                curr = &list1[i];
                i++;
            } else {
                curr = &list2[j];
                j++;
            }
            
            last = _merge(last, curr, results);
        }
        
        while (i < list1.size()) {
            last = _merge(last, &list1[i], results);
            i++;
        }
        while (j < list2.size()) {
            last = _merge(last, &list2[j], results);
            j++;
        }
        
        results.push_back(*last);
        return results;
    }
    
private:
    Interval *_merge(Interval *last, Interval *curr, 
                    vector<Interval> &results) {
        if (last == nullptr) {
            return curr;
        }
        
        if (curr->start > last->end) {
            results.push_back(*last);
            return curr;
        }
        
        last->end = max(last->end, curr->end);
        return last;
    }
};

// Merge K Sorted Arrays
class Element {
public:
    int row, col, val;
    Element(int row, int col, int val) {
        this->row = row;
        this->col = col;
        this->val = val;
    }
};
class myComp {
public:
    bool operator() (const Element *a, const Element *b) {
        return a->val >= b->val;
    }
};
class Solution {
public:
    /**
     * @param arrays: k sorted integer arrays
     * @return: a sorted array
     */
    vector<int> mergekSortedArrays(vector<vector<int>> &arrays) {
        vector<int> result;
        if (arrays.empty()) {
            return result;
        }
        
        priority_queue<Element *, vector<Element *>, myComp> heap;
        for (int i = 0; i < arrays.size(); i++) {
            if (arrays[i].empty()) {
                continue;
            }
            Element *elem = new Element(i, 0, arrays[i][0]);
            heap.push(elem);
        }
        
        while (!heap.empty()) {
            Element *elem = heap.top();
            heap.pop();
            result.push_back(elem->val);
            if (++elem->col < arrays[elem->row].size()) {
                elem->val = arrays[elem->row][elem->col];
                heap.push(elem);
            }
        }
        
        return result;
    }
};

// Merge K Sorted Interval Lists
/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */
class Element {
public:
    int row, col;
    Interval *interval;
    Element(int row, int col, Interval *interval) {
        this->row = row;
        this->col = col;
        this->interval = interval;
    }
};
class myComp {
public:
    bool operator() (const Element *a, const Element *b) {
        return a->interval->start >= b->interval->start;
    }
};
class Solution {
public:
    /**
     * @param intervals: the given k sorted interval lists
     * @return:  the new sorted interval list
     */
    vector<Interval> mergeKSortedIntervalLists(
                        vector<vector<Interval>> &intervals) {
        vector<Interval> result;
        if (intervals.empty()) {
            return result;
        }
        
        priority_queue<Element *, vector<Element *>, myComp> heap;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i].empty()) {
                continue;
            }
            Element *elem = new Element(i, 0, &intervals[i][0]);
            heap.push(elem);
        }
        
        while (!heap.empty()) {
            Element *elem = heap.top();
            heap.pop();
            result.push_back(*elem->interval);
            elem->col++;
            if (elem->col < intervals[elem->row].size()) {
                elem->interval = &intervals[elem->row][elem->col];
                heap.push(elem);
            }
        }
        
        return _merge(result);;
    }
    
private:
    vector<Interval> _merge(vector<Interval> &intervals) {
        if (intervals.size() <= 1) {
            return intervals;
        }
        
        vector<Interval> result;
        int start = intervals[0].start;
        int end = intervals[0].end;
        for (Interval &interval : intervals) {
            if (interval.start <= end) {
                end = max(end, interval.end);
            } else {
                result.push_back(Interval(start, end));
                start = interval.start;
                end = interval.end;
            }
        }
        result.push_back(Interval(start, end));
        return result;
    }
};

// Intersection of Two Arrays
class Solution {
public:
    /**
     * @param nums1: an integer array
     * @param nums2: an integer array
     * @return: an integer array
     */
    vector<int> intersection(vector<int> &nums1, 
                             vector<int> &nums2) {
        vector<int> result;
        if (nums1.empty() || nums2.empty()) {
            return result;
        }
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                if (result.empty() || 
                    result[result.size() - 1] != nums1[i]) {
                    result.push_back(nums1[i]);
                }
                i++;
                j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }
        
        return result;
    }
};

// Intersection of Two Arrays II
class Solution {
public:
    /**
     * @param nums1: an integer array
     * @param nums2: an integer array
     * @return: an integer array
     */
    vector<int> intersection(vector<int> &nums1, 
                             vector<int> &nums2) {
        vector<int> results;
        if (nums1.empty() || nums2.empty()) {
            return results;
        }
        
        unordered_map<int, int> map;
        for (int i = 0; i < nums1.size(); i++) {
            if (map.count(nums1[i])) {
                map[nums1[i]]++;
            } else {
                map[nums1[i]] = 1;
            }
        }
        
        for (int i = 0; i < nums2.size(); i++) {
            if (map.count(nums2[i]) && map[nums2[i]] > 0) {
                results.push_back(nums2[i]);
                map[nums2[i]]--;
            }
        }
        
        return results;
    }
};

// Intersection of Two Arrays II
class Solution {
public:
    /**
     * @param nums1: an integer array
     * @param nums2: an integer array
     * @return: an integer array
     */
    vector<int> intersection(vector<int> &nums1, 
                             vector<int> &nums2) {
        vector<int> result;
        if (nums1.empty() || nums2.empty()) {
            return result;
        }
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                result.push_back(nums1[i]);
                i++;
                j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }
        
        return result;
    }
};

// Intersection of Arrays
class Solution {
public:
    /**
     * @param arrs: the arrays
     * @return: the number of the intersection of the arrays
     */
    int intersectionOfArrays(vector<vector<int>> &arrs) {
        if (arrs.empty()) {
            return 0;
        }
        
        unordered_map<int, int> map;
        for (int i = 0; i < arrs.size(); i++) {
            for (int j = 0; j <arrs[i].size(); j++) {
                if (map.count(arrs[i][j])) {
                    map[arrs[i][j]]++;
                } else {
                    map[arrs[i][j]] = 1;
                }
            }
        }
        
        int result = 0;
        for (auto &item : map) {
            if (item.second == arrs.size()) {
                result++;
            }
        }
        
        return result;
    }
};

// Sparse Matrix Multiplication
class Solution {
public:
    /**
     * @param A: a sparse matrix
     * @param B: a sparse matrix
     * @return: the result of A * B
     */
    vector<vector<int>> multiply(vector<vector<int>> &A, 
                                 vector<vector<int>> &B) {
        int m = A.size(), t = A[0].size(), n = B[0].size();
        vector<vector<int>> C(m, vector<int>(n, 0));
        
        vector<vector<int>> col(t, vector<int>());
        for (int k = 0; k < t; k++) {
            for (int j = 0; j < n; j++) {
                if (B[k][j] != 0) {
                    col[k].push_back(j);
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < t; k++) {
                if (A[i][k] == 0) {
                    continue;
                }
                for (int j : col[k]) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        
        return C;
    }
};

// Median of Two Sorted Arrays
class Solution {
public:
    /*
     * @param A: An integer array
     * @param B: An integer array
     * @return: a double whose format is *.5 or *.0
     */
    double findMedianSortedArrays(vector<int> &A, vector<int> &B) {
        int n = A.size() + B.size();
        if (n % 2 == 0) {
            return ((double)_findKth(A, 0, B, 0, n / 2) + 
                    (double)_findKth(A, 0, B, 0, n / 2 + 1)) / 2.;
        }
        
        return _findKth(A, 0, B, 0, n / 2 + 1);
    }
    
private:
    int _findKth(vector<int> &A, int startOfA, 
                 vector<int> &B, int startOfB, int k) {
        if (startOfA >= A.size()) {
            return B[startOfB + k - 1];
        }
        if (startOfB >= B.size()) {
            return A[startOfA + k - 1];
        }
        
        if (k == 1) {
            return min(A[startOfA], B[startOfB]);
        }
        
        int halfKthOfA = startOfA + k / 2 - 1 < A.size() ?
            A[startOfA + k / 2 - 1] : INT_MAX;
        int halfKthOfB = startOfB + k / 2 - 1 < B.size() ?
            B[startOfB + k / 2 - 1] : INT_MAX;
        if (halfKthOfA < halfKthOfB) {
            return _findKth(A, startOfA + k / 2, B, startOfB, k - k / 2);
        } else {
            return _findKth(A, startOfA, B, startOfB + k / 2, k - k / 2);
        }
    }
};

// Median of K Sorted Arrays
class Solution {
public:
    /**
     * @param nums: the given k sorted arrays
     * @return: the median of the given k sorted arrays
     */
    double findMedian(vector<vector<int>> &nums) {
        int n = _getTotal(nums);
        if (n == 0) {
            return 0.;
        }
        
        if (n % 2 != 0) {
            return (double)_findKth(nums, n / 2 + 1);
        }
        return ((double)_findKth(nums, n / 2) + 
                (double)_findKth(nums, n / 2 + 1)) / 2.;
    }
    
private:
    int _getTotal(vector<vector<int>> &nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i].size();
        }
        return sum;
    }
    
    int _findKth(vector<vector<int>> &nums, int k) {
        int start = 0, end = INT_MAX;
        
        // find the last number x that >= k numbers are >= x
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_getGTE(nums, mid) >= k) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (_getGTE(nums, start) >= k) {
            return start;
        }
        return end;
    }
    
    // get how many numbers greater than or equal to val in 2d array
    int _getGTE(vector<vector<int>> &nums, int val) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += _getGTE(nums[i], val);
        }
        return sum;
    }
    
    // get how many numbers greater than or equal to val in an array
    int _getGTE(vector<int> &nums, int val) {
        if (nums.empty()) {
            return 0;
        }
        
        // find first element >= val
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] >= val) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (nums[start] >= val) {
            return nums.size() - start;
        }
        if (nums[end] >= val) {
            return nums.size() - end;
        }
        return 0;
    }
};

// Best Time to Buy and Sell Stock
class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) {
            return 0;
        }
        
        int minPrice = INT_MAX, profit = 0;
        for (int price : prices) {
            minPrice = min(minPrice, price);
            profit = max(profit, price - minPrice);
        }
        
        return profit;
    }
};

// Submatrix Sum
class Solution {
public:
    /*
     * @param matrix: an integer matrix
     * @return: the coordinate of the left-up and right-down number
     */
    vector<vector<int>> submatrixSum(vector<vector<int>> &matrix) {
        vector<vector<int>> result(2, vector<int>(2, 0));
        if (matrix.empty() || matrix[0].empty()) {
            return result;
        }
        
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> sum(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum[i + 1][j + 1] = matrix[i][j] + sum[i + 1][j] + 
                                    sum[i][j + 1] - sum[i][j];
            }
        }
        
        for (int l = 0; l < m; l++) {
            for (int h = l + 1; h <= m; h++) {
                unordered_map<int, int> map;
                for (int j = 0; j <= n; j++) {
                    int diff = sum[h][j] - sum[l][j];
                    if (map.count(diff)) {
                        int k = map[diff];
                        result[0][0] = l;
                        result[0][1] = k;
                        result[1][0] = h - 1;
                        result[1][1] = j - 1;
                        return result;
                    } else {
                        map[diff] = j;
                    }
                }
            }
        }
        
        return result;
    }
};

// Maximum Submatrix
class Solution {
public:
    /**
     * @param matrix: the given matrix
     * @return: the largest possible sum
     */
    int maxSubmatrix(vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> prefixColSum(n + 1, vector<int>(m, 0));
        _getPrefixColSum(matrix, prefixColSum);
        
        int maxSum = INT_MIN;
        for (int up = 0; up < n; up++) {
            for (int down = up; down < n; down++) {
                vector<int> arr(m);
                _compression(matrix, up, down, prefixColSum, arr);
                maxSum = max(maxSum, _maximumSubarray(m, arr));
            }
        }
        
        return maxSum;
    }
    
private:
    void _getPrefixColSum(vector<vector<int>> &matrix, 
                          vector<vector<int>> &prefixColSum) {
        int n = matrix.size(), m = matrix[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefixColSum[i + 1][j] = prefixColSum[i][j] + 
                                         matrix[i][j];
            }
        }
    }

    void _compression(vector<vector<int>> &matrix, int up, int down, 
                   vector<vector<int>> &prefixColSum, 
                   vector<int> &arr) {
        int m = matrix[0].size();
        for (int i = 0; i < m; i++) {
            arr[i] = prefixColSum[down + 1][i] - prefixColSum[up][i];
        }
    }

    int _maximumSubarray(int m, vector<int> &arr) {
        int minSum = 0, maxSum = INT_MIN, sum = 0;
        
        for (int i = 0; i < m; i++) {
            sum += arr[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        
        return maxSum;
    }
};

// Range Sum Query Immutable
class NumArray {
private:
    vector<int> prefix;

public:
    NumArray(vector<int> nums) {
        prefix = vector<int>(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        return prefix[j + 1] - prefix[i];
    }
};

// Range Sum Query 2D Immutable
class NumMatrix {
private:
    vector<vector<int>> dp;
    
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }
        int n = matrix.size(), m = matrix[0].size();
        
        dp = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                dp[r + 1][c + 1] = matrix[r][c] + dp[r + 1][c]
                                   + dp[r][c + 1] - dp[r][c];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1]
               - dp[row2 + 1][col1] + dp[row1][col1];
    }
};

// Range Sum Query Mutable
class NumArray {
public:
    NumArray(vector<int> nums) {
        arr = vector<int>(nums.size(), 0);
        bit = vector<int>(nums.size() + 1, 0);
        
        for (int i = 0; i < nums.size(); i++) {
            update(i, nums[i]);
        }
    }
    
    void update(int index, int val) {
        int delta = val - arr[index];
        arr[index] = val;
        
        for (int i = index + 1; i <= arr.size(); i += _lowbit(i)) {
            bit[i] += delta;
        }
    }
    
    int sumRange(int i, int j) {
        return _getPrefixSum(j) - _getPrefixSum(i - 1);
    }
    
private:
    vector<int> arr, bit;
    
    int _lowbit(int x) {
        return x & (-x);
    }
    
    int _getPrefixSum(int index) {
        int sum = 0;
        for (int i = index + 1; i > 0; i -= _lowbit(i)) {
            sum += bit[i];
        }
        return sum;
    }
};

// Range Sum Query 2D Mutable
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        m = matrix.size();
        n = matrix[0].size();
        arr = vector<vector<int>>(m, vector<int>(n, 0));
        bit = vector<vector<int>>(m + 1, vector<int>(n + 1));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                update(i, j, matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        int delta = val - arr[row][col];
        arr[row][col] = val;
        
        for (int i = row + 1; i <= m; i += _lowbit(i)) {
            for (int j = col + 1; j <= n; j += _lowbit(j)) {
                bit[i][j] += delta;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return _prefixSum(row2, col2)
               - _prefixSum(row2, col1 - 1)
               - _prefixSum(row1 - 1, col2)
               + _prefixSum(row1 - 1, col1 - 1);
    }
    
private:
    vector<vector<int>> arr, bit;
    int m, n;
    
    int _lowbit(int x) {
        return x & (-x);
    }
    
    int _prefixSum(int row, int col) {
        int sum = 0;
        for (int i = row + 1; i > 0; i -= _lowbit(i)) {
            for (int j = col + 1; j > 0; j -= _lowbit(j)) {
                sum += bit[i][j];
            }
        }
        return sum;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */

// Count of Smaller Number before itself













