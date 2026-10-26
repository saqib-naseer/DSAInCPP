/*
    Problem: Articulation Point in Graph

    An articulation point (cut vertex) is a vertex whose removal,
    along with all edges connected to it, increases the number of
    connected components in the graph.

    ------------------------------------------------------------
    APPROACH: DFS + Discovery Time + Low Time
    ------------------------------------------------------------

    We use the same low-link idea used in the Bridge problem.

    For every node we maintain:

    1. disc[node]
       Discovery time of the node during DFS.
       It tells us when the node was first visited.

    2. low[node]
       Earliest discovery time that this node/subtree can reach
       using DFS tree edges and a back edge.

    ------------------------------------------------------------
    NORMAL NODE CONDITION
    ------------------------------------------------------------

    Suppose:

            node
             |
           child

    After completing DFS(child), check:

        low[child] >= disc[node]

    If true, the child's subtree cannot connect to a vertex
    discovered before 'node' without going through 'node'.

    Therefore, removing 'node' separates that child's subtree,
    so 'node' is an articulation point.

    This condition is used only when node is NOT the DFS root:

        parent != -1

    ------------------------------------------------------------
    ROOT SPECIAL CASE
    ------------------------------------------------------------

    The DFS root has no parent, so the normal condition cannot
    be used for it.

    The root is an articulation point only when it has more
    than one DFS child.

        parent == -1 && children > 1

    IMPORTANT:
    children means the number of unvisited neighbors for which
    this node actually started a recursive DFS call.

    It does NOT mean adj[node].size().

    ------------------------------------------------------------
    THREE CASES WHILE CHECKING A NEIGHBOR
    ------------------------------------------------------------

    1. neighbour == parent
       Ignore it because this is the edge we came from.

    2. neighbour is already visited
       We found a back edge.

       low[node] = min(low[node], disc[neighbour]);

    3. neighbour is unvisited
       Run DFS on it.

       After DFS returns:

       low[node] = min(low[node], low[neighbour]);

       Then check whether the current node is an
       articulation point.

    ------------------------------------------------------------
    DISCONNECTED GRAPH
    ------------------------------------------------------------

    The graph may contain multiple connected components.

    Therefore, instead of only calling DFS from node 0,
    we start DFS from every still-unvisited vertex.

    ------------------------------------------------------------
    COMPLEXITY
    ------------------------------------------------------------

    Time Complexity: O(V + E)
    Each vertex and edge is processed during DFS.

    Space Complexity: O(V + E)
    Adjacency list + DFS recursion + helper arrays.
*/

class Solution {
public:

    void dfsHelper(
        int node,
        int parent,
        vector<vector<int>>& adj,
        vector<bool>& artPoints,
        int& timer,
        vector<bool>& vis,
        vector<int>& low,
        vector<int>& disc
    ) {

        // Mark current node as visited.
        vis[node] = true;

        // Assign discovery time and initial low value.
        disc[node] = low[node] = timer++;

        // Counts DFS children of this node.
        int child = 0;

        // Explore all neighbors.
        for (int i = 0; i < adj[node].size(); i++) {

            int neigh = adj[node][i];

            // Ignore the edge through which we entered this node.
            if (neigh == parent) {
                continue;
            }

            // Already visited neighbor -> back edge.
            else if (vis[neigh]) {

                // Back edge directly reaches this previously
                // discovered node, so use its discovery time.
                low[node] = min(low[node], disc[neigh]);
            }

            // Unvisited neighbor -> DFS child.
            else {

                dfsHelper(
                    neigh,
                    node,
                    adj,
                    artPoints,
                    timer,
                    vis,
                    low,
                    disc
                );

                // Child has finished exploring its entire subtree.
                // Bring its earliest reachable time upward.
                low[node] = min(low[node], low[neigh]);

                // For a NON-ROOT node:
                // If child's subtree cannot reach a node discovered
                // before the current node, current node is an AP.
                if (parent != -1 &&
                    low[neigh] >= disc[node]) {

                    artPoints[node] = true;
                }

                // Count only actual DFS children.
                child++;
            }
        }

        // Special rule for DFS root.
        if (parent == -1 && child > 1) {
            artPoints[node] = true;
        }
    }

    vector<int> articulationPoints(
        int V,
        vector<vector<int>>& edges
    ) {

        // Build undirected adjacency list.
        vector<vector<int>> adj(V);

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> ans;

        vector<int> low(V);
        vector<int> disc(V);

        vector<bool> visited(V, false);
        vector<bool> artPoints(V, false);

        int timer = 0;

        // Graph can be disconnected, so start DFS
        // from every unvisited vertex.
        for (int i = 0; i < V; i++) {

            if (!visited[i]) {

                dfsHelper(
                    i,
                    -1,
                    adj,
                    artPoints,
                    timer,
                    visited,
                    low,
                    disc
                );
            }
        }

        // Collect all articulation points.
        for (int i = 0; i < V; i++) {

            if (artPoints[i]) {
                ans.push_back(i);
            }
        }

        // GFG expects {-1} when no articulation point exists.
        if (ans.empty()) {
            return {-1};
        }

        return ans;
    }
};