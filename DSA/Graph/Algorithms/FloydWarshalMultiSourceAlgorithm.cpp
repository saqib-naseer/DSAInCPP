class Solution {
public:

    /*
        FLOYD-WARSHALL ALGORITHM
        ------------------------

        Purpose:
        Find the shortest distance between EVERY pair of vertices.

        Unlike Dijkstra/Bellman-Ford, which normally calculate
        shortest paths from ONE source, Floyd-Warshall calculates:

            every source -> every destination


        dist[i][j]
        = shortest known distance from node i to node j.


        CORE IDEA:

        For every possible intermediate node k, ask:

            "Can going from i -> k -> j
             make the current i -> j distance cheaper?"


        Current route:

            i ----------------> j
                 dist[i][j]


        Alternative route:

            i ------> k ------> j

            dist[i][k] + dist[k][j]


        Relaxation:

            dist[i][j] =
                min(
                    dist[i][j],
                    dist[i][k] + dist[k][j]
                );


        LOOP MEANING:

            k = MIDDLE / VIA node
            i = START / FROM node
            j = END / TO node


        IMPORTANT:
        k must be the OUTERMOST loop.

        Floyd-Warshall gradually allows:

            k = 0 -> node 0 can be used as middle
            k = 1 -> node 1 can also be used as middle
            k = 2 -> node 2 can also be used as middle
            ...

        Previous improvements are reused to build longer paths.


        INFINITY:

        In this GFG problem:

            1e8 = no known path

        Before calculating:

            dist[i][k] + dist[k][j]

        both parts must exist.

        Therefore check:

            dist[i][k] != 1e8
            dist[k][j] != 1e8


        Negative edge weights are allowed.

        Time Complexity:
            O(V^3)

        Space Complexity:
            O(1) extra here because the given matrix
            is modified in-place.

        Mental Line:

            "For every MIDDLE k,
             can i -> k -> j improve i -> j?"
    */

    void floydWarshall(vector<vector<int>>& dist) {

        int V = dist.size();


        // k = intermediate / middle node
        for (int k = 0; k < V; k++) {

            // i = starting node
            for (int i = 0; i < V; i++) {

                // j = destination node
                for (int j = 0; j < V; j++) {

                    // Both i -> k and k -> j must exist
                    // 1e8 means no path exists (GFG)
                    if (dist[i][k] != 1e8 &&
                        dist[k][j] != 1e8) {

                        // Try reaching j from i through k
                        dist[i][j] = min(
                            dist[i][j],
                            dist[i][k] + dist[k][j]
                        );
                    }
                }
            }
        }
    }
};