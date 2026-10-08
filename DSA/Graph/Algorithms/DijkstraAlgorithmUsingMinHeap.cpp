class Solution {
public:

    /*
        DIJKSTRA'S ALGORITHM
        --------------------
        Purpose:
        Find the shortest distance from a source node to every other node
        in a weighted graph with NON-NEGATIVE edge weights.

        Main Idea:
        1. Keep the shortest known distance of every node in dist[].
        2. Use a MIN-HEAP storing:
                {distance, node}
        3. Always process the node having the smallest known distance.
        4. For every neighbor, try to improve its distance (RELAXATION).

        Relaxation:
            newDistance = dist[node] + edgeWeight

            If:
                newDistance < dist[neighbor]

            Then:
                dist[neighbor] = newDistance
                push {newDistance, neighbor} into heap

        Why Min-Heap?
        It always gives us the node with the smallest distance first.

        Important:
        - A node can enter the heap multiple times.
        - Example: {10, node} may be pushed first, then {5, node}.
        - The old {10, node} remains in the heap.
        - Skip such stale entries using:
              if (currDist > dist[node]) continue;

        No visited[] is required when using the stale-entry check.

        Dijkstra works with:
            Non-negative edge weights.

        Dijkstra should NOT be used with:
            Negative edge weights.

        Complexity:
            Time  : O((V + E) log V)
            Space : O(V + E)

        Mental Model:
            "Take cheapest node -> Relax neighbors -> Push improvements"
    */

    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {

        // Min-heap: {distance, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        // Shortest known distance from source
        vector<int> dist(V, INT_MAX);

        // Weighted adjacency list: {neighbor, weight}
        vector<vector<pair<int, int>>> adj(V);

        // Build undirected weighted graph
        for (vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Source starts at distance 0
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {

            // Get cheapest available node
            int currDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Skip old/stale heap entry
            if (currDist > dist[node])
                continue;

            // Explore neighbors
            for (pair<int, int> neigh : adj[node]) {

                int neighNode = neigh.first;
                int weight = neigh.second;

                // Distance through current node
                int newDist = dist[node] + weight;

                // Relax the edge
                if (newDist < dist[neighNode]) {

                    dist[neighNode] = newDist;

                    // Push improved distance
                    pq.push({newDist, neighNode});
                }
            }
        }

        return dist;
    }
};