class Solution {
public:
    struct DSU {
        vector<int> parent, rnk;
        DSU(int n) : parent(n), rnk(n, 0) {
            iota(parent.begin(), parent.end(), 0);
        }
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        bool unite(int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx == ry)
                return false;
            if (rnk[rx] < rnk[ry])
                swap(rx, ry);
            parent[ry] = rx;
            if (rnk[rx] == rnk[ry])
                rnk[rx]++;
            return true;
        }
        bool sameSet(int x, int y) { return find(x) == find(y); }
    };

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DSU dsu(n);
        unordered_map<string, int> emailToIdx;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < (int)accounts[i].size(); j++) {
                auto& e = accounts[i][j];
                if (emailToIdx.count(e))
                    dsu.unite(i, emailToIdx[e]);
                else
                    emailToIdx[e] = i;
            }
        }
        unordered_map<int, set<string>> groups;
        for (auto& [e, i] : emailToIdx)
            groups[dsu.find(i)].insert(e);
        vector<vector<string>> out;
        for (auto& [root, emails] : groups) {
            vector<string> row{accounts[root][0]};
            row.insert(row.end(), emails.begin(), emails.end());
            out.push_back(row);
        }
        return out;
    }
};
