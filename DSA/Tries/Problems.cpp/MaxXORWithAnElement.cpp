class TrieNode {
public:
    TrieNode* children[2];

    TrieNode() {
        children[0] = NULL;
        children[1] = NULL;
    }
};

class Solution {
public:

    TrieNode* root = new TrieNode();


    // -------------------------------------------------------
    // INSERT A NUMBER INTO BINARY TRIE
    // -------------------------------------------------------
    //
    // Example:
    // num = 5
    // binary = 101
    //
    // We insert every bit one by one into the Trie.
    //
    void insert(int num) {

        TrieNode* curr = root;

        // Numbers can be up to 10^9,
        // so bits from 30 -> 0 are enough.
        for (int i = 30; i >= 0; i--) {

            // Get ith bit of num
            int bit = (num >> i) & 1;

            // If this path does not exist, create it
            if (curr->children[bit] == NULL) {
                curr->children[bit] = new TrieNode();
            }

            // Move down the Trie
            curr = curr->children[bit];
        }
    }


    // -------------------------------------------------------
    // FIND MAXIMUM XOR OF x WITH A NUMBER INSIDE THE TRIE
    // -------------------------------------------------------
    //
    // Main XOR idea:
    //
    // x bit = 0 -> we WANT 1
    // x bit = 1 -> we WANT 0
    //
    // because:
    //
    // 0 XOR 1 = 1
    // 1 XOR 0 = 1
    //
    // We want 1 in the XOR result whenever possible.
    //
    int getMaxXOR(int x) {

        TrieNode* curr = root;

        int xorResult = 0;

        for (int i = 30; i >= 0; i--) {

            // Get ith bit of x
            int bit = (x >> i) & 1;

            // We want the OPPOSITE bit
            int oppositeBit = 1 - bit;

            // If opposite bit exists, take it
            // because this gives XOR bit = 1
            if (curr->children[oppositeBit] != NULL) {

                // Set ith bit of our XOR answer to 1
                xorResult = xorResult | (1 << i);

                curr = curr->children[oppositeBit];
            }
            else {

                // Opposite bit doesn't exist,
                // so we have no choice.
                // Take the same bit.
                //
                // XOR bit will be 0, so we don't
                // need to change xorResult.
                curr = curr->children[bit];
            }
        }

        return xorResult;
    }


    // -------------------------------------------------------
    // MAIN SOLUTION
    // -------------------------------------------------------

    vector<int> maximizeXor(
        vector<int>& nums,
        vector<vector<int>>& queries
    ) {

        // ---------------------------------------------------
        // STEP 1: Sort nums
        // ---------------------------------------------------
        //
        // Example:
        //
        // nums = [5,2,4,6,6,3]
        //
        // becomes:
        //
        // nums = [2,3,4,5,6,6]
        //
        // This allows us to insert numbers into Trie
        // from smallest -> largest.
        //
        sort(nums.begin(), nums.end());


        // ---------------------------------------------------
        // STEP 2: Create offline queries
        // ---------------------------------------------------
        //
        // Original query:
        //
        // [x, m]
        //
        // But we also need to remember its ORIGINAL INDEX.
        //
        // So we store:
        //
        // [m, x, originalIndex]
        //
        // Why put m first?
        //
        // Because when we sort this vector, C++ will
        // automatically sort primarily according to m.
        //

        vector<vector<int>> offlineQueries;

        for (int i = 0; i < queries.size(); i++) {

            int x = queries[i][0];
            int m = queries[i][1];

            offlineQueries.push_back({m, x, i});
        }


        // ---------------------------------------------------
        // STEP 3: Sort queries according to m
        // ---------------------------------------------------
        //
        // Example:
        //
        // Original:
        //
        // [12,4]
        // [8,1]
        // [6,3]
        //
        // We stored:
        //
        // [4,12,0]
        // [1,8,1]
        // [3,6,2]
        //
        // After sorting:
        //
        // [1,8,1]
        // [3,6,2]
        // [4,12,0]
        //
        // Therefore we process:
        //
        // m = 1
        // m = 3
        // m = 4
        //
        // Trie can now keep GROWING.
        //
        sort(offlineQueries.begin(), offlineQueries.end());


        // Answer array
        vector<int> ans(queries.size());


        // ---------------------------------------------------
        // j tells us where we currently are inside nums.
        // ---------------------------------------------------
        //
        // nums:
        //
        // [2,3,4,5,6,6]
        //  ↑
        //  j
        //
        int j = 0;


        // ---------------------------------------------------
        // STEP 4: Process queries from smallest m -> largest m
        // ---------------------------------------------------

        for (auto query : offlineQueries) {

            int m = query[0];
            int x = query[1];
            int originalIndex = query[2];


            // -----------------------------------------------
            // Insert EVERY number that is <= m
            // -----------------------------------------------
            //
            // Example:
            //
            // nums = [2,3,4,5,6,6]
            // m = 3
            //
            // Insert:
            //
            // 2
            // 3
            //
            // Stop when nums[j] > m.
            //
            while (j < nums.size() && nums[j] <= m) {

                insert(nums[j]);

                // IMPORTANT:
                //
                // j NEVER goes back.
                //
                // The next query has an equal or larger m,
                // so these numbers will still be valid.
                j++;
            }


            // -----------------------------------------------
            // If Trie is empty
            // -----------------------------------------------
            //
            // Example:
            //
            // nums = [2,3,4]
            // query = [8,1]
            //
            // There is no number <= 1.
            //
            if (j == 0) {

                ans[originalIndex] = -1;
            }

            // -----------------------------------------------
            // Otherwise find best XOR
            // -----------------------------------------------
            else {

                ans[originalIndex] = getMaxXOR(x);
            }
        }


        return ans;
    }
};