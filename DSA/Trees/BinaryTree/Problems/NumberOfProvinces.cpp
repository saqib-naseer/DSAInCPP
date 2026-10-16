/*
    Problem: 547. Number of Provinces

    A province is a group of cities that are directly or indirectly connected.

    We are given an adjacency matrix:

        isConnected[i][j] == 1

    means city i is directly connected to city j.

    Example:

        isConnected =
        [
            [1,1,0],
            [1,1,0],
            [0,0,1]
        ]

    Graph:

        0 ----- 1

        2

    There are 2 connected components, so there are 2 provinces.


    PATTERN:
    --------
    Graph + Connected Components using DFS/BFS


    MAIN IDEA:
    ----------
    Each province is simply one connected component.

    We scan every city.

    If a city has NOT been visited:
        1. We discovered a new province.
        2. Increment province count.
        3. Run DFS from that city.
        4. DFS marks every city belonging to that province as visited.

    Therefore:

        Number of times we START a new DFS
        =
        Number of connected components
        =
        Number of provinces


    GRAPH REPRESENTATION:
    ---------------------
    The input itself is an adjacency matrix.

    Here we convert it into an adjacency list for DFS practice.

    Since:

        isConnected[i][j] == isConnected[j][i]

    the matrix already contains both directions.

    Example:

        isConnected[0][1] = 1
        isConnected[1][0] = 1

    Therefore, while scanning the complete matrix, we only need:

        adj[i].push_back(j)

    We should NOT additionally do adj[j].push_back(i), because the reverse
    connection will already be encountered when processing the other row.


    IMPORTANT INDEXING:
    -------------------
    Constraint:

        1 <= n <= 200

    means there are between 1 and 200 cities.

    It does NOT mean indexing starts from 1.

    C++ vectors are 0-indexed:

        n cities -> indices 0 to n-1


    Time Complexity:
        Building adjacency list: O(n^2)
        DFS traversal:           O(V + E)

        Overall: O(n^2)

    Space Complexity:
        O(n^2) in the worst case for adjacency list
        + O(n) visited/recursion stack.
*/

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {

        int n = isConnected.size();

        // Adjacency list:
        // adj[i] contains all cities directly connected to city i.
        vector<vector<int>> adj(n);

        // Convert the given adjacency matrix into an adjacency list.
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (isConnected[i][j] == 1) {

                    // Matrix already contains both directions,
                    // so adding i -> j is enough here.
                    adj[i].push_back(j);
                }
            }
        }

        vector<bool> visited(n, false);

        int provinces = 0;

        // Check every city because the graph may be disconnected.
        for (int i = 0; i < n; i++) {

            // An unvisited city means we found a new connected component.
            if (!visited[i]) {

                provinces++;

                // Mark this entire province as visited.
                dfs(i, visited, adj);
            }
        }

        return provinces;
    }

    void dfs(int node,
             vector<bool>& visited,
             vector<vector<int>>& adj) {

        // Current city now belongs to the province being explored.
        visited[node] = true;

        // Explore every city directly connected to this city.
        for (int neighbour : adj[node]) {

            if (!visited[neighbour]) {
                dfs(neighbour, visited, adj);
            }
        }
    }
};