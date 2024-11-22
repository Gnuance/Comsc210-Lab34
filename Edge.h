#ifndef EDGE_H
#define EDGE_H

using namespace std;

class Edge
{
public:
    int src, dest, weight;

    // Static function to get largest vertex within a container of edge
    template <typename Container<Edge>>
    static int getMaxVertex(const Container<Edge>& c){

    }
};

#endif