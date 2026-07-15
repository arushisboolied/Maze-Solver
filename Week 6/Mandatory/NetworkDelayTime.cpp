class Solution {
public:
    vector<long long> dijkstra(int n, int src,
                               vector<vector<pair<int, int>>>& adj) {
        vector<long long> dist(n, LLONG_MAX);
        dist[src] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<>>
            pq;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u])
                continue;
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& t : times)
            adj[t[0]].push_back({t[1], t[2]});
        auto dist = dijkstra(n + 1, k, adj);
        long long maxD = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == LLONG_MAX)
                return -1;
            maxD = max(maxD, dist[i]);
        }
        return (int)maxD;
    }
};
