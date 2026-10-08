class Solution {
public:

    /*
        DIJKSTRA'S ALGORITHM - BASIC / ARRAY VERSION
        ---------------------------------------------

        Purpose:
        Find shortest distance from source to every other node
        in a weighted graph with NON-NEGATIVE edge weights.

        Main Idea:
        We maintain two arrays:

        1. dist[]
           - Shortest distance found so far from source.
           - dist[src] = 0
           - Others initially = INT_MAX

        2. explored[]
           - false = node is not finalized yet
           - true  = shortest distance of this node is finalized

        Algorithm:
        1. Find the unexplored node having minimum dist[].
        2. Mark that node explored.
        3. Relax all its unexplored neighbors.
        4. Repeat.

        Relaxation:
            newDist = dist[node] + weight

            if newDist < dist[neighbor]:
                dist[neighbor] = newDist

        Why can we finalize the minimum node?
        Because Dijkstra works with non-negative weights.
        The cheapest unexplored node cannot later get a cheaper
        path through another more expensive unexplored node.

        IMPORTANT:
        This version manually scans all V nodes to find the minimum.

        Complexity:
            Time  : O(V^2 + E) -> usually written O(V^2)
            Space : O(V + E)

        This version may TLE for large graphs.

        Optimized Dijkstra:
            Use a Min-Heap / Priority Queue
            Time: O((V + E) log V)

        Mental Model:
            "Find cheapest unexplored -> Finalize -> Relax neighbors"
    */

    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {

        // Shortest known distance from source
        vector<int> dist(V, INT_MAX);

        // Whether node's shortest distance is finalized
        vector<bool> explored(V, false);

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

        // Source is distance 0 from itself
        dist[src] = 0;

        // At most V nodes can be finalized
        int count = V;

        while (count--) {

            int node = -1;
            int minDist = INT_MAX;

            // Find cheapest unexplored node
            for (int i = 0; i < V; i++) {

                if (!explored[i] && dist[i] < minDist) {
                    node = i;
                    minDist = dist[i];
                }
            }

            // No more reachable nodes
            if (node == -1)
                break;
      /*
                  // Finalize this node
                Here, explored really means:
      The shortest distance TO this node is finalized.
      
      It does not mean:
      I have finished processing everything FROM this node.*/
            explored[node] = true;

            // Relax its neighbors
            for (pair<int, int> neigh : adj[node]) {

                int v = neigh.first;
                int w = neigh.second;

                // Distance through current node
                int newDist = dist[node] + w;

                // Update if a shorter path is found
                if (!explored[v] && newDist < dist[v]) {
                    dist[v] = newDist;
                }
            }
        }

        return dist;
    }
};