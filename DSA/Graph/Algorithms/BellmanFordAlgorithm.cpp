class Solution {
public:

    /*
        BELLMAN-FORD ALGORITHM
        ----------------------

        Purpose:
        Find the shortest distance from a source node to every other
        node in a weighted DIRECTED graph.

        Unlike Dijkstra, Bellman-Ford can handle NEGATIVE edge weights.

        Main Idea:
        Relax EVERY edge V-1 times.

        Why V-1?
        A shortest simple path can contain at most V-1 edges.

        In the worst case, one round guarantees that shortest-path
        information can propagate one more edge forward.

        So:
            Round 1   -> paths using up to 1 edge
            Round 2   -> paths using up to 2 edges
            ...
            Round V-1 -> paths using up to V-1 edges

        Relaxation:
            For edge:

                u -> v   weight w

            if reaching v through u is cheaper:

                dist[u] + w < dist[v]

            then:

                dist[v] = dist[u] + w


        Unreachable Nodes:
        We use 1e8 as INF.

        If:
            dist[u] == 1e8

        then source has not reached u yet.

        Therefore u cannot currently provide a path to v,
        so we skip that edge.


        Negative Cycle Detection:
        After V-1 rounds, normal shortest distances should be finalized.

        We check EVERY edge one more time.

        If any distance can STILL become smaller:

            dist[u] + w < dist[v]

        then a reachable NEGATIVE WEIGHT CYCLE exists.

        Return {-1}.


        Mental Model:

            dist[src] = 0

                  ↓

            Repeat V-1 times

                  ↓

            Check EVERY edge

                  ↓

            Can u make v cheaper?

                  ↓

            YES -> update dist[v]

                  ↓

            After V-1 rounds,
            check all edges ONE MORE time

                  ↓

            Still improving?

            YES -> Negative Cycle


        Remember:

        BELLMAN-FORD
        = EVERY EDGE × (V-1)
          + ONE EXTRA CHECK
    */

    vector<int> bellmanFord(int V,
                            vector<vector<int>>& edges,
                            int src) {

        // 1e8 represents an unreachable node
        vector<int> dist(V, 1e8);

        // Distance from source to itself is 0
        dist[src] = 0;


        // Relax every edge V-1 times
        for (int i = 0; i < V - 1; i++) {

            for (auto edge : edges) {

                int u = edge[0];
                int v = edge[1];
                int w = edge[2];


                // Cannot travel from u if u is not reachable yet
                if (dist[u] == 1e8)
                    continue;


                // Relax edge u -> v
                if (dist[u] + w < dist[v]) {

                    dist[v] = dist[u] + w;
                }
            }
        }


        // One extra relaxation round to detect a negative cycle
        for (auto edge : edges) {

            int u = edge[0];
            int v = edge[1];
            int w = edge[2];


            // Ignore edges starting from unreachable nodes
            if (dist[u] == 1e8)
                continue;


            // Improvement after V-1 rounds means negative cycle
            if (dist[u] + w < dist[v]) {

                return {-1};
            }
        }


        return dist;
    }
};