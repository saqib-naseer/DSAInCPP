class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {

        // color[node]:
        // -1 = not visited / no group assigned yet
        //  0 = Group A
        //  1 = Group B
        vector<int> color(graph.size(), -1);

        // We need this outer loop because the graph
        // may have multiple disconnected components.
        for (int i = 0; i < graph.size(); i++) {

            // If this node is still uncolored,
            // it belongs to a new component.
            if (color[i] == -1) {

                queue<int> q;

                // Start BFS from this node.
                // We can arbitrarily put the starting node in Group A.
                q.push(i);
                color[i] = 0;

                while (!q.empty()) {

                    int node = q.front();
                    q.pop();

                    int nodeCol = color[node];

                    // Check all neighbors of current node.
                    for (int j = 0; j < graph[node].size(); j++) {

                        int neighbor = graph[node][j];

                        // CASE 1:
                        // Neighbor has not been assigned a group yet.
                        if (color[neighbor] == -1) {

                            // Put neighbor in the opposite group.
                            // If node = 0, neighbor = 1
                            // If node = 1, neighbor = 0
                            color[neighbor] = 1 - nodeCol;

                            q.push(neighbor);
                        }

                        // CASE 2:
                        // Neighbor already has a group assigned.
                        else {

                            // An edge cannot connect two nodes
                            // belonging to the same group.
                            if (color[neighbor] == nodeCol) {
                                return false;
                            }
                        }
                    }
                }
            }
        }

        // No edge was found connecting nodes
        // of the same group.
        return true;
    }
};