bool validPath(int n, vector<vector<int>>& edges,
               int source, int destination) {

    // visited[i] tells whether node i has already
    // been discovered by BFS.
    vector<bool> visited(n, false);

    // Convert edge list -> adjacency list.
    vector<vector<int>> adj(n);

    for (auto& edge : edges) {

        int u = edge[0];
        int v = edge[1];

        // Undirected graph, so add both directions.
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Start BFS from source.
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {

        // Take next node to explore.
        int node = q.front();
        q.pop();

        // We successfully reached destination.
        if (node == destination) {
            return true;
        }

        // Explore all neighbours of current node.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbour = adj[node][i];

            // Only discover a node once.
            if (!visited[neighbour]) {

                // Mark when adding to queue so that
                // another node cannot add it again.
                visited[neighbour] = true;

                q.push(neighbour);
            }
        }
    }

    // BFS finished without reaching destination.
    return false;
}