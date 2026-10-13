class Solution {
public:

    /*
        NUMBER OF CONNECTED COMPONENTS - DFS
        -------------------------------------

        Goal:
        Count how many separate groups/components exist
        in an undirected graph.

        Main Idea:
        Loop through every node.

        If a node has NOT been visited:
            1. We have discovered a NEW component.
            2. Run DFS from that node.
            3. DFS visits every node belonging to that component.
            4. Increment component count once.

        Example:

            Component 1:
            0 -> 1 -> 2

            Component 2:
            3 -> 4

        Outer loop reaches 0:
            unvisited -> DFS visits 0,1,2
            count = 1

        Outer loop reaches 1,2:
            already visited -> skip

        Outer loop reaches 3:
            unvisited -> DFS visits 3,4
            count = 2

        Answer = 2


        Important Pattern:

            for every node:
                if NOT visited:
                    DFS/BFS
                    count++

        One DFS call completely explores ONE connected component.

        Time Complexity:
            O(V + E)

        Space Complexity:
            O(V + E) for adjacency list
            + O(V) recursion/visited in worst case.
    */

    int countComponents(int n, vector<vector<int>>& edges) {

        int count = 0;

        // Tracks nodes already belonging to a discovered component
        vector<bool> visited(n, false);

        // Build adjacency list
        vector<vector<int>> adj(n);

        for (vector<int>& edge : edges) {

            int u = edge[0];
            int v = edge[1];

            // Undirected graph: add both directions
            adj[u].push_back(v);
            adj[v].push_back(u);
        }


        // A disconnected graph may have multiple components,
        // so we must check every node.
        for (int i = 0; i < n; i++) {

            // Unvisited node means we found a new component
            if (!visited[i]) {

                // Visit the entire component
                dfsHelper(i, visited, adj);

                // One complete component discovered
                count++;
            }
        }

        return count;
    }


    void dfsHelper(int node,
                   vector<bool>& visited,
                   vector<vector<int>>& adj) {

        // Mark current node visited
        visited[node] = true;


        // Visit all connected neighbors
        for (int neighbour : adj[node]) {

            if (!visited[neighbour]) {

                dfsHelper(neighbour, visited, adj);
            }
        }
    }
};