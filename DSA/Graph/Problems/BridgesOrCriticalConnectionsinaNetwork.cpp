/*
    LeetCode 1192: Critical Connections in a Network
    Topic: Graphs - DFS - Bridges (Tarjan's Algorithm)

    PROBLEM:
    Given an undirected connected graph containing n nodes
    and a list of edges, find all critical connections.

    A critical connection (bridge) is an edge whose removal
    disconnects part of the graph.

    Example:

        0 ----- 1
         \     /
          \   /
            2 ----- 3

    Edges: [[0,1], [1,2], [2,0], [2,3]]

    Answer: [[2,3]]

    The edges 0-1, 1-2, and 2-0 form a cycle.
    Removing any one of them does not disconnect the graph.

    However, removing 2-3 disconnects node 3.

    -------------------------------------------------------
    APPROACH: DFS + DISCOVERY TIME + LOW-LINK VALUES
    -------------------------------------------------------

    We maintain three important arrays:

    1. vis[node]
       Whether the node has already been visited.

    2. tin[node]
       Discovery time of the node during DFS.

       Example:
       DFS visits 0 -> 1 -> 2 -> 3

       tin[0] = 0
       tin[1] = 1
       tin[2] = 2
       tin[3] = 3

    3. low[node]
       Earliest discovery time reachable from this node
       or its DFS subtree using tree edges downward
       and at most one back edge upward.

       In simple words:
       How far back can this subtree reach without
       relying on its connection to the DFS parent?

    -------------------------------------------------------
    THREE CASES WHILE EXPLORING NEIGHBORS
    -------------------------------------------------------

    CASE 1: Neighbor is the DFS parent.

        Ignore it because this is the edge we used
        to enter the current node.

    CASE 2: Neighbor is already visited.

        We found a back edge to an ancestor.

        low[node] = min(low[node], tin[neighbor])

        This means an alternate route exists.

    CASE 3: Neighbor is not visited.

        Recursively explore the neighbor.

        After DFS returns:

        low[node] = min(low[node], low[neighbor])

        Now check whether the edge is a bridge.

    -------------------------------------------------------
    BRIDGE CONDITION
    -------------------------------------------------------

        if (low[child] > tin[parent])

    Explanation:

    If the child's subtree cannot reach the parent
    or any ancestor of the parent through another route,
    removing the parent-child edge disconnects that subtree.

    Therefore, the edge is a BRIDGE.

    Important:
    We use > and NOT >=.

    If low[child] == tin[parent], an alternate route
    back to the parent exists, so it is not a bridge.

    -------------------------------------------------------
    COMPLEXITY
    -------------------------------------------------------

    V = number of vertices
    E = number of edges

    Time Complexity: O(V + E)
    Each vertex and edge is processed a constant number
    of times during DFS.

    Space Complexity: O(V + E)
    Adjacency list: O(V + E)
    Visited, tin, low arrays: O(V)
    DFS recursion stack: O(V)

    Auxiliary space excluding adjacency list: O(V)
*/

class Solution {
public:

    void dfsHelper(
        int node,
        int parent,
        vector<bool>& vis,
        vector<vector<int>>& cons,
        vector<int>& low,
        vector<int>& tin,
        int& timer,
        vector<vector<int>>& adj
    ) {

        // Mark the current node as visited.
        vis[node] = true;

        // Assign discovery time and initial low value.
        tin[node] = low[node] = timer++;

        // Explore all neighbors of the current node.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbour = adj[node][i];

            // CASE 1: Ignore the edge to our DFS parent.
            if (neighbour == parent) {
                continue;
            }

            // CASE 2: Already visited neighbor (back edge).
            if (vis[neighbour]) {

                // We can reach an earlier discovered node.
                low[node] = min(low[node], tin[neighbour]);
            }

            // CASE 3: Unvisited neighbor (DFS tree edge).
            else {

                // Explore the child's entire subtree.
                dfsHelper(
                    neighbour,
                    node,
                    vis,
                    cons,
                    low,
                    tin,
                    timer,
                    adj
                );

                // Child reports how far back it can reach.
                low[node] = min(low[node], low[neighbour]);

                // Can the child's subtree reach this node
                // or any of its ancestors through another edge?
                if (low[neighbour] > tin[node]) {

                    // No alternate route exists: bridge found.
                    cons.push_back({node, neighbour});
                }
            }
        }
    }

    vector<vector<int>> criticalConnections(
        int n,
        vector<vector<int>>& connections
    ) {

        // STEP 1: Build an undirected adjacency list.
        vector<vector<int>> adj(n);

        for (int i = 0; i < connections.size(); i++) {

            int u = connections[i][0];
            int v = connections[i][1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // STEP 2: Initialize DFS tracking arrays.
        vector<bool> vis(n, false);
        vector<int> low(n, -1);
        vector<int> tin(n, -1);

        // Stores all discovered bridges.
        vector<vector<int>> cons;

        // Shared timer for unique discovery timestamps.
        int timer = 0;

        // STEP 3: Run DFS.
        // LeetCode 1192 guarantees a connected graph.
        dfsHelper(0, -1, vis, cons, low, tin, timer, adj);

        // STEP 4: Return all bridges.
        return cons;
    }
};
