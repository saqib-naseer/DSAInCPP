/*
    Problem: Minimum Spanning Tree using Prim's Algorithm

    Goal:
    Connect all V vertices with minimum total edge weight
    while forming a tree (connected + no cycles).

    -------------------------------------------------------
    PRIM'S MAIN IDEA
    -------------------------------------------------------

    Start from any vertex (here we start from node 0).

    Keep a min-heap containing possible edges that can
    connect new vertices to our current MST.

    Heap entry:

        {weight, {node, parent}}

    Example:

        {5, {3, 1}}

    means:

        "Node 3 can be connected to our MST
         through node 1 with cost 5."

    IMPORTANT:

        PUSHING a node into the heap
        does NOT mean it has joined the MST.

        Heap = candidate connections only.

    A node joins the MST only when its cheapest valid
    candidate is POPPED from the min-heap.

    Why?

    The same node may enter the heap multiple times
    through different edges.

    Example:

        0 --10-- 1
        |
        2
        |
        2 --1--- 1

    Node 1 may first enter heap with cost 10.

    Later we may discover a much cheaper way:

        2 -> 1 with cost 1

    The min-heap ensures the cheaper candidate is
    processed first.

    -------------------------------------------------------
    ALGORITHM
    -------------------------------------------------------

    1. Build an undirected weighted adjacency list.

       adj[u] stores:
           {neighbour, weight}

    2. Push starting node:

           {0, {0, -1}}

       Cost 0 because connecting the starting node
       requires no edge.

    3. Repeatedly pop the cheapest candidate.

    4. If node is already part of MST:
           skip it.

    5. Otherwise:
           mark it as part of MST
           add popped edge weight to total cost

    6. Push edges leading to vertices that are not
       already part of MST.

    -------------------------------------------------------
    PATTERN
    -------------------------------------------------------

        Weighted Undirected Graph
                +
        Minimum Spanning Tree
                +
        Prim's Algorithm
                +
        Min Heap / Priority Queue

    Memory:

        PRIM = Grow one tree using the cheapest
               available connection.

    Time Complexity:
        Building adjacency list: O(E)

        Every edge may enter the priority queue.
        Heap operations cost logarithmic time.

        Approximately O(E log E),
        commonly also expressed as O(E log V)
        for standard Prim implementations.

    Space Complexity:
        O(V + E)
        for adjacency list, visited/MST array and heap.
*/

class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {

        // adj[u] = {neighbour, edgeWeight}
        vector<vector<pair<int, int>>> adj(V);

        // Build undirected weighted adjacency list.
        for (const auto& edge : edges) {

            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            // Since graph is undirected, add both directions.
            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }

        // isMST[i] tells whether vertex i has already
        // been permanently included in the MST.
        vector<bool> isMST(V, false);

        /*
            Min heap stores:

                {weight, {node, parent}}

            The smallest weight candidate stays on top.

            parent is useful if we later want to actually
            construct/print the MST edges.

            For this problem we only need total MST cost.
        */
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > pq;

        // Start Prim from vertex 0.
        // No edge is needed to include the starting node,
        // therefore its initial cost is 0.
        pq.push({0, {0, -1}});

        int mstCost = 0;

        while (!pq.empty()) {

            // Get the cheapest available candidate.
            int weight = pq.top().first;
            int node = pq.top().second.first;
            int parent = pq.top().second.second;

            pq.pop();

            /*
                IMPORTANT:

                The same node may have been pushed into the
                heap through multiple different edges.

                If it already joined the MST through a cheaper
                edge, this heap entry is now useless.
            */
            if (isMST[node]) {
                continue;
            }

            /*
                NOW the node officially joins the MST.

                Notice:
                We mark it here when POPPED,
                NOT when it was pushed into the heap.
            */
            isMST[node] = true;

            // The popped edge is the connection we selected.
            mstCost += weight;

            /*
                Look at all edges leaving this newly added node.

                They become possible candidates for expanding
                our MST further.
            */
            for (const auto& neighbour : adj[node]) {

                int nextNode = neighbour.first;
                int edgeWeight = neighbour.second;

                // No need to connect a vertex already in MST.
                if (!isMST[nextNode]) {

                    /*
                        This does NOT mean nextNode has joined MST.

                        We are only saying:

                        "Here is one possible way to connect
                         nextNode later."

                        The min-heap will decide which candidate
                        is cheapest.
                    */
                    pq.push({
                        edgeWeight,
                        {nextNode, node}
                    });
                }
            }
        }

        return mstCost;
    }
};