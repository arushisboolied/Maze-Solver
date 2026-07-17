
/*
    coin-collecting maze solver: plans the shortest total route S -> (every coin) -> G using
    four single-pair path algorithms (BFS, DFS, Dijkstra, A*) plus a coin-order backtracking
    search (bestOrder) that treats the pairwise distances as edge weights.
*/

#include <bits/stdc++.h>
using namespace std;

// ENFORCED STRUCTURES

struct Grid {
    int R, C;
    vector<string> cells;
};

struct Result {
    int cost = -1;                 // total steps or total weight; -1 if target unreachable
    vector<pair<int,int>> path;    // cells in order, s..g inclusive
    int expanded = 0;              // cells visited by the search
};


// STATS TO REPORT

struct Stats {
    long long bfsCalls = 0;
    long long dfsCalls = 0;
    long long dijkstraCalls = 0;
    long long astarCalls = 0;
    long long dijkstraExpandedTotal = 0;
    long long astarExpandedTotal = 0;
    long long bfsExpandedTotal = 0;
    long long dfsExpandedTotal = 0;
    long long dfsLongerThanBfs = 0;   // how many pairs where plain DFS did NOT find the shortest path
    long long bestOrderCalls = 0;
    long long dfsOrderingsTried = 0;      // complete orderings reached summed over both bestOrder calls
    long long dfsTotalRecursiveCalls = 0; // every recursive call including pruned ones
};

Stats stats;


// GRID NEIGHBOUR LOGIC

vector<pair<int,int>> neighbours(const Grid& g, int r, int c) {

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<pair<int,int>> out;

    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];

        if (nr < 0 || nr >= g.R || nc < 0 || nc >= g.C)
            continue;
        if (g.cells[nr][nc] == '#')
            continue;

        out.push_back({nr, nc});
    }

    return out;
}


int idxOf(const Grid& g, pair<int,int> p){

    return p.first * g.C + p.second;
}

/*
'.', 'S', 'G', 'c' all cost 1 to enter; digits give their own cost
BFS and DFS ignore this and treat every step as cost 1
*/

int cellCost(char ch) {

    if (ch >= '0' && ch <= '9')
        return ch - '0';

    return 1;
}

vector<pair<int,int>> reconstruct(const Grid& g, pair<int,int> s, pair<int,int> t, const vector<int>& parent) {

    vector<pair<int,int>> path;
    int cur = idxOf(g, t);
    int sIdx = idxOf(g, s);

    while (true) {
        path.push_back({cur / g.C, cur % g.C});

        if (cur == sIdx)
            break;

        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    return path;
}


// BFS - SINGLE PAIR, UNIFORM COST

Result bfs(const Grid& g, pair<int,int> s, pair<int,int> t) {

    int n = g.R * g.C;
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    Result res;
    int sIdx = idxOf(g, s), tIdx = idxOf(g, t);
    dist[sIdx] = 0;
    queue<pair<int,int>> q;
    q.push(s);

    while (!q.empty()) {

        auto cur = q.front(); q.pop();
        res.expanded++;

        if (idxOf(g, cur) == tIdx)
            break;

        for (auto& nb : neighbours(g, cur.first, cur.second)) {

            int ni = idxOf(g, nb);

            if (dist[ni] == -1) {
                dist[ni] = dist[idxOf(g, cur)] + 1;
                parent[ni] = idxOf(g, cur);
                q.push(nb);
            }
        }
    }

    if (dist[tIdx] == -1) {
        res.cost = -1;
        return res;
    }
    res.cost = dist[tIdx];
    res.path = reconstruct(g, s, t, parent);

    return res;
}


// DFS - SINGLE PAIR, ITERATIVE

Result dfs(const Grid& g, pair<int,int> s, pair<int,int> t) {

    int n = g.R * g.C;
    vector<char> visited(n, 0);
    vector<int> parent(n, -1);
    vector<int> depth(n, -1);
    Result res;
    int sIdx = idxOf(g, s), tIdx = idxOf(g, t);
    stack<pair<int,int>> st;
    st.push(s);
    visited[sIdx] = 1;
    depth[sIdx] = 0;
    bool found = false;

    while (!st.empty()) {

        auto cur = st.top(); st.pop();
        res.expanded++;

        if (idxOf(g, cur) == tIdx) {
            found = true;
            break;
        }

        for (auto& nb : neighbours(g, cur.first, cur.second)) {
            int ni = idxOf(g, nb);

            if (!visited[ni]) {
                visited[ni] = 1;
                parent[ni] = idxOf(g, cur);
                depth[ni] = depth[idxOf(g, cur)] + 1;
                st.push(nb);
            }
        }
    }

    if (!found) {
        res.cost = -1;
        return res;
    }
    res.cost = depth[tIdx];
    res.path = reconstruct(g, s, t, parent);

    return res;
}


// DIJKSTRA - SINGLE PAIR, WEIGHTED

Result dijkstra(const Grid& g, pair<int,int> s, pair<int,int> t) {

    int n = g.R * g.C;
    vector<long long> dist(n, LLONG_MAX);
    vector<int> parent(n, -1);
    vector<char> settled(n, 0);
    Result res;
    int sIdx = idxOf(g, s), tIdx = idxOf(g, t);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[sIdx] = 0;
    pq.push({0, sIdx});

    while (!pq.empty()) {

        auto top = pq.top(); pq.pop();
        long long d = top.first;
        int u = top.second;

        if (settled[u])
            continue;

        settled[u] = 1;
        res.expanded++;

        if (u == tIdx)
            break;

        int r = u / g.C;
        int c = u % g.C;

        for (auto& nb : neighbours(g, r, c)) {

            int ni = idxOf(g, nb);

            if (settled[ni])
                continue;

            long long nd = d + cellCost(g.cells[nb.first][nb.second]);

            if (nd < dist[ni]) {
                dist[ni] = nd;
                parent[ni] = u;
                pq.push({nd, ni});
            }
        }
    }

    if (dist[tIdx] == LLONG_MAX) {
        res.cost = -1;
        return res;
    }

    res.cost = (int)dist[tIdx];
    res.path = reconstruct(g, s, t, parent);

    return res;
}


// A* - SINGLE-PAIR, WEIGHTED

Result astar(const Grid& g, pair<int,int> s, pair<int,int> t) {

    int n = g.R * g.C;
    vector<long long> dist(n, LLONG_MAX);
    vector<int> parent(n, -1);
    vector<char> settled(n, 0);
    Result res;
    int sIdx = idxOf(g, s);
    int tIdx = idxOf(g, t);

    auto heuristic = [&](int r, int c) -> long long {
        return llabs((long long)r - t.first) + llabs((long long)c - t.second);
    };

    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[sIdx] = 0;
    pq.push({heuristic(s.first, s.second), sIdx});

    while (!pq.empty()) {

        auto top = pq.top(); pq.pop();
        int u = top.second;

        if (settled[u])
            continue;

        settled[u] = 1;
        res.expanded++;

        if (u == tIdx)
            break;

        int r = u / g.C;
        int c = u % g.C;

        for (auto& nb : neighbours(g, r, c)) {

            int ni = idxOf(g, nb);

            if (settled[ni])
                continue;

            long long nd = dist[u] + cellCost(g.cells[nb.first][nb.second]);

            if (nd < dist[ni]) {
                dist[ni] = nd;
                parent[ni] = u;
                pq.push({nd + heuristic(nb.first, nb.second), ni});
            }
        }
    }

    if (dist[tIdx] == LLONG_MAX) {
        res.cost = -1;
        return res;
    }

    res.cost = (int)dist[tIdx];
    res.path = reconstruct(g, s, t, parent);

    return res;
}

//bestOrder - COIN VISIT BACKTRACKING

void bestOrderRecurse(int depth, const vector<int>& coinIdx, int startIdx, int goalIdx,
                              vector<int>& current, vector<char>& used, long long partialSum,
                              const vector<vector<int>>& dist, long long& bestTotal,
                              vector<int>& bestOut) {

    stats.dfsTotalRecursiveCalls++;
    if (partialSum >= bestTotal)
        return; // no need to prune

    int K = (int)coinIdx.size();

    if (depth == K) {

        stats.dfsOrderingsTried++;
        int last = current.empty() ? startIdx : current.back();
        long long total = partialSum + dist[last][goalIdx];

        if (total < bestTotal) {
            bestTotal = total;
            bestOut = current;
        }

        return;
    }

    int prevIdx = current.empty() ? startIdx : current.back();

    for (int i = 0; i < K; i++) {

        if (used[i])
            continue;

        int nextIdx = coinIdx[i];
        long long newSum = partialSum + dist[prevIdx][nextIdx];

        if (newSum >= bestTotal)
            continue; // prune this branch

        used[i] = 1;
        current.push_back(nextIdx);
        bestOrderRecurse(depth + 1, coinIdx, startIdx, goalIdx, current, used, newSum, dist, bestTotal, bestOut);
        current.pop_back();
        used[i] = 0;
    }
}

int bestOrder(const vector<vector<int>>& dist, int startIdx, int goalIdx, vector<int>& outOrder) {

    stats.bestOrderCalls++;
    int total = (int)dist.size();
    vector<int> coinIdx;

    for (int i = 0; i < total; i++)
        if (i != startIdx && i != goalIdx) coinIdx.push_back(i);

    vector<int> current;
    vector<char> used(coinIdx.size(), 0);
    long long bestTotal = LLONG_MAX;
    vector<int> bestOut;
    bestOrderRecurse(0, coinIdx, startIdx, goalIdx, current, used, 0, dist, bestTotal, bestOut);
    outOrder = bestOut;

    return (int)bestTotal;
}


// KEY POINTS

struct KeyPoint {
    pair<int,int> pos;
    char type;
};

string labelOf(const KeyPoint& k) {

    if (k.type == 'S')
        return "S";
    if (k.type == 'G')
        return "G";

    return "c(" + to_string(k.pos.first) + "," + to_string(k.pos.second) + ")";
}

string orderToString(const vector<KeyPoint>& kp, const vector<int>& fullOrder) {

    string s;

    for (size_t i = 0; i < fullOrder.size(); i++) {
        if (i)
            s += " -> ";
        s += labelOf(kp[fullOrder[i]]);
    }

    return s;
}

void printGrid(const vector<string>& grid) {
    for (auto& row : grid) cout << row << "\n";
}


// MAIN FUNCTION

int main(int argc, char* argv[]) {

    string inputPath;

    for (int i = 1; i < argc; i++) {
        string a = argv[i];
        if (!a.empty())
            inputPath = a;
    }

    ifstream fin(inputPath);
    int R, C;
    fin >> R >> C;
    int sr, sc, gr, gc;
    fin >> sr >> sc >> gr >> gc;
    fin.ignore();

    Grid g;
    g.R = R; g.C = C;
    g.cells.resize(R);

    for (int i = 0; i < R; i++) {

        getline(fin, g.cells[i]);

        while (!g.cells[i].empty() && (g.cells[i].back() == '\r' || g.cells[i].back() == '\n'))
            g.cells[i].pop_back();

        if ((int)g.cells[i].size() < C)
            g.cells[i].resize(C, '.');
    }

    vector<KeyPoint> kp;
    kp.push_back({{sr, sc}, 'S'});

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (g.cells[r][c] == 'c') kp.push_back({{r, c}, 'c'});

    kp.push_back({{gr, gc}, 'G'});
    int K = kp.size() - 2;
    int total = K + 2;
    int startIdx = 0, goalIdx = total - 1;

    vector<vector<int>> bfsMatrix(total, vector<int>(total, 0));
    vector<vector<int>> dijkstraMatrix(total, vector<int>(total, 0));
    vector<vector<int>> astarMatrix(total, vector<int>(total, 0));
    vector<vector<Result>> bfsRes(total, vector<Result>(total));
    vector<vector<Result>> dijkstraRes(total, vector<Result>(total));
    bool reachable = true;

    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total; j++) {
            if (i == j) continue;

            Result rb = bfs(g, kp[i].pos, kp[j].pos);
            stats.bfsCalls++;
            stats.bfsExpandedTotal += rb.expanded;
            bfsRes[i][j] = rb;
            bfsMatrix[i][j] = rb.cost;
            if (rb.cost < 0)
                reachable = false;

            Result rf = dfs(g, kp[i].pos, kp[j].pos);
            stats.dfsCalls++;
            stats.dfsExpandedTotal += rf.expanded;
            if (rb.cost >= 0 && rf.cost > rb.cost)
                stats.dfsLongerThanBfs++;

            Result rd = dijkstra(g, kp[i].pos, kp[j].pos);
            stats.dijkstraCalls++;
            stats.dijkstraExpandedTotal += rd.expanded;
            dijkstraRes[i][j] = rd;
            dijkstraMatrix[i][j] = rd.cost;

            Result ra = astar(g, kp[i].pos, kp[j].pos);
            stats.astarCalls++;
            stats.astarExpandedTotal += ra.expanded;
            astarMatrix[i][j] = ra.cost;
        }
    }

    if (!reachable) {
        cout << "No path found\n";
        return 0;
    }

    vector<int> uniformOrder, weightedOrder;
    int uniformTotal = bestOrder(bfsMatrix, startIdx, goalIdx, uniformOrder);
    int weightedTotal = bestOrder(dijkstraMatrix, startIdx, goalIdx, weightedOrder);

    vector<int> uniformFull = {startIdx};
    for (int x : uniformOrder)
        uniformFull.push_back(x);
    uniformFull.push_back(goalIdx);

    vector<int> weightedFull = {startIdx};
    for (int x : weightedOrder) weightedFull.push_back(x);
    weightedFull.push_back(goalIdx);

    // VISUALIZE
    vector<string> uniformVis = g.cells;
    for (size_t i = 0; i + 1 < uniformFull.size(); i++) {
        int a = uniformFull[i], b = uniformFull[i + 1];
        for (auto& cell : bfsRes[a][b].path) {
            char& ch = uniformVis[cell.first][cell.second];
            if (ch != 'S' && ch != 'G' && ch != 'c')
                ch = '*';
        }
    }
    vector<string> weightedVis = g.cells;
    for (size_t i = 0; i + 1 < weightedFull.size(); i++) {
        int a = weightedFull[i], b = weightedFull[i + 1];
        for (auto& cell : dijkstraRes[a][b].path) {
            char& ch = weightedVis[cell.first][cell.second];
            if (ch != 'S' && ch != 'G' && ch != 'c')
                ch = '*';
        }
    }

    // OUTPUT
    cout << "=== UNIFORM COST (BFS + DFS) ===\n";
    cout << "Coins: " << K << "\n";
    cout << "Best order: " << orderToString(kp, uniformFull) << "\n";
    cout << "Total steps: " << uniformTotal << "\n";
    cout << "Path:\n";
    printGrid(uniformVis);
    cout << "\n";

    cout << "=== WEIGHTED (Dijkstra + A*) ===\n";
    cout << "Coins: " << K << "\n";
    cout << "Best order: " << orderToString(kp, weightedFull) << "\n";
    cout << "Total cost: " << weightedTotal << "\n";
    cout << "A* cells expanded across all pair queries: " << stats.astarExpandedTotal << "\n";
    cout << "Dijkstra cells expanded across all pair queries: " << stats.dijkstraExpandedTotal << "\n";
    cout << "\n";

    cout << "SUMMARY | BFS pairs computed: " << stats.bfsCalls
         << " | DFS orderings tried: " << stats.dfsOrderingsTried
         << " | Dijkstra:" << stats.dijkstraExpandedTotal
         << " | A*:" << stats.astarExpandedTotal << "\n";

    return 0;
}
