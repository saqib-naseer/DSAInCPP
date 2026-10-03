class Solution {
public:
    vector<int> findOrder(int numCourses,
                          vector<vector<int>>& prerequisites) {

        // For prerequisites[i] = [a, b]:
        //
        // To take course 'a', course 'b' must be completed first.
        //
        // Therefore the directed edge is:
        // b -> a
        vector<vector<int>> adj(numCourses);

        // indegree[course] =
        // number of prerequisites that course is waiting for.
        vector<int> indegree(numCourses, 0);


        // Build adjacency list and calculate indegree.
        for (int i = 0; i < prerequisites.size(); i++) {

            int course = prerequisites[i][0];
            int prerequisite = prerequisites[i][1];

            // prerequisite -> course
            adj[prerequisite].push_back(course);

            // Course has one more incoming prerequisite.
            indegree[course]++;
        }


        queue<int> q;

        // Courses with indegree 0 have no prerequisites,
        // so they can be taken immediately.
        for (int i = 0; i < numCourses; i++) {

            if (indegree[i] == 0) {
                q.push(i);
            }
        }


        // Stores the topological ordering.
        vector<int> ans;


        // Kahn's Algorithm / BFS Topological Sort
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // Current course is ready, so add it
            // to our course ordering.
            ans.push_back(node);


            // Completing this course satisfies one prerequisite
            // for every course that depends on it.
            for (int neighbor : adj[node]) {

                indegree[neighbor]--;


                // All prerequisites of this course
                // have now been completed.
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }


        // If all courses were added:
        //     valid topological ordering exists.
        //
        // Otherwise:
        //     a cycle exists, so completing all courses
        //     is impossible. Return an empty vector.
        return ans.size() == numCourses
               ? ans
               : vector<int>{};
    }
};