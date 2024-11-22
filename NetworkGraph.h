#ifndef NETWORK_GRAPH_H
#define NETWORK_GRAPH_H
#include <iostream>
#include <iomanip>
#include <vector>
#include "Edge.h"
using namespace std;

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

class Graph
{
public:
    // A vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges, int numVertices)
    {
        // Resize the vector to hold Size elements of type vector<Edge>
        adjList.resize(numVertices);

        // Add edges to the directed graph
        for (auto &edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // Insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // For an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph()
    {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

#endif