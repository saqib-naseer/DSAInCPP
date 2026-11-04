/*
    Problem: Number of Distinct Islands

    An island is a group of 'L' cells connected in 4 directions:
    up, down, left, right.

    We need to count DIFFERENT island shapes.

    Important:
    Two islands can be at completely different positions in the grid
    but still have the same shape.

    Example:

        L L                 L L
        L                   L

    These are the SAME shape even if they occur at different locations.

    --------------------------------------------------
    MAIN IDEA
    --------------------------------------------------

    Actual coordinates cannot represent shape because the same shape
    can appear at different positions.

    Therefore, for each island:

    1. Take its first cell as the BASE cell:
           baseRow, baseCol

    2. During BFS, convert every cell into a position RELATIVE
       to that base:

           (currentRow - baseRow,
            currentCol - baseCol)

    Example:

        Actual cells:
            (3,4), (3,5), (4,4)

        Base:
            (3,4)

        Relative coordinates:
            (0,0), (0,1), (1,0)

    Another identical island somewhere else:

        Actual:
            (7,8), (7,9), (8,8)

        Base:
            (7,8)

        Relative:
            (0,0), (0,1), (1,0)

    Both produce the SAME relative coordinates,
    therefore they have the SAME shape.

    We store every shape inside a set.

    A set automatically keeps only unique shapes.

    Final answer:
        number of distinct islands = shapes.size()

    Time Complexity: O(m * n)
    Space Complexity: O(m * n)
*/

class Solution {
public:

    // Only 4 directions for this problem.
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};

    bool isValid(int row, int col, int m, int n) {
        return row >= 0 && row < m &&
               col >= 0 && col < n;
    }

    int countDistinctIslands(vector<vector<char>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        /*
            Each vector<pair<int,int>> represents ONE island's shape.

            The set stores only unique shapes.
        */
        set<vector<pair<int,int>>> distinctShapes;

        // Scan the entire grid.
        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                // Found the beginning of a new island.
                if (grid[i][j] == 'L') {

                    // This first cell becomes our reference/base.
                    int baseRow = i;
                    int baseCol = j;

                    // Stores the relative coordinates of this island.
                    vector<pair<int,int>> shape;

                    queue<pair<int,int>> q;

                    q.push({i, j});

                    // Mark visited by converting land into water.
                    grid[i][j] = 'W';

                    while (!q.empty()) {

                        int row = q.front().first;
                        int col = q.front().second;

                        q.pop();

                        /*
                            Store RELATIVE coordinates, not actual coordinates.

                            The base cell itself becomes:

                                (baseRow - baseRow,
                                 baseCol - baseCol)

                                = (0,0)
                        */
                        shape.push_back({
                            row - baseRow,
                            col - baseCol
                        });

                        // Explore all 4 neighboring cells.
                        for (int k = 0; k < 4; k++) {

                            int newRow = row + rows[k];
                            int newCol = col + cols[k];

                            if (isValid(newRow, newCol, m, n) &&
                                grid[newRow][newCol] == 'L') {

                                // Mark visited before pushing into queue.
                                grid[newRow][newCol] = 'W';

                                q.push({newRow, newCol});
                            }
                        }
                    }

                    /*
                        BFS for this island is finished.

                        'shape' now contains its normalized/relative
                        coordinates.

                        If this shape already exists, set will ignore it.
                    */
                    distinctShapes.insert(shape);
                }
            }
        }

        // Number of unique shapes.
        return distinctShapes.size();
    }
};