/*
    Lab 34: Multi-step network graph project. Create and transform a network graph in various ways. See README.md
*/

#include <iostream>
#include <vector>
#include "NetworkGraph.h"
using namespace std;

// const int SIZE = 7;

int main()
{
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0, 1, 12},
        {0, 2, 8},
        {0, 3, 21},
        {2, 3, 6},
        {2, 6, 2},
        {5, 6, 6},
        {4, 5, 9},
        {2, 4, 4},
        {2, 5, 5}};

    // Creates graph
    Graph graph(edges, GetNumVertices(edges));

    // Prints adjacency list representation of graph
    graph.printGraph();

    // STEP 1 -- See README.md
    // BFS and DFS starting from beginning node
    int startingNode = 0;
    // Breadth first search from node 0
    cout << "BFS from node: " << startingNode << " --> ";
    graph.BFS(0);
    // Breadth first search from node 0
    cout << "DFS from node: " << startingNode << " --> ";
    graph.DFS(0);

    return 0;
}
