#include <bits/stdc++.h>
#include "../src/csr/csr.h"

using namespace std;
struct InputEdge {
    int u, v;
long long cap;
};

struct MaxflowResult {
    long long flow = 0;
    long long cutCapacity = 0;
      vector<int> sourceSide;
    vector<int> sinkSide;
    vector<InputEdge> cutEdges;
};

MaxflowResult solveMaxflowMincut(const CSRGraph& csr,int source,int sink);

bool readInput(const string& file,WeightedAdjList& graph,int& source,int& sink) {
    ifstream in(file);
    if (!in) {
        cerr << "Error: cannot open input file: "<< file << '\n';
        return false;
    }

    int V, E;
    if (!(in>>V >> E) || V <= 0 || E < 0) {
        cerr << "Error: invalid V/E.\n";
        return false;
    }

    graph.assign(V, {});
    long long totalListed = 0;
       for (int i = 0; i < V; ++i) {
        int u, degree;

        if (!(in >> u >> degree) ||
            u < 0 || u >= V ||
            degree < 0) {

            cerr << "Error: invalid adjacency-list row.\n";
            return false;
        }

        for (int j = 0; j < degree; ++j) {
            int v;
            int cap;

            if (!(in >> v >> cap) ||
                v < 0 || v >= V ||
                cap <= 0) {
                        cerr << "Error: invalid directed edge/capacity.\n";
                return false;
            }

            graph[u].push_back({v, cap});

            ++totalListed;
        }
    }

string label;

    if (!(in>> label >>source) ||
        label != "SOURCE") {
        cerr << "Error: missing SOURCE.\n";
        return false;
    }

 if (!(in >> label>> sink) ||
        label != "SINK") {

        cerr << "Error: missing SINK.\n";
        return false;
    }

    if (source < 0 ||source >= V ||sink < 0 ||sink >= V || source == sink) {
        cerr << "Error: invalid source/sink.\n";
        return false;
    }

    if (totalListed != E) {
        cerr << "Error: declared E=" << E<< " but adjacency lists contain "<< totalListed<< " directed edges.\n";

        return false;
    }
    vector<char> visited(V, false);
    queue<int> q;
    visited[source] = true;
    q.push(source);
    while (!q.empty()) {

        int u = q.front();
        q.pop();
        for (const auto& edge : graph[u]) {

            int v = edge.first;

            if (!visited[v]) {

                visited[v] = true;
                q.push(v);
            }
        }
    }

    if (!visited[sink]) {
        cerr << "Error: no source-to-sink path exists.\n";
        return false;
    }

    return true;
}
int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: maxflow_driver <input_file>\n";
        return 1;
    }

    WeightedAdjList adjacencyList;
    int source;
    int sink;
    if (!readInput(
            argv[1],
            adjacencyList,
            source,
            sink)) {

        return 1;
    }
 CSRGraph csr =convertToCSR(adjacencyList);

    auto start =chrono::steady_clock::now();

    MaxflowResult result =solveMaxflowMincut(csr,source,sink);

    auto stop =chrono::steady_clock::now();
double ms =chrono::duration<double, milli>(stop - start).count();


cout << "Algorithm: Maxflow-Mincut\n";
cout << "Source: "<< source << '\n';
cout << "Sink: "<< sink << '\n';
cout << "Maximum flow: "<< result.flow << '\n';
cout<< "Minimum cut capacity: " << result.cutCapacity << '\n';
cout <<"Number of cut edges: "<< result.cutEdges.size() << '\n';
cout<<fixed << setprecision(6);
cout<< "Execution time: "<< ms<< " ms\n";
if (result.flow != result.cutCapacity) {

    cerr << "Warning: max-flow/min-cut equality check failed.\n";
             return 2;
}
return 0;
}