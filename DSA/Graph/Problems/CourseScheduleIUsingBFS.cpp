class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        // Directed adjacency list:
        // prerequisite -> course
        //
        // For [a, b]:
        // course b must be completed before course a.
        //
        // Therefore the directed edge is:
        // b -> a
        vector<vector<int>> adj(numCourses);

        // indegree[course] =
        // number of prerequisites that course is waiting for.
        vector<int> indegree(numCourses, 0);


        // Build the graph and calculate indegree.
        for (int i = 0; i < prerequisites.size(); i++) {

            int course = prerequisites[i][0];
            int prerequisite = prerequisites[i][1];

            // prerequisite -> course
            adj[prerequisite].push_back(course);

            // 'course' has one more prerequisite.
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


        // Count how many courses we are able to complete.
        int count = 0;


        // Kahn's Algorithm (BFS Topological Sort)
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // We can successfully complete this course.
            count++;


            // Completing this course satisfies one prerequisite
            // for every course that depends on it.
            for (int neighbor : adj[node]) {

                indegree[neighbor]--;


                // If all prerequisites of this course
                // are now completed, it is ready.
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }


        // If every course was processed:
        //     No cycle exists -> all courses can be completed.
        //
        // If count < numCourses:
        //     Some courses are stuck in a cycle.
        return count == numCourses;
    }
};