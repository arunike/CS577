#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

#define graph_access(u,v) graph[u * num_nodes + v]

void initializeGraph(int num_nodes, int num_nodes_A, int num_edges, vector<int>& graph) {
    int src, dest;

    for (int i = 0; i < num_edges; i++) {
        cin >> src >> dest;

        dest += num_nodes_A;

        graph_access(src, dest) = 1;
    }

    for (int i = 1; i <= num_nodes_A; i++) {
        graph_access(0, i) = 1;
    }

    for (int i = num_nodes_A + 1; i < num_nodes - 1; i++) {
        graph_access(i, num_nodes - 1) = 1;
    }
}

bool findPathBFS(int num_nodes, vector<int>& graph, vector<int>& path) {
    deque<int> queue;

    vector<bool> visited(num_nodes, false);

    queue.push_back(0);

    visited[0] = true;
    path[0] = -1;

    while (!queue.empty()) {
        int current = queue.front();

        queue.pop_front();

        for (int next = 0; next < num_nodes; next++) {
            if (!visited[next] && graph_access(current, next) > 0) {
                queue.push_back(next);
                path[next] = current;
                visited[next] = true;
            }
        }
    }

    return visited[num_nodes - 1];
}

int calculateResidualCapacity(int num_nodes, vector<int>& graph, vector<int>& path) {
    int flow = INT_MAX;

    for (int v = num_nodes - 1; path[v] != -1; v = path[v]) {
        int u = path[v];

        flow = min(flow, graph_access(u, v));
    }

    for (int v = num_nodes - 1; path[v] != -1; v = path[v]) {
        int u = path[v];
        graph_access(u, v) -= flow;
        graph_access(v, u) += flow;
    }

    return flow;
}

int maxFlowFordFulkerson(int num_nodes, vector<int>& graph) {
    vector<int> path(num_nodes);
    int max_flow = 0;

    while (findPathBFS(num_nodes, graph, path)) {
        max_flow += calculateResidualCapacity(num_nodes, graph, path);
    }

    return max_flow;
}

int main() {
    int num_instances, num_nodes_A, num_nodes_B, num_edges;

    cin >> num_instances;

    while (num_instances--) {
        cin >> num_nodes_A >> num_nodes_B >> num_edges;
        int num_nodes_total = num_nodes_A + num_nodes_B + 2;

        vector<int> graph(num_nodes_total * num_nodes_total, 0);

        initializeGraph(num_nodes_total, num_nodes_A, num_edges, graph);

        int max_flow = maxFlowFordFulkerson(num_nodes_total, graph);
        
        cout << max_flow << ' ' << (num_nodes_A == num_nodes_B && max_flow == num_nodes_B ? 'Y' : 'N') << endl;
    }

    return 0;
}
