class Solution {
public:
    bool prerequisiteTasks(int n, vector<vector<int>>& pre) {

        // We use Kahn's Algorithm (BFS Topological Sort).
        //
        // If we can process all n tasks in topological order,
        // all prerequisites can be satisfied.
        //
        // If some tasks cannot be processed, a cycle exists.

        // Build directed adjacency list.
        vector<vector<int>> adj(n);

        for (int i = 0; i < pre.size(); i++) {

            // pre[i] = [a, b]
            //
            // b must be completed BEFORE a.
            //
            // Therefore:
            // b -> a
            adj[pre[i][1]].push_back(pre[i][0]);
        }


        // indegree[i] = number of prerequisites
        // that task i is still waiting for.
        vector<int> indegree(n, 0);

        for (int i = 0; i < adj.size(); i++) {

            for (int j = 0; j < adj[i].size(); j++) {

                int neighbor = adj[i][j];

                // Edge i -> neighbor means neighbor
                // has one incoming prerequisite.
                indegree[neighbor]++;
            }
        }


        queue<int> q;

        // Tasks with indegree 0 have no prerequisites,
        // so they can be completed immediately.
        for (int i = 0; i < n; i++) {

            if (indegree[i] == 0) {
                q.push(i);
            }
        }


        // Count how many tasks we are able to complete.
        int count = 0;


        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // This task can now be completed.
            count++;


            // Since 'node' has been completed,
            // remove its dependency from its neighbors.
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbor = adj[node][i];

                indegree[neighbor]--;


                // If neighbor now has no remaining prerequisites,
                // it is ready to be completed.
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }


        // If all n tasks were processed:
        //      no cycle exists -> possible to finish all tasks.
        //
        // If count < n:
        //      some tasks remained stuck because of a cycle.
        return count == n;
    }
};