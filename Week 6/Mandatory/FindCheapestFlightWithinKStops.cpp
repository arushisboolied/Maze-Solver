class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst,
                          int K) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        for (int i = 0; i <= K; i++) {
            vector<int> next = dist;
            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] != INT_MAX && dist[u] + w < next[v])
                    next[v] = dist[u] + w;
            }
            dist = next;
        }
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
