/*
    PRIM'S ALGORITHM - MINIMUM SPANNING TREE (MST)

    PURPOSE:
    Find the minimum total cost required to connect all vertices
    of a weighted, undirected, connected graph.

    MAIN IDEA:
    Prim grows ONE connected tree.

    Start from any vertex, usually vertex 0.

    At every step:
        1. Look at the cheapest available candidate from the min-heap.
        2. If that vertex is already inside the MST, SKIP it.
        3. Otherwise:
            - Add the vertex to the MST.
            - Add the edge weight to MST cost.
            - Push its available neighbors into the min-heap.

    MIN HEAP:
    Stores:

        {weight, node}

    The heap contains candidate offers for connecting vertices
    to the current MST.

    IMPORTANT:
    Pushing something into the heap does NOT mean it has been
    accepted into the MST.

    It is only a candidate.

    A vertex becomes part of the MST when:

        1. It is popped as the cheapest candidate.
        2. It is not already inside the MST.

    WHY CAN THE SAME NODE APPEAR MULTIPLE TIMES?

    A node may be reachable through multiple edges.

    Example:

        0 ----10---- 2
        |
        2
        |
        1 ----3----- 2

    Heap may contain:

        {10, 2}
        {3, 2}

    The cheaper offer {3,2} will be accepted first.

    Later {10,2} is popped, but node 2 is already in MST,
    so that stale offer is skipped.

    IMPORTANT VISITED RULE:

    Ordinary BFS:
        Mark visited when PUSHING.

    Lazy Prim:
        Mark isMST when POPPING and ACCEPTING.

    Why?

    In Prim, pushing means:
        "Here is one possible offer."

    It does NOT mean:
        "This is definitely the cheapest way to connect this vertex."

    MST PROPERTY:
        For V vertices, MST contains exactly V - 1 edges.

    TIME COMPLEXITY:
        Using adjacency list + min heap:

        O(E log V)

    SPACE COMPLEXITY:
        O(V + E)

    MEMORY TRICK:

        PRIM:
        "Grow one tree using the cheapest available connection."

        Heap push:
            CANDIDATE / OFFER

        Heap pop + not already MST:
            ACCEPT

        Already in MST:
            SKIP

    PRIM VS KRUSKAL:

        Prim:
            Grow ONE tree.
            Min Heap + isMST[]

        Kruskal:
            Look at ALL edges globally.
            Sort Edges + DSU

        Prim asks:
            "What is the cheapest available connection
             to grow my current tree?"

        Kruskal asks:
            "What is the cheapest remaining edge that
             does not create a cycle?"
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// Returns the total cost of the Minimum Spanning Tree.
int primMST(int V, vector<vector<pair<int, int>>>& adj) {

    // Min-heap stores {edgeWeight, node}.
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    // Tracks vertices that have been permanently added to MST.
    vector<bool> isMST(V, false);

    // Start from vertex 0 with cost 0.
    pq.push({0, 0});

    int mstCost = 0;

    // Process cheapest available candidates.
    while (!pq.empty()) {

        // Get the cheapest candidate.
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // Skip stale offers for vertices already inside MST.
        if (isMST[node])
            continue;

        // Permanently add this vertex to the MST.
        isMST[node] = true;

        // Add the cost of the edge used to reach this vertex.
        mstCost += weight;

        // Explore all neighbors of the newly accepted vertex.
        for (auto& neighbour : adj[node]) {

            int nextNode = neighbour.first;
            int edgeWeight = neighbour.second;

            // Only outside vertices are useful candidates.
            if (!isMST[nextNode]) {
                pq.push({edgeWeight, nextNode});
            }
        }
    }

    return mstCost;
}


int main() {

    int V = 5;

    // Weighted undirected adjacency list.
    //
    // adj[u] contains:
    // {neighbor, edgeWeight}
    vector<vector<pair<int, int>>> adj(V);

    // Edge: 0 --2-- 1
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    // Edge: 0 --6-- 3
    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    // Edge: 1 --3-- 2
    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    // Edge: 1 --8-- 3
    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    // Edge: 1 --5-- 4
    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    // Edge: 2 --7-- 4
    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    // Edge: 3 --9-- 4
    adj[3].push_back({4, 9});
    adj[4].push_back({3, 9});

    cout << "MST Cost: " << primMST(V, adj) << endl;

    return 0;
}