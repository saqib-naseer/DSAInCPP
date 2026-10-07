class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {

        // adj[u] contains all courses that depend on course u.
        vector<vector<int>> adj(n + 1);

        // indegree[i] = number of prerequisites course i is waiting for.
        vector<int> inDegree(n + 1, 0);

        // Build the directed graph.
        //
        // relation = [u, v]
        // means:
        // course u must be completed before course v.
        //
        // u ---> v
        for (auto &relation : relations) {

            int u = relation[0];
            int v = relation[1];

            adj[u].push_back(v);
            inDegree[v]++;
        }

        // completionTime[i] =
        // earliest month by which course i can be COMPLETELY finished.
        vector<int> completionTime(n + 1, 0);

        queue<int> q;

        // Courses with indegree 0 have no prerequisites.
        // Therefore, they can all start immediately at month 0.
        //
        // If course i takes time[i-1] months:
        //
        // start = 0
        // finish = time[i-1]
        for (int i = 1; i <= n; i++) {

            if (inDegree[i] == 0) {

                q.push(i);

                // Course numbers are 1-based,
                // but time[] is 0-based.
                completionTime[i] = time[i - 1];
            }
        }

        // Kahn's Algorithm
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // Visit every course that depends on 'node'.
            for (int neighbor : adj[node]) {

                /*
                    Suppose:

                    node ----> neighbor

                    If node finishes at month 5
                    and neighbor takes 3 months,

                    then through this path:
                    neighbor can finish at month 8.

                    But neighbor may have MULTIPLE prerequisites.

                         A ----\
                                ---> C
                         B ----/

                    C cannot start until BOTH A and B finish.

                    Therefore, we keep the maximum completion time
                    coming from all prerequisite paths.
                */

                completionTime[neighbor] =
                    max(completionTime[neighbor],
                        completionTime[node] + time[neighbor - 1]);

                // One prerequisite of neighbor has now been processed.
                inDegree[neighbor]--;

                // If indegree becomes 0, all prerequisites are done.
                // The course is now READY.
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // All courses can run in parallel whenever possible.
        // So the total answer is NOT the sum of all course times.
        //
        // We finish everything when the LAST course finishes.
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            ans = max(ans, completionTime[i]);
        }

        return ans;
    }
};