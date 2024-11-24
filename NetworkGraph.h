#ifndef NETWORK_GRAPH_H
#define NETWORK_GRAPH_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include "Edge.h"
using namespace std;

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

const string DIVIDER = string(50, '='); // Divider to separate graph content

class Graph
{
public:
    // A vector of vectors of Pairs to represent an adjacency list
    map<int, vector<Pair>> adjList;
    // Node names to apply to vertices
    map<int, string> nodeNames;

    // Graph Constructor
    Graph(vector<Edge> const &edges, const map<int, string> &nNames)
        : nodeNames(nNames)
    {
        // Resize the vector to hold Size elements of type vector<Edge>
        // adjList.resize(numVertices);

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
        cout << "Current VPN Bandwidth:" << endl;
        cout << DIVIDER << endl;
        for (int i = 0; i < adjList.size(); i++)
        {
            if (!adjList[i].empty())
            {
                cout << nodeNames.at(i) << ":\n\t";
                int count = 0;
                for (Pair v : adjList[i])
                {
                    if (count > 0)
                        cout << " | ";
                    cout << v.first << ":" << nodeNames.at(v.first) << " (" << v.second << " Mb/s)";
                    count++;
                }
                cout << endl;
            }
        }
    }

    // Breadth-First Search (BFS)
    void BFS(int start)
    {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        // Console output header
        cout << "\nDefault Proxy Layer Map (BFS)\n";
        cout << DIVIDER;
        // int count = 0; // For output formatting
        cout << "\nDefault Proxy\t\tCountries Served";
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            // cout << node << " "; // Process node (print it)
            cout << "\n"
                 << node << ":"
                 << nodeNames.at(node); // Process node (print it)

            // Visit all the neighbors
            for (const auto &neighbor : adjList[node])
            {
                int neighborNode = neighbor.first;
                if (!visited[neighborNode])
                {
                    visited[neighborNode] = true;
                    q.push(neighborNode);
                    // Output formatted connections
                    cout << "\t\t\t--> " << neighbor.first << ":" << nodeNames.at(neighbor.first) << " (" << neighbor.second << "Mb/s)\n";
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS) - Iterative version (using stack)
    void DFS(int start)
    {
        vector<bool> visited(adjList.size(), false);
        stack<int> s;
        s.push(start);

        // Console output header
        cout << "\nNetwork Topology: Testing Connectivity (DFS)\n";
        cout << DIVIDER;
        // int count = 0; // For output formatting
        while (!s.empty())
        {
            int node = s.top();
            s.pop();

            if (!visited[node])
            {
                visited[node] = true;

                cout << "\nUndiscovered Proxies For: " << node << ":" << nodeNames.at(node); // Process node (print it)

                // Visit all the neighbors
                for (const auto &neighbor : adjList[node])
                {
                    int neighborNode = neighbor.first;
                    if (!visited[neighborNode])
                    {
                        s.push(neighborNode);
                        // Output formatted connections
                        cout << "\n\t--> " << neighbor.first << ":" << nodeNames.at(neighbor.first) << " (" << neighbor.second << "Mb/s)";
                    }
                }
                cout << endl; // Spacing for each node loop
            }
        }
        cout << endl;
    }

    // Dijkstra's algorithm & helper functions
    // Find shortest path with Dijkstra's algorithm
    void dijkstraShortestPath(int start, vector<int> &distances, vector<int> &previous)
    {
        // Initialize distances to infinity and previous nodes to -1
        distances.assign(adjList.size(), INT_MAX);
        previous.assign(adjList.size(), -1);
        distances[start] = 0;

        // Min-heap priority queue: stores pairs of (distance, node)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, start)); // Start with the source node

        while (!pq.empty())
        {
            int currentNode = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            // If the current distance is greater than the recorded distance, skip it
            if (currentDist > distances[currentNode])
                continue;

            // Visit all adjacent nodes
            for (const auto &neighbor : adjList[currentNode])
            {
                int neighborNode = neighbor.first;
                int edgeWeight = neighbor.second;
                int newDist = currentDist + edgeWeight;

                // If the new distance is shorter, update and push to the priority queue
                if (newDist < distances[neighborNode])
                {
                    distances[neighborNode] = newDist;
                    previous[neighborNode] = currentNode; // Track the previous node
                    pq.push(make_pair(newDist, neighborNode));
                }
            }
        }
    }

    // Method to print the shortest path from start node to each node
    void printShortestPathsWithDetails(int start)
    {
        vector<int> distances;
        vector<int> previous;
        dijkstraShortestPath(start, distances, previous);

        cout << "\nShortest Paths (min bandwidth) from " << start << " (" << nodeNames.at(start) << "):\n";
        cout << DIVIDER << endl;

        // for (int i = 0; i < adjList.size(); ++i)
        for (const auto &vertex : adjList)
        {
            if (distances[vertex.first] != INT_MAX)
            // {
            //     cout << vertex.first << ": Unreachable" << endl;
            // }
            // else
            {
                cout << start << " (" << nodeNames.at(start) << ") -> " << vertex.first << " (" << nodeNames.at(vertex.first) << ") : " << distances[vertex.first];
                // printPath(previous, start, i); // Print the path
                cout << endl;
            }
        }
    }

    // Helper function to print the path from start node to a given node
    void printPath(const vector<int> &previous, int start, int end)
    {
        if (end == -1)
            return; // No path to this node

        // Stack to store the path from start to end
        stack<int> pathStack;

        // Backtrack from the end node to the start node
        int current = end;
        while (current != start)
        {
            pathStack.push(current);
            current = previous[current];
        }

        // Push the start node to the stack
        pathStack.push(start);

        // Print the path in the correct order
        while (!pathStack.empty())
        {
            cout << pathStack.top();
            pathStack.pop();
            if (!pathStack.empty())
            {
                cout << " <- ";
            }
        }
    }

    // Prim's algorithm for MST computation
    void primMST(int start)
    {
        // Priority queue to store (edge weight, vertex) pairs
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

        // Vector to store the minimum weight edge for each vertex
        vector<int> minWeight(adjList.size(), INT_MAX);

        // Vector to keep track of visited vertices
        vector<bool> inMST(adjList.size(), false);

        // Vector to keep track of the parent (source vertex) for each vertex
        vector<int> parent(adjList.size(), -1);

        // Start with the starting vertex
        minWeight[start] = 0;
        pq.push(make_pair(0, start)); // (weight, vertex)

        // Variable to store the total weight of the MST
        int totalWeight = 0;

        cout << "\nMinimum Spanning Tree (MST) using Prim's Algorithm:\n";
        cout << DIVIDER << endl;

        // Continue until all vertices are processed
        while (!pq.empty())
        {
            // Get the vertex with the smallest edge weight
            int u = pq.top().second;
            int weight = pq.top().first;
            pq.pop();

            // Skip if the vertex is already included in the MST
            if (inMST[u])
            {
                continue;
            }

            // Include vertex u in MST
            inMST[u] = true;
            totalWeight += weight;

            // If u is not the starting vertex, print the edge (parent -> u)
            if (parent[u] != -1)
            {
                cout << "Edge added: " << parent[u] << " (" << nodeNames.at(parent[u]) << ") -> " << u << " (" << nodeNames.at(u)
                     << ") at " << weight << " Mb/s" << endl;
            }

            // Iterate through all neighbors of u
            for (const auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                int edgeWeight = neighbor.second;

                // If vertex v is not in the MST and the edge weight is smaller than the current min weight
                if (!inMST[v] && edgeWeight < minWeight[v])
                {
                    // Update the min weight for v and set u as its parent
                    minWeight[v] = edgeWeight;
                    parent[v] = u; // Set u as the parent of v
                    pq.push(make_pair(edgeWeight, v));
                }
            }
        }

        // Print the total weight of the MST
        cout << "Total weight of MST: " << totalWeight << endl;
    }
};

#endif