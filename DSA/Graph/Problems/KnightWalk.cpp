class Solution {
public:

    /*
        MINIMUM STEPS BY KNIGHT - BFS
        -----------------------------

        Goal:
        Find the minimum number of knight moves needed to travel
        from knightPos to targetPos on an n x n chessboard.

        Knight Movement:
        A knight moves in an L-shape:

            2 rows + 1 column
        OR
            1 row + 2 columns

        This gives 8 possible moves:

            (-2,-1)  (-2,+1)
            (+2,-1)  (+2,+1)
            (-1,-2)  (-1,+2)
            (+1,-2)  (+1,+2)

        Why BFS?
        Every knight move has the same cost = 1.

        BFS explores positions level-by-level:

            Level 0 -> 0 moves from start
            Level 1 -> 1 move from start
            Level 2 -> 2 moves from start
            ...

        Therefore, the first time we reach the target,
        we have found the minimum number of moves.

        Visited:
        chess[i][j] tells us whether BFS has already
        discovered position (i,j).

        Once a position is discovered, we NEVER need to
        enqueue it again because BFS reached it using the
        minimum possible number of moves.

        Important:
        Positions in this problem are 1-based:

            1 <= row <= n
            1 <= col <= n

        Therefore visited is created with size (n+1)x(n+1).

        Time Complexity:
            O(n^2)

        Space Complexity:
            O(n^2)
    */


    // All 8 possible knight movements
    int rows[8] = {-2, -2, 2, 2, 1, -1, 1, -1};
    int cols[8] = {-1,  1,-1, 1, 2,  2,-2, -2};


    // Check whether position lies inside the 1-based chessboard
    bool isValid(int i, int j, int size) {

        return i >= 1 && j >= 1 &&
               i <= size && j <= size;
    }


    int minStepToReachTarget(vector<int>& knightPos,
                             vector<int>& targetPos,
                             int n) {

        // Already standing at target
        if (knightPos == targetPos)
            return 0;


        // +1 because chessboard positions are 1-based
        vector<vector<bool>> chess(
            n + 1,
            vector<bool>(n + 1, false)
        );


        queue<pair<int,int>> q;

        // Start BFS from knight's initial position
        q.push({knightPos[0], knightPos[1]});

        // Mark starting position visited
        chess[knightPos[0]][knightPos[1]] = true;


        // Number of knight moves made so far
        int steps = 0;


        while (!q.empty()) {

            // Number of positions in current BFS level
            int count = q.size();


            while (count--) {

                int i = q.front().first;
                int j = q.front().second;

                q.pop();


                // Try all 8 possible knight moves
                for (int k = 0; k < 8; k++) {

                    int new_i = i + rows[k];
                    int new_j = j + cols[k];


                    // Position must be inside board
                    // and must not have been discovered before
                    if (isValid(new_i, new_j, n) &&
                        !chess[new_i][new_j]) {


                        // MARK BEFORE SENDING
                        chess[new_i][new_j] = true;


                        // Target reached in the next move
                        if (new_i == targetPos[0] &&
                            new_j == targetPos[1]) {

                            return steps + 1;
                        }


                        // Process this position in next BFS level
                        q.push({new_i, new_j});
                    }
                }
            }


            // Finished one complete BFS level
            steps++;
        }


        // Target cannot be reached
        return -1;
    }
};