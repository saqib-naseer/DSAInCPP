class TrieNode {
public:

    // Marks whether a complete word ends at this node.
    bool isEnd;

    // children[0] -> 'a', children[1] -> 'b', ... children[25] -> 'z'
    TrieNode* children[26];

    TrieNode() {

        // Initially, the node has no children.
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }

        isEnd = false;
    }
};


class Solution {
public:

    // Root is the starting point of the Trie.
    TrieNode* root = new TrieNode();


    string longestString(vector<string> &words) {

        string ans = "";

        // STEP 1:
        // Insert every word into the Trie.
        for (int i = 0; i < words.size(); i++) {
            insert(words[i]);
        }


        // STEP 2:
        // Check every word to see if ALL of its prefixes
        // are also complete words in the Trie.
        for (int i = 0; i < words.size(); i++) {

            if (isValid(words[i])) {

                // Prefer the longer valid word.
                if (words[i].size() > ans.size()) {
                    ans = words[i];
                }

                // If lengths are equal, choose the
                // lexicographically smaller word.
                else if (words[i].size() == ans.size()) {

                    if (words[i] < ans) {
                        ans = words[i];
                    }
                }
            }
        }

        return ans;
    }


    // Returns true only if EVERY prefix of 'word'
    // exists as a complete word in the Trie.
    bool isValid(string word) {

        TrieNode* curr = root;

        for (char c : word) {

            int index = c - 'a';

            // Required path does not exist.
            if (curr->children[index] == nullptr) {
                return false;
            }

            // Move to the node representing the current character.
            curr = curr->children[index];

            // KEY IDEA:
            // At every character, the prefix formed so far
            // must itself be a complete word.
            //
            // Example for "apple":
            // a -> ap -> app -> appl -> apple
            // Every node above must have isEnd == true.
            if (curr->isEnd == false) {
                return false;
            }
        }

        // If we reached here, every prefix was a complete word.
        return true;
    }


    // Standard Trie insertion.
    void insert(string word) {

        TrieNode* curr = root;

        for (char c : word) {

            int index = c - 'a';

            // Create the character node if its path
            // does not already exist.
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }

            // Move deeper in the Trie.
            curr = curr->children[index];
        }

        // Mark the end of the complete word.
        curr->isEnd = true;
    }
};