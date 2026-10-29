/*
    TARJAN'S ALGORITHM - STRONGLY CONNECTED COMPONENTS
    ===================================================

    Problem:
    Given a directed graph, find all Strongly Connected Components (SCCs).

    SCC:
    A group of vertices where every vertex can reach every other vertex
    in the same component.

    Example:

        0 -> 1 -> 2
        ^         |
        |_________|

        2 -> 3
        3 <-> 4
        4 -> 5

    Possible SCCs:

        {0, 1, 2}
        {3, 4}
        {5}


    --------------------------------------------------
    MAIN IDEA
    --------------------------------------------------

    Tarjan finds all SCCs using only ONE DFS.

    We maintain:

    1. disc[node]
       Discovery time of the node.
       It tells us WHEN the node was first visited.

    2. low[node]
       Earliest discovery time reachable from this node
       while considering the current unfinished SCC search.

    3. Stack
       Contains nodes that are currently part of unfinished SCCs.

    4. inStack[node]
       Tells whether a node is currently inside the stack.


    --------------------------------------------------
    IMPORTANT LOW UPDATE RULES
    --------------------------------------------------

    CASE 1: Neighbor is NOT visited

        DFS(neighbor)

        After DFS returns:

        low[node] = min(low[node], low[neighbor]);

    Why?

        The child explored its complete subtree.
        If the child can reach an earlier node,
        then the parent can also reach that earlier node
        through the child.

        MEMORY:

            CHILD RETURNS -> USE LOW[CHILD]


    CASE 2: Neighbor is already visited AND still in stack

        low[node] = min(low[node], disc[neighbor]);

    Why?

        We directly found a previously discovered node
        which is still part of the current unfinished SCC.

        MEMORY:

            OLD NODE IN STACK -> USE DISC[NEIGHBOR]


    CASE 3: Neighbor is visited but NOT in stack

        Ignore it.

    Why?

        That node already belongs to a completed SCC.


    --------------------------------------------------
    HOW DO WE KNOW AN SCC IS COMPLETE?
    --------------------------------------------------

    If:

        low[node] == disc[node]

    then 'node' is the root/head of an SCC.

    Pop nodes from the stack until 'node' itself is popped.

    Every popped node belongs to the SAME SCC.


    --------------------------------------------------
    BEST MEMORY RULE
    --------------------------------------------------

        DFS goes DOWN.
        LOW information comes UP.

        Child returns
            -> LOW[child]

        Visited node still in stack
            -> DISC[neighbor]

        LOW[node] == DISC[node]
            -> SCC FOUND
            -> POP UNTIL NODE


    Time Complexity:
        O(V + E)

    Space Complexity:
        O(V)
        excluding the graph itself.
*/


class Solution {
public:

    void dfsHelper(
        int node,
        vector<vector<int>>& adj,
        vector<vector<int>>& ans,
        vector<bool>& vis,
        int& timer,
        vector<bool>& inStack,
        stack<int>& st,
        vector<int>& low,
        vector<int>& disc
    ) {

        // Mark node as visited.
        vis[node] = true;

        // Assign discovery time and initial low value.
        disc[node] = low[node] = timer++;

        // Current node is part of an unfinished SCC.
        st.push(node);
        inStack[node] = true;


        // Explore all outgoing edges.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];


            // CASE 1:
            // Neighbor has never been visited.
            if (!vis[neighbor]) {

                dfsHelper(
                    neighbor,
                    adj,
                    ans,
                    vis,
                    timer,
                    inStack,
                    st,
                    low,
                    disc
                );


                /*
                    DFS child has returned.

                    The child may have discovered a path
                    to a much earlier node.

                    So pass that information upward.

                    CHILD RETURNS -> LOW[CHILD]
                */
                low[node] = min(
                    low[node],
                    low[neighbor]
                );
            }


            // CASE 2:
            // Neighbor was already visited.
            else {

                /*
                    Only consider it if it is STILL
                    inside the Tarjan stack.

                    If it is not in the stack,
                    its SCC has already been completed.
                */
                if (inStack[neighbor]) {

                    /*
                        We directly reached an already
                        discovered node.

                        OLD NODE IN STACK -> DISC[NEIGHBOR]
                    */
                    low[node] = min(
                        low[node],
                        disc[neighbor]
                    );
                }
            }
        }


        /*
            If discovery time equals low value,
            this node is the ROOT of an SCC.

            Everything on top of the stack up to
            this node belongs to this SCC.
        */
        if (disc[node] == low[node]) {

            vector<int> component;


            // Pop until we reach the SCC root.
            while (!st.empty()) {

                int topNode = st.top();
                st.pop();

                // This node now belongs to a completed SCC.
                inStack[topNode] = false;

                // Store it in the current SCC.
                component.push_back(topNode);


                // Stop after popping the SCC root.
                if (topNode == node) {
                    break;
                }
            }


            // Problem requires nodes inside SCC to be sorted.
            sort(component.begin(), component.end());

            // Store this SCC.
            ans.push_back(component);
        }
    }


    vector<vector<int>> findSCC(vector<vector<int>>& adj) {

        int V = adj.size();

        vector<vector<int>> ans;

        // Normal visited information.
        vector<bool> vis(V, false);

        // Is node currently inside Tarjan's stack?
        vector<bool> inStack(V, false);

        // Discovery time.
        vector<int> disc(V);

        // Lowest reachable discovery time.
        vector<int> low(V);

        // Stores nodes belonging to unfinished SCCs.
        stack<int> st;

        // Unique discovery time for every node.
        int timer = 0;


        /*
            Run DFS from every unvisited node because
            the directed graph may not be reachable
            from a single starting vertex.
        */
        for (int i = 0; i < V; i++) {

            if (!vis[i]) {

                dfsHelper(
                    i,
                    adj,
                    ans,
                    vis,
                    timer,
                    inStack,
                    st,
                    low,
                    disc
                );
            }
        }


        // Problem requires SCCs in lexicographical order.
        sort(ans.begin(), ans.end());

        return ans;
    }
};