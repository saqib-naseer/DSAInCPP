class Solution {
public:
    // Changes for 4 directions:
    // Up, Down, Right, Left
    int row[4] = {-1, 1, 0, 0};
    int col[4] = {0, 0, 1, -1};

    int r, c;

    // Check if a cell is inside the grid.
    bool isValid(int newRow, int newCol) {
        return newRow >= 0 && newRow < r &&
               newCol >= 0 && newCol < c;
    }

    int numIslands(vector<vector<char>>& grid) {

        r = grid.size();
        c = grid[0].size();

        int islandCount = 0;

        // Queue stores {row, column} for BFS.
        queue<pair<int, int>> q;

        // Scan every cell in the grid.
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {

                // If we find land, it means we found
                // the starting point of a NEW island.
                //
                // Previously visited land is changed to '0',
                // so it will not enter here again.
                if (grid[i][j] == '1') {

                    islandCount++;

                    // Mark starting land as visited by
                    // converting it from land -> water.
                    grid[i][j] = '0';

                    q.push({i, j});

                    // BFS explores the ENTIRE current island.
                    while (!q.empty()) {

                        // Current land cell.
                        int currentRow = q.front().first;
                        int currentCol = q.front().second;
                        q.pop();

                        // Check its 4 immediate neighbours.
                        for (int k = 0; k < 4; k++) {

                            int newRow = currentRow + row[k];
                            int newCol = currentCol + col[k];

                            // Neighbour must:
                            // 1. Be inside the grid
                            // 2. Be land ('1')
                            if (isValid(newRow, newCol) &&
                                grid[newRow][newCol] == '1') {

                                // Mark visited immediately so the
                                // same cell isn't added again.
                                grid[newRow][newCol] = '0';

                                // This neighbour will later become
                                // a current cell and explore its
                                // own 4 neighbours.
                                q.push({newRow, newCol});
                            }
                        }
                    }
                }
            }
        }

        return islandCount;
    }
};