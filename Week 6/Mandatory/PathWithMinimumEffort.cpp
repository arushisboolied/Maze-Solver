class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& h) {
        int R = h.size(), C = h[0].size();
        vector<vector<int>> dist(R, vector<int>(C, INT_MAX));
        dist[0][0] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                       greater<>>
            pq;
        pq.push({0, 0, 0});
        const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
        while (!pq.empty()) {
            auto [d, r, c] = pq.top();
            pq.pop();
            if (d > dist[r][c])
                continue;
            if (r == R - 1 && c == C - 1)
                return d;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                    continue;
                int nd = max(d, abs(h[nr][nc] - h[r][c]));
                if (nd < dist[nr][nc]) {
                    dist[nr][nc] = nd;
                    pq.push({nd, nr, nc});
                }
            }
        }
        return 0;
    }
};
