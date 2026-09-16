class TrieNode {
public:
    // Each index represents one lowercase character:
    // 0 -> 'a', 1 -> 'b', ... 25 -> 'z'
    TrieNode* children[26];

    // True if a complete word ends at this node.
    bool isEnd;

    TrieNode() {
        // Initially this node has no children.
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }

        isEnd = false;
    }
};


class WordDictionary {
public:
    TrieNode* root;

    WordDictionary() {
        // Root does not represent any character.
        // It is the starting point of all words.
        root = new TrieNode();
    }
    

    void addWord(string word) {
        TrieNode* curr = root;

        for (char c : word) {

            // Convert character to children array index.
            int index = c - 'a';

            // Create the path if it does not already exist.
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }

            // Move to the node representing the current character.
            curr = curr->children[index];
        }

        // Mark the last node as the end of a complete word.
        curr->isEnd = true;
    }
    

    bool search(string word) {
        // Start searching from the root and first character.
        return searchHelper(word, 0, root);
    }


    bool searchHelper(string word, int index, TrieNode* curr) {

        // All characters have been matched.
        // Search succeeds only if a complete word ends here.
        if (index == word.size()) {
            return curr->isEnd;
        }


        // CASE 1: Normal character
        if (word[index] != '.') {

            int i = word[index] - 'a';

            // The required character exists, so continue
            // searching from that child.
            if (curr->children[i] != nullptr) {
                return searchHelper(
                    word,
                    index + 1,
                    curr->children[i]
                );
            }

            // Required character path does not exist.
            return false;
        }


        // CASE 2: Wildcard '.'
        // '.' can represent ANY one character, so try
        // every existing child of the current node.
        else {

            for (int i = 0; i < 26; i++) {

                if (curr->children[i] != nullptr) {

                    // Try matching the remaining word from this child.
                    // If ANY possible path succeeds, the search succeeds.
                    if (searchHelper(
                        word,
                        index + 1,
                        curr->children[i]
                    )) {
                        return true;
                    }
                }
            }
        }

        // We reach here for '.' only when ALL possible
        // child paths have been tried and all failed.
        return false;
    }
};