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

int main_menu();                      // outputs prompt and collects user selection
bool isValidOption(string, int, int); // helper function to validate user input

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

    // STEP 1 -- See README
    // BFS and DFS starting from beginning node
    int startingNode = 0;

    // prompt user for selection and input
    // user selection 4 is the program exit code
    int userSelectedOption;
    do
    {
        userSelectedOption = main_menu();
        switch (userSelectedOption)
        {
        case 1:
            // Prints adjacency list representation of graph
            graph.printGraph();
            break;
        case 2:
            // Breadth first search from node 0
            graph.BFS(0);
            break;
        case 3:
            // Depth first search from node 0
            graph.DFS(0);
            break;
        case 4:
            // STEP 4 -- Shortest paths through graph from node 0
            graph.printShortestPathsWithDetails(0);
            break;
        case 5:
            // STEP 5 -- MST using Prim's Algorithm
            graph.primMST(0);
            break;
        default:
            break;
        }
    } while (userSelectedOption != 0);

    cout << "Thank you for using the network graph tool" << endl;

    return 0;
}

// main menu fuction for STEP 6
int main_menu()
{
    string userInput = "";

    do
    {
        // output prompt
        cout << "VPN: Network Menu" << "\n"
             << "[1] Display Bandwidth Summary" << "\n"
             << "[2] Default Proxy Map [BFS]" << "\n"
             << "[3] Test Network Nodes [DFS]" << "\n"
             << "[4] Display Minimum Bandwidth From Source" << "\n"
             << "[5] MST: Minimum Spanning Tree For Network" << "\n"
             << "[0] Quit" << "\n"
             << "Choice --> ";
        getline(cin, userInput); // get user input as string and test
        cout << endl;
    } while (!isValidOption(userInput, 0, 5));

    // if isValidOption passed, stoi(userInput) has already been tested and is safe
    return stoi(userInput);
}

// return t/f if userInput is a valid int between min and max
// helper function for main_menu and delete_goat
// WARNING: stoi() will convert a double to an int or any string following an int.
// Ex: stoi("2.9") will return 2 and so will stoi("2tGznso"), etc.
bool isValidOption(string userInput, int minOption, int maxOption)
{
    int selectedOption = 0;
    try
    {
        selectedOption = stoi(userInput);
    }
    catch (const std::exception &e)
    {
        cout << "Invalid input: Please enter a valid integer." << "\n\n";
        return false;
    }

    // if userInput is an int but outside expected range
    if (selectedOption < minOption || selectedOption > maxOption)
    {
        cout << "Invalid input: Please enter an integer between " << minOption << " and " << maxOption << "." << "\n\n";
        return false;
    }

    return true;
}
