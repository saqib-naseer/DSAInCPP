/*
    Problem: Euler Path and Euler Circuit in an Undirected Graph

    We have to determine:
        2 -> Euler Circuit exists
        1 -> Euler Path exists
        0 -> Neither exists

    --------------------------------------------------
    MAIN IDEA
    --------------------------------------------------

    For an Euler Path/Circuit, we need to check TWO things:

    1. CONNECTIVITY
       All vertices having at least one edge must belong
       to the same connected component.

       Vertices with degree 0 can be ignored because
       Euler Path/Circuit is concerned with using edges.

       To check connectivity:
       - Find the first vertex having degree > 0.
       - Run DFS from that vertex.
       - After DFS, if another vertex has degree > 0
         but was not visited, the graph is disconnected.
       - In that case, Euler Path/Circuit is impossible.

    2. ODD DEGREE COUNT

       Degree of a vertex in an adjacency list is:
           adj[i].size()

       Why degree matters:

       For middle vertices:
           ENTER + LEAVE
       Edges are used in pairs, so degree should be EVEN.

       For an Euler Path:
           Start can have one extra LEAVE  -> ODD
           End can have one extra ENTER    -> ODD

       Therefore:

           0 odd-degree vertices
               -> Euler Circuit
               -> return 2

           2 odd-degree vertices
               -> Euler Path
               -> return 1

           More than 2 odd-degree vertices
               -> Neither
               -> return 0

    --------------------------------------------------
    COMPLEXITY
    --------------------------------------------------

    Time: O(V + E)
        DFS visits every vertex/edge at most once.

    Space: O(V)
        visited array + recursion stack.
*/

class Solution {
public:

    // DFS to visit all connected vertices.
    void dfs(int node,
             vector<vector<int>>& adj,
             vector<bool>& visited) {

        visited[node] = true;

        // Visit all connected neighbours.
        for (int neighbour : adj[node]) {

            if (!visited[neighbour]) {
                dfs(neighbour, adj, visited);
            }
        }
    }

    int isEulerCircuit(int V, vector<vector<int>>& adj) {

        vector<bool> visited(V, false);

        // Find first vertex having at least one edge.
        int start = -1;

        for (int i = 0; i < V; i++) {

            if (adj[i].size() > 0) {
                start = i;
                break;
            }
        }

        // If an edge-containing vertex exists, check connectivity.
        if (start != -1) {

            // Visit its entire connected component.
            dfs(start, adj, visited);

            // Check if any vertex with edges was not reached.
            for (int i = 0; i < V; i++) {

                if (adj[i].size() > 0 && !visited[i]) {
                    return 0;
                }
            }
        }

        // Count vertices having odd degree.
        int oddCount = 0;

        for (int i = 0; i < V; i++) {

            int degree = adj[i].size();

            if (degree % 2 != 0) {
                oddCount++;
            }
        }

        // All degrees even -> Euler Circuit.
        if (oddCount == 0) {
            return 2;
        }

        // Exactly two odd degrees -> Euler Path.
        if (oddCount == 2) {
            return 1;
        }

        // Otherwise neither exists.
        return 0;
    }
};