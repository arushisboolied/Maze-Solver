// Going to solve this using XOR (Thank u apna college)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int val : nums) ans = ans^val;
        return ans;
    }
};
