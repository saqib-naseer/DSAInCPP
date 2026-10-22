/*
    Problem: Minimum Spanning Tree using Prim's Algorithm

    Goal:
    Find the minimum total edge weight required to connect all vertices
    of a weighted undirected graph without creating cycles.

    Pattern:
    Weighted Undirected Graph + Minimum Spanning Tree + Greedy + Min Heap

    Prim's Algorithm:
    -----------------
    Prim grows ONE tree.

    Start from any node (here node 0) with cost 0.

    Use a min-heap containing:
        {edgeWeight, node}

    The heap contains CANDIDATES for joining the MST.

    IMPORTANT:
    Pushing a node into the heap does NOT mean it has joined the MST.
    A node officially joins the MST only when it is popped as the
    cheapest available candidate and it is not already in the MST.

    Why can the same node appear multiple times in the heap?

        0 --10-- 1
        |       /
        2     1
        |   /
        2

    Node 1 may first be pushed with cost 10.
    Later another node may offer a cheaper connection to 1 with cost 1.

    The min-heap ensures the cheaper candidate is popped first.

    When a node is popped:

        If already in MST:
            Skip it because this is an old/more expensive candidate.

        Otherwise:
            Mark it as part of MST.
            Add its edge weight to total MST cost.
            Push its non-MST neighbours into the heap.

    Starting node is pushed with weight 0 because no edge is required
    to start the MST.

    We do NOT need parent[] when only the total MST cost is required.
    Parent information is only needed if we want to store/print the
    actual MST edges.

    Memory Trick:
        Heap = possible offers
        Pop cheapest offer
        If node not taken -> accept it
        Add cost
        Offer its neighbours

    Prim = Grow ONE tree using the cheapest available connection.

    Time Complexity:
        O(E log V) with adjacency list + min heap.

    Space Complexity:
        O(V + E) for adjacency list, heap and MST visited array.
*/

class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {

        // adj[node] = {neighbour, edgeWeight}
        vector<vector<pair<int, int>>> adj(V);

        // Build weighted undirected adjacency list.
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }

        // Tracks vertices already permanently included in MST.
        vector<bool> isMST(V, false);

        // Min heap stores {edgeWeight, node}.
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        // Start from node 0 with no connection cost.
        pq.push({0, 0});

        int mstCost = 0;

        while (!pq.empty()) {

            // Get the cheapest available candidate.
            int weight = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Ignore duplicate candidate if node already joined MST.
            if (isMST[node])
                continue;

            // Node officially joins MST here.
            isMST[node] = true;

            // Pay the cost of the selected connection.
            mstCost += weight;

            // Offer all non-MST neighbours as future candidates.
            for (const auto& neighbour : adj[node]) {

                int nextNode = neighbour.first;
                int edgeWeight = neighbour.second;

                if (!isMST[nextNode]) {
                    pq.push({edgeWeight, nextNode});
                }
            }
        }

        return mstCost;
    }
};