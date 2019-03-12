/******************** Bit Manipulation ********************/

// Single Number, use Bit Manipulation
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++)
            nums[i] ^= nums[i - 1];
        return nums[nums.size() - 1];
    }
};

// Number of 1 Bits
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            result += n & 1;
            n >>= 1;
        }
        return result;
    }
};

// Reverse Bits
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t r = 0;
        for (int i = 0; i < 32; i++) {
            r <<= 1;
            r |= n & 1;
            n >>= 1;
        }
        return r;
    }
};

// Single Number II-1
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> bitnum(32);
        int result = 0;
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < nums.size(); j++)
                bitnum[i] += (nums[j] >> i) & 1;
            result |= (bitnum[i] % 3) << i;
        }
        return result;
    }
};

// Single Number II-2
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            int sum = 0;
            for (int j = 0; j < nums.size(); j++) {
                if ((nums[j] >> i) & 1 == 1) {
                    sum++;
                    sum %= 3;
                }
            }
            if (sum != 0) result |= sum << i;
        }
        return result;
    }
};

// Single Number III
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int diff = 0;
        for (int i = 0; i < nums.size(); i++)
            diff ^= nums[i];
        diff &= -diff;
        vector<int> result(2, 0);
        for (int i = 0; i < nums.size(); i++) {
            if ((nums[i] & diff) == 0)
                result[0] ^= nums[i];
            else result[1] ^= nums[i];
        }
        return result;
    }
};


