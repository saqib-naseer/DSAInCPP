class Solution {
public:
    bool isCycle(int V, vector<vector<int>>& edges) {

        // STEP 1: Convert edge list into adjacency list.
        //
        // Since the graph is undirected:
        // edge {u, v} means:
        // u -> v
        // v -> u
        vector<vector<int>> adj(V);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // visited[i] = 1 means vertex i has already been visited.
        vector<int> visited(V, 0);

        // STEP 2: Run DFS from every unvisited vertex.
        //
        // We cannot simply call dfsHelper(0, ...)
        // because the graph may have multiple disconnected components.
        for (int i = 0; i < V; i++) {

            if (!visited[i]) {

                // -1 means the starting node has no parent.
                if (dfsHelper(i, -1, adj, visited)) {
                    return true;
                }
            }
        }

        // No component contained a cycle.
        return false;
    }


    bool dfsHelper(
        int node,
        int parent,
        vector<vector<int>>& adj,
        vector<int>& visited
    ) {

        // Mark current node as visited.
        visited[node] = 1;

        // Explore all neighbours of current node.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbour = adj[node][i];

            // In an undirected graph, the node we came from
            // will naturally appear in the adjacency list.
            //
            // Example:
            // 0 ----- 1
            //
            // While exploring 1, we see 0 again.
            // But 0 is the parent, so this is NOT a cycle.
            if (neighbour == parent) {
                continue;
            }

            // If neighbour was already visited AND it is not
            // our parent, we reached an old node through
            // another path -> cycle exists.
            if (visited[neighbour]) {
                return true;
            }

            // Neighbour is unvisited, so continue DFS.
            //
            // Current node becomes the parent of neighbour.
            if (dfsHelper(neighbour, node, adj, visited)) {
                return true;
            }
        }

        // Finished exploring this path without finding a cycle.
        return false;
    }
};