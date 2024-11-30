#include "Route.h"
using namespace std;
// Constructor
GPS::GPS(Graph* graph) : graph(graph) {
    memset(vertexNames, 0, sizeof(vertexNames));  // Initialize the vertex names array
}

/**
 * @brief Helper function to map vertex names to indices in the graph.
 * 
 * This function searches for a vertex by name and returns its index. If the vertex is not found, it
 * adds the vertex to the list and returns its new index.
 * 
 * @param name The name of the vertex.
 * @return The index of the vertex.
 */
int GPS::getVertexIndex(const string& name) {
    for (int i = 0; i < vertexCount; ++i) {
        if (vertexNames[i] == name) {
            return i;
        }
    }

    // If the vertex name is not found, add it to the list
    vertexNames[vertexCount] = name;
    return vertexCount++;
}

/**
 * @brief Helper function to find all paths between two vertices using depth-first search (DFS).
 * 
 * This function recursively explores all adjacent vertices from the start vertex and stores all paths
 * from the start to the end vertex. It also calculates the total weight of each path.
 * 
 * @param start The starting vertex.
 * @param end The destination vertex.
 * @param path The current path being explored.
 * @param pathIndex The index of the current vertex in the path.
 * @param allPaths The array to store all found paths.
 * @param allPathsCount A counter for the total number of paths found.
 * @param visited An array to track visited vertices.
 * @param totalWeight An array to store the total weights of the paths.
 * @param totalWeightCount A counter for the total number of weights.
 */
void GPS::findAllPathsDFS(Vertex* start, Vertex* end, 
                           string path[], int pathIndex, 
                           string allPaths[][MAX_VERTICES], 
                           int& allPathsCount, bool visited[], 
                           int totalWeight[], int& totalWeightCount) {

    int startIndex = getVertexIndex(start->name);

    if (visited[startIndex]) return;  // Prevent revisiting nodes

    visited[startIndex] = true;  // Mark the current vertex as visited
    path[pathIndex] = start->name;  // Add the current vertex to the path
    pathIndex++;

    // If we reached the end vertex, store the current path and total weight
    if (start == end) {
        if (allPathsCount >= MAX_VERTICES) {
            cerr << "The total possible paths found exceed MAX VERTICES" << endl;
            return;
        }

        int currentTotalWeight = 0; // To calculate total weight of this path

        for (int i = 0; i < pathIndex; i++) {
            allPaths[allPathsCount][i] = path[i];  // Store path
        }

        // Calculate total weight of the path
        for (int i = 0; i < pathIndex - 1; i++) {
            Vertex* current = graph->findVertex(path[i]);
            EdgeNode* edgeNode = current->edges;
            while (edgeNode) {
                if (edgeNode->edge->destination->name == path[i + 1]) {
                    currentTotalWeight += edgeNode->edge->travelTime;  // Add edge weight
                    break;
                }
                edgeNode = edgeNode->next;
            }
        }

        // Store the total weight of the current path
        totalWeight[totalWeightCount] = currentTotalWeight;
        totalWeightCount++;

        allPathsCount++;  // Increment path count
    } else {
        // Explore all adjacent vertices (neighbors)
        EdgeNode* edgeNode = start->edges;
        while (edgeNode) {
            Vertex* neighbor = edgeNode->edge->destination;
            int neighborIndex = getVertexIndex(neighbor->name);

            // Only proceed if the neighbor hasn't been visited
            if (!visited[neighborIndex]) {
                findAllPathsDFS(neighbor, end, path, pathIndex, allPaths, allPathsCount, visited, totalWeight, totalWeightCount);
            }
            edgeNode = edgeNode->next;
        }
    }

    // Backtrack: unmark the current vertex as visited
    pathIndex--;
    visited[startIndex] = false;
}

/**
 * @brief Function to print all paths between two vertices along with their total weights.
 * 
 * This function initiates the process of finding all paths from the start vertex to the end vertex using
 * depth-first search. It then prints each path and its associated total weight.
 * 
 * @param startName The name of the starting vertex.
 * @param endName The name of the destination vertex.
 */
void GPS::printAllPaths(const string& startName, const string& endName) {
    Vertex* start = graph->findVertex(startName);
    Vertex* end = graph->findVertex(endName);

    if (!start || !end) {
        cerr << "Error: One or both intersections not found!" << endl;
        return;
    }

    cout << "Start: " << start->name << ", End: " << end->name << endl;

    string path[MAX_VERTICES];               // Array to store the current path
    string allPaths[MAX_VERTICES][MAX_VERTICES]; // Array to store all possible paths
    int totalWeight[MAX_VERTICES] = { 0 };            // Array to store total weights of paths
    bool visited[MAX_VERTICES] = { false };       // Array to track visited vertices

    int pathIndex = 0;      // Index for the current path
    int allPathsCount = 0;  // Counter for all paths
    int totalWeightCount = 0;  // Counter for total weights

    // Start finding all paths using DFS
    findAllPathsDFS(start, end, path, pathIndex, allPaths, allPathsCount, visited, totalWeight, totalWeightCount);

    cout << "Total Paths Found: " << allPathsCount << endl;
    cout << "Paths: " << endl;

    // Print each path and its total weight
    for (int i = 0; i < allPathsCount; i++) {
        cout << "Path: ";
        for (int j = 0; allPaths[i][j] != ""; j++) {
            cout << allPaths[i][j] << " ";
        }
        cout << "| Weight: " << totalWeight[i] << endl;
    }
}






///rerouting for emergency vehicle
void GPS::rerouteEmergencyVehicle(const string& startName, const string& endName) {
    Vertex* start = graph->findVertex(startName);
    Vertex* end = graph->findVertex(endName);

    if (!start || !end) {
        cout << "The intersections were not found for rerouting vehicle\n";
        return;
    }
    string path[MAX_VERTICES];               // Array to store the current path
    string allPaths[MAX_VERTICES][MAX_VERTICES]; // Array to store all possible paths
    int totalWeight[MAX_VERTICES] = { 0 };            // Array to store total weights of paths
    bool visited[MAX_VERTICES] = { false };        // Array to track visited vertices

    int pathIndex = 0;      // Index for the current path
    int allPathsCount = 0;  // Counter for all paths
    int totalWeightCount = 0;  // Counter for total weights

    // Start finding all paths using DFS
    findAllPathsDFS(start, end, path, pathIndex, allPaths, allPathsCount, visited, totalWeight, totalWeightCount);

    if (allPathsCount == 0) {
        cout << "No path found between " << startName << " and " << endName << endl;
        return;
    }

    // Find the path with the minimum weight
    int minWeight = 5500000;
    int minWeightIndex = -1;

    for (int i = 0; i < totalWeightCount; i++) {
        if (totalWeight[i] < minWeight) {
            minWeight = totalWeight[i];
            minWeightIndex = i;
        }
    }

    if (minWeightIndex == -1) {
        cout << "\nCould not determine the path to reroute to\n";
        return;
    }

    // Print the least weight path
    cout << "\nRerouted vehicle to\n ";
    for (int j = 0; allPaths[minWeightIndex][j] != ""; j++) {
        cout << allPaths[minWeightIndex][j] << " ";
    }
}
