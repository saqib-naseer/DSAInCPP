class Solution {
public:
    // Direction arrays for moving:
    // Up, Down, Right, Left
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, 1, -1};

    int row, col;

    // Check whether a cell lies inside the grid.
    bool isValid(int r, int c) {
        return r >= 0 && r < row &&
               c >= 0 && c < col;
    }

    void fill(vector<vector<char>>& grid) {

        row = grid.size();
        col = grid[0].size();

        // Queue stores boundary-connected 'O' cells.
        // These cells must NOT be converted to 'X'.
        queue<pair<int, int>> q;

        /*
            Main Idea:
            Any 'O' touching the boundary cannot be surrounded.

            Also, any 'O' connected to a boundary 'O'
            cannot be surrounded.

            We temporarily mark all such safe cells as 'T'.

            After BFS:
                'O' -> surrounded, change to 'X'
                'T' -> safe, change back to 'O'
        */


        // -------------------------------
        // STEP 1: Check TOP boundary
        // -------------------------------
        for (int i = 0; i < col; i++) {

            if (grid[0][i] == 'O') {

                // Mark as safe/visited.
                grid[0][i] = 'T';

                q.push({0, i});
            }
        }


        // -------------------------------
        // STEP 2: Check LEFT boundary
        // -------------------------------
        // Start from 1 because top-left corner
        // was already checked above.
        for (int i = 1; i < row; i++) {

            if (grid[i][0] == 'O') {

                grid[i][0] = 'T';

                q.push({i, 0});
            }
        }


        // -------------------------------
        // STEP 3: Check BOTTOM boundary
        // -------------------------------
        // Start from 1 because bottom-left corner
        // was already checked by the left boundary.
        for (int i = 1; i < col; i++) {

            if (grid[row - 1][i] == 'O') {

                grid[row - 1][i] = 'T';

                q.push({row - 1, i});
            }
        }


        // -------------------------------
        // STEP 4: Check RIGHT boundary
        // -------------------------------
        // Skip both corners because they have
        // already been checked.
        for (int i = 1; i < row - 1; i++) {

            if (grid[i][col - 1] == 'O') {

                grid[i][col - 1] = 'T';

                q.push({i, col - 1});
            }
        }


        // -----------------------------------------
        // STEP 5: BFS from all boundary 'O' cells
        // -----------------------------------------
        //
        // This is multi-source BFS because all safe
        // boundary 'O' cells are already in the queue.
        //
        // Any 'O' connected to them is also safe.
        while (!q.empty()) {

            int currentRow = q.front().first;
            int currentCol = q.front().second;

            q.pop();

            // Check all 4 neighbours.
            for (int k = 0; k < 4; k++) {

                int newRow = currentRow + rows[k];
                int newCol = currentCol + cols[k];

                // If neighbour is inside the grid and is 'O',
                // it is connected to a boundary region.
                if (isValid(newRow, newCol) &&
                    grid[newRow][newCol] == 'O') {

                    // Mark immediately so it cannot
                    // be added to the queue again.
                    grid[newRow][newCol] = 'T';

                    q.push({newRow, newCol});
                }
            }
        }


        // -----------------------------------------
        // STEP 6: Process the entire grid
        // -----------------------------------------
        //
        // Remaining 'O' = not connected to boundary
        //               = surrounded by 'X'
        //               = change to 'X'
        //
        // 'T' = boundary-connected safe 'O'
        //     = restore back to 'O'
        for (int i = 0; i < row; i++) {

            for (int j = 0; j < col; j++) {

                if (grid[i][j] == 'O') {

                    // Surrounded region.
                    grid[i][j] = 'X';
                }
                else if (grid[i][j] == 'T') {

                    // Restore safe region.
                    grid[i][j] = 'O';
                }
            }
        }
    }
};


/*
    PATTERN:
    Boundary Traversal + Multi-Source BFS

    KEY IDEA:
    Instead of finding which 'O' cells ARE surrounded,
    find which 'O' cells CANNOT be surrounded.

    Boundary 'O'
        |
        v
    Mark as 'T'
        |
        v
    Multi-source BFS
        |
        v
    Mark every connected 'O' as 'T'
        |
        v
    Remaining 'O' -> 'X'
    Safe 'T'      -> 'O'


    'T' acts as our visited state,
    so a separate visited[][] is not required.


    TIME COMPLEXITY:
    O(row * col)

    SPACE COMPLEXITY:
    O(row * col) worst case for BFS queue
*/