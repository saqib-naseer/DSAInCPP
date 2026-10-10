class Solution {
public:

    /*
        DIJKSTRA - SHORTEST PATH + LEXICOGRAPHICALLY SMALLEST PATH
        ----------------------------------------------------------

        Goal:
        Find the shortest path from src to dest in a weighted,
        undirected graph with non-negative edge weights.

        Extra Requirement:
        If multiple paths have the same shortest distance,
        return the lexicographically smallest path.

        Normal Dijkstra heap stores:
            {distance, node}

        Here we also need to know the complete path, so heap stores:
            {distance, {path, node}}

        Example:
            {5, {[1, 2, 4], 4}}

        Means:
            We reached node 4 with total cost 5
            using path [1, 2, 4].

        Heap Priority:
        Because greater<> is used:

            1. Smaller distance comes first.
            2. If distances are equal,
               smaller path comes first lexicographically.
            3. Node is used only if previous values also tie.

        Example:
            {5, {[1,2,4], 4}}
            {5, {[1,3,4], 4}}

        First one comes first because:
            [1,2,4] < [1,3,4]

        Relaxation:
            newDist = currDist + weight

        We allow:
            newDist <= dist[neighbor]

        '<'  -> found a cheaper path.
        '==' -> found another shortest path which may be
                lexicographically smaller.

        Why make/copy a path for every neighbor?
        A node can have multiple neighbors.

        From path:
            [1,2]

        We may need:
            [1,2,3]
            [1,2,4]

        Each neighbor therefore needs its own path.

        Stale Entry:
        A node may enter the heap multiple times.

        If:
            currDist > dist[node]

        then this heap entry represents an older, more expensive route,
        so we skip it.

        Important:
        This approach is easy to understand but stores complete vectors
        inside the priority queue, so it uses more time/memory than
        ordinary Dijkstra with only {distance,node}.

        Mental Model:

            POP cheapest state
                    ↓
            Skip stale state
                    ↓
            Destination? return path
                    ↓
            Check neighbors
                    ↓
            Create path for each neighbor
                    ↓
            Push into heap

        Dijkstra requires non-negative edge weights.
    */

    vector<int> shortestPath(int V,
                             vector<vector<int>>& edges,
                             int src,
                             int dest) {

        // Weighted adjacency list
        vector<vector<pair<int, int>>> adj(V + 1);

        for (vector<int> edge : edges) {

            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Shortest known distance
        vector<int> dist(V + 1, INT_MAX);

        // state = {distance, {path, node}}
        using state = pair<int, pair<vector<int>, int>>;

        // Min-heap
        priority_queue<
            state,
            vector<state>,
            greater<state>
        > pq;

        // Source starts at distance 0
        dist[src] = 0;

        // Initial state: {distance, {path, node}}
        pq.push({0, {{src}, src}});

        while (!pq.empty()) {

            // Get cheapest state
            int currDist = pq.top().first;
            vector<int> path = pq.top().second.first;
            int node = pq.top().second.second;

            pq.pop();

            // Skip old distance
            if (currDist > dist[node])
                continue;

            // Cheapest valid destination path
            if (node == dest)
                return path;

            // Explore neighbors
            for (pair<int, int> neighbour : adj[node]) {

                int neigh = neighbour.first;
                int w = neighbour.second;

                // Distance through current node
                int newDist = currDist + w;

                // Cheaper or equal shortest path
                if (newDist <= dist[neigh]) {

                    dist[neigh] = newDist;

                    // Choose this neighbor
                    path.push_back(neigh);

                    // Store this path in heap
                    pq.push({newDist, {path, neigh}});

                    // Undo for next neighbor
                    path.pop_back();
                }
            }
        }

        // Destination unreachable
        return {-1};
    }
};