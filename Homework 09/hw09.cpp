#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
#include <string>

using namespace std;

int findPathBFS(int num_nodes, vector<vector<int> >& graph, vector<int>& path) {
    fill(path.begin(), path.end(), -1);
    vector<bool> visited(num_nodes, false);
    queue<int> q;

    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < num_nodes; ++v) {
            if (graph[u][v] > 0 && !visited[v]) {
                path[v] = u;

                if (v == num_nodes - 1) {
                    return true;
                }

                q.push(v);

                visited[v] = true;
            }
        }
    }

    return false;
}

int updateResidualGraph(int num_nodes, vector<vector<int> >& graph, vector<int>& path) {
    int flow = INT_MAX;

    for (int v = num_nodes - 1; path[v] >= 0; v = path[v]) {
        int u = path[v];
        flow = min(flow, graph[u][v]);
    }

    for (int v = num_nodes - 1; path[v] >= 0; v = path[v]) {
        int u = path[v];
        graph[u][v] -= flow;
        graph[v][u] += flow;
    }
    return flow;
}

int calculateMaxFlow(int num_nodes, vector<vector<int> >& graph) {
    vector<int> path(num_nodes);
    int max_flow = 0;

    while (findPathBFS(num_nodes, graph, path)) {
        max_flow += updateResidualGraph(num_nodes, graph, path);
    }

    return max_flow;
}

int main() {
    int num_instances;
    cin >> num_instances;

    while (num_instances--) {
        int num_nodes, num_edges;
        cin >> num_nodes >> num_edges;
        
        vector<vector<int> > graph(num_nodes, vector<int>(num_nodes, 0));

        for (int i = 0; i < num_edges; ++i) {
            int src, dest, cap;
            cin >> src >> dest >> cap;
            graph[src - 1][dest - 1] += cap;
        }

        cout << calculateMaxFlow(num_nodes, graph) << endl;
    }

    return 0;
}