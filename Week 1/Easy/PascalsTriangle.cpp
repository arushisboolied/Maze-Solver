class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if(numRows == 0) return {};
        if(numRows == 1) return {{1}}; 
        vector<vector<int>> pingala = {{1},{1,1}};
        for(int i = 3; i <= numRows; i++){
            vector<int> newline(i,1);
            for(int j = 1; j < i - 1; j++){
                newline[j] = pingala[i-2][j-1] + pingala[i-2][j]; 
            }
            pingala.push_back(newline);
        }
        return pingala;
    }
};
