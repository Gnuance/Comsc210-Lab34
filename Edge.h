#ifndef EDGE_H
#define EDGE_H

#include <set>
using namespace std;

class Edge
{
public:
    int src, dest, weight;

    // Static function to get largest vertex within a container of edge
    template <typename Container>
    static int getMaxVertex(const Container& container){
        
        // List of nodes connected by edges
        set<int> nodes;

        // Add all unique nodes to set
        for (const auto edge : container)
        {
            nodes.insert(edge.src);
            nodes.insert(edge.dest);
        }
        
    }
};

#endif