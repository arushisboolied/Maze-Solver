class Solution {
public:
    long long hours(const vector<int>& piles, int k) {
        int h = 0;
        for (int x : piles) {
            h += (x + k - 1) / k;
        }
        return h;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = *max_element(piles.begin(), piles.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hours(piles, mid) <= h)
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
    }
};
