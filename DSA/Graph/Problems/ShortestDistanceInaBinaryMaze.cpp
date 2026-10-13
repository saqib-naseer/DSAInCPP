class Solution {
public:

    /*
        SHORTEST DISTANCE IN A BINARY MAZE - BFS
        -----------------------------------------

        Goal:
        Find the minimum number of STEPS needed to travel
        from src to dest.

        Grid meaning:
            1 = traversable/open cell
            0 = blocked cell

        Movement:
            Only 4 directions are allowed:
            Up, Down, Left, Right.

        Why BFS?
        Every movement has equal cost = 1.

        BFS explores cells level-by-level, so the first time
        we reach the destination, we have used the minimum
        possible number of steps.

        We use the input matrix itself as visited[]:

            1 = unvisited/open
            0 = blocked OR already visited

        When a new cell is discovered, mark it 0 BEFORE
        pushing it into the queue. This prevents the same
        cell from being added multiple times.

        Important:
        Here the answer is number of MOVES/STEPS.

        Therefore:
            src == dest -> 0 steps

        This is different from LeetCode 1091, where the
        number of CELLS in the path was requested.

        Time Complexity:
            O(rows * cols)

        Space Complexity:
            O(rows * cols) in the worst case for the queue.
    */

    // Up, Down, Left, Right
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = { 0, 0,-1, 1};


    // Check whether a cell lies inside the matrix
    bool isValid(int i, int j, int r, int c) {

        return i >= 0 && j >= 0 &&
               i < r && j < c;
    }


    int shortestPath(vector<vector<int>>& mat,
                     vector<int>& src,
                     vector<int>& dest) {

        int r = mat.size();
        int c = mat[0].size();


        // Cannot start from a blocked cell
        if (mat[src[0]][src[1]] == 0)
            return -1;


        // Already standing at the destination
        if (src[0] == dest[0] &&
            src[1] == dest[1])
            return 0;


        queue<pair<int,int>> q;

        // Start BFS from source
        q.push({src[0], src[1]});

        // Mark source visited
        mat[src[0]][src[1]] = 0;


        // Number of moves made so far
        int steps = 0;


        while (!q.empty()) {

            // Number of cells in current BFS level
            int count = q.size();


            while (count--) {

                int i = q.front().first;
                int j = q.front().second;

                q.pop();


                // Explore all 4 directions
                for (int k = 0; k < 4; k++) {

                    int new_i = i + rows[k];
                    int new_j = j + cols[k];


                    // Cell must be inside the matrix
                    // and must be open/unvisited
                    if (isValid(new_i, new_j, r, c) &&
                        mat[new_i][new_j] == 1) {


                        // MARK BEFORE SENDING
                        mat[new_i][new_j] = 0;


                        // Destination belongs to the next BFS level
                        if (new_i == dest[0] &&
                            new_j == dest[1]) {

                            return steps + 1;
                        }


                        q.push({new_i, new_j});
                    }
                }
            }


            // Finished one complete BFS level
            steps++;
        }


        // Destination cannot be reached
        return -1;
    }
};