/*
    TARJAN'S ALGORITHM - BRIDGES & ARTICULATION POINTS
    --------------------------------------------------

    Tarjan's low-link technique uses DFS to find:

    1. Bridges (Critical Edges)
    2. Articulation Points (Critical Vertices)

    --------------------------------------------------
    IMPORTANT ARRAYS
    --------------------------------------------------

    tin[node]
        = Discovery time of the node.
        = When did DFS first visit this node?

    low[node]
        = Earliest discovery time reachable from
          this node's DFS subtree.

    --------------------------------------------------
    LOW UPDATE RULES
    --------------------------------------------------

    CASE 1: Neighbor is parent

        Ignore it.

    CASE 2: Neighbor is already visited

        This is a back edge.

        low[node] = min(low[node], tin[neighbor]);

        MEMORY:
        Visited neighbor -> use TIN.

    CASE 3: Neighbor is unvisited

        Run DFS on the child.

        After DFS returns:

        low[node] = min(low[node], low[child]);

        MEMORY:
        DFS child returns -> use LOW.

    --------------------------------------------------
    BRIDGE CONDITION
    --------------------------------------------------

        low[child] > tin[node]

    If true:

        node ----- child

    is a BRIDGE.

    Meaning:
    Child's subtree has no alternative connection
    back to node or an earlier discovered node.

    --------------------------------------------------
    ARTICULATION POINT CONDITION
    --------------------------------------------------

    For a NON-ROOT node:

        low[child] >= tin[node]

    If true:

        node

    is an ARTICULATION POINT.

    Meaning:
    If node is removed, that child's subtree
    becomes separated from the remaining graph.

    --------------------------------------------------
    ROOT SPECIAL CASE
    --------------------------------------------------

    DFS root has:

        parent == -1

    The normal articulation-point condition is NOT
    used for the root.

    Root is an articulation point if:

        DFS children > 1

    IMPORTANT:
    DFS children means the number of unvisited
    neighbors for which root actually starts DFS.

    It is NOT adj[root].size().

    --------------------------------------------------
    EASY MEMORY
    --------------------------------------------------

    Visited neighbor:
        use tin[neighbor]

    DFS child returns:
        use low[child]

    Bridge:
        low[child] > tin[node]

    Articulation Point:
        low[child] >= tin[node]

    Root Articulation Point:
        children > 1

    --------------------------------------------------
    COMPLEXITY
    --------------------------------------------------

    Time:  O(V + E)

    Auxiliary Space: O(V)
    Including adjacency list: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

class Tarjan {
private:

    int timer;

    vector<vector<int>> adj;

    vector<bool> visited;

    // Discovery time of every node.
    vector<int> tin;

    // Earliest discovery time reachable from subtree.
    vector<int> low;

    // Marks articulation points.
    vector<bool> isArticulation;

    // Stores bridges.
    vector<pair<int, int>> bridges;


    void dfs(int node, int parent) {

        // Mark current node as visited.
        visited[node] = true;

        // Assign discovery time and initial low value.
        tin[node] = low[node] = timer++;

        // Number of actual DFS children.
        int children = 0;


        for (int neighbour : adj[node]) {

            // Ignore the edge we used to enter this node.
            if (neighbour == parent) {
                continue;
            }


            // CASE 1:
            // Neighbor is already visited.
            // This represents a back edge.
            if (visited[neighbour]) {

                // Back edge directly reaches this previously
                // discovered node, so use its tin value.
                low[node] = min(
                    low[node],
                    tin[neighbour]
                );
            }


            // CASE 2:
            // Neighbor is unvisited -> DFS child.
            else {

                dfs(neighbour, node);

                // Child has finished exploring its subtree.
                // Bring its earliest reachable time upward.
                low[node] = min(
                    low[node],
                    low[neighbour]
                );


                // -----------------------------
                // CHECK FOR BRIDGE
                // -----------------------------

                // Child cannot reach node or anything
                // discovered before node through another route.
                if (low[neighbour] > tin[node]) {

                    bridges.push_back({
                        node,
                        neighbour
                    });
                }


                // -----------------------------
                // CHECK FOR ARTICULATION POINT
                // -----------------------------

                // This condition is only for non-root nodes.
                //
                // Child's subtree cannot reach any node
                // discovered before the current node.
                if (parent != -1 &&
                    low[neighbour] >= tin[node]) {

                    isArticulation[node] = true;
                }


                // Count actual DFS children.
                children++;
            }
        }


        // -----------------------------
        // ROOT SPECIAL CASE
        // -----------------------------

        // Root is an articulation point only if it
        // started more than one separate DFS branch.
        if (parent == -1 && children > 1) {

            isArticulation[node] = true;
        }
    }


public:

    Tarjan(int n) {

        adj.resize(n);

        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);

        isArticulation.assign(n, false);

        timer = 0;
    }


    // Add undirected edge.
    void addEdge(int u, int v) {

        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    void run() {

        int n = adj.size();

        // Graph may be disconnected.
        // Run DFS from every unvisited node.
        for (int i = 0; i < n; i++) {

            if (!visited[i]) {
                dfs(i, -1);
            }
        }
    }


    vector<pair<int, int>> getBridges() {

        return bridges;
    }


    vector<int> getArticulationPoints() {

        vector<int> result;

        for (int i = 0; i < isArticulation.size(); i++) {

            if (isArticulation[i]) {
                result.push_back(i);
            }
        }

        return result;
    }
};


int main() {

    /*
        Example:

              0
             / \
            1---2
                |
                3
               / \
              4---5

        Bridges:
            2 - 3

        Articulation Points:
            2, 3
    */

    Tarjan graph(6);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    graph.addEdge(2, 3);

    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 3);

    graph.run();


    cout << "Bridges:\n";

    for (auto edge : graph.getBridges()) {

        cout << edge.first
             << " - "
             << edge.second
             << '\n';
    }


    cout << "\nArticulation Points:\n";

    for (int node : graph.getArticulationPoints()) {

        cout << node << " ";
    }

    cout << '\n';

    return 0;
}