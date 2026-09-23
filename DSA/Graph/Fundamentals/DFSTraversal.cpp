class Solution {
public:
    vector<int> dfs(vector<vector<int>>& adj) {

        // Stores the DFS traversal order.
        vector<int> ans;

        // visited[i] tells whether node i has already been visited.
        // Initially, all nodes are unvisited.
        vector<bool> visited(adj.size(), false);

        // Start DFS from node 0.
        dfsHelper(0, adj, ans, visited);

        return ans;
    }

    void dfsHelper(
        int node,
        vector<vector<int>>& adj,
        vector<int>& ans,
        vector<bool>& visited
    ) {

        // Mark the current node as visited.
        // This prevents us from visiting it again.
        visited[node] = true;

        // Add current node to DFS traversal.
        ans.push_back(node);

        // Explore every neighbour of the current node.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbour = adj[node][i];

            // If neighbour has not been visited,
            // recursively perform DFS from that neighbour.
            if (!visited[neighbour]) {
                dfsHelper(neighbour, adj, ans, visited);
            }
        }

        // When no unvisited neighbour remains,
        // this function returns automatically.
        // This is the BACKTRACKING part of DFS.
    }
};