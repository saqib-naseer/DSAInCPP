class Solution {
public:
    bool isCyclic(int V, vector<vector<int>>& edges) {

        // STEP 1: Build directed adjacency list.
        //
        // For an edge u -> v:
        // v is an outgoing neighbor of u.
        vector<vector<int>> adj(V);

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
        }


        // STEP 2: Calculate indegree of every node.
        //
        // indegree[node] = number of incoming edges.
        //
        // We can also think of it as:
        // "How many unprocessed prerequisites does this node have?"
        vector<int> indeg(V, 0);

        for (int i = 0; i < adj.size(); i++) {

            for (int j = 0; j < adj[i].size(); j++) {

                int neighbor = adj[i][j];

                // Edge: i -> neighbor
                // So neighbor gets one incoming edge.
                indeg[neighbor]++;
            }
        }


        // STEP 3: Put all nodes having indegree 0 into queue.
        //
        // indegree == 0 means:
        // This node is not waiting for any other node,
        // so Kahn's algorithm can process it.
        queue<int> q;

        for (int i = 0; i < indeg.size(); i++) {

            if (indeg[i] == 0) {
                q.push(i);
            }
        }


        // Count how many vertices Kahn's algorithm
        // is able to process.
        int count = 0;


        // STEP 4: Perform Kahn's algorithm.
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // Successfully processed one vertex.
            count++;


            // Remove this node's effect from all its neighbors.
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbor = adj[node][i];

                // 'node' has been processed, so one prerequisite
                // of 'neighbor' is now completed.
                indeg[neighbor]--;


                // If neighbor has no remaining prerequisites,
                // it is now ready to be processed.
                if (indeg[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }


        // STEP 5: Detect cycle.
        //
        // If count == V:
        // Every vertex was successfully processed.
        // Therefore NO cycle exists.
        //
        // If count < V:
        // Some vertices could never reach indegree 0.
        // They are stuck depending on each other.
        // Therefore a cycle exists.
        return count != V;
    }
};