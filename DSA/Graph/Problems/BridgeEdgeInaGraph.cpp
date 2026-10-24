class Solution {
public:
    void dfsHelper(int node, int parent,
        vector<bool>& vis, bool& hasBridge,
        vector<int>& low, vector<int>& tin,
        int& timer, vector<vector<int>>& adj,
        int c, int d) {

        low[node] = tin[node] = timer++;
        vis[node] = true;

        for (int i = 0; i < adj[node].size(); i++) {
            int neighbour = adj[node][i];

            if (neighbour == parent) {
                continue;
            }
            else if (vis[neighbour]) {
                low[node] = min(low[node], tin[neighbour]);
            }
            else {
                dfsHelper(neighbour, node, vis, hasBridge,
                          low, tin, timer, adj, c, d);

                low[node] = min(low[node], low[neighbour]);

                if (low[neighbour] > tin[node]) {
                    if ((node == c && neighbour == d) ||
                        (node == d && neighbour == c)) {
                        hasBridge = true;
                    }
                }
            }
        }
    }

    bool isBridge(int V, vector<vector<int>>& edges, int c, int d) {

        vector<vector<int>> adj(V);

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int timer = 0;

        vector<bool> vis(V, false);
        vector<int> low(V);
        vector<int> tin(V);

        bool hasBridge = false;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfsHelper(i, -1, vis, hasBridge,
                          low, tin, timer, adj, c, d);
            }
        }

        return hasBridge;
    }
};
