class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> ps(nums.size(), 0);
        int count = 0;

        ps[0] = nums[0];
        for(int i = 1; i < nums.size(); i++){
            ps[i] = ps[i-1] + nums[i];
        }

        unordered_map<int,int> hash;
        for(int i = 0; i < nums.size(); i++){
            if(ps[i] == k) count++;

            int x = ps[i] - k;
            if(hash.find(x) != hash.end())
                count += hash[x];
            if(hash.find(ps[i]) == hash.end())
                hash[ps[i]] = 0;
            hash[ps[i]]++;
        }
        return count;
    }
};
