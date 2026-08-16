#include <bits/stdc++.h>
#include "csr/csr.h"

using namespace std;

struct InputEdge {
    int u, v;
    long long cap;
};

struct FlowEdge {
    int to, rev;
    long long cap;
};

class Dinic {
    int n;
    vector<vector<FlowEdge>> g;
    vector<int> level, it;
    vector<InputEdge> originalEdges;

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);

        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& e : g[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] != -1;
    }

    long long dfs(int u, int t, long long pushed) {
        if (u == t)
            return pushed;

        for (int& i = it[u]; i < (int)g[u].size(); ++i) {

            FlowEdge& e = g[u][i];

            if (e.cap <= 0 || level[e.to] != level[u] + 1)
                continue;

            long long tr = dfs(
                e.to,
                t,
                min(pushed, e.cap)
            );

            if (tr == 0)
                continue;

            e.cap -= tr;
            g[e.to][e.rev].cap += tr;

            return tr;
        }

        return 0;
    }

public:
    Dinic(const CSRGraph& csr)
        : n((int)csr.row_ptr.size() - 1),
          g(n),
          level(n),
          it(n) {

        for (int u = 0; u < n; ++u) {

            for (int p = csr.row_ptr[u];
                 p < csr.row_ptr[u + 1];
                 ++p) {

                int v = csr.col_idx[p];

                long long capacity = csr.values[p];

                addEdge(u, v, capacity);

                originalEdges.push_back(
                    {u, v, capacity}
                );
            }
        }
    }

    void addEdge(int u, int v, long long capacity) {

        FlowEdge forward{
            v,
            (int)g[v].size(),
            capacity
        };

        FlowEdge reverse{
            u,
            (int)g[u].size(),
            0
        };

        g[u].push_back(forward);
        g[v].push_back(reverse);
    }

    long long maxFlow(int s, int t) {

        long long flow = 0;

        while (bfs(s, t)) {

            fill(it.begin(), it.end(), 0);

            while (true) {

                long long pushed =
                    dfs(s, t, LLONG_MAX / 4);

                if (pushed == 0)
                    break;

                flow += pushed;
            }
        }

        return flow;
    }

    vector<char> sourceReachable(int s) const {

        vector<char> visited(n, false);

        queue<int> q;

        visited[s] = true;
        q.push(s);

        while (!q.empty()) {

            int u = q.front();
            q.pop();

            for (const auto& e : g[u]) {

                if (e.cap > 0 && !visited[e.to]) {

                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }

        return visited;
    }

    const vector<InputEdge>& getOriginalEdges() const {
        return originalEdges;
    }
};


struct MaxflowResult {

    long long flow = 0;

    long long cutCapacity = 0;

    vector<int> sourceSide;

    vector<int> sinkSide;

    vector<InputEdge> cutEdges;
};


MaxflowResult solveMaxflowMincut(
    const CSRGraph& csr,
    int source,
    int sink
) {

    Dinic dinic(csr);

    MaxflowResult result;
    result.flow =
        dinic.maxFlow(source, sink);
    vector<char> reachable =
        dinic.sourceReachable(source);

    int n =
        (int)csr.row_ptr.size() - 1;

    for (int v = 0; v < n; ++v) {

        if (reachable[v])
            result.sourceSide.push_back(v);
        else
            result.sinkSide.push_back(v);
    }
    for (const auto& e :
         dinic.getOriginalEdges()) {

        if (reachable[e.u] &&
            !reachable[e.v]) {

            result.cutEdges.push_back(e);

            result.cutCapacity += e.cap;
        }
    }

    return result;
}