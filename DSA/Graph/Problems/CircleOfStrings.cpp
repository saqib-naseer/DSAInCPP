/*
    Problem: Circle of Strings

    We are given an array of strings and need to determine whether ALL strings
    can be arranged in a circle.

    Two strings can be connected when:
        last character of first string == first character of next string.

    Example:
        ["for", "geek", "rig", "kaf"]

    IMPORTANT GRAPH CONVERSION:
    ---------------------------
    Treat each LETTER as a vertex/node.
    Treat each STRING as ONE directed edge:

        first character ----> last character

    Examples:
        "for"  => f -> r
        "rig"  => r -> g
        "geek" => g -> k
        "kaf"  => k -> f

    Therefore the graph becomes:

        f -> r -> g -> k
        ^              |
        |______________|

    Notice:
        We DO NOT create edges between characters inside a word.

        "abcd" means:
            a -> d

        NOT:
            a -> b -> c -> d

    Why?
    Because for chaining strings, only the FIRST and LAST characters matter.

    This problem is therefore a Directed Euler Circuit problem.

    To form one circle using every string exactly once, we need:

    CONDITION 1: INDEGREE == OUTDEGREE
    ------------------------------------
    Every used letter must have:

        indegree == outdegree

    Why?
    Every time we ENTER a letter through one string,
    we must be able to LEAVE it through another string.

    For an edge:
        a -> b

    we do:
        outdegree[a]++
        indegree[b]++

    Multiple strings may create the same edge.
    Example:
        "ab", "ab"

    gives TWO separate edges:
        a -> b
        a -> b

    so:
        outdegree[a] += 2
        indegree[b]  += 2


    CONDITION 2: CONNECTIVITY
    -------------------------
    Balanced degrees alone are not enough.

    Example:
        a <-> b

        c <-> d

    Every vertex has equal indegree/outdegree, but the graph has two
    separate components. We cannot create ONE circle using all strings.

    Therefore:
        1. Start DFS from a letter used by the strings.
        2. Follow directed edges.
        3. Every letter participating in the graph must be visited.

    Since there are only 26 lowercase English letters, the graph has
    at most 26 vertices.

    Pattern:
        Graph + Directed Euler Circuit

    Time Complexity:
        O(total number of strings + graph traversal)
        Effectively O(N), because there are only 26 vertices.

    Space Complexity:
        O(N) for storing graph edges.
*/

class Solution {
public:
    bool isCircle(vector<string>& arr) {

        // adj[u] stores all letters reachable from letter u.
        // Example: "abc" creates edge a -> c.
        vector<vector<int>> adj(26);

        // Number of edges entering each letter.
        vector<int> indeg(26, 0);

        // Number of edges leaving each letter.
        vector<int> outdeg(26, 0);

        // Convert every string into ONE directed edge:
        // first character -> last character.
        for (const auto& word : arr) {

            int u = word[0] - 'a';
            int v = word[word.size() - 1] - 'a';

            // The whole word is represented by edge u -> v.
            adj[u].push_back(v);

            // Edge leaves u and enters v.
            outdeg[u]++;
            indeg[v]++;
        }

        // For a directed Euler Circuit, every used vertex
        // must have equal incoming and outgoing edges.
        for (int i = 0; i < 26; i++) {
            if (indeg[i] != outdeg[i])
                return false;
        }

        // Check whether all letters involved in strings
        // belong to the same connected part of the graph.
        vector<bool> visited(26, false);

        // Start DFS from the first character of any string.
        int start = arr[0][0] - 'a';

        dfsHelper(start, visited, adj);

        // Ignore letters that don't participate in any string.
        // Every used letter must have been reached by DFS.
        for (int i = 0; i < 26; i++) {
            if (indeg[i] > 0 && !visited[i])
                return false;
        }

        // Balanced degrees + connectivity => circle exists.
        return true;
    }

    void dfsHelper(int node,
                   vector<bool>& visited,
                   vector<vector<int>>& adj) {

        visited[node] = true;

        // Visit every letter reachable through outgoing edges.
        for (int neighbour : adj[node]) {

            if (!visited[neighbour]) {
                dfsHelper(neighbour, visited, adj);
            }
        }
    }
};