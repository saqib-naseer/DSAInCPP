class Solution {
public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges) {

        // Weighted adjacency list:
        // adj[u] stores {neighbor, weight}
        vector<vector<pair<int, int>>> adj(V);

        // indegree[i] = number of incoming edges to node i
        // Used for Kahn's Topological Sort
        vector<int> inDeg(V, 0);

        // Build directed weighted graph
        for (vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            inDeg[v]++;
        }

        // ------------------------------------------------
        // KAHN'S TOPOLOGICAL SORT
        // ------------------------------------------------

        queue<int> q;

        // Initially, all nodes having indegree 0 are ready.
        // We cannot only push source 0 because an unreachable
        // node may still have an edge into a reachable node.
        for (int i = 0; i < V; i++) {
            if (inDeg[i] == 0) {
                q.push(i);
            }
        }

        // dist[i] = shortest distance from source 0 to node i
        // Initially every node is unreachable.
        vector<int> dist(V, INT_MAX);

        // Distance from source to itself is 0.
        dist[0] = 0;

        // Process nodes in topological order.
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // Check all outgoing weighted edges:
            // node --w--> neigh
            for (pair<int, int> neighbour : adj[node]) {

                int neigh = neighbour.first;
                int w = neighbour.second;

                // Relax the edge ONLY if current node
                // is reachable from source 0.
                //
                // Example:
                // dist[node] = 5, weight = 3
                // Possible new distance to neigh = 8
                if (dist[node] != INT_MAX) {
                    dist[neigh] = min(
                        dist[neigh],
                        dist[node] + w
                    );
                }

                // Kahn's algorithm:
                // One incoming dependency has been processed.
                inDeg[neigh]--;

                // All incoming nodes have now been processed,
                // so neigh is ready to process.
                if (inDeg[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }

        // Convert unreachable nodes from INT_MAX to -1.
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                dist[i] = -1;
            }
        }

        return dist;
    }
};