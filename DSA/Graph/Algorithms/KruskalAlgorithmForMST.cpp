/*
    KRUSKAL'S ALGORITHM - MINIMUM SPANNING TREE (MST)

    PURPOSE:
    Find the minimum total cost required to connect all vertices
    of a weighted, undirected, connected graph.

    MAIN IDEA:
    Kruskal looks at edges globally from cheapest to most expensive.

    For every edge (u, v):

        1. Find the DSU root of u.
        2. Find the DSU root of v.

        If roots are SAME:
            u and v are already connected.
            Taking this edge would create a cycle.
            SKIP the edge.

        If roots are DIFFERENT:
            The edge safely connects two different components.
            TAKE the edge.
            Add its weight to MST cost.
            UNION the two components.

    DSU:
        parent[] -> represents connected components
        find()   -> finds root/representative of a component
        union()  -> merges two components
        rank[]   -> keeps DSU trees short

    PATH COMPRESSION:
        findParent() makes nodes point closer/directly to their root,
        making future find operations faster.

    UNION BY RANK:
        Lower-rank tree goes under higher-rank tree.
        If ranks are equal, choose either root and increase its rank.

    IMPORTANT:
        DSU tree is NOT the actual MST.
        DSU only tracks which vertices are already connected.

    MST PROPERTY:
        For V vertices, MST contains exactly V - 1 edges.

    TIME COMPLEXITY:
        Sorting edges: O(E log E)
        DSU operations: almost O(1) average
        Overall: O(E log E)

    MEMORY TRICK:

        KRUSKAL:
        "Take the cheapest edge that does not create a cycle."

        SAME ROOT      -> SKIP
        DIFFERENT ROOT -> TAKE + UNION
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// Find the root of a node's DSU component.
int findParent(int node, vector<int>& parent) {

    // A node pointing to itself is the root.
    if (parent[node] == node)
        return node;

    // Find root and compress the path.
    parent[node] = findParent(parent[node], parent);

    return parent[node];
}


// Merge two different DSU components using rank.
void unionByRank(int rootU, int rootV,
                 vector<int>& parent,
                 vector<int>& rank) {

    // Put lower-rank tree under higher-rank tree.
    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    }
    else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    }
    else {
        // Equal ranks: choose rootU as the new root.
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}


// Returns the total cost of the Minimum Spanning Tree.
int kruskalMST(int V, vector<vector<int>>& edges) {

    // Sort all edges from smallest weight to largest.
    sort(edges.begin(), edges.end(),
        [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

    // Initially every vertex is its own DSU parent.
    vector<int> parent(V);

    // Initially every DSU tree has rank 0.
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    int mstCost = 0;
    int edgesUsed = 0;

    // Process edges from cheapest to most expensive.
    for (auto& edge : edges) {

        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];

        // Find the components containing u and v.
        int rootU = findParent(u, parent);
        int rootV = findParent(v, parent);

        // Different roots mean this edge will not create a cycle.
        if (rootU != rootV) {

            // Accept the edge into the MST.
            mstCost += weight;

            // Merge the two components.
            unionByRank(rootU, rootV, parent, rank);

            edgesUsed++;

            // MST is complete after selecting V - 1 edges.
            if (edgesUsed == V - 1)
                break;
        }
    }

    return mstCost;
}


int main() {

    int V = 5;

    // Each edge is stored as:
    // {u, v, weight}
    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    cout << "MST Cost: " << kruskalMST(V, edges) << endl;

    return 0;
}