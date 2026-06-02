class Solution {
public:
    void subsets(vector<int>& nums, vector<vector<int>>& allSubsets,
                 vector<int>& ans, int idx) {
        if (idx == nums.size()) {
            allSubsets.push_back({ans});
            return;
        }
        ans.push_back(nums[idx]);
        subsets(nums, allSubsets, ans, idx + 1);

        ans.pop_back();
        int i = idx + 1;
        while (i < nums.size() && nums[i] == nums[i - 1])
            i++;
        subsets(nums, allSubsets, ans, i);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> allSubsets;
        vector<int> ans;
        sort(nums.begin(), nums.end());

        subsets(nums, allSubsets, ans, 0);

        return allSubsets;
    }
};