/*
    Problem: Count Strongly Connected Components - Kosaraju's Algorithm

    A Strongly Connected Component (SCC) is a group of vertices in a
    directed graph where every vertex can reach every other vertex.

    Approach: Kosaraju's Algorithm

    Step 1: Find DFS finishing order
    --------------------------------
    - Run DFS on the original graph.
    - After visiting all neighbors of a node, push the node into a stack.
    - This stores nodes according to their DFS finishing time.
    - We must start DFS from every unvisited vertex because the graph
      may not be reachable from a single starting vertex.

    Step 2: Reverse all edges
    -------------------------
    If original edge is:

        u -> v

    reversed edge becomes:

        v -> u

    This creates the transpose/reversed graph.

    Step 3: Process nodes using the stack
    --------------------------------------
    - Reset visited array.
    - Pop nodes one by one from the stack.
    - If the popped node is not visited, run DFS on the reversed graph.
    - Every new DFS traversal represents exactly ONE SCC.
    - Increment the SCC count.

    Memory Rule:

        DFS + Stack
            ->
        Reverse Edges
            ->
        DFS using Stack
            ->
        Each DFS = One SCC

    Time Complexity:
        O(V + E)

        First DFS      = O(V + E)
        Reverse graph  = O(V + E)
        Second DFS     = O(V + E)

    Space Complexity:
        O(V + E)

        Reversed adjacency list = O(V + E)
        Visited arrays          = O(V)
        Stack                   = O(V)
        DFS recursion stack     = O(V)
*/

class Solution {
public:

    // First DFS:
    // Store nodes in stack according to finishing time.
    void topoSort(int node,
                  vector<vector<int>>& adj,
                  stack<int>& st,
                  vector<bool>& vis) {

        vis[node] = true;

        // Visit all unvisited neighbors.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            if (!vis[neighbor]) {
                topoSort(neighbor, adj, st, vis);
            }
        }

        // Push only AFTER all neighbors are processed.
        st.push(node);
    }


    // Second DFS:
    // Explore one SCC in the reversed graph.
    void dfsHelper(int node,
                   vector<vector<int>>& adj,
                   vector<bool>& vis) {

        vis[node] = true;

        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            if (!vis[neighbor]) {
                dfsHelper(neighbor, adj, vis);
            }
        }
    }


    int countSCC(vector<vector<int>>& adj) {

        int V = adj.size();

        // --------------------------------
        // STEP 1: Find finishing order
        // --------------------------------

        vector<bool> vis(V, false);
        stack<int> st;

        // Graph may not be reachable from one node,
        // so try every unvisited vertex.
        for (int i = 0; i < V; i++) {

            if (!vis[i]) {
                topoSort(i, adj, st, vis);
            }
        }


        // --------------------------------
        // STEP 2: Reverse all graph edges
        // --------------------------------

        vector<vector<int>> revAdj(V);

        for (int i = 0; i < V; i++) {

            for (int j = 0; j < adj[i].size(); j++) {

                int neighbor = adj[i][j];

                // Original:
                // i -> neighbor
                //
                // Reversed:
                // neighbor -> i
                revAdj[neighbor].push_back(i);
            }
        }


        // --------------------------------
        // STEP 3: DFS on reversed graph
        // using finishing-time order
        // --------------------------------

        vector<bool> vis2(V, false);

        int count = 0;

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            // If this node is unvisited, we found a new SCC.
            if (!vis2[node]) {

                count++;

                // This DFS visits the complete SCC.
                dfsHelper(node, revAdj, vis2);
            }
        }

        return count;
    }
};