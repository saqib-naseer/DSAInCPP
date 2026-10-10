class Solution {
public:

    /*
        DIJKSTRA - SHORTEST PATH WITH PARENT[] + LEXICOGRAPHIC TIE
        -----------------------------------------------------------

        Goal:
        Find the shortest path from src to dest in a weighted,
        undirected graph.

        If multiple paths have the same minimum distance,
        choose the lexicographically smaller path.

        Main structures:

        dist[node]
            = shortest distance found from src to node.

        parent[node]
            = previous node in the currently selected shortest path.

        getPath(node, parent)
            = reconstructs the complete path from src to node by
              repeatedly following parent[] backwards and reversing.

        Heap stores:
            {distance, node}

        -----------------------------------------------------------
        RELAXATION CASES
        -----------------------------------------------------------

        CASE 1: newDist < dist[neighbour]

            We found a genuinely cheaper route.

            Update:
                dist[neighbour]
                parent[neighbour]

            Then push neighbour into the heap.


        CASE 2: newDist == dist[neighbour]

            Distance is the same, so now compare the actual paths.

            New candidate path:
                getPath(node, parent) + neighbour

            Existing path:
                getPath(neighbour, parent)

            If:
                newPath < oldPath

            then the new route is lexicographically smaller.

            Distance stays the same.
            Only parent[neighbour] changes.

            Push neighbour again because improving its path may also
            improve the lexicographical paths of nodes after it.

        -----------------------------------------------------------
        getPath() IDEA
        -----------------------------------------------------------

        Example:

            parent[5] = 3
            parent[3] = 2
            parent[2] = 1
            parent[1] = -1

        Starting from 5:

            5 -> 3 -> 2 -> 1 -> -1

        Collected:
            [5,3,2,1]

        Reverse:
            [1,2,3,5]

        -----------------------------------------------------------
        MENTAL MODEL
        -----------------------------------------------------------

        dist[]   = How cheap is the route?
        parent[] = Who did I come from?
        getPath  = Show me the complete route.

        Better distance:
            update DIST + PARENT

        Equal distance:
            compare NEW PATH vs OLD PATH
            and update PARENT if new path is smaller.
    */

    vector<int> shortestPath(int V,
                             vector<vector<int>>& edges,
                             int src,
                             int dest) {

        // Weighted adjacency list
        vector<vector<pair<int,int>>> adj(V + 1);

        for (vector<int> edge : edges) {

            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }


        // Shortest distance found for every node
        vector<int> dist(V + 1, INT_MAX);

        // Previous node in the selected shortest path
        vector<int> parent(V + 1, -1);


        // Min-heap: {distance, node}
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;


        // Start from source
        dist[src] = 0;

        pq.push({0, src});


        while (!pq.empty()) {

            int currDist = pq.top().first;
            int node = pq.top().second;

            pq.pop();


            // Ignore an older, more expensive heap entry
            if (currDist > dist[node])
                continue;


            // Explore all neighbors
            for (pair<int,int> neighbour : adj[node]) {

                int neigh = neighbour.first;
                int weight = neighbour.second;

                int newDist = currDist + weight;


                // CASE 1: Found a cheaper route
                if (newDist < dist[neigh]) {

                    dist[neigh] = newDist;

                    parent[neigh] = node;

                    pq.push({newDist, neigh});
                }


                // CASE 2: Same distance - compare paths
                else if (newDist == dist[neigh]) {

                    // Candidate path through current node
                    vector<int> newPath =
                        getPath(node, parent);

                    newPath.push_back(neigh);


                    // Currently selected path to neighbor
                    vector<int> oldPath =
                        getPath(neigh, parent);


                    // Keep lexicographically smaller path
                    if (newPath < oldPath) {

                        parent[neigh] = node;

                        // Reprocess so path improvement can propagate
                        pq.push({newDist, neigh});
                    }
                }
            }
        }


        // Destination cannot be reached
        if (dist[dest] == INT_MAX)
            return {-1};


        // Reconstruct final selected path
        return getPath(dest, parent);
    }


    // Reconstruct source -> node using parent[]
    vector<int> getPath(int node, vector<int>& parent) {

        vector<int> path;


        // Travel backwards using parent links
        while (node != -1) {

            path.push_back(node);

            node = parent[node];
        }


        // Currently node -> source, so reverse it
        reverse(path.begin(), path.end());

        return path;
    }
};