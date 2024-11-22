#ifndef EDGE_H
#define EDGE_H

#include <unordered_set>
using namespace std;

class Edge
{
public:
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
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

    // Return umber of vertices
    return nodes.size();
}

#endif