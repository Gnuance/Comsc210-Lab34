# LAB 34: NETWORK GRAPH
## Requirements
    + Step 1
        - Through prompt engineering, transform the code by adding the necessary code to do a DFS and BFS in your code. Write a short driver program to exercise your code.
        - Complete Step 1 with a specific commit comment "Step 1 complete."
    + Step 2
        - Change the graph by deleting at least two nodes and adding at least six nodes. Change the weights as well. 
        - Complete Step 2 with a specific commit comment "Step 2 complete."
    + Step 3
        - Through expert prompt engineering, wrap an application around this new graph. It should be some real-world example that is represented by your graph.
        - Complete Step 3 with a specific commit comment "Step 3 complete."
    + Step 4
        - Through prompt engineering add code to provide the shortest path through your graph.
        - Complete Step 4 with a specific commit comment "Step 4 complete."
    + Step 5
        - Through prompt engineering, add code to provide the minimum spanning tree of your graph.
        - Complete Step 5 with a specific commit comment "Step 5 complete."
    + Step 6
        - Place a menu in front of all this functionality.
        - Complete Step 6 with a specific commit comment "Step 6 complete."

## Design Decisions
    + Moving graph into it's own class file to clean up main and improve readability.
    + Also moved Edge into its own with a new function to calculate the number of vertices
        - I didn't like the hardcoded size in the call to Graph() in case the program ever needs to be implemented dynamically because the number of vertices is simply the unique number of src & dest items.

## Completion Updates
    + Step 1 - Completed
    + Step 2 - Nodes 1 & 4 removed. Nodes 7-12 added and weights revised. Had to modify NetworkGraph.h::void printGraph() to check if !adjList[i].empty before printing.
    + Step 3 - Modeling a VPN using a graph. DFS discovers available network nodes (Network Discovery) & BFS is used to determine most efficient pathfinding.