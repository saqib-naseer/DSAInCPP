class TrieNode {
public:
    // Each node can have 26 children: a-z
    TrieNode* children[26];

    // Number of inserted words that PASS THROUGH this node.
    //
    // Example:
    // Insert: "apple", "app", "apply"
    //
    // At node representing "app":
    // prefixCount = 3
    //
    // because all 3 words start with "app".
    int prefixCount;

    // Number of inserted words that END exactly at this node.
    //
    // Example:
    // Insert: "app", "app", "apple"
    //
    // At node representing "app":
    // wordCount = 2
    //
    // because "app" was inserted twice.
    int wordCount;


    TrieNode() {
        // Initially there are no children.
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }

        prefixCount = 0;
        wordCount = 0;
    }
};


class Trie {
public:

    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }


    // --------------------------------------------------------
    // INSERT
    // --------------------------------------------------------
    // Insert one occurrence of a word.
    //
    // While moving through every character:
    //      prefixCount++
    //
    // At the final character:
    //      wordCount++
    //
    void insert(string word) {

        TrieNode* curr = root;

        for (char c : word) {

            int index = c - 'a';

            // Create the path if it doesn't already exist.
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }

            // Move to the character node.
            curr = curr->children[index];

            // One more inserted word passes through this node.
            curr->prefixCount++;
        }

        // The complete word ends at this node.
        curr->wordCount++;
    }


    // --------------------------------------------------------
    // COUNT EXACT WORD
    // --------------------------------------------------------
    // Returns how many times the exact word was inserted.
    //
    // Example:
    // Insert:
    // "app"
    // "app"
    // "apple"
    //
    // countWordsEqualTo("app") -> 2
    //
    int countWordsEqualTo(string word) {

        TrieNode* curr = root;

        for (char c : word) {

            int index = c - 'a';

            // Path doesn't exist -> word was never inserted.
            if (curr->children[index] == nullptr) {
                return 0;
            }

            curr = curr->children[index];
        }

        // Number of words ending exactly here.
        return curr->wordCount;
    }


    // --------------------------------------------------------
    // COUNT WORDS WITH PREFIX
    // --------------------------------------------------------
    // Returns how many inserted words start with this prefix.
    //
    // Example:
    // Insert:
    // "app"
    // "apple"
    // "apply"
    //
    // countWordsStartingWith("app") -> 3
    //
    int countWordsStartingWith(string prefix) {

        TrieNode* curr = root;

        for (char c : prefix) {

            int index = c - 'a';

            // Prefix doesn't exist.
            if (curr->children[index] == nullptr) {
                return 0;
            }

            curr = curr->children[index];
        }

        // Number of words passing through this prefix node.
        return curr->prefixCount;
    }


    // --------------------------------------------------------
    // ERASE
    // --------------------------------------------------------
    // Removes ONE occurrence of the word.
    //
    // While moving through the word:
    //      prefixCount--
    //
    // At the final character:
    //      wordCount--
    //
    // We don't need to physically delete Trie nodes.
    //
    void erase(string word) {

        TrieNode* curr = root;

        for (char c : word) {

            int index = c - 'a';

            curr = curr->children[index];

            // One fewer word now passes through this node.
            curr->prefixCount--;
        }

        // One fewer occurrence of the exact word.
        curr->wordCount--;
    }
};