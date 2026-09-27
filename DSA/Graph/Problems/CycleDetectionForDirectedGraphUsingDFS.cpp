class Solution {
public:
    bool isCyclic(int V, vector<vector<int>>& edges) {

        // STEP 1: Build directed adjacency list.
        //
        // For edge u -> v:
        // v is an outgoing neighbor of u.
        vector<vector<int>> adj(V);

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
        }


        // visited[node]:
        // Has this node EVER been visited by any DFS?
        //
        // path[node]:
        // Is this node currently present in the CURRENT DFS recursion path?
        //
        // A cycle exists if we reach a node that is already
        // present in our current DFS path.
        vector<bool> vis(V, false);
        vector<bool> path(V, false);


        // STEP 2: Run DFS from every unvisited node.
        //
        // We need this loop because the graph can have
        // multiple disconnected components.
        for (int i = 0; i < V; i++) {

            if (!vis[i]) {

                // If any DFS component contains a cycle,
                // the entire graph contains a cycle.
                if (dfsHelper(i, adj, path, vis)) {
                    return true;
                }
            }
        }

        return false;
    }


    bool dfsHelper(int node,
                   vector<vector<int>>& adj,
                   vector<bool>& path,
                   vector<bool>& vis) {

        // STEP 3: Mark node as globally visited.
        //
        // This remains true even after we return from this DFS call.
        vis[node] = true;


        // Also mark node as part of the CURRENT DFS path.
        //
        // This will be reset to false when we backtrack.
        path[node] = true;


        // STEP 4: Explore all outgoing neighbors.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];


            // CASE 1:
            // Neighbor is already in the CURRENT DFS path.
            //
            // Example:
            //
            // 0 -> 1 -> 2
            //      ^    |
            //      |____|
            //
            // While processing 2, we see 1 again.
            //
            // path[1] == true
            //
            // This means we came back to a node that is still
            // active in our current recursion chain.
            //
            // Therefore we found a back edge => CYCLE.
            if (path[neighbor]) {
                return true;
            }


            // CASE 2:
            // Neighbor has never been visited.
            //
            // Continue DFS from that neighbor.
            //
            // If deeper recursion finds a cycle,
            // propagate true back to the caller.
            if (!vis[neighbor] &&
                dfsHelper(neighbor, adj, path, vis)) {

                return true;
            }


            // CASE 3:
            // visited[neighbor] == true
            // path[neighbor] == false
            //
            // This node was visited earlier, but it is NOT
            // part of our current recursion path.
            //
            // Therefore this does NOT indicate a cycle.
        }


        // STEP 5: BACKTRACK.
        //
        // We have completely explored this node and are now
        // returning from its DFS call.
        //
        // Keep:
        // visited[node] = true
        //
        // because the node has already been explored globally.
        //
        // But remove it from CURRENT recursion path.
        path[node] = false;


        // No cycle found through this node.
        return false;
    }
};