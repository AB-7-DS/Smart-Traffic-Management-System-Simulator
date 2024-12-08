#include "Route.h"
#include "bits/stdc++.h"
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
            // cerr << "The total possible paths found exceed MAX VERTICES" << endl;
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

void GPS::findAllOptimalPaths(Vertex* start, Vertex* end, 
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
          
            return;
        }

        int currentTotalWeight = 0; // To calculate total weight of this path

        // Store the current path
        for (int i = 0; i < pathIndex; i++) {
            allPaths[allPathsCount][i] = path[i];
        }

        // Calculate total weight of the path
        for (int i = 0; i < pathIndex - 1; i++) {
            Vertex* current = graph->findVertex(path[i]);
            EdgeNode* edgeNode = current->edges;
            while (edgeNode) {
                if (edgeNode->edge->destination->name == path[i + 1]) {
                    // Only add weight if the edge is not blocked
                    if (!edgeNode->edge->isBlocked()) {
                        currentTotalWeight += edgeNode->edge->travelTime;  // Add edge weight
                    }
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

            // Skip blocked intersections (if vertex is blocked), visited vertices, and blocked edges
            if (!visited[neighborIndex] && !edgeNode->edge->isBlocked()) {
                findAllOptimalPaths(neighbor, end, path, pathIndex, allPaths, allPathsCount, visited, totalWeight, totalWeightCount);
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

string GPS::getPathAsString(const string& startName, const string& endName) {
    Vertex* start = graph->findVertex(startName);
    Vertex* end = graph->findVertex(endName);

    // Check for invalid start or end vertices
    if (!start || !end) {
        cerr << "Error: One or both intersections not found!" << endl;
        return ""; // Return an empty string to handle the error case
    }

    // Arrays for pathfinding
    string path[MAX_VERTICES];                 // Array to store the current path
    string allPaths[MAX_VERTICES][MAX_VERTICES]; // Array to store all possible paths
     int totalWeight[MAX_VERTICES] = { 0 };     // Array to store total weights of paths
    bool visited[MAX_VERTICES] = { false };    // Array to track visited vertices

    int pathIndex = 0;          // Index for the current path
    int allPathsCount = 0;      // Counter for all paths
    int totalWeightCount = 0;   // Counter for total weights

    // Start finding all paths using DFS
    findAllPathsDFS(start, end, path, pathIndex, allPaths, allPathsCount, visited, totalWeight, totalWeightCount);

    // If no paths are found, return an empty string
    if (allPathsCount == 0) {
        cerr << "Error: No paths found between the intersections!" << endl;
        return ""; // Return an empty string to signify no paths found
    }

    // Construct the first full path as a single concatenated string
    string fullPath;
    for (int i = 0; i < MAX_VERTICES && !allPaths[0][i].empty(); ++i) {
        fullPath += allPaths[0][i]; // Append the vertex name directly
    }

    return fullPath;
}
string GPS::rerouteEmergencyVehicle(const string& startName, const string& endName) {
    Vertex* start = graph->findVertex(startName);
    Vertex* end = graph->findVertex(endName);

    if (!start || !end) {
        cout << "The intersections were not found for rerouting vehicle\n";
        return "";
    }

    // Arrays to represent gScore, fScore, and cameFrom
    int gScore[MAX_VERTICES];
    int fScore[MAX_VERTICES];
    Vertex* cameFrom[MAX_VERTICES] = {nullptr};
    bool closedSet[MAX_VERTICES] = {false}; // Tracks visited nodes
    Vertex* openSet[MAX_VERTICES] = {nullptr}; // Open set
    int openSetSize = 0; // Tracks the size of the open set

    // Initialize gScore and fScore
    for (int i = 0; i < MAX_VERTICES; i++) {
        gScore[i] = 1000000000;
        fScore[i] = 1000000000;
    }

    int startIndex = getVertexIndex(startName);
    int endIndex = getVertexIndex(endName);

    gScore[startIndex] = 0;
    fScore[startIndex] = heuristic(start, end);

    // Add start to open set
    openSet[openSetSize++] = start;

    while (openSetSize > 0) {
        // Find the node in the open set with the lowest fScore
        int currentIndex = -1;
        int currentFScore = INT_MAX;
        Vertex* current = nullptr;
        for (int i = 0; i < openSetSize; i++) {
            int index = getVertexIndex(openSet[i]->name);
            if (fScore[index] < currentFScore) {
                currentIndex = i;
                currentFScore = fScore[index];
                current = openSet[i];
            }
        }

        // If we reached the end, reconstruct the path
        if (current == end) {
            string shortestPath = "";
            for (Vertex* v = end; v != nullptr; v = cameFrom[getVertexIndex(v->name)]) {
                shortestPath = v->name + " " + shortestPath;
            }
            return shortestPath;
        }

        // Remove the current node from the open set
        for (int i = currentIndex; i < openSetSize - 1; i++) {
            openSet[i] = openSet[i + 1];
        }
        openSetSize--;

        // Add current to closed set
        closedSet[getVertexIndex(current->name)] = true;

        // Explore neighbors
        EdgeNode* edgeNode = current->edges;
        while (edgeNode) {
            Vertex* neighbor = edgeNode->edge->destination;
            int neighborIndex = getVertexIndex(neighbor->name);

            // Skip if the road is blocked
            if (edgeNode->edge->blocked || closedSet[neighborIndex]) {
                edgeNode = edgeNode->next;
                continue;
            }

            int tentativeGScore = gScore[getVertexIndex(current->name)] + edgeNode->edge->travelTime;

            // If neighbor is not in open set, add it
            bool inOpenSet = false;
            for (int i = 0; i < openSetSize; i++) {
                if (openSet[i] == neighbor) {
                    inOpenSet = true;
                    break;
                }
            }
            if (!inOpenSet) {
                openSet[openSetSize++] = neighbor;
            }

            // Update scores and path
            if (tentativeGScore < gScore[neighborIndex]) {
                cameFrom[neighborIndex] = current;
                gScore[neighborIndex] = tentativeGScore;
                fScore[neighborIndex] = gScore[neighborIndex] + heuristic(neighbor, end);
            }

            edgeNode = edgeNode->next;
        }
    }

    cout << "No path found between " << startName << " and " << endName << endl;
    return ""; // Return an empty string if no path is found
}


// Heuristic function: Straight-line distance (dummy implementation)
int GPS::heuristic(const Vertex* a, const Vertex* b) {
    return abs(a->name[0] - b->name[0]); // Replace with actual heuristic if coordinates exist
}
void GPS::printAllPathsDijkstra(const std::string& startName, const std::string& endName) {
    Vertex* start = graph->findVertex(startName);
    Vertex* end = graph->findVertex(endName);

    if (!start || !end) {
        std::cerr << "Error: One or both intersections not found!" << std::endl;
        return;
    }

    struct PathNode {
        Vertex* vertex;                // Current vertex
        std::string path[MAX_VERTICES]; // Path taken so far
        int pathLength;                // Number of vertices in the path
        int weight;                    // Total weight of the path

        // Default constructor
        PathNode() : vertex(nullptr), pathLength(0), weight(0) {}

        // Parameterized constructor
        PathNode(Vertex* v, int w) : vertex(v), pathLength(0), weight(w) {}
    };

    PathNode queue[MAX_VERTICES];
    bool visited[MAX_VERTICES] = {false};
    int queueStart = 0, queueEnd = 0;

    // Initialize the queue with the starting vertex
    queue[queueEnd] = PathNode(start, 0);
    queue[queueEnd].path[0] = start->name;
    queue[queueEnd].pathLength = 1;
    queueEnd++;

    std::cout << "All paths from " << startName << " to " << endName << ":\n";

    while (queueStart != queueEnd) {
        PathNode current = queue[queueStart++];
        Vertex* currentVertex = current.vertex;

        if (currentVertex == end) {
            // Print the path if we reached the destination
            std::cout << "Path: ";
            for (int i = 0; i < current.pathLength; i++) {
                std::cout << current.path[i];
                if (i < current.pathLength - 1) std::cout << " ";
            }
            std::cout << " | Current Weight: " << current.weight << "\n";
            continue;
        }

        // Visit neighbors
        EdgeNode* edgeNode = currentVertex->edges;
        while (edgeNode) {
            Vertex* neighbor = edgeNode->edge->destination;
            int neighborIndex = getVertexIndex(neighbor->name);

            // Enqueue the new path without checking blocked edges
            if (!visited[neighborIndex]) {
                PathNode newPath(neighbor, current.weight + edgeNode->edge->travelTime);
                for (int i = 0; i < current.pathLength; i++) {
                    newPath.path[i] = current.path[i];
                }
                newPath.path[current.pathLength] = neighbor->name;
                newPath.pathLength = current.pathLength + 1;

                queue[queueEnd++] = newPath;
            }

            edgeNode = edgeNode->next;
        }

        // Mark the current vertex as visited
        visited[getVertexIndex(currentVertex->name)] = true;
    }
}


