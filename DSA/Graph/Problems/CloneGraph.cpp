/*
    Problem: Clone Graph

    We are given a node of a connected undirected graph.
    We need to create a completely NEW copy of the graph.

    Each original node must have:
        1. A new cloned node with the same value.
        2. The same connections, but connections must point
           to CLONED nodes, not original nodes.

    ---------------------------------------------------------
    MAIN IDEA: DFS + HASH MAP
    ---------------------------------------------------------

    The main difficulty is that graphs can contain cycles.

    Example:

        1 ---- 2
        |      |
        4 ---- 3

    DFS could go:

        1 -> 2 -> 3 -> 4 -> 1 -> ...

    So we need to remember which nodes we have already cloned.

    We use:

        unordered_map<Node*, Node*> mp;

    Think of it as:

        ORIGINAL NODE  ->  CLONED NODE

    Example:

        Original 1  ->  Clone 1
        Original 2  ->  Clone 2
        Original 3  ->  Clone 3
        Original 4  ->  Clone 4

    This map does TWO jobs:

        1. Tells us whether a node was already processed.
        2. Gives us the cloned node that belongs to it.

    ---------------------------------------------------------
    DFS IDEA
    ---------------------------------------------------------

    dfs(originalNode)

    returns:

        cloned version of originalNode

    If node was already cloned:
        return its clone from map.

    Otherwise:
        create clone
        store it in map

        recursively clone every neighbor

        add cloned neighbors to clone->neighbors

        return clone
*/


class Solution {
public:

    // Maps each ORIGINAL node to its CLONED node.
    //
    // Example:
    //
    // mp[originalNode1] = clonedNode1
    //
    unordered_map<Node*, Node*> mp;


    Node* dfs(Node* node) {

        /*
            First check:

            Have we already created a clone for this node?

            mp.find(node) != mp.end()

            means:

            "Yes, this original node already exists in our map."
        */
        if (mp.find(node) != mp.end()) {

            // Return the clone we already created.
            //
            // DO NOT create another clone.
            return mp[node];
        }


        /*
            This node has never been cloned before.

            Create a completely NEW node with the same value.
        */
        Node* clone = new Node(node->val);


        /*
            IMPORTANT:

            Save the mapping BEFORE exploring neighbors.

            Original node -> Clone node

            Example:

                mp[original1] = clone1;

            Now if recursion reaches original1 again because
            of a cycle, we know clone1 already exists.
        */
        mp[node] = clone;


        /*
            Look at every neighbor of the ORIGINAL node.
        */
        for (Node* neighbor : node->neighbors) {

            /*
                Recursively ask:

                "Give me the cloned version of this neighbor."

                If neighbor hasn't been cloned:
                    dfs() will create it.

                If neighbor was already cloned:
                    dfs() will return it from the map.
            */
            Node* clonedNeighbor = dfs(neighbor);


            /*
                Connect our CLONED node with the
                CLONED neighbor.

                IMPORTANT:

                We add:

                    clonedNeighbor

                NOT:

                    neighbor

                because neighbor belongs to the ORIGINAL graph.
            */
            clone->neighbors.push_back(clonedNeighbor);
        }


        // Return the cloned version of this node.
        return clone;
    }


    Node* cloneGraph(Node* node) {

        // Empty graph.
        if (node == nullptr) {
            return nullptr;
        }


        /*
            Start DFS from the given original node.

            dfs(node) will eventually clone the entire
            connected graph and return the clone corresponding
            to the starting node.
        */
        return dfs(node);
    }
};
