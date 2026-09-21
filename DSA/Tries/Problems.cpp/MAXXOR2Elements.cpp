class Trie {
public:
    // Binary Trie:
    // children[0] -> path for bit 0
    // children[1] -> path for bit 1
    Trie* children[2];

    Trie() {
        children[0] = nullptr;
        children[1] = nullptr;
    }
};

class Solution {
public:
    Trie* root = new Trie();


    // ---------------------------------------------------------
    // INSERT NUMBER INTO BINARY TRIE
    // ---------------------------------------------------------
    // Store every number as a path of bits.
    //
    // Example (using 4 bits):
    // 10 = 1010
    //
    // root -> 1 -> 0 -> 1 -> 0
    //
    // We go MSB -> LSB because higher bits have more value.
    // ---------------------------------------------------------
    void insert(int num) {

        Trie* curr = root;

        for (int i = 30; i >= 0; i--) {

            // Extract ith bit:
            // (num >> i) brings ith bit to the end
            // & 1 extracts only that bit
            int bit = (num >> i) & 1;

            // Create path if it doesn't exist
            if (curr->children[bit] == nullptr) {
                curr->children[bit] = new Trie();
            }

            // Move to that bit
            curr = curr->children[bit];
        }
    }


    // ---------------------------------------------------------
    // FIND BEST XOR FOR ONE NUMBER
    // ---------------------------------------------------------
    //
    // XOR rule:
    //
    // SAME bits      -> 0
    // DIFFERENT bits -> 1
    //
    // 0 ^ 1 = 1
    // 1 ^ 0 = 1
    //
    // Therefore:
    //
    // my bit = 0 -> WANT Trie bit 1
    // my bit = 1 -> WANT Trie bit 0
    //
    // Always try OPPOSITE first.
    //
    // If opposite exists:
    //      XOR bit becomes 1
    //
    // Otherwise:
    //      take same bit
    //      XOR bit stays 0
    // ---------------------------------------------------------
    int getMaxXOR(int num) {

        Trie* curr = root;

        // We build the XOR answer bit-by-bit.
        // Initially all bits are 0.
        int XORResult = 0;

        // Start from highest-value bit
        for (int i = 30; i >= 0; i--) {

            int currBit = (num >> i) & 1;


            // -------------------------
            // Current bit = 0
            // -------------------------
            // We WANT 1 because:
            // 0 ^ 1 = 1
            if (currBit == 0) {

                // Opposite bit exists
                if (curr->children[1] != nullptr) {

                    // XOR produced 1 at position i.
                    //
                    // (1 << i) creates a mask with bit i = 1.
                    // OR sets bit i of XORResult to 1.
                    XORResult = XORResult | (1 << i);

                    // Follow the preferred/opposite path
                    curr = curr->children[1];
                }
                else {

                    // No 1 available.
                    // Forced to take 0:
                    //
                    // 0 ^ 0 = 0
                    //
                    // XORResult already has 0 here,
                    // so nothing needs to be changed.
                    curr = curr->children[0];
                }
            }


            // -------------------------
            // Current bit = 1
            // -------------------------
            // We WANT 0 because:
            // 1 ^ 0 = 1
            else {

                // Opposite bit exists
                if (curr->children[0] != nullptr) {

                    // XOR produced 1 at position i,
                    // so set that bit in our answer.
                    XORResult = XORResult | (1 << i);

                    // Follow the preferred/opposite path
                    curr = curr->children[0];
                }
                else {

                    // No 0 available.
                    // Forced to take 1:
                    //
                    // 1 ^ 1 = 0
                    //
                    // Leave XORResult unchanged.
                    curr = curr->children[1];
                }
            }
        }

        return XORResult;
    }


    // ---------------------------------------------------------
    // MAXIMUM XOR OF TWO NUMBERS
    // ---------------------------------------------------------
    int findMaximumXOR(vector<int>& nums) {

        // STEP 1:
        // Put all numbers into Binary Trie.
        for (int num : nums) {
            insert(num);
        }

        int maximum = 0;

        // STEP 2:
        // For every number, find the number/path in Trie
        // that gives the largest possible XOR.
        for (int num : nums) {

            int currentXOR = getMaxXOR(num);

            maximum = max(maximum, currentXOR);
        }

        return maximum;
    }
};