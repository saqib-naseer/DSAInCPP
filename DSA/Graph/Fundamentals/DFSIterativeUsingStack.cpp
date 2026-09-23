class Solution {
public:
    vector<int> dfs(vector<vector<int>>& adj) {

        int n = adj.size();

        // Keeps track of visited nodes.
        vector<bool> visited(n, false);

        // Stores DFS traversal order.
        vector<int> ans;

        // Instead of recursion, we manually use a stack.
        stack<int> st;

        // Start DFS from node 0.
        st.push(0);
        visited[0] = true;

        // Continue until there are no nodes left to explore.
        while (!st.empty()) {

            // Take the node from the TOP of stack.
            int node = st.top();
            st.pop();

            // Add current node to traversal.
            ans.push_back(node);

            // Check all neighbours of current node.
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbour = adj[node][i];

                // If neighbour has not been visited,
                // mark it and push it into stack.
                if (!visited[neighbour]) {

                    visited[neighbour] = true;
                    st.push(neighbour);
                }
            }
        }

        return ans;
    }
};