
/*
    Problem: Check for Path in a 2D Grid with Obstacles (GFG)
    Pattern: Graph / Grid Traversal / BFS / Path Existence

    Problem Statement:
    Given an n x n grid containing:
        0 -> Wall (cannot traverse)
        1 -> Source (starting position)
        2 -> Destination (target position)
        3 -> Free cell (can traverse)

    Determine whether a path exists from source to destination.
    Movement is allowed in 4 directions: Up, Down, Left, Right.

    Approach: Breadth-First Search (BFS)

    Algorithm:
    1. Traverse the grid to find the source cell (value 1).
    2. Insert the source coordinates into a queue.
    3. Mark the source as visited by changing its value to 0.
    4. While the queue is not empty:
       - Remove the front cell from the queue.
       - Explore its 4 neighboring cells.
       - Skip neighbors outside the grid.
       - If a neighbor contains 2, return true.
       - If a neighbor contains 3:
           a. Mark it visited by changing its value to 0.
           b. Insert it into the queue.
    5. If BFS completes without reaching destination, return false.

    Important Concepts:
    - BFS explores all reachable cells.
    - A separate visited array is unnecessary because we modify mat.
    - Mark cells visited BEFORE pushing into the queue.
    - Check destination BEFORE modifying the cell.
    - No level-order traversal or steps counter is required.
    - DFS can also solve this problem because we only need
      to determine whether a path exists.

    Time Complexity: O(n^2)
    - Finding the source takes O(n^2).
    - BFS processes each reachable cell at most once.

    Auxiliary Space Complexity: O(n^2)
    - The BFS queue can contain up to O(n^2) cells.
    - No separate visited matrix is used.

    Note: This approach modifies the original input matrix.
*/

class Solution {
public:
    // Up, Down, Left, Right
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};

    // Check grid boundaries.
    bool isValid(int i, int j, int n) {
        return i >= 0 && j >= 0 && i < n && j < n;
    }

    bool isPathPossible(vector<vector<int>>& mat) {

        int n = mat.size();
        int src_i = -1, src_j = -1;

        // Find the source (1).
        bool found = false;

        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    src_i = i;
                    src_j = j;
                    found = true;
                    break;
                }
            }
        }

        // Initialize BFS.
        queue<pair<int, int>> q;
        q.push({src_i, src_j});

        // Mark source as visited.
        mat[src_i][src_j] = 0;

        while (!q.empty()) {

            // Get current cell.
            int i = q.front().first;
            int j = q.front().second;
            q.pop();

            // Explore all 4 directions.
            for (int k = 0; k < 4; k++) {

                int new_i = i + rows[k];
                int new_j = j + cols[k];

                // Skip out-of-bound cells.
                if (!isValid(new_i, new_j, n))
                    continue;

                // Destination found.
                if (mat[new_i][new_j] == 2)
                    return true;

                // Visit only free, unvisited cells.
                if (mat[new_i][new_j] == 3) {

                    // Mark visited to prevent revisits.
                    mat[new_i][new_j] = 0;

                    // Add neighbor to BFS queue.
                    q.push({new_i, new_j});
                }
            }
        }

        // No path exists.
        return false;
    }
};
