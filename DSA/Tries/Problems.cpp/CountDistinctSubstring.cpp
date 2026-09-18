class TrieNode {
public:

    // Each index represents a lowercase character:
    // children[0] -> 'a', children[1] -> 'b', ... children[25] -> 'z'
    TrieNode* children[26];

    TrieNode() {

        // Initially, no character paths exist from this node.
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
};


class Solution {
public:

    // Root is the starting point for every substring.
    TrieNode* root = new TrieNode();


    int countSubs(string& s) {

        // Counts the number of distinct non-empty substrings.
        int count = 0;


        // 'i' represents the STARTING position of a substring.
        //
        // Example: s = "abc"
        //
        // i = 0 -> a, ab, abc
        // i = 1 -> b, bc
        // i = 2 -> c
        for (int i = 0; i < s.size(); i++) {

            // Every new starting position begins from Trie root.
            TrieNode* curr = root;


            // 'j' EXTENDS the substring starting from index i.
            for (int j = i; j < s.size(); j++) {

                // Convert current character to Trie child index.
                int index = s[j] - 'a';


                // If this path does not exist, we have discovered
                // a new character sequence = a new distinct substring.
                if (curr->children[index] == nullptr) {

                    curr->children[index] = new TrieNode();

                    // Every newly created Trie node represents
                    // exactly one new distinct substring.
                    count++;
                }


                // Move deeper in the Trie so the next character
                // extends the current substring.
                curr = curr->children[index];
            }
        }


        return count;
    }
};