class Solution {
public:
    int rows;
    int cols;

    // 4-direction movement:
    // Up, Down, Right, Left
    int r[4] = {-1, 1, 0, 0};
    int c[4] = {0, 0, 1, -1};

    // Check whether the neighbour is inside the grid.
    bool isValid(int newRow, int newCol) {
        return newRow >= 0 && newRow < rows &&
               newCol >= 0 && newCol < cols;
    }

    int orangesRotting(vector<vector<int>>& grid) {

        rows = grid.size();
        cols = grid[0].size();

        // Multi-source BFS:
        // Queue stores {row, col} of rotten oranges.
        queue<pair<int, int>> q;

        // Put ALL initially rotten oranges into the queue.
        // They all start spreading at the same time.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }

        int timer = 0;

        // Each BFS level represents one minute.
        while (!q.empty()) {

            // Number of rotten oranges belonging
            // to the CURRENT minute/level.
            int qSize = q.size();

            // Tracks whether any fresh orange became
            // rotten during this minute.
            bool anyRotten = false;

            // Process only the current BFS level.
            while (qSize--) {

                int i = q.front().first;
                int j = q.front().second;
                q.pop();

                // Check all 4 neighbouring cells.
                for (int k = 0; k < 4; k++) {

                    int newRow = i + r[k];
                    int newCol = j + c[k];

                    // Neighbour must:
                    // 1. Be inside the grid
                    // 2. Contain a fresh orange
                    if (isValid(newRow, newCol) &&
                        grid[newRow][newCol] == 1) {

                        // Make it rotten immediately.
                        grid[newRow][newCol] = 2;

                        anyRotten = true;

                        // It will spread infection in
                        // the NEXT BFS level/minute.
                        q.push({newRow, newCol});
                    }
                }
            }

            // Increase time only if infection actually spread.
            if (anyRotten) {
                timer++;
            }
        }

        // If a fresh orange still exists,
        // it was impossible to reach.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }

        return timer;
    }
};