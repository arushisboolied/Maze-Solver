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

        subsets(nums, allSubsets, ans, idx + 1);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> allSubsets;
        vector<int> ans;

        subsets(nums, allSubsets, ans, 0);

        return allSubsets;
    }
};
