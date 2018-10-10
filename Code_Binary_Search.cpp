/******************** Binary Search ********************/

// Classical Binary Search
class Solution {
public:
    /**
     * @param nums: An integer array sorted in ascending order
     * @param target: An integer
     * @return: An integer
     */
    int findPosition(vector<int> &nums, int target) {
        if (nums.empty()) return -1;
            
        int start = 0, end = nums.size();
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                end = mid;
            } else if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
};

// First Position of Target
class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    int binarySearch(vector<int> &nums, int target) {
        if (nums.empty()) return -1;
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                end = mid;
            } else if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
};

// Last Position of Target
class Solution {
public:
    /**
     * @param nums: An integer array sorted in ascending order
     * @param target: An integer
     * @return: An integer
     */
    int lastPosition(vector<int> &nums, int target) {
        if (nums.empty()) return -1;
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                start = mid;
            } else if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[end] == target) {
            return end;
        }
        if (nums[start] == target) {
            return start;
        }
        return -1;
    }
};

// First Bad Version
class Solution {
public:
    /**
     * @param n: An integer
     * @return: An integer which is the first bad version.
     */
    int findFirstBadVersion(int n) {
        int start = 1, end = n;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (SVNRepo::isBadVersion(mid)) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (SVNRepo::isBadVersion(start)) {
            return start;
        }
        return end;
    }
};

// Find K Closest Elements
class Solution {
public:
    /**
     * @param nums: an integer array
     * @param target: An integer
     * @param k: An integer
     * @return: an integer array
     */
    vector<int> kClosestNumbers(vector<int> &nums, 
                                int target, int k) {
        if (nums.empty()) return vector<int>();
        
        int left = _findLowerClosest(nums, target);
        int right = left + 1;
        
        vector<int> result(k, 0);
        for (int i = 0; i < k; i++) {
            if (_isLeftColser(nums, target, left, right)) {
                result[i] = nums[left];
                left--;
            } else {
                result[i] = nums[right];
                right++;
            }
        }
        
        return result;
    }
    
private:
    // find the last element that less than target
    int _findLowerClosest(vector<int> &nums, int target) {
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[end] < target) {
            return end;
        }
        if (nums[start] < target) {
            return start;
        }
        return -1;
    }
    
    bool _isLeftColser(vector<int> &nums, 
                       int target, int left, int right) {
        if (left < 0) {
            return false;
        }
        if (right >= nums.size()) {
            return true;
        }
        
        return target - nums[left] <= nums[right] - target;
    }
};

// Search in a Big Sorted Array
class Solution {
public:
    /*
     * @param reader: An instance of ArrayReader.
     * @param target: An integer
     * @return: An integer which is the first index of target.
     */
    int searchBigSortedArray(ArrayReader *reader, int target) {
        int index = 0;
        while (reader->get(index) < target) {
            index = index * 2 + 1;
        }

        // find first element that greater than or equals to target
        int start = 0, end = index;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (reader->get(mid) >= target) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (reader->get(start) == target) {
            return start;
        }
        if (reader->get(end) == target) {
            return end;
        }
        return -1;
    }
};

// Find Minimum in Rotated Sorted Array
class Solution {
public:
    /**
     * @param nums: a rotated sorted array
     * @return: the minimum number in the array
     */
    int findMin(vector<int> &nums) {
        if (nums.empty()) return -1;
        
        int start = 0, end = nums.size() - 1;
        int target = nums[nums.size() - 1];
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] <= target) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        // return min(nums[start], nums[end]);
        if (nums[start] <= target) {
            return nums[start];
        }
        return nums[end];
    }
};

// Maximum Number in Mountain Sequence
class Solution {
public:
    /**
     * @param nums: a mountain sequence which increase firstly and then decrease
     * @return: then mountain top
     */
    int mountainSequence(vector<int> &nums) {
        if (nums.empty()) return 0;
        
        // find first element that greater than the next
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > nums[mid + 1]) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        // return max(nums[start], nums[end]);
        if (nums[start] > nums[start + 1]) {
            return nums[start];
        }
        return nums[end];
    }
};

// Search a 2D Matrix
// Search a 2D Matrix II
// Search for a Range
// Total Occurrence of Target
// Smallest Rectangle Enclosing Black Pixels

// Find Peak Element
class Solution {
public:
    /**
     * @param nums: An integers array.
     * @return: return any of peek positions.
     */
    int findPeak(vector<int> &nums) {
        if (nums.size() < 3) return -1;
        
        int start = 1, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > nums[mid - 1]) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] > nums[end]) {
            return start;
        } else {
            return start;
        }
    }
};

// Search in Rotated Sorted Array
class Solution {
public:
    /**
     * @param nums: an integer rotated sorted array
     * @param target: an integer to be searched
     * @return: an integer
     */
    int search(vector<int> &nums, int target) {
        if (nums.empty()) return -1;
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[start] < nums[mid]) {
                if (nums[start] <= target && target <= nums[mid]) {
                    end = mid;
                } else {
                    start = mid;
                }
            } else {
                if (nums[mid] <= target && target <= nums[end]) {
                    start = mid;
                } else {
                    end = mid;
                }
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
};

// Fast Power
public class Solution {
    /**
     * @param a: A 32bit integer
     * @param b: A 32bit integer
     * @param n: A 32bit integer
     * @return: An integer
     */
    public int fastPower(int a, int b, int n) {
        if (n == 1) {
            return a % b;
        }
        if (n == 0) {
            return 1 % b;
        }
        
        long product = fastPower(a, b, n / 2);
        product = (product * product) % b;
        if (n % 2 == 1) {
            product = (product * a) % b;
        }
        
        return (int)product;
    }
}

// Pow(x, n)
class Solution {
public:
    /**
     * @param x: the base number
     * @param n: the power number
     * @return: the result
     */
    double myPow(double x, int n) {
        if (n == 0) {
            return 1.;
        }
        
        long long l = n;
        if (l > 0) {
            return _pow(x, l);
        }
        return 1. / _pow(x, -l);
    }
    
private:
    double _pow(double x, long long n) {
        if (n == 0) {
            return 1.;
        }
        
        double p = _pow(x, n / 2);
        p *= p;
        if (n % 2 == 1) {
            p *= x;
        }
        
        return p;
    }
};

// Fibonacci II
// Copy Book
