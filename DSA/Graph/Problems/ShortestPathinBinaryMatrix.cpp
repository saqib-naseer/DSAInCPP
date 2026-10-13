class Solution {
public:

    /*
        SHORTEST PATH IN BINARY MATRIX - BFS
        -------------------------------------

        Goal:
        Travel from the top-left cell (0,0) to the
        bottom-right cell (n-1,n-1).

        Rules:
        - We can only travel through cells containing 0.
        - Cells containing 1 are blocked.
        - Movement is allowed in 8 directions:
              Up, Down, Left, Right
              + 4 diagonals.

        Why BFS?
        Every move has the same cost (1 step).

        BFS explores the grid level-by-level:

            Level 1 = cells at path length 1
            Level 2 = cells at path length 2
            Level 3 = cells at path length 3
            ...

        Therefore, the first time we reach the destination,
        we have found the shortest path.

        Important:
        The problem defines path length as the NUMBER OF CELLS
        visited, not the number of moves.

        Therefore:
            Starting cell already has path length 1.

        Visited:
        Instead of creating a separate visited[][] array,
        we change a visited 0 into 1.

        Mental Model:

            0 = available
            1 = blocked OR already visited

        Mark a cell visited BEFORE pushing it into the queue
        so the same cell is not added multiple times.

        Time Complexity:
            O(n^2)

        Space Complexity:
            O(n^2) worst case for the BFS queue.
    */

    // 8 possible movements
    int row[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int col[8] = { 0, 0,-1, 1, -1,  1,-1, 1};


    // Check whether cell is inside the grid
    bool isValid(int i, int j, int size) {

        return i >= 0 && j >= 0 &&
               i < size && j < size;
    }


    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

        int n = grid.size();


        // Starting cell is blocked
        if (grid[0][0] == 1)
            return -1;


        // Single open cell is already the destination
        if (n == 1)
            return 1;


        queue<pair<int,int>> q;


        // Start BFS from top-left
        q.push({0, 0});

        // Mark start as visited
        grid[0][0] = 1;


        // Starting cell itself counts in path length
        int steps = 1;


        while (!q.empty()) {

            // Number of cells in current BFS level
            int count = q.size();


            while (count--) {

                int i = q.front().first;
                int j = q.front().second;

                q.pop();


                // Try all 8 directions
                for (int k = 0; k < 8; k++) {

                    int new_i = i + row[k];
                    int new_j = j + col[k];


                    // Cell must be inside grid and unvisited/open
                    if (isValid(new_i, new_j, n) &&
                        grid[new_i][new_j] == 0) {


                        // MARK BEFORE SENDING
                        grid[new_i][new_j] = 1;


                        // Destination reached
                        if (new_i == n - 1 &&
                            new_j == n - 1) {

                            return steps + 1;
                        }


                        // Process in next BFS level
                        q.push({new_i, new_j});
                    }
                }
            }


            // Move to next BFS level
            steps++;
        }


        // Destination cannot be reached
        return -1;
    }
};