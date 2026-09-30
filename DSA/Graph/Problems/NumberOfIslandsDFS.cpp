class Solution {
public:
    // Changes for 4 directions:
    // Up, Down, Right, Left
    int row[4] = {-1, 1, 0, 0};
    int col[4] = {0, 0, 1, -1};

    int r, c;

    // Check whether a cell is inside the grid.
    bool isValid(int row, int col) {
        return row >= 0 && row < r &&
               col >= 0 && col < c;
    }

    int numIslands(vector<vector<char>>& grid) {

        r = grid.size();
        c = grid[0].size();

        int islandCount = 0;

        // Scan every cell in the grid.
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {

                // If we find land, this is the start
                // of a NEW island.
                //
                // Previously visited land has already
                // been changed from '1' to '0'.
                if (grid[i][j] == '1') {

                    islandCount++;

                    // DFS will visit/consume all land
                    // connected to this cell.
                    dfs(i, j, grid);
                }
            }
        }

        return islandCount;
    }

    void dfs(int r, int c, vector<vector<char>>& grid) {

        // Mark current land cell as visited.
        // We use the grid itself instead of visited[][].
        grid[r][c] = '0';

        // Check all 4 immediate neighbours.
        for (int k = 0; k < 4; k++) {

            int newRow = r + row[k];
            int newCol = c + col[k];

            // If neighbour is:
            // 1. Inside the grid
            // 2. Land ('1')
            //
            // Recursively explore it.
            if (isValid(newRow, newCol) &&
                grid[newRow][newCol] == '1') {

                dfs(newRow, newCol, grid);
            }
        }
    }
};