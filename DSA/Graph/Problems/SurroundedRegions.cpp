/*
    Problem: Surrounded Regions
    LeetCode 130

    Given a board containing 'X' and 'O', capture all regions of 'O'
    that are completely surrounded by 'X'.

    An 'O' is NOT surrounded if:
    - It is on the boundary of the board, OR
    - It is connected to another 'O' that can reach the boundary.


    Approach: Boundary BFS + In-Place Marking

    Main Idea:
    Instead of trying to directly find which 'O's are surrounded,
    find the 'O's that CANNOT be surrounded.

    Any 'O' present on the boundary is automatically safe because
    it is not completely enclosed by 'X'.

    Also, any 'O' connected to a boundary 'O' is safe.


    Steps:

    1. Check all four boundaries:
       - Top row
       - Bottom row
       - Left column
       - Right column

    2. Whenever a boundary 'O' is found:
       - Change it to 'T'
       - Push it into the BFS queue

       'T' means:
       "This O is safe and must not be captured."

    3. Run BFS from all boundary 'O's.

       If we find another connected 'O':
       - Change it to 'T'
       - Push it into the queue

       Changing 'O' -> 'T' also acts as our visited marking,
       so we do not need a separate visited matrix.

    4. After BFS:
       - Remaining 'O' cells were never connected to the boundary,
         so they are surrounded. Change them to 'X'.

       - 'T' cells are safe, so change them back to 'O'.


    Example:

        Input:

            X X X X
            X O O X
            X X O X
            X O X X
              ↑
           boundary O


        Mark boundary-connected O's as T:

            X X X X
            X O O X
            X X O X
            X T X X


        Remaining O's are surrounded:

            X X X X
            X X X X
            X X X X
            X T X X


        Restore T -> O:

            X X X X
            X X X X
            X X X X
            X O X X


    Time Complexity:
        O(M * N)

        Every cell is processed at most a constant number of times.

    Space Complexity:
        O(M * N)

        In the worst case, the BFS queue can contain many cells.

        No separate visited matrix is required because 'T'
        acts as our visited/safe marker.
*/

class Solution {
public:

    // Directions:
    // Up, Down, Left, Right
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};


    // Check whether a cell is inside the board.
    bool isValid(int r, int c, int m, int n) {
        return r >= 0 && r < m &&
               c >= 0 && c < n;
    }


    void solve(vector<vector<char>>& board) {

        int m = board.size();
        int n = board[0].size();

        // Queue stores all safe boundary-connected 'O' cells.
        queue<pair<int, int>> q;


        /*
            STEP 1:
            Find all boundary 'O's.

            These cells can never be surrounded.

            Mark them as 'T' immediately so that:
            - We know they are safe.
            - They also become visited.
        */


        // Top boundary.
        for (int col = 0; col < n; col++) {

            if (board[0][col] == 'O') {

                board[0][col] = 'T';

                q.push({0, col});
            }
        }


        // Left boundary.
        for (int row = 1; row < m; row++) {

            if (board[row][0] == 'O') {

                board[row][0] = 'T';

                q.push({row, 0});
            }
        }


        // Right boundary.
        int lastCol = n - 1;

        for (int row = 1; row < m; row++) {

            if (board[row][lastCol] == 'O') {

                board[row][lastCol] = 'T';

                q.push({row, lastCol});
            }
        }


        // Bottom boundary.
        int lastRow = m - 1;

        for (int col = 1; col < n; col++) {

            if (board[lastRow][col] == 'O') {

                board[lastRow][col] = 'T';

                q.push({lastRow, col});
            }
        }


        /*
            STEP 2:
            BFS from all safe boundary 'O's.

            Any 'O' connected to a safe 'O'
            is also safe.

            Therefore:

                O -> T

            'T' also acts as our visited marker.
        */
        while (!q.empty()) {

            int r = q.front().first;
            int c = q.front().second;

            q.pop();


            // Explore all four neighboring cells.
            for (int k = 0; k < 4; k++) {

                int newR = r + rows[k];
                int newC = c + cols[k];


                // Process only valid, unvisited 'O' cells.
                if (isValid(newR, newC, m, n) &&
                    board[newR][newC] == 'O') {

                    // This O is connected to the boundary,
                    // so it cannot be captured.
                    board[newR][newC] = 'T';

                    // Continue BFS from this safe cell.
                    q.push({newR, newC});
                }
            }
        }


        /*
            STEP 3:
            Process the entire board.

            O -> X
                Still 'O' means BFS never reached it,
                so it is surrounded.

            T -> O
                'T' means it was connected to the boundary,
                so restore it back to 'O'.
        */
        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                if (board[i][j] == 'O') {

                    // Surrounded region.
                    board[i][j] = 'X';
                }
                else if (board[i][j] == 'T') {

                    // Safe boundary-connected region.
                    board[i][j] = 'O';
                }
            }
        }
    }
};