/*
    Problem: 695. Max Area of Island
    Pattern: Grid Traversal + BFS + Connected Components

    Problem:
    We are given a binary grid where:
        1 = Land
        0 = Water

    An island is a group of land cells connected in 4 directions:
    up, down, left, and right.

    We need to return the maximum number of cells belonging
    to any single island.

    Approach:
    1. Traverse every cell of the grid.
    2. Whenever an unvisited land cell (1) is found:
       - This represents the start of a new island.
       - Start BFS from this cell.
       - Mark it visited by changing 1 -> 0.
       - Set area = 1 for the starting land cell.
    3. During BFS:
       - Pop one land cell from the queue.
       - Explore its 4 neighboring cells.
       - If a neighbor is inside the grid and contains 1:
           - Increase the current island's area.
           - Mark it visited (1 -> 0).
           - Push it into the queue.
    4. When BFS finishes, the entire current island has been explored.
    5. Compare its area with maxArea.
    6. Continue scanning for another unvisited island.

    Why mark 1 -> 0?
    It acts as our visited mechanism.
    Once a land cell is discovered, we mark it immediately so
    it cannot be added to the BFS queue again.

    Important:
    - area is reset for every new island.
    - maxArea is NOT reset because it stores the best answer so far.
    - Diagonal cells are not connected.
    - No BFS level-order traversal is needed because we are counting
      cells, not finding minimum distance.

    Time Complexity: O(m * n)
    Each grid cell is processed at most once.

    Space Complexity: O(m * n)
    In the worst case, the BFS queue can contain many grid cells.
*/

class Solution {
public:
    // Directions: Up, Down, Left, Right.
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};

    // Check whether a cell is inside the grid.
    bool isValid(int i, int j, int m, int n) {
        return i >= 0 && j >= 0 && i < m && j < n;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> q;

        // If there is no island, answer remains 0.
        int maxArea = 0;

        // Search for unvisited land cells.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Found the beginning of a new island.
                if (grid[i][j] == 1) {

                    // Mark starting cell as visited.
                    grid[i][j] = 0;

                    // Start BFS from this land cell.
                    q.push({i, j});

                    // Starting cell itself contributes area 1.
                    int area = 1;

                    // Explore the complete current island.
                    while (!q.empty()) {

                        int curr_i = q.front().first;
                        int curr_j = q.front().second;
                        q.pop();

                        // Check all 4 neighboring cells.
                        for (int k = 0; k < 4; k++) {

                            int new_i = curr_i + rows[k];
                            int new_j = curr_j + cols[k];

                            // Visit only valid, unvisited land.
                            if (isValid(new_i, new_j, m, n) &&
                                grid[new_i][new_j] == 1) {

                                // This cell belongs to the current island.
                                area++;

                                // Mark visited before enqueueing.
                                grid[new_i][new_j] = 0;

                                q.push({new_i, new_j});
                            }
                        }
                    }

                    // BFS finished -> current island is fully counted.
                    maxArea = max(maxArea, area);
                }
            }
        }

        return maxArea;
    }
};