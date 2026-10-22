/*
    Problem: LeetCode 1584 - Min Cost to Connect All Points

    Pattern:
    Minimum Spanning Tree (MST) + Kruskal's Algorithm + DSU

    Goal:
    Connect all given points with the minimum possible total cost.

    Each point is treated as a graph vertex.

    Since any point can be connected to any other point, we create an
    edge between every pair of points.

    The weight of an edge is the Manhattan distance:

        |x1 - x2| + |y1 - y2|

    KRUSKAL'S IDEA:
    ----------------
    Kruskal processes ALL graph edges from cheapest to most expensive.

    Normally we could sort all edges by weight. Here we use a min-heap
    instead, so pq.top() always gives us the cheapest remaining edge.

    For every edge:

        u -------- v

    1. Find the DSU root of u.
    2. Find the DSU root of v.

    If both roots are SAME:
        u and v are already connected through previously selected edges.
        Taking this edge would create a cycle.
        Therefore skip it.

    If roots are DIFFERENT:
        They belong to different connected components.
        This edge is safe to take.
        Add its weight to MST cost.
        Merge their DSU groups.

    DSU (Disjoint Set Union):
    -------------------------
    parent[]:
        Represents the connected groups.

    findParent():
        Finds the root/representative of a node's group.

    Path Compression:
        While finding the root, directly connect nodes closer to the root
        so future find operations become faster.

    unionByRank():
        Merges two different DSU groups.

    rank[]:
        Helps prevent DSU trees from becoming unnecessarily tall.
        The lower-rank root is attached under the higher-rank root.
        If ranks are equal, either can become root and its rank increases.

    IMPORTANT:
    The DSU parent tree is NOT the actual MST.

    Kruskal builds the MST by accepting edges.
    DSU only keeps track of which vertices are already connected.

    In this problem we only need the MST's total cost, so we do not
    explicitly store the accepted MST edges.

    Example Kruskal decision:

        rootU == rootV
            -> same component
            -> edge creates cycle
            -> skip

        rootU != rootV
            -> different components
            -> accept edge
            -> add weight
            -> union components

    Time Complexity:
        Number of possible edges = O(N^2)

        Creating all edges:
            O(N^2)

        Each edge is inserted/removed from the min-heap:
            O(log E)

        Overall:
            O(N^2 log N)

    Space Complexity:
        O(N^2) because the heap stores all possible edges.

    Memory Trick:

        Kruskal =
        "Take globally cheapest edge.
         If it doesn't create a cycle, keep it."

        DSU =
        "Are these two nodes already in the same group?"

        find()  -> find the group's root
        union() -> merge two groups
        rank    -> keep DSU trees short
*/

class Solution {
public:

    int findParent(int u, vector<int>& parent) {

        // A node pointing to itself is the root of its group.
        if (parent[u] == u)
            return u;

        // Find the root and compress the path.
        parent[u] = findParent(parent[u], parent);

        // Return the representative of this group.
        return parent[u];
    }

    void unionByRank(int rootU, int rootV,
                     vector<int>& rank,
                     vector<int>& parent) {

        // Attach the lower-rank tree under the higher-rank tree.
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        }
        else {
            // Equal ranks: choose rootV as the new root.
            parent[rootU] = rootV;

            // Equal-rank trees joined, so the new root's rank increases.
            rank[rootV]++;
        }
    }

    int minCostConnectPoints(vector<vector<int>>& points) {

        // Min-heap stores {weight, {u, v}}.
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > pq;

        // Create an edge between every unique pair of points.
        for (int i = 0; i < points.size(); i++) {

            // Start from i + 1 to avoid duplicate edges.
            for (int j = i + 1; j < points.size(); j++) {

                // Calculate Manhattan distance between the two points.
                int weight =
                    abs(points[i][0] - points[j][0]) +
                    abs(points[i][1] - points[j][1]);

                // Add this edge as a Kruskal candidate.
                pq.push({weight, {i, j}});
            }
        }

        // parent[i] represents the DSU parent of node i.
        vector<int> parent(points.size());

        // Initially every node belongs to its own separate group.
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
        }

        // Initially all DSU trees have rank 0.
        vector<int> rank(points.size(), 0);

        // Total weight of accepted MST edges.
        int cost = 0;

        // Process all edges from cheapest to most expensive.
        while (!pq.empty()) {

            // Get the cheapest remaining edge.
            auto edge = pq.top();
            pq.pop();

            // Extract edge information.
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            // Find the current DSU groups of both endpoints.
            int rootU = findParent(u, parent);
            int rootV = findParent(v, parent);

            // Different roots mean this edge will not create a cycle.
            if (rootU != rootV) {

                // Accept this edge into the MST.
                cost += weight;

                // Merge the two connected components.
                unionByRank(rootU, rootV, rank, parent);
            }
        }

        return cost;
    }
};