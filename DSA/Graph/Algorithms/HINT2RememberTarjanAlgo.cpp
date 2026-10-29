TARJAN SHORTCUT

BRIDGE
------
low[child] > tin[node]

Meaning:
Child cannot reach node or anything above node.

Memory:
BRIDGE = >

----------------------------------------

ARTICULATION POINT
------------------
low[child] >= tin[node]

Meaning:
Child cannot reach ABOVE node.
It may reach node itself, but removing node disconnects child.

Memory:
ARTICULATION = >=

Special case:
DFS root is articulation point if it has > 1 DFS children.

----------------------------------------

STRONGLY CONNECTED COMPONENT (SCC)
----------------------------------
low[node] == disc[node]

Meaning:
We found the HEAD/ROOT of an SCC.

Then:
Pop stack until this node.

Memory:
SCC = ==

----------------------------------------

ULTIMATE SHORTCUT:

Bridge       →  >
Articulation →  >=
SCC          →  ==

        >     Bridge
        >=    Articulation
        ==    SCC


------------------------------------------------------------------------------
There is another shortcut that helps remember what each algorithm is looking at:

Bridge:
    parent ---- child
                 ↑
    check low[child] > tin[parent]


Articulation:
    parent ---- child
                 ↑
    check low[child] >= tin[parent]


SCC:
    current node
         ↑
    check low[node] == disc[node]

So visually:
BRIDGE:
P ---- C
       low[C] > tin[P]


ARTICULATION:
P ---- C
       low[C] >= tin[P]


SCC:
N
low[N] == disc[N]

And one more very useful memory connection:
Bridge & Articulation
→ UNDIRECTED graph
→ concerned with disconnecting graph


Tarjan SCC
→ DIRECTED graph
→ concerned with grouping mutually reachable nodes
→ needs STACK