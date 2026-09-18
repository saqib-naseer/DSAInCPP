class TrieNode {
public:
    TrieNode* children[26];

    // Instead of only isEnd, store the complete word.
    // Empty string means no word ends at this node.
    string word;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }

        word = "";
    }
};


class Solution {
public:

    TrieNode* root = new TrieNode();


    // ---------------------------------------------------------
    // Insert all dictionary words into Trie
    // ---------------------------------------------------------
    void insert(string& word) {

        TrieNode* curr = root;

        for (char c : word) {

            int index = c - 'a';

            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }

            curr = curr->children[index];
        }

        // Store the complete word at the ending node.
        // Example:
        //
        // ROOT -> o -> a -> t -> h
        //                       word = "oath"
        curr->word = word;
    }


    // ---------------------------------------------------------
    // DFS + Backtracking
    // ---------------------------------------------------------
    void dfs(
        vector<vector<char>>& board,
        int row,
        int col,
        TrieNode* curr,
        vector<string>& ans
    ) {

        // 1. Check board boundaries.
        if (row < 0 || row >= board.size() ||
            col < 0 || col >= board[0].size()) {
            return;
        }


        // '#' means this cell is already being used
        // in our current word/path.
        if (board[row][col] == '#') {
            return;
        }


        char c = board[row][col];
        int index = c - 'a';


        // 2. PREFIX PRUNING
        //
        // Current board character does not continue
        // any word stored in our Trie.
        //
        // Example:
        //
        // Trie currently represents "ca"
        // and possible children are 't' and 'r'.
        //
        // If board gives 'x', "cax..." cannot match
        // any dictionary word, so stop this DFS branch.
        if (curr->children[index] == nullptr) {
            return;
        }


        // Move Trie pointer along with board character.
        curr = curr->children[index];


        // 3. Did we reach a complete dictionary word?
        if (curr->word != "") {

            ans.push_back(curr->word);

            // Prevent adding the same word multiple times
            // if another board path finds it again.
            curr->word = "";
        }


        // 4. Mark current board cell as visited.
        //
        // We cannot use the same board cell twice
        // while constructing ONE word.
        board[row][col] = '#';


        // 5. Explore all 4 neighboring cells.
        //
        //             up
        //              ↑
        //     left ← current → right
        //              ↓
        //             down

        dfs(board, row - 1, col, curr, ans); // UP

        dfs(board, row + 1, col, curr, ans); // DOWN

        dfs(board, row, col - 1, curr, ans); // LEFT

        dfs(board, row, col + 1, curr, ans); // RIGHT


        // 6. BACKTRACK
        //
        // Restore the original character so this cell
        // can be used by another DFS path.
        board[row][col] = c;
    }


    vector<string> findWords(
        vector<vector<char>>& board,
        vector<string>& words
    ) {

        vector<string> ans;


        // STEP 1:
        // Put every dictionary word into the Trie.
        for (string& word : words) {
            insert(word);
        }


        // STEP 2:
        // Every board cell can potentially be the
        // starting character of a dictionary word.
        for (int row = 0; row < board.size(); row++) {

            for (int col = 0; col < board[0].size(); col++) {

                // IMPORTANT:
                // Every new starting cell begins
                // searching from the Trie ROOT.
                dfs(board, row, col, root, ans);
            }
        }


        return ans;
    }
};