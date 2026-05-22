// This solution uses Kadane's Algorithm =) 
// Brute Force TLE's btw

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> profits(prices.size() - 1, 0);
        for(int i = 0; i < prices.size() - 1; i++)
            profits[i] = prices[i+1] - prices[i];
        int currSum = 0, maxSum = 0;
        for(int val: profits){
            currSum += val;
            maxSum = max(maxSum, currSum);
            currSum = max(currSum, 0);
        }
        return max(maxSum, 0);
    }
};
