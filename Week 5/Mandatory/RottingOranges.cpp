class Solution {
public:
    int orangesRotting(vector<vector<int>>& g) {
        int R = g.size(), C = g[0].size(), fresh = 0;
        queue<pair<int, int>> q;
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++) {
                if (g[r][c] == 2)
                    q.push({r, c});
                else if (g[r][c] == 1)
                    fresh++;
            }
        int t = 0;
        const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
        while (!q.empty() && fresh > 0) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto [r, c] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= R || nc < 0 || nc >= C ||
                        g[nr][nc] != 1)
                        continue;
                    g[nr][nc] = 2;
                    fresh--;
                    q.push({nr, nc});
                }
            }
            t++;
        }
        return fresh ? -1 : t;
    }
};
