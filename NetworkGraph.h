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
    vector<vector<Pair>> adjList;
    // Node names to apply to vertices
    map<int, string> nodeNames;

    // Graph Constructor
    Graph(vector<Edge> const &edges, int numEdges, const map<int, string> &nNames)
        : nodeNames(nNames)
    {
        // Resize the vector to hold Size elements of type vector<Edge>
        adjList.resize(numEdges);

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
                for (Pair v : adjList[i])
                    cout << "(" << nodeNames.at(v.first) << ": " << v.second << " Mb/s) ";
                cout << endl;
            }
        }
    }

    // Breadth-First Search (BFS) -- Compliments of ChatGPT
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
                    cout << "\t\t\t--> " << nodeNames.at(neighbor.first) << " (" << neighbor.second << "Mb/s)\n";
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS) - Iterative version (using stack) -- Compliments of ChatGPT
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

                cout << "\nUndiscovered Proxies For: " << nodeNames.at(node); // Process node (print it)

                // Visit all the neighbors
                for (const auto &neighbor : adjList[node])
                {
                    int neighborNode = neighbor.first;
                    if (!visited[neighborNode])
                    {
                        s.push(neighborNode);
                        // Output formatted connections
                        cout << "\n\t--> " << nodeNames.at(neighbor.first) << " (" << neighbor.second << "Mb/s)";
                    }
                }
                cout << endl; // Spacing for each node loop
            }
        }
        cout << endl;
    }

    // Algorithm to detect shortest path through graph
    void dijkstraShortestPath(int start, const vector<vector<Edge>> &graph, vector<int> &distances)
    {
        // Initialize distances to infinity
        distances.assign(graph.size(), INT_MAX);
        distances[start] = 0;

        // Min-heap priority queue: stores pairs of (node, distance)
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        pq.push(Edge(start, 0));

        while (!pq.empty())
        {
            int node = pq.top().node;
            int dist = pq.top().weight;
            pq.pop();

            // If the current distance is greater than the recorded distance, skip
            if (dist > distances[node])
                continue;

            // Visit all adjacent nodes
            for (const Edge &edge : graph[node])
            {
                int newDist = dist + edge.weight;

                // If the new distance is shorter, update and push to the priority queue
                if (newDist < distances[edge.node])
                {
                    distances[edge.node] = newDist;
                    pq.push(Edge(edge.node, newDist));
                }
            }
        }
    }
};

#endif