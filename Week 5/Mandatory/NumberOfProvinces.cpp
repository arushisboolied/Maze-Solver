class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> vis(n, false);
        int comps = 0;
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (int v = 0; v < n; v++)
                if (isConnected[u][v] && !vis[v])
                    dfs(v);
        };
        for (int u = 0; u < n; u++)
            if (!vis[u]) {
                dfs(u);
                comps++;
            }
        return comps;
    }
};
