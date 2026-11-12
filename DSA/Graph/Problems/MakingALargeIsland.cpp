/*
    Problem: Making A Large Island
    LeetCode 827

    Given a binary grid:
        1 = land
        0 = water

    We are allowed to change AT MOST one 0 into 1.

    Return the size of the largest island we can create.

    An island is connected in 4 directions:
        Up, Down, Left, Right.


    --------------------------------------------------
    MAIN IDEA
    --------------------------------------------------

    Suppose the grid is:

        1 1 0 1
        1 0 0 1

    There are two separate islands:

        A A 0 B
        A 0 0 B

    Island A size = 3
    Island B size = 2

    If we change the top-middle 0 into 1:

        A A 1 B
        A 0 0 B

    that new 1 connects BOTH islands.

    New size:

        1 + size(A) + size(B)
        = 1 + 3 + 2
        = 6


    --------------------------------------------------
    PHASE 1: LABEL EVERY ISLAND
    --------------------------------------------------

    We first use DFS to find every existing island.

    Instead of leaving island cells as 1, give each
    island a unique ID:

        Original:

        1 1 0 1
        1 0 0 1

        After labeling:

        2 2 0 3
        2 0 0 3

    Island 2 has size 3.
    Island 3 has size 2.

    We store:

        islandSize[2] = 3
        islandSize[3] = 2

    We start IDs from 2 because:
        0 = water
        1 = original unprocessed land


    --------------------------------------------------
    PHASE 2: TRY FLIPPING EVERY 0
    --------------------------------------------------

    For every 0:

        Look UP
        Look DOWN
        Look LEFT
        Look RIGHT

    Find which islands touch this 0.

    Then:

        possible size = 1
                        +
                        sizes of all UNIQUE
                        neighboring islands

    The 1 represents the 0 that we are changing to 1.


    --------------------------------------------------
    WHY DO WE NEED A SET?
    --------------------------------------------------

    Consider:

        2 2 2
        2 0 2
        2 2 2

    The middle 0 touches island 2 from multiple sides.

    We must NOT do:

        1 + size[2] + size[2] + size[2] + size[2]

    because these are all the SAME island.

    So we use a set to store unique neighboring
    island IDs.


    Time Complexity:
        O(N^2)

    Space Complexity:
        O(N^2) in the worst case because of DFS recursion
        and the island-size map.
*/

class Solution {
public:

    // Up, Down, Left, Right
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};


    // Check if cell is inside the grid.
    bool isValid(int r, int c, int n) {
        return r >= 0 && r < n &&
               c >= 0 && c < n;
    }


    /*
        DFS finds one complete island.

        It does two jobs:

        1. Changes every cell of this island:
               1 -> islandId

        2. Counts how many cells belong to this island.

        Example:

            1 1
            1 0

        with islandId = 2 becomes:

            2 2
            2 0

        and returns size = 3.
    */
    int dfs(int r,
            int c,
            vector<vector<int>>& grid,
            int islandId,
            int n) {

        // Mark this cell with its island ID.
        grid[r][c] = islandId;

        // Current cell itself contributes 1.
        int size = 1;


        // Explore its four neighbors.
        for (int k = 0; k < 4; k++) {

            int newR = r + rows[k];
            int newC = c + cols[k];


            // Only visit original, unprocessed land (1).
            if (isValid(newR, newC, n) &&
                grid[newR][newC] == 1) {

                // Add the size found through this neighbor.
                size += dfs(
                    newR,
                    newC,
                    grid,
                    islandId,
                    n
                );
            }
        }


        return size;
    }


    int largestIsland(vector<vector<int>>& grid) {

        int n = grid.size();


        /*
            islandSize[id] = number of cells
                             in that island.

            Example:

                islandSize[2] = 5
                islandSize[3] = 8
        */
        unordered_map<int, int> islandSize;


        // IDs 0 and 1 already have meanings,
        // so start island IDs from 2.
        int islandId = 2;

        int answer = 0;


        /*
            ==========================================
            PHASE 1:
            Find and label every existing island.
            ==========================================
        */

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                // Found unprocessed land.
                if (grid[i][j] == 1) {

                    // DFS labels the entire island
                    // and returns its size.
                    int size = dfs(
                        i,
                        j,
                        grid,
                        islandId,
                        n
                    );


                    // Remember the size of this island.
                    islandSize[islandId] = size;


                    // Important for the case where
                    // the grid already contains a large island
                    // and we don't need to flip anything.
                    answer = max(answer, size);


                    // Next island gets a different ID.
                    islandId++;
                }
            }
        }


        /*
            After Phase 1, something like:

                1 1 0 1
                1 0 0 1

            may have become:

                2 2 0 3
                2 0 0 3

            with:

                islandSize[2] = 3
                islandSize[3] = 2
        */


        /*
            ==========================================
            PHASE 2:
            Pretend to change each 0 into 1.
            ==========================================
        */

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                // We only want to try water cells.
                if (grid[i][j] != 0) {
                    continue;
                }


                /*
                    Store UNIQUE islands touching this 0.

                    We use a set because the same island
                    may touch this 0 from multiple directions.
                */
                unordered_set<int> neighboringIslands;


                // Check all four directions.
                for (int k = 0; k < 4; k++) {

                    int newR = i + rows[k];
                    int newC = j + cols[k];


                    if (isValid(newR, newC, n)) {

                        int id = grid[newR][newC];


                        /*
                            IDs >= 2 represent actual islands.

                            0 = water
                            1 = no longer present after labeling
                                all original islands
                        */
                        if (id >= 2) {
                            neighboringIslands.insert(id);
                        }
                    }
                }


                /*
                    Start from 1 because we are pretending:

                        this 0 -> 1

                    So the newly-created land cell itself
                    contributes one cell.
                */
                int possibleSize = 1;


                /*
                    Add each neighboring island exactly once.
                */
                for (int id : neighboringIslands) {

                    possibleSize += islandSize[id];
                }


                // Keep the best result.
                answer = max(answer, possibleSize);
            }
        }


        return answer;
    }
};