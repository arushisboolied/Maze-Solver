class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1;
        int maxVolume = INT_MIN;
        while(i < j){
            int currVolume = (j-i)*min(height[j],height[i]);
            maxVolume = max(currVolume,maxVolume);
            if(height[i] < height[j]) i++;
            else j--;
        }
        return max(maxVolume,0);
    }
};
