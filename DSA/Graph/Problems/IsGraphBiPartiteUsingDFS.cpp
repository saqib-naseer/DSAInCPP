class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {

        // color[node]:
        // -1 = not visited / no group assigned
        //  0 = Group A
        //  1 = Group B
        //
        // color[] also acts as our visited array.
        vector<int> color(graph.size(), -1);


        // The graph may be disconnected, so we must
        // check every component separately.
        for (int i = 0; i < graph.size(); i++) {

            // If this node is still uncolored,
            // it belongs to a new unexplored component.
            if (color[i] == -1) {

                // We can assign any starting color.
                color[i] = 0;

                // Start DFS from THIS component.
                // If any conflict is found, graph is not bipartite.
                if (!dfsHelper(i, color, graph)) {
                    return false;
                }
            }
        }

        // All components were successfully divided
        // into two groups.
        return true;
    }


    bool dfsHelper(int node,
                   vector<int>& color,
                   vector<vector<int>>& graph) {

        // Explore all neighbors of the current node.
        for (int i = 0; i < graph[node].size(); i++) {

            int neighbor = graph[node][i];


            // CASE 1:
            // Neighbor has not been visited/colored yet.
            if (color[neighbor] == -1) {

                // Connected nodes must belong to opposite groups.
                //
                // current = 0 -> neighbor = 1
                // current = 1 -> neighbor = 0
                color[neighbor] = 1 - color[node];


                // Continue DFS from the neighbor.
                //
                // If a deeper recursive call finds a conflict,
                // propagate false all the way back.
                if (!dfsHelper(neighbor, color, graph)) {
                    return false;
                }
            }

            // CASE 2:
            // Neighbor has already been colored.
            else {

                // If both endpoints of an edge have the
                // same color, they belong to the same group.
                //
                // That violates the bipartite condition.
                if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }

        // No coloring conflict was found from this node.
        return true;
    }
};