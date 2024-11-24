/*
    Lab 34: Multi-step network graph project. Create and transform a network graph in various ways. See README.md
*/

#include <iostream>
#include <vector>
#include <map>
#include "NetworkGraph.h"
using namespace std;

// STEP 3 -- See Readme
// Define node names (country names for example)
const map<int, string> NODE_NAMES = {
    {0, "USA"}, {1, "Canada"}, {2, "Belgium"}, {3, "Austria"}, {4, "Germany"}, {5, "France"}, {6, "Italy"}, {7, "Spain"}, {8, "UK"}, {9, "Portugal"}, {10, "Netherlands"}, {11, "Switzerland"}, {12, "Sweden"}};

int main()
{
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        // STEP 2 -- Nodes 1 & 4 removed -- See README
        {0, 2, 5},
        {0, 3, 19},
        {0, 8, 24},
        {2, 3, 7},
        {2, 5, 11},
        {2, 6, 15},
        {2, 10, 35},
        {3, 7, 5},
        {5, 6, 9},
        {5, 8, 12},
        {6, 10, 4},
        {6, 11, 3},
        {7, 9, 8},
        {8, 6, 14},
        {9, 12, 6},
        {10, 12, 8}};

    // Creates graph
    Graph graph(edges, NODE_NAMES);

    // Prints adjacency list representation of graph
    graph.printGraph();

    // STEP 1 -- See README
    // BFS and DFS starting from beginning node
    int startingNode = 0;
    // Breadth first search from node 0
    graph.DFS(0);
    // Breadth first search from node 0
    // cout << "\nBFS starting from node " << startingNode << ":" << endl;
    graph.BFS(0);

    graph.printShortestPathsWithDetails(0);

    return 0;
}
