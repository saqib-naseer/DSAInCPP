class Solution {
public:
    vector<int> bfs(vector<vector<int>>& adj) {

        // visited[i] tells whether node i has already been discovered.
        // Initially, no node is visited.
        vector<int> visited(adj.size(), 0);

        // BFS uses a queue (FIFO).
        // Nodes discovered first are processed first.
        queue<int> q;

        // Start BFS from node 0.
        q.push(0);

        // Mark as visited WHEN pushing into the queue.
        // This prevents the same node from being added multiple times.
        visited[0] = true;

        // Stores BFS traversal order.
        vector<int> ans;

        // Continue until there are no nodes left to process.
        while (!q.empty()) {

            // Take the node at the front of the queue.
            int node = q.front();
            q.pop();

            // This node is now being processed.
            ans.push_back(node);

            // adj[node] contains all neighbours of 'node'.
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbour = adj[node][i];

                // If this neighbour has not been discovered yet:
                if (!visited[neighbour]) {

                    // Add it to the queue so its neighbours
                    // can be explored later.
                    q.push(neighbour);

                    // Mark immediately to avoid duplicate insertion.
                    visited[neighbour] = true;
                }
            }
        }

        return ans;
    }
};