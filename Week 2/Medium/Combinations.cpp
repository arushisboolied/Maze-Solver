class Solution {
public: 
    void backtrack(int n, int k, int start, vector<int>& path, vector<vector<int>>& res){
        if(path.size() == k){
            res.push_back({path});
        }
        for(int i = start; i < n + 1; i++){
            path.push_back(i);
            backtrack(n,k,i+1,path,res);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> answer;
        vector<int> path;
        backtrack(n,k,1,path,answer);
        return answer;
    }
};