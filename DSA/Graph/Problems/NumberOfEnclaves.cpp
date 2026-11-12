/*
    Problem: Number of Enclaves
    LeetCode 1020

    Given a binary grid:
        0 = water
        1 = land

    We need to count the number of land cells from which we
    cannot walk outside the boundary of the grid.

    Movement is allowed in 4 directions:
        Up, Down, Left, Right.


    Approach: Boundary Multi-Source BFS + In-Place Marking

    Main Observation:
    Any land cell (1) present on the boundary can escape from
    the grid, so it cannot be an enclave.

    Also, any land cell connected to a boundary land cell can
    eventually reach the boundary and escape.

    Therefore, instead of directly searching for enclaves:

        1. Find all boundary land cells.
        2. Put them into the BFS queue.
        3. Change them from 1 -> 0.
        4. BFS through all connected land cells and also change
           them from 1 -> 0.
        5. After BFS, every remaining 1 cannot reach the boundary.
        6. Count those remaining 1s.

    In-Place Marking:
    We do not need a separate visited matrix.

        1 -> unprocessed land
        0 -> water OR land already known to be able to escape

    As soon as we discover an escapable land cell, we change
    it to 0 before putting it into the queue.

    This prevents it from being processed again.


    Connection with Surrounded Regions:

        Surrounded Regions:
            Boundary O -> safe
            BFS connected O's
            Remaining O's -> surrounded

        Number of Enclaves:
            Boundary 1 -> can escape
            BFS connected 1's
            Remaining 1's -> enclaves


    Time Complexity:
        O(M * N)

        Every cell is processed at most a constant number of times.

    Space Complexity:
        O(M * N)

        The BFS queue can contain many cells in the worst case.
        No separate visited matrix is required.
*/

class Solution {
public:

    // Directions:
    // Up, Down, Left, Right
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};


    // Check whether a cell is inside the grid.
    bool isValid(int r, int c, int m, int n) {
        return r >= 0 && r < m &&
               c >= 0 && c < n;
    }


    int numEnclaves(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        int count = 0;

        // Queue stores land cells that can reach the boundary.
        queue<pair<int, int>> q;


        /*
            STEP 1:
            Find all boundary land cells.

            Boundary land can directly escape from the grid,
            so it cannot be part of an enclave.

            Change 1 -> 0 immediately.
            This also acts as our visited marking.
        */


        // Top row.
        for (int i = 0; i < n; i++) {

            if (grid[0][i] == 1) {

                grid[0][i] = 0;

                q.push({0, i});
            }
        }


        // Left column.
        for (int i = 1; i < m; i++) {

            if (grid[i][0] == 1) {

                grid[i][0] = 0;

                q.push({i, 0});
            }
        }


        // Bottom row.
        for (int i = 1; i < n; i++) {

            if (grid[m - 1][i] == 1) {

                grid[m - 1][i] = 0;

                q.push({m - 1, i});
            }
        }


        // Right column.
        for (int i = 1; i < m; i++) {

            if (grid[i][n - 1] == 1) {

                grid[i][n - 1] = 0;

                q.push({i, n - 1});
            }
        }


        /*
            STEP 2:
            BFS from all boundary land cells.

            Any land cell connected to boundary land can also
            eventually reach the boundary.

            Therefore, change every connected 1 -> 0.
        */
        while (!q.empty()) {

            int r = q.front().first;
            int c = q.front().second;

            q.pop();


            // Explore all four neighboring cells.
            for (int k = 0; k < 4; k++) {

                int newR = r + rows[k];
                int newC = c + cols[k];


                // Process only valid land cells.
                if (isValid(newR, newC, m, n) &&
                    grid[newR][newC] == 1) {

                    // This land is connected to the boundary,
                    // so it can escape and is not an enclave.
                    grid[newR][newC] = 0;

                    // Continue BFS from this land cell.
                    q.push({newR, newC});
                }
            }
        }


        /*
            STEP 3:
            Count the remaining land cells.

            Any 1 still present was never reached from
            the boundary.

            Therefore, it cannot escape and is an enclave.
        */
        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {

                    count++;
                }
            }
        }


        return count;
    }
};