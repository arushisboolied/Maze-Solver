class Solution {
public:
    void dfsGrid(vector<vector<char>>& g, int r, int c) {
        int R = g.size(), C = g[0].size();
        if (r < 0 || r >= R || c < 0 || c >= C || g[r][c] != '1')
            return;
        g[r][c] = '0';
        dfsGrid(g, r + 1, c);
        dfsGrid(g, r - 1, c);
        dfsGrid(g, r, c + 1);
        dfsGrid(g, r, c - 1);
    }

    int numIslands(vector<vector<char>>& g) {
        int count = 0, R = g.size(), C = g[0].size();
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                if (g[r][c] == '1') {
                    count++;
                    dfsGrid(g, r, c);
                }
        return count;
    }
};
