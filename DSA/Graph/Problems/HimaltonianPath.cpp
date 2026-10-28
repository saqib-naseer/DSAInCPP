/*
    Problem: Hamiltonian Path

    A Hamiltonian Path is a path in a graph that visits
    every vertex exactly once.

    ---------------------------------------------------------
    APPROACH: DFS + BACKTRACKING
    ---------------------------------------------------------

    We try every vertex as a possible starting point.

    From the current node:
        1. Mark it as visited.
        2. Increase the count of vertices in the current path.
        3. If count == V, we have visited every vertex,
           so a Hamiltonian Path exists.
        4. Otherwise, try every unvisited neighbor.
        5. Recursively continue the path from that neighbor.
        6. If none of the neighbors lead to a complete path,
           unmark the current node and backtrack.

    ---------------------------------------------------------
    WHY DO WE UNMARK?
    ---------------------------------------------------------

    In normal DFS, once a node is visited, we usually keep
    it visited.

    Here, visited[] represents vertices in the CURRENT
    attempted path.

    If the current path fails, the node must be removed
    from that path so it can be used in another possible path.

        Choose  -> mark visited
        Explore -> DFS
        Fail    -> unmark visited

    This is the backtracking step.

    ---------------------------------------------------------
    WHY TRY EVERY STARTING VERTEX?
    ---------------------------------------------------------

    A Hamiltonian Path can start from any vertex.

    A path may not exist starting from vertex 0 but may exist
    starting from another vertex.

    Therefore, every vertex is tried as a possible start.

    ---------------------------------------------------------
    COUNT
    ---------------------------------------------------------

    count tells us how many vertices are currently included
    in our path.

    When:

        count == V

    every vertex has been visited exactly once.

    ---------------------------------------------------------
    HAMILTONIAN VS EULER
    ---------------------------------------------------------

    Hamiltonian Path:
        Visit every VERTEX exactly once.

    Euler Path:
        Use every EDGE exactly once.

    Memory:
        Euler -> Edge
        Hamiltonian -> Vertex

    ---------------------------------------------------------
    COMPLEXITY
    ---------------------------------------------------------

    Time Complexity:
        O(V!) in the worst case.

        We may need to explore many possible orders of
        vertices before finding a valid path.

    Auxiliary Space:
        O(V)

        visited[] + recursion stack.
*/

class Solution {
public:

    bool dfsHelper(int node,
                   int count,
                   vector<vector<int>>& adj,
                   vector<bool>& vis,
                   int V) {

        // Add current node to our current path.
        vis[node] = true;

        // One more vertex has been included.
        count++;

        // All vertices have been visited exactly once.
        if (count == V) {
            return true;
        }

        // Try every neighbor as the next vertex in the path.
        for (int i = 0; i < adj[node].size(); i++) {

            int neigh = adj[node][i];

            // We can only use a vertex that is not already
            // present in our current path.
            if (!vis[neigh] &&
                dfsHelper(neigh, count, adj, vis, V)) {

                // A complete Hamiltonian Path was found.
                return true;
            }
        }

        // None of the choices from this node worked.
        //
        // Remove this node from the current path so that
        // another possible path can use it.
        vis[node] = false;

        return false;
    }


    bool checkPath(vector<vector<int>>& adj) {

        int V = adj.size();

        vector<bool> vis(V, false);

        // Hamiltonian Path can start from any vertex,
        // so try every vertex as the starting point.
        for (int i = 0; i < V; i++) {

            if (dfsHelper(i, 0, adj, vis, V)) {
                return true;
            }
        }

        // No starting vertex produced a Hamiltonian Path.
        return false;
    }
};