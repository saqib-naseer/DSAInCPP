/*
    KOSARAJU'S ALGORITHM
    ====================

    Purpose:
    Find Strongly Connected Components (SCCs) in a DIRECTED graph.

    SCC:
    A group of vertices where every vertex can reach every other vertex.

    --------------------------------------------------
    3 STEPS TO REMEMBER
    --------------------------------------------------

    STEP 1: DFS + FINISHING ORDER
    - Run DFS on the original graph.
    - Push a node into stack AFTER visiting all its neighbors.
    - Run DFS from every unvisited vertex.

    STEP 2: REVERSE ALL EDGES
    - If original edge is:
            u -> v

      reversed edge becomes:
            v -> u

    STEP 3: DFS ON REVERSED GRAPH
    - Pop nodes from the stack.
    - If node is not visited:
          run DFS on reversed graph
          count one SCC

    MEMORY RULE:

        DFS + STACK
             ↓
        REVERSE EDGES
             ↓
        DFS AGAIN
             ↓
        EACH DFS = ONE SCC


    Why Stack?
    ----------
    Stack gives us nodes according to DFS finishing time.
    The node that finishes last is processed first.


    Why Reverse?
    ------------
    Nodes inside the same SCC remain reachable from each other,
    but connections between different SCCs change direction.

    Combined with finishing order, this allows DFS to discover
    one SCC at a time.


    Example:

        Original:

        0 → 1 → 2
        ↑       |
        └───────┘

                ↓

        3 ⇄ 4

        SCCs:
        {0,1,2}
        {3,4}

        Answer = 2


    Time Complexity:
        O(V + E)

    Space Complexity:
        O(V + E)
*/


#include <bits/stdc++.h>
using namespace std;


// STEP 1:
// DFS on original graph and store finishing order.
void dfsFinish(int node,
               vector<vector<int>>& adj,
               vector<bool>& vis,
               stack<int>& st) {

    vis[node] = true;

    for (int neighbor : adj[node]) {

        if (!vis[neighbor]) {
            dfsFinish(neighbor, adj, vis, st);
        }
    }

    // IMPORTANT:
    // Push AFTER processing all neighbors.
    st.push(node);
}


// STEP 3:
// Normal DFS on the reversed graph.
void dfsReverse(int node,
                vector<vector<int>>& revAdj,
                vector<bool>& vis) {

    vis[node] = true;

    for (int neighbor : revAdj[node]) {

        if (!vis[neighbor]) {
            dfsReverse(neighbor, revAdj, vis);
        }
    }
}


int kosaraju(vector<vector<int>>& adj) {

    int V = adj.size();

    // =========================================
    // STEP 1: Find DFS finishing order
    // =========================================

    vector<bool> vis(V, false);
    stack<int> st;

    // Important:
    // Graph may not be reachable from one node.
    for (int i = 0; i < V; i++) {

        if (!vis[i]) {
            dfsFinish(i, adj, vis, st);
        }
    }


    // =========================================
    // STEP 2: Reverse every edge
    // =========================================

    vector<vector<int>> revAdj(V);

    for (int node = 0; node < V; node++) {

        for (int neighbor : adj[node]) {

            // Original:
            // node -> neighbor
            //
            // Reverse:
            // neighbor -> node

            revAdj[neighbor].push_back(node);
        }
    }


    // =========================================
    // STEP 3: DFS using stack order
    // =========================================

    vector<bool> vis2(V, false);

    int sccCount = 0;

    while (!st.empty()) {

        int node = st.top();
        st.pop();

        if (!vis2[node]) {

            // Every new DFS means we found
            // one complete SCC.
            sccCount++;

            dfsReverse(node, revAdj, vis2);
        }
    }

    return sccCount;
}


/*
    QUICK REVISION
    ==============

    Kosaraju = 3 Steps

    1. DFS original graph
       → push node AFTER neighbors
       → creates finishing-time stack

    2. Reverse all edges
       → u -> v becomes v -> u

    3. Pop stack
       → if unvisited, DFS reversed graph
       → every DFS = one SCC


    Most Important Lines:

        // Step 1
        dfsFinish(neighbor, adj, vis, st);
        st.push(node);


        // Step 2
        revAdj[neighbor].push_back(node);


        // Step 3
        if (!vis2[node]) {
            sccCount++;
            dfsReverse(node, revAdj, vis2);
        }


    Final Memory:

        DFS → STACK → REVERSE → DFS → COUNT SCCs
*/