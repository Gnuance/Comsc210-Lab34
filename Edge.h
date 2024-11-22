#ifndef EDGE_H
#define EDGE_H

#include <unordered_set>
using namespace std;

class Edge
{
public:
    int src, dest, weight;
};

// Function to get largest vertex within a container of edge
template <typename Container>
int GetNumVertices(const Container &container)
{
    // List of nodes connected by edges
    unordered_set<int> nodes;

    // Add all unique nodes to set
    for (const auto edge : container)
    {
        nodes.insert(edge.src);
        nodes.insert(edge.dest);
    }

    return nodes.size();
}

#endif