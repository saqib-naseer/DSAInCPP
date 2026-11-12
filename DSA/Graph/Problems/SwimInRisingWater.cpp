/*
    Problem: Swim in Rising Water
    LeetCode 778

    We start at the top-left cell (0, 0) and want to reach
    the bottom-right cell (n-1, n-1).

    grid[r][c] represents the elevation (height) of that cell.

    At time t:
        We can use any cell whose elevation <= t.

    Moving between available neighboring cells takes ZERO time.

    Therefore, the problem is NOT asking:
        "What is the shortest path?"

    It is asking:
        "What is the minimum water level/time needed so that
         some path from start to destination becomes possible?"


    MAIN IDEA:

    Suppose our path contains elevations:

        0 -> 2 -> 5 -> 3 -> 4

    We cannot complete this path until time 5.

    Why?

    Because 5 is the highest elevation on this path.

    Therefore:

        time needed for a path
        = maximum elevation on that path

    We want a path whose maximum elevation is as small as possible.


    APPROACH: Min-Heap / Dijkstra-like BFS

    We always explore the smallest elevation available to us next.

    Keep:

        time = highest elevation we have been forced to cross so far

    Whenever we pop a cell:

        time = max(time, cell elevation)

    Example:

        Visit 0 -> time = 0
        Visit 1 -> time = 1
        Visit 2 -> time = 2
        Visit 5 -> time = 5
        Visit 3 -> time stays 5

    Notice:
        Going from elevation 5 to elevation 3 does NOT reduce time.

        Once we had to wait until time 5, the current time
        remains at least 5.


    WHY MIN-HEAP?

    If several neighboring cells are available to explore:

        20, 4, 7

    we prefer 4 first.

    We don't want to unnecessarily force the water level/time
    to become 20 if a lower route may reach the destination.


    When we finally reach the destination, 'time' is the minimum
    water level needed to connect start to destination.


    Time Complexity:
        O(N^2 log(N^2))

    Space Complexity:
        O(N^2)
*/

class Solution {
public:

    // Up, Down, Left, Right
    int rows[4] = {-1, 1, 0, 0};
    int cols[4] = {0, 0, -1, 1};


    bool isValid(int r, int c, int n) {
        return r >= 0 && r < n &&
               c >= 0 && c < n;
    }


    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();

        /*
            Min-heap stores:

                {elevation, {row, column}}

            The cell with the smallest elevation
            will come out first.
        */
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > pq;


        // visited prevents processing the same cell again.
        vector<vector<bool>> visited(
            n,
            vector<bool>(n, false)
        );


        // Start from top-left.
        pq.push({grid[0][0], {0, 0}});

        visited[0][0] = true;


        /*
            'time' means:

            Highest elevation we have been forced
            to handle so far.

            This is also the minimum water level needed
            for our explored route.
        */
        int time = 0;


        while (!pq.empty()) {

            // Get the smallest elevation currently available.
            int elevation = pq.top().first;

            int r = pq.top().second.first;
            int c = pq.top().second.second;

            pq.pop();


            /*
                Water must be at least as high as this cell.

                Example:

                    current time = 5
                    cell = 3

                    time remains 5

                But:

                    current time = 5
                    cell = 8

                    time becomes 8
            */
            time = max(time, elevation);


            /*
                If we reached bottom-right,
                we have found the minimum required time.
            */
            if (r == n - 1 && c == n - 1) {
                return time;
            }


            // Explore four neighboring cells.
            for (int k = 0; k < 4; k++) {

                int newR = r + rows[k];
                int newC = c + cols[k];


                if (isValid(newR, newC, n) &&
                    !visited[newR][newC]) {

                    /*
                        Mark visited when pushing so that
                        the same cell is not added repeatedly.
                    */
                    visited[newR][newC] = true;


                    /*
                        Add the neighbor to the min-heap.

                        We do NOT manually increase time here.

                        The heap lets us consider smaller
                        elevations before larger ones.
                    */
                    pq.push({
                        grid[newR][newC],
                        {newR, newC}
                    });
                }
            }
        }


        return time;
    }
};


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {

        vector<vector<int>> result;

        for (int i = 0; i < intervals.size(); i++) {

            int existingStart = intervals[i][0];
            int existingEnd = intervals[i][1];

            int newStart = newInterval[0];
            int newEnd = newInterval[1];

            // CASE 1:
            // Existing interval is completely BEFORE newInterval.
            //
            // [1,2]       [4,8]
            //
            // Just keep the existing interval.
            if (existingEnd < newStart) {

                result.push_back(intervals[i]);
            }

            // CASE 2:
            // Existing interval is completely AFTER newInterval.
            //
            // [4,8]       [12,16]
            //
            // newInterval is now complete, so save it.
            else if (existingStart > newEnd) {

                result.push_back(newInterval);

                // Current existing interval becomes our new interval
                // to handle from now on.
                newInterval = intervals[i];
            }

            // CASE 3:
            // Neither completely before nor completely after.
            // Therefore they OVERLAP.
            //
            // existing:   [3,5]
            // new:          [4,8]
            //
            // merged:     [3,8]
            else {

                newInterval[0] = min(newStart, existingStart);
                newInterval[1] = max(newEnd, existingEnd);
            }
        }

        // Whatever interval is still in our hand
        // must be added at the end.
        result.push_back(newInterval);

        return result;
    }
};

Create queue
Create visited matrix
Create distance matrix


STEP 1:

Loop through entire matrix

    if mat[i][j] == 0:

        push (i,j) into queue

        visited[i][j] = true

        distance[i][j] = 0


STEP 2:

while queue is not empty

    take current cell

    for 4 directions

        calculate newRow, newCol

        if valid
        AND not visited

            visited = true

            distance[newRow][newCol]
                =
            distance[currentRow][currentCol] + 1

            push neighbor into queue


STEP 3:

return distance
class Solution {
public:
    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {

        // Store {value per kg, {value, weight}}
        vector<pair<double, pair<int, int>>> items;

        for (int i = 0; i < val.size(); i++) {

            // How much value do we get for 1 unit of weight?
            double ratio = (double)val[i] / wt[i];

            items.push_back({ratio, {val[i], wt[i]}});
        }

        // Highest value-per-weight item should come first.
        sort(items.begin(), items.end(),
             [](auto& a, auto& b) {
                 return a.first > b.first;
             });

        double totalValue = 0;

        for (auto& item : items) {

            double ratio = item.first;
            int value = item.second.first;
            int weight = item.second.second;

            // Whole item can fit.
            if (weight <= capacity) {

                totalValue += value;
                capacity -= weight;
            }

            // Whole item cannot fit, so take only the fraction that fits.
            else {

                /*
                    Example:

                    Item:
                    weight = 30
                    value = 120
                    ratio = 120 / 30 = 4 per kg

                    Remaining capacity = 20

                    We can take 20 kg.

                    Value gained:
                    20 * 4 = 80
                */
                totalValue += capacity * ratio;

                // Bag is completely full now.
                break;
            }
        }

        return totalValue;
    }
};


class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {

        int five = 0; // Number of $5 bills we have
        int ten = 0;  // Number of $10 bills we have

        for (int bill : bills) {

            // Customer pays exactly $5, so no change is needed.
            if (bill == 5) {
                five++;
            }

            // Customer pays $10, so we must return $5.
            else if (bill == 10) {

                // Cannot give $5 change.
                if (five == 0)
                    return false;

                five--;
                ten++;
            }

            // Customer pays $20, so we must return $15.
            else {

                // Greedy choice: Prefer $10 + $5.
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }

                // Otherwise try three $5 bills.
                else if (five >= 3) {
                    five -= 3;
                }

                // Cannot make $15 change.
                else {
                    return false;
                }
            }
        }

        return true;
    }
};


class Solution {
public:
    unordered_map<Node*, Node*> mp;

    Node* dfs(Node* node) {

        if (mp.find(node) != mp.end()) {
            return mp[node];
        }

        Node* clone = new Node(node->val);

        mp[node] = clone;

        for (Node* neighbor : node->neighbors) {

            Node* clonedNeighbor = dfs(neighbor);

            clone->neighbors.push_back(clonedNeighbor);
        }

        return clone;
    }

    Node* cloneGraph(Node* node) {

        if (node == nullptr) {
            return nullptr;
        }

        return dfs(node);
    }
};


/*
    Problem: Clone Graph

    We are given a node of a connected undirected graph.
    We need to create a completely NEW copy of the graph.

    Each original node must have:
        1. A new cloned node with the same value.
        2. The same connections, but connections must point
           to CLONED nodes, not original nodes.

    ---------------------------------------------------------
    MAIN IDEA: DFS + HASH MAP
    ---------------------------------------------------------

    The main difficulty is that graphs can contain cycles.

    Example:

        1 ---- 2
        |      |
        4 ---- 3

    DFS could go:

        1 -> 2 -> 3 -> 4 -> 1 -> ...

    So we need to remember which nodes we have already cloned.

    We use:

        unordered_map<Node*, Node*> mp;

    Think of it as:

        ORIGINAL NODE  ->  CLONED NODE

    Example:

        Original 1  ->  Clone 1
        Original 2  ->  Clone 2
        Original 3  ->  Clone 3
        Original 4  ->  Clone 4

    This map does TWO jobs:

        1. Tells us whether a node was already processed.
        2. Gives us the cloned node that belongs to it.

    ---------------------------------------------------------
    DFS IDEA
    ---------------------------------------------------------

    dfs(originalNode)

    returns:

        cloned version of originalNode

    If node was already cloned:
        return its clone from map.

    Otherwise:
        create clone
        store it in map

        recursively clone every neighbor

        add cloned neighbors to clone->neighbors

        return clone
*/


class Solution {
public:

    // Maps each ORIGINAL node to its CLONED node.
    //
    // Example:
    //
    // mp[originalNode1] = clonedNode1
    //
    unordered_map<Node*, Node*> mp;


    Node* dfs(Node* node) {

        /*
            First check:

            Have we already created a clone for this node?

            mp.find(node) != mp.end()

            means:

            "Yes, this original node already exists in our map."
        */
        if (mp.find(node) != mp.end()) {

            // Return the clone we already created.
            //
            // DO NOT create another clone.
            return mp[node];
        }


        /*
            This node has never been cloned before.

            Create a completely NEW node with the same value.
        */
        Node* clone = new Node(node->val);


        /*
            IMPORTANT:

            Save the mapping BEFORE exploring neighbors.

            Original node -> Clone node

            Example:

                mp[original1] = clone1;

            Now if recursion reaches original1 again because
            of a cycle, we know clone1 already exists.
        */
        mp[node] = clone;


        /*
            Look at every neighbor of the ORIGINAL node.
        */
        for (Node* neighbor : node->neighbors) {

            /*
                Recursively ask:

                "Give me the cloned version of this neighbor."

                If neighbor hasn't been cloned:
                    dfs() will create it.

                If neighbor was already cloned:
                    dfs() will return it from the map.
            */
            Node* clonedNeighbor = dfs(neighbor);


            /*
                Connect our CLONED node with the
                CLONED neighbor.

                IMPORTANT:

                We add:

                    clonedNeighbor

                NOT:

                    neighbor

                because neighbor belongs to the ORIGINAL graph.
            */
            clone->neighbors.push_back(clonedNeighbor);
        }


        // Return the cloned version of this node.
        return clone;
    }


    Node* cloneGraph(Node* node) {

        // Empty graph.
        if (node == nullptr) {
            return nullptr;
        }


        /*
            Start DFS from the given original node.

            dfs(node) will eventually clone the entire
            connected graph and return the clone corresponding
            to the starting node.
        */
        return dfs(node);
    }
};

/*
    KRUSKAL'S ALGORITHM - MINIMUM SPANNING TREE

    Main Idea:
    1. Sort all edges from smallest weight to largest weight.
    2. Pick edges one by one from cheapest to most expensive.
    3. Before taking an edge (u, v), check:
           Are u and v already in the same connected group?

       - YES  -> skip edge because it would create a cycle.
       - NO   -> take edge, add its weight, and join their groups.

    DSU (Disjoint Set Union) helps us manage these groups.

    DSU uses:
    parent[] -> helps represent which group a node belongs to.
    find()   -> finds the root/representative of a node's group.
    union()  -> combines two different groups.
    rank[]   -> helps keep the DSU tree short.

    Rank intuition:
    When joining two DSU trees:
        smaller rank goes under bigger rank.

    If both ranks are equal:
        either can go under the other,
        and the new root's rank increases by 1.

    Important:
    rank has NOTHING to do with edge weight or MST cost.
    It is only an optimization for keeping DSU trees short.

    Time Complexity:
    Sorting edges: O(E log E)
    DSU operations are almost O(1) on average.
    Overall: O(E log E)
*/

class Solution {
public:

    // Finds the root/representative of node.
    int findParent(int node, vector<int>& parent) {

        // If node is its own parent, we reached the root.
        if (parent[node] == node)
            return node;

        // Find the root and directly connect node to it.
        parent[node] = findParent(parent[node], parent);

        // Return the root of this group.
        return parent[node];
    }

BINARY TREE — TRAVERSALS

1. Preorder Traversal
   - Node → Left → Right

2. Inorder Traversal
   - Left → Node → Right

3. Postorder Traversal
   - Left → Right → Node

4. Level Order Traversal
   - BFS using queue

5. Recursive Traversals
   - Uses recursion / call stack

6. Iterative Traversals
   - Uses explicit stack

7. Morris Traversal
   - Traversal without recursion or stack
   - Uses temporary threaded links in the tree
   - O(N) time
   - O(1) auxiliary space
   - Most commonly used for Inorder
   - Can also be adapted for Preorder
   
   
    // Combines the groups containing u and v.
    void unionByRank(int u, int v,
                     vector<int>& parent,
                     vector<int>& rank) {

        // Find root of u's group.
        int rootU = findParent(u, parent);

        // Find root of v's group.
        int rootV = findParent(v, parent);

        // They are already in the same group.
        if (rootU == rootV)
            return;

        // U's tree is shorter, so put it under V's tree.
        if (rank[rootU] < rank[rootV]) {

            parent[rootU] = rootV;
        }

        // V's tree is shorter, so put it under U's tree.
        else if (rank[rootV] < rank[rootU]) {

            parent[rootV] = rootU;
        }

        // Both trees have the same rank.
        else {

            // We can choose either root; make V go under U.
            parent[rootV] = rootU;

            // Equal-height trees joined, so resulting tree becomes taller.
            rank[rootU]++;
        }
    }


    int spanningTree(int V, vector<vector<int>>& edges) {

        // Sort all edges by weight: [u, v, weight].
        sort(edges.begin(), edges.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        // parent[i] stores the parent of node i in DSU.
        vector<int> parent(V);

        // rank[i] helps keep DSU trees short.
        vector<int> rank(V, 0);

        // Initially every node is its own separate group.
        for (int i = 0; i < V; i++) {

            parent[i] = i;
        }

        // Stores total weight of our MST.
        int mstCost = 0;

        // Process edges from cheapest to most expensive.
        for (const auto& edge : edges) {

            // First endpoint.
            int u = edge[0];

            // Second endpoint.
            int v = edge[1];

            // Weight of this edge.
            int weight = edge[2];

            // Find which group u currently belongs to.
            int rootU = findParent(u, parent);

            // Find which group v currently belongs to.
            int rootV = findParent(v, parent);

            /*
                Different roots mean:

                    u and v are currently in DIFFERENT groups.

                Therefore connecting them will NOT create a cycle.
            */
            if (rootU != rootV) {

                // Take this edge into our MST.
                mstCost += weight;

                // Their two groups now become one group.
                unionByRank(u, v, parent, rank);
            }

            /*
                If rootU == rootV:

                    u and v are already connected.

                Adding this edge would create a cycle,
                so Kruskal simply ignores it.
            */
        }

        // Return minimum total cost.
        return mstCost;
    }
};


Number of Islands — BFS

Pattern:
Grid + Connected Components + BFS

Meaning:
'1' = Land
'0' = Water

Main Idea:
Each connected group of land = 1 island.

Steps:
1. Scan every grid cell.
2. If grid[i][j] == '1':
   - Found a NEW island.
   - islandCount++
   - Mark it visited ('1' -> '0').
   - Push it into BFS queue.
3. BFS explores the ENTIRE connected island.
4. For every cell, check Up/Down/Right/Left.
5. If neighbour is valid land:
   - Mark it visited immediately.
   - Push into queue.
6. Continue scanning for another unvisited '1'.
7. Return islandCount.

4 Directions:
row = {-1, 1, 0, 0}
col = { 0, 0, 1,-1}

UP    = (-1, 0)
DOWN  = (+1, 0)
RIGHT = ( 0,+1)
LEFT  = ( 0,-1)

newRow = currentRow + row[k]
newCol = currentCol + col[k]

Important:
Direction loop checks immediate neighbours.
BFS makes those neighbours future current cells,
so eventually the ENTIRE island is explored.

Visited Trick:
Instead of separate visited[][]:
'1' -> '0'

Outer loops:
Find NEW islands.

BFS:
Explores/consumes the WHOLE current island.

No qSize needed:
We are not calculating time or levels.

TC: O(rows * cols)
SC: O(rows * cols) worst case for BFS queue



EULER PATH & EULER CIRCUIT - UNDIRECTED GRAPH

PATTERN:
Graph + Connectivity (DFS/BFS) + Vertex Degree

--------------------------------------------------
WHAT IS EULER?
--------------------------------------------------

Euler Path:
Use EVERY EDGE exactly once.

Euler Circuit:
Use EVERY EDGE exactly once AND return to starting node.

IMPORTANT:
Euler is about EDGES, not about visiting every vertex.

--------------------------------------------------
TWO THINGS MUST BE CHECKED
--------------------------------------------------

1. CONNECTIVITY
2. NUMBER OF ODD-DEGREE VERTICES


==================================================
1. CONNECTIVITY
==================================================

All vertices that HAVE EDGES must belong to the
same connected component.

WHY?

If graph is:

0 --- 1 --- 2


3 --- 4

Starting from 0, we can use edges around 0,1,2.

But we can never reach edge 3---4.

We would need to teleport.

Therefore Euler Path/Circuit is impossible.


IMPORTANT EXCEPTION:

A vertex having degree 0 can be ignored.

Example:

0


1 --- 2 --- 3

Node 0 is disconnected, but has NO edges.

Euler only requires us to use every EDGE.

So node 0 does not matter.

Therefore:

For Euler connectivity:

"All vertices with degree > 0 must be connected."


HOW TO CHECK CONNECTIVITY:

1. Find first vertex having degree > 0.

   adj[i].size() > 0

2. Run DFS/BFS from that vertex.

3. After DFS, check every vertex.

4. If:

   adj[i].size() > 0 && !visited[i]

   then this vertex HAS edges but DFS could not
   reach it.

   Therefore graph's edges are disconnected.

   return 0.


MEANING OF IMPORTANT CONDITION:

adj[i].size() > 0
= node has at least one edge

!visited[i]
= DFS could not reach this node

Together:

node has edges + node was not reachable
= disconnected edges
= Euler impossible


==================================================
2. DEGREE CHECK
==================================================

In an undirected graph:

degree of node i = adj[i].size()


WHY EVEN DEGREE?

For a middle node:

ENTER + LEAVE = 2 edges

If visited again:

ENTER + LEAVE = another 2 edges

So middle nodes use edges in pairs.

Therefore middle nodes have EVEN degree.


WHY CAN START AND END BE ODD?

START:
We can leave without first entering.
So it can have one extra edge -> ODD.

END:
We can enter without leaving again.
So it can have one extra edge -> ODD.

Therefore only TWO odd vertices are possible:
one START and one END.


==================================================
FINAL RULE
==================================================

FIRST:
Check connectivity of all vertices having degree > 0.

If disconnected:
    return 0

If connected:

oddCount == 0
    -> Euler Circuit
    -> return 2

oddCount == 2
    -> Euler Path
    -> return 1

otherwise
    -> Neither
    -> return 0


==================================================
EASY MEMORY TRICK
==================================================

Ask TWO questions:

1. CAN I REACH ALL THE ROADS?
   -> DFS/BFS connectivity

2. CAN I ENTER AND LEAVE PROPERLY?
   -> odd/even degree


0 odd = CIRCUIT
2 odd = PATH
more than 2 = NEITHER


==================================================
COMPLEXITY
==================================================

Time: O(V + E)
Space: O(V)

DFS/BFS visits each vertex/edge at most once.


==================================================
DO NOT CONFUSE
==================================================

This problem is UNDIRECTED.

Use:
    degree = adj[i].size()

Do NOT think about indegree/outdegree here.

Indegree/outdegree are used for directed graphs.




        vector<int> dist(V, 1e8);

           dist[src] = 0;


           // Relax all edges V-1 times
           for(int i = 0; i < V - 1; i++){
            int flag=0;
               for(vector<int> edge : edges){

                   int u = edge[0];
                   int v = edge[1];
                   int w = edge[2];

                if(dist[u]==1e8) continue;
                
                   // Relax u -> v
                   if(dist[u] != INT_MAX &&
                      dist[u] + w < dist[v]){
                        flag=1;
                       dist[v] = dist[u] + w;
                   }
               }
               if(!flag) return dist;
           }


           // One extra round:
           // if distance still improves,
           // a reachable negative cycle exists
           for(vector<int> edge : edges){

               int u = edge[0];
               int v = edge[1];
               int w = edge[2];
                if(dist[u]==1e8) continue;
               if(dist[u] != INT_MAX &&
                  dist[u] + w < dist[v]){

                   return {-1};
               }
           }


           return dist;
    }
	
	
	
class Solution {
public:

    // Build path from source to node using parent[]
    vector<int> getPath(int node, vector<int>& parent) {

        vector<int> path;

        // Follow parent links backwards
        while(node != -1){

            path.push_back(node);

            node = parent[node];
        }

        // Convert node->source into source->node
        reverse(path.begin(), path.end());

        return path;
    }


    vector<int> shortestPath(int V,
                             vector<vector<int>>& edges,
                             int src,
                             int dest) {

        // Weighted adjacency list
        vector<vector<pair<int,int>>> adj(V + 1);

        for(vector<int> edge : edges){

            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }


        // Shortest distances
        vector<int> dist(V + 1, INT_MAX);

        // Previous node in selected path
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


        while(!pq.empty()){

            int currDist = pq.top().first;
            int node = pq.top().second;

            pq.pop();


            // Skip old heap entry
            if(currDist > dist[node])
                continue;


            // Check neighbors
            for(pair<int,int> neigh : adj[node]){

                int neighbour = neigh.first;
                int weight = neigh.second;

                int newDist =
                    currDist + weight;


                // CASE 1: cheaper distance
                if(newDist < dist[neighbour]){

                    dist[neighbour] = newDist;

                    parent[neighbour] = node;

                    pq.push({
                        newDist,
                        neighbour
                    });
                }


                // CASE 2: same distance
                else if(newDist == dist[neighbour]){

                    // New possible path
                    vector<int> newPath =
                        getPath(node, parent);

                    newPath.push_back(neighbour);


                    // Current existing path
                    vector<int> oldPath =
                        getPath(neighbour, parent);


                    // Keep smaller path
                    if(newPath < oldPath){

                        parent[neighbour] = node;

                        pq.push({
                            newDist,
                            neighbour
                        });
                    }
                }
            }
        }


        // No path exists
        if(dist[dest] == INT_MAX)
            return {-1};


        // Reconstruct final path
        return getPath(dest, parent);
    }
};





























class Solution {
public:

    vector<int> shortestPath(int V, vector<vector<int>>& edges,
                             int src, int dest) {

        // Weighted adjacency list
        vector<vector<pair<int,int>>> adj(V + 1);

        for (vector<int> edge : edges) {

            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        /*
            Priority queue stores:

            { distance, { path, node } }

            Because greater<> is used:

            1. Smaller distance comes first.
            2. If distance is same,
               lexicographically smaller path comes first.
        */

        using State =
            pair<int, pair<vector<int>, int>>;

        priority_queue<
            State,
            vector<State>,
            greater<State>
        > pq;

        vector<int> dist(V + 1, INT_MAX);

        dist[src] = 0;

        // Start with source
        pq.push({0, {{src}, src}});

        while (!pq.empty()) {

            int currDist = pq.top().first;
            vector<int> path = pq.top().second.first;
            int node = pq.top().second.second;

            pq.pop();

            // Old distance
            if (currDist > dist[node])
                continue;

            // First destination popped is our answer
            if (node == dest)
                return path;

            // Explore neighbors
            for (auto neigh : adj[node]) {

                int neighbour = neigh.first;
                int weight = neigh.second;

                int newDist = currDist + weight;

                if (newDist <= dist[neighbour]) {

                    // Better distance
                    if (newDist < dist[neighbour])
                        dist[neighbour] = newDist;

                    // Create path to neighbor
                    vector<int> newPath = path;
                    newPath.push_back(neighbour);

                    pq.push({
                        newDist,
                        {newPath, neighbour}
                    });
                }
            }
        }

        return {-1};
    }
};



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

class Solution {
public:
    string findOrder(vector<string> &words) {
        
        vector<bool> present(26, false);

        for (string &word : words) {
            for (char ch : word) {
                present[ch - 'a'] = true;
            }
        }

        vector<vector<int>> adj(26);
        vector<int> indegree(26, 0);

        for (int i = 0; i < words.size() - 1; i++) {

            string &first = words[i];
            string &second = words[i + 1];

            int len = min(first.size(), second.size());
            bool foundDifference = false;

            for (int j = 0; j < len; j++) {

                if (first[j] != second[j]) {

                    foundDifference = true;

                    int u = first[j] - 'a';
                    int v = second[j] - 'a';

                    adj[u].push_back(v);
                    indegree[v]++;

                    break;
                }
            }

            if (!foundDifference && first.size() > second.size()) {
                return "";
            }
        }

        queue<int> q;

        for (int i = 0; i < 26; i++) {
            if (present[i] && indegree[i] == 0) {
                q.push(i);
            }
        }

        string ans = "";

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            ans += char(node + 'a');

            for (int neighbor : adj[node]) {

                indegree[neighbor]--;

                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        int uniqueLetters = 0;

        for (int i = 0; i < 26; i++) {
            if (present[i]) {
                uniqueLetters++;
            }
        }

        if (ans.size() != uniqueLetters) {
            return "";
        }

        return ans;
    }
};
----------------------------


class Solution {
public:
    string findOrder(vector<string> &words) {

        /*
            =====================================================
            STEP 1: Find which letters actually exist
            =====================================================

            Alien alphabet uses lowercase English letters,
            but the answer should contain the unique letters
            that appear in the given words.

            present[i] tells us whether a letter exists.

            'a' - 'a' = 0
            'b' - 'a' = 1
            ...
            'z' - 'a' = 25
        */

        vector<bool> present(26, false);

        for (string &word : words) {

            for (char ch : word) {

                present[ch - 'a'] = true;
            }
        }


        /*
            =====================================================
            STEP 2: Build directed graph between letters
            =====================================================

            If we discover:

                a must come before c

            we create:

                a -> c

            adj[u] contains all letters that must come AFTER u.
        */

        vector<vector<int>> adj(26);

        // indegree[x] =
        // how many letters must come before letter x.
        vector<int> indegree(26, 0);


        /*
            Compare every pair of neighboring words.

            Example:

                words[0] vs words[1]
                words[1] vs words[2]
                words[2] vs words[3]
        */

        for (int i = 0; i < words.size() - 1; i++) {

            string &first  = words[i];
            string &second = words[i + 1];


            /*
                We can compare characters only up to
                the length of the shorter word.

                Example:

                    "baa"   length = 3
                    "abcd"  length = 4

                We can safely compare only 3 positions.
            */

            int len = min(first.size(), second.size());

            bool foundDifference = false;


            /*
                Compare both words from LEFT to RIGHT.

                We are looking for the FIRST different character.

                Example:

                    abcd
                    abca

                    a == a
                    b == b
                    c == c
                    d != a

                Therefore:

                    d must come before a

                    d -> a
            */

            for (int j = 0; j < len; j++) {

                if (first[j] != second[j]) {

                    foundDifference = true;


                    // Convert characters into graph node numbers.
                    //
                    // Example:
                    // 'a' -> 0
                    // 'b' -> 1
                    // 'c' -> 2

                    int u = first[j] - 'a';
                    int v = second[j] - 'a';


                    /*
                        Since first word appears before second word:

                            first[j] must come before second[j]

                        Therefore:

                            u -> v
                    */

                    adj[u].push_back(v);

                    // v has one more letter that must come before it.
                    indegree[v]++;


                    /*
                        VERY IMPORTANT:

                        Only the FIRST different character matters.

                        Once dictionary order is decided,
                        later characters tell us nothing about
                        the ordering of these two words.
                    */

                    break;
                }
            }


            /*
                =================================================
                SPECIAL CASE: Invalid prefix
                =================================================

                Consider:

                    "abcd"
                    "abc"

                Comparing:

                    a == a
                    b == b
                    c == c

                No different character is found.

                But "abc" is a prefix of "abcd".

                In a valid dictionary:

                    "abc"
                    "abcd"

                must be the order.

                Therefore:

                    "abcd"
                    "abc"

                is INVALID.
            */

            if (!foundDifference &&
                first.size() > second.size()) {

                return "";
            }
        }


        /*
            =====================================================
            STEP 3: Kahn's Algorithm
            =====================================================

            At this point our word problem is finished.

            We now simply have a directed graph.

            Example:

                b -> d -> a -> c

            We need its topological ordering.
        */

        queue<int> q;


        /*
            Put every PRESENT letter having indegree 0
            into the queue.

            indegree == 0 means:

            "No other letter is required to come before me."

            So this letter is READY.
        */

        for (int i = 0; i < 26; i++) {

            if (present[i] && indegree[i] == 0) {

                q.push(i);
            }
        }


        // This will contain our alien alphabet.
        string ans = "";

        // Count how many unique letters Kahn successfully processes.
        int count = 0;


        /*
            Standard Kahn's Algorithm.
        */

        while (!q.empty()) {

            int node = q.front();
            q.pop();


            /*
                Convert graph node back into character.

                0 + 'a' -> 'a'
                1 + 'a' -> 'b'
                2 + 'a' -> 'c'
            */

            ans += char(node + 'a');

            count++;


            /*
                Current letter has now been placed in the answer.

                Therefore remove its dependency from
                all letters that come after it.
            */

            for (int neighbor : adj[node]) {

                indegree[neighbor]--;


                /*
                    If neighbor now has indegree 0:

                    All letters that were required to come
                    before it have been processed.

                    So it is READY.
                */

                if (indegree[neighbor] == 0) {

                    q.push(neighbor);
                }
            }
        }


        /*
            =====================================================
            STEP 4: Detect cycle
            =====================================================

            Count how many unique letters actually exist.
        */

        int uniqueLetters = 0;

        for (int i = 0; i < 26; i++) {

            if (present[i]) {
                uniqueLetters++;
            }
        }


        /*
            If Kahn processed fewer letters than exist:

                count < uniqueLetters

            then some letters were stuck.

            That means the graph contains a cycle.

            Example:

                a -> c -> e -> a

            No valid alphabet ordering exists.
        */

        if (count != uniqueLetters) {
            return "";
        }


        // Valid topological ordering = valid alien alphabet.
        return ans;
    }
};



class TrieNode {
public:
    TrieNode* children[2];

    TrieNode() {
        children[0] = NULL;
        children[1] = NULL;
    }
};

class Solution {
public:

    TrieNode* root = new TrieNode();


    // -------------------------------------------------------
    // INSERT A NUMBER INTO BINARY TRIE
    // -------------------------------------------------------
    //
    // Example:
    // num = 5
    // binary = 101
    //
    // We insert every bit one by one into the Trie.
    //
    void insert(int num) {

        TrieNode* curr = root;

        // Numbers can be up to 10^9,
        // so bits from 30 -> 0 are enough.
        for (int i = 30; i >= 0; i--) {

            // Get ith bit of num
            int bit = (num >> i) & 1;

            // If this path does not exist, create it
            if (curr->children[bit] == NULL) {
                curr->children[bit] = new TrieNode();
            }

            // Move down the Trie
            curr = curr->children[bit];
        }
    }


    // -------------------------------------------------------
    // FIND MAXIMUM XOR OF x WITH A NUMBER INSIDE THE TRIE
    // -------------------------------------------------------
    //
    // Main XOR idea:
    //
    // x bit = 0 -> we WANT 1
    // x bit = 1 -> we WANT 0
    //
    // because:
    //
    // 0 XOR 1 = 1
    // 1 XOR 0 = 1
    //
    // We want 1 in the XOR result whenever possible.
    //
    int getMaxXOR(int x) {

        TrieNode* curr = root;

        int xorResult = 0;

        for (int i = 30; i >= 0; i--) {

            // Get ith bit of x
            int bit = (x >> i) & 1;

            // We want the OPPOSITE bit
            int oppositeBit = 1 - bit;

            // If opposite bit exists, take it
            // because this gives XOR bit = 1
            if (curr->children[oppositeBit] != NULL) {

                // Set ith bit of our XOR answer to 1
                xorResult = xorResult | (1 << i);

                curr = curr->children[oppositeBit];
            }
            else {

                // Opposite bit doesn't exist,
                // so we have no choice.
                // Take the same bit.
                //
                // XOR bit will be 0, so we don't
                // need to change xorResult.
                curr = curr->children[bit];
            }
        }

        return xorResult;
    }


    // -------------------------------------------------------
    // MAIN SOLUTION
    // -------------------------------------------------------

    vector<int> maximizeXor(
        vector<int>& nums,
        vector<vector<int>>& queries
    ) {

        // ---------------------------------------------------
        // STEP 1: Sort nums
        // ---------------------------------------------------
        //
        // Example:
        //
        // nums = [5,2,4,6,6,3]
        //
        // becomes:
        //
        // nums = [2,3,4,5,6,6]
        //
        // This allows us to insert numbers into Trie
        // from smallest -> largest.
        //
        sort(nums.begin(), nums.end());


        // ---------------------------------------------------
        // STEP 2: Create offline queries
        // ---------------------------------------------------
        //
        // Original query:
        //
        // [x, m]
        //
        // But we also need to remember its ORIGINAL INDEX.
        //
        // So we store:
        //
        // [m, x, originalIndex]
        //
        // Why put m first?
        //
        // Because when we sort this vector, C++ will
        // automatically sort primarily according to m.
        //

        vector<vector<int>> offlineQueries;

        for (int i = 0; i < queries.size(); i++) {

            int x = queries[i][0];
            int m = queries[i][1];

            offlineQueries.push_back({m, x, i});
        }


        // ---------------------------------------------------
        // STEP 3: Sort queries according to m
        // ---------------------------------------------------
        //
        // Example:
        //
        // Original:
        //
        // [12,4]
        // [8,1]
        // [6,3]
        //
        // We stored:
        //
        // [4,12,0]
        // [1,8,1]
        // [3,6,2]
        //
        // After sorting:
        //
        // [1,8,1]
        // [3,6,2]
        // [4,12,0]
        //
        // Therefore we process:
        //
        // m = 1
        // m = 3
        // m = 4
        //
        // Trie can now keep GROWING.
        //
        sort(offlineQueries.begin(), offlineQueries.end());


        // Answer array
        vector<int> ans(queries.size());


        // ---------------------------------------------------
        // j tells us where we currently are inside nums.
        // ---------------------------------------------------
        //
        // nums:
        //
        // [2,3,4,5,6,6]
        //  ↑
        //  j
        //
        int j = 0;


        // ---------------------------------------------------
        // STEP 4: Process queries from smallest m -> largest m
        // ---------------------------------------------------

        for (auto query : offlineQueries) {

            int m = query[0];
            int x = query[1];
            int originalIndex = query[2];


            // -----------------------------------------------
            // Insert EVERY number that is <= m
            // -----------------------------------------------
            //
            // Example:
            //
            // nums = [2,3,4,5,6,6]
            // m = 3
            //
            // Insert:
            //
            // 2
            // 3
            //
            // Stop when nums[j] > m.
            //
            while (j < nums.size() && nums[j] <= m) {

                insert(nums[j]);

                // IMPORTANT:
                //
                // j NEVER goes back.
                //
                // The next query has an equal or larger m,
                // so these numbers will still be valid.
                j++;
            }


            // -----------------------------------------------
            // If Trie is empty
            // -----------------------------------------------
            //
            // Example:
            //
            // nums = [2,3,4]
            // query = [8,1]
            //
            // There is no number <= 1.
            //
            if (j == 0) {

                ans[originalIndex] = -1;
            }

            // -----------------------------------------------
            // Otherwise find best XOR
            // -----------------------------------------------
            else {

                ans[originalIndex] = getMaxXOR(x);
            }
        }


        return ans;
    }
};