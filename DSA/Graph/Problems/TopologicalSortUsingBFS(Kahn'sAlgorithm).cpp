class Solution {
public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {

        // STEP 1: Build directed adjacency list.
        // For edge u -> v:
        // u must come before v in the topological ordering.
        vector<vector<int>> adj(V);

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
        }


        // STEP 2: Calculate indegree of every node.
        //
        // indegree[node] = number of incoming edges to that node.
        //
        // Example:
        // 0 -> 2
        // 1 -> 2
        //
        // indegree[2] = 2
        vector<int> indeg(V);

        for (int i = 0; i < adj.size(); i++) {

            for (int j = 0; j < adj[i].size(); j++) {

                int neighbor = adj[i][j];

                // Edge is: i -> neighbor
                // So neighbor gets one incoming edge.
                indeg[neighbor]++;
            }
        }


        // STEP 3: Push all nodes having indegree 0 into queue.
        //
        // indegree 0 means:
        // No node needs to come before this node.
        // Therefore, it is ready to be placed in topo order.
        queue<int> q;

        for (int i = 0; i < indeg.size(); i++) {

            if (indeg[i] == 0) {
                q.push(i);
            }
        }


        // Store final topological ordering.
        vector<int> ans;


        // STEP 4: Process nodes using BFS.
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // This node has no remaining dependencies,
            // so add it to topological order.
            ans.push_back(node);


            // STEP 5: Remove this node's effect from its neighbors.
            //
            // If:
            // node -> neighbor
            //
            // Since 'node' has now been processed,
            // one prerequisite of 'neighbor' is completed.
            // Therefore decrease neighbor's indegree.
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbor = adj[node][i];

                indeg[neighbor]--;


                // If indegree becomes 0, all nodes that needed
                // to come before this neighbor have been processed.
                //
                // So this neighbor is now ready.
                if (indeg[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }


        return ans;
    }
};