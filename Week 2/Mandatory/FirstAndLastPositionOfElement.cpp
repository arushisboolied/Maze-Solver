class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l1 = 0, r1 = nums.size();
        while (l1 < r1) {
            int mid = l1 + (r1 - l1) / 2;
            if (nums[mid] < target)
                l1 = mid + 1;
            else
                r1 = mid;
        }
        int l2 = 0, r2 = nums.size();
        while (l2 < r2) {
            int mid = l2 + (r2 - l2) / 2;
            if (nums[mid] <= target)
                l2 = mid + 1;
            else
                r2 = mid;
        }
        if (l1 == nums.size() || nums[l1] != target)
            return {-1, -1};
        else
            return {l1, l2 - 1};
    }
};
