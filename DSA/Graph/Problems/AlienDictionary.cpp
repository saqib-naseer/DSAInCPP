
class Solution {
public:
    string findOrder(vector<string> &words) {

        /*
            =====================================================
            STEP 1: Find which letters actually exist
            =====================================================

            Alien alphabet uses lowercase English letters,
            but the answer should contain the unique letters
            that appear in the given words.

            present[i] tells us whether a letter exists.

            'a' - 'a' = 0
            'b' - 'a' = 1
            ...
            'z' - 'a' = 25
        */

        vector<bool> present(26, false);

        for (string &word : words) {

            for (char ch : word) {

                present[ch - 'a'] = true;
            }
        }


        /*
            =====================================================
            STEP 2: Build directed graph between letters
            =====================================================

            If we discover:

                a must come before c

            we create:

                a -> c

            adj[u] contains all letters that must come AFTER u.
        */

        vector<vector<int>> adj(26);

        // indegree[x] =
        // how many letters must come before letter x.
        vector<int> indegree(26, 0);


        /*
            Compare every pair of neighboring words.

            Example:

                words[0] vs words[1]
                words[1] vs words[2]
                words[2] vs words[3]
        */

        for (int i = 0; i < words.size() - 1; i++) {

            string &first  = words[i];
            string &second = words[i + 1];


            /*
                We can compare characters only up to
                the length of the shorter word.

                Example:

                    "baa"   length = 3
                    "abcd"  length = 4

                We can safely compare only 3 positions.
            */

            int len = min(first.size(), second.size());

            bool foundDifference = false;


            /*
                Compare both words from LEFT to RIGHT.

                We are looking for the FIRST different character.

                Example:

                    abcd
                    abca

                    a == a
                    b == b
                    c == c
                    d != a

                Therefore:

                    d must come before a

                    d -> a
            */

            for (int j = 0; j < len; j++) {

                if (first[j] != second[j]) {

                    foundDifference = true;


                    // Convert characters into graph node numbers.
                    //
                    // Example:
                    // 'a' -> 0
                    // 'b' -> 1
                    // 'c' -> 2

                    int u = first[j] - 'a';
                    int v = second[j] - 'a';


                    /*
                        Since first word appears before second word:

                            first[j] must come before second[j]

                        Therefore:

                            u -> v
                    */

                    adj[u].push_back(v);

                    // v has one more letter that must come before it.
                    indegree[v]++;


                    /*
                        VERY IMPORTANT:

                        Only the FIRST different character matters.

                        Once dictionary order is decided,
                        later characters tell us nothing about
                        the ordering of these two words.
                    */

                    break;
                }
            }


            /*
                =================================================
                SPECIAL CASE: Invalid prefix
                =================================================

                Consider:

                    "abcd"
                    "abc"

                Comparing:

                    a == a
                    b == b
                    c == c

                No different character is found.

                But "abc" is a prefix of "abcd".

                In a valid dictionary:

                    "abc"
                    "abcd"

                must be the order.

                Therefore:

                    "abcd"
                    "abc"

                is INVALID.
            */

            if (!foundDifference &&
                first.size() > second.size()) {

                return "";
            }
        }


        /*
            =====================================================
            STEP 3: Kahn's Algorithm
            =====================================================

            At this point our word problem is finished.

            We now simply have a directed graph.

            Example:

                b -> d -> a -> c

            We need its topological ordering.
        */

        queue<int> q;


        /*
            Put every PRESENT letter having indegree 0
            into the queue.

            indegree == 0 means:

            "No other letter is required to come before me."

            So this letter is READY.
        */

        for (int i = 0; i < 26; i++) {

            if (present[i] && indegree[i] == 0) {

                q.push(i);
            }
        }


        // This will contain our alien alphabet.
        string ans = "";

        // Count how many unique letters Kahn successfully processes.
        int count = 0;


        /*
            Standard Kahn's Algorithm.
        */

        while (!q.empty()) {

            int node = q.front();
            q.pop();


            /*
                Convert graph node back into character.

                0 + 'a' -> 'a'
                1 + 'a' -> 'b'
                2 + 'a' -> 'c'
            */

            ans += char(node + 'a');

            count++;


            /*
                Current letter has now been placed in the answer.

                Therefore remove its dependency from
                all letters that come after it.
            */

            for (int neighbor : adj[node]) {

                indegree[neighbor]--;


                /*
                    If neighbor now has indegree 0:

                    All letters that were required to come
                    before it have been processed.

                    So it is READY.
                */

                if (indegree[neighbor] == 0) {

                    q.push(neighbor);
                }
            }
        }


        /*
            =====================================================
            STEP 4: Detect cycle
            =====================================================

            Count how many unique letters actually exist.
        */

        int uniqueLetters = 0;

        for (int i = 0; i < 26; i++) {

            if (present[i]) {
                uniqueLetters++;
            }
        }


        /*
            If Kahn processed fewer letters than exist:

                count < uniqueLetters

            then some letters were stuck.

            That means the graph contains a cycle.

            Example:

                a -> c -> e -> a

            No valid alphabet ordering exists.
        */

        if (count != uniqueLetters) {
            return "";
        }


        // Valid topological ordering = valid alien alphabet.
        return ans;
    }
};
