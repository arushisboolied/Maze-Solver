class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int area = 0;
        stack<int> st;
        for(int i = 0; i < heights.size(); i++){
            while(!st.empty() && heights[st.top()] > heights[i]){
                int top = st.top();
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                area = max(area,heights[top]*width);
            }
            st.push(i);
        }
        return area;
    }
};
