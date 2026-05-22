class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum1 = 0, sum2 = 0, n = nums.size();
        for(int i = 0; i < n; i++){
            sum1 += (i + 1);
            sum2 += nums[i];
        }
        return (sum1 - sum2);
    }
};
