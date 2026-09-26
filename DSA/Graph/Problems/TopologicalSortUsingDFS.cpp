class Solution {
public:

    vector<int> topoSort(int V, vector<vector<int>>& edges) {

        // STEP 1: Build directed adjacency list.
        // For an edge u -> v:
        // u must appear before v in the topological ordering.
        vector<vector<int>> adj(V);

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
        }


        // STEP 2: visited[] prevents processing the same node again.
        // This is especially important when multiple nodes point
        // toward the same node.
        vector<bool> visited(V, false);

        // Stack stores nodes according to their DFS finishing time.
        // A node is pushed only AFTER all its outgoing neighbors
        // have been completely explored.
        stack<int> st;


        // STEP 3: Start DFS from every unvisited node.
        //
        // We cannot just call DFS(0), because the graph may have
        // multiple disconnected components.
        for (int i = 0; i < V; i++) {

            if (!visited[i]) {
                dfsHelper(i, st, visited, adj);
            }
        }


        // STEP 4: Stack contains reverse finishing order.
        //
        // Example:
        //
        // 0 -> 1 -> 2
        //
        // DFS finishes:
        // 2, 1, 0
        //
        // Stack pop order:
        // 0, 1, 2
        //
        // which gives the topological ordering.
        vector<int> ans;

        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }


    void dfsHelper(int node,
                   stack<int>& st,
                   vector<bool>& visited,
                   vector<vector<int>>& adj) {

        // Mark immediately so another DFS path does not
        // process this node again.
        visited[node] = true;


        // Explore every node that the current node points to.
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            if (!visited[neighbor]) {
                dfsHelper(neighbor, st, visited, adj);
            }
        }


        // IMPORTANT:
        // Push the current node only AFTER all its neighbors
        // have been completely explored.
        //
        // For edge:
        //
        //      u -> v
        //
        // Topological order requires:
        //
        //      u before v
        //
        // But DFS finishes:
        //
        //      v before u
        //
        // Therefore we store finishing order in a stack.
        // Popping the stack reverses it:
        //
        //      u before v
        //
        st.push(node);
    }
};