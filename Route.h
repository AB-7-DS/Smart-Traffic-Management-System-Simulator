#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <string>
#include <cstring>
#include "graph.h"  // Assuming you have a Graph class for managing vertices and edges
using namespace std;

/**
 * @class GPS
 * @brief Class for managing GPS navigation and finding all possible paths between two vertices.
 * 
 * This class uses depth-first search (DFS) to find all possible paths between two vertices in a graph,
 * along with calculating and storing the total weight of each path.
 */
class GPS {
private:
    Graph* graph;  ///< Pointer to the Graph object
    static const int MAX_VERTICES = 250;  ///< Maximum number of vertices
    std::string vertexNames[MAX_VERTICES];  ///< Array to store vertex names
    
    int vertexCount = 0;  ///< Counter for the number of vertices

    /**
     * @brief Helper function to map vertex names to indices in the graph.
     * 
     * This function searches for a vertex by name and returns its index. If the vertex is not found, it
     * adds the vertex to the list and returns its new index.
     * 
     * @param name The name of the vertex.
     * @return The index of the vertex.
     */
    int getVertexIndex(const std::string& name);

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
    void findAllPathsDFS(Vertex* start, Vertex* end, 
                         std::string path[], int pathIndex, 
                         std::string allPaths[][MAX_VERTICES], 
                         int& allPathsCount, bool visited[], 
                         int totalWeight[], int& totalWeightCount);

public:
    /**
     * @brief Constructor for the GPS class.
     * 
     * Initializes the GPS object with a reference to a graph object.
     * 
     * @param graph A pointer to the Graph object.
     */
    GPS(Graph* graph);

    /**
     * @brief Function to print all paths between two vertices along with their total weights.
     * 
     * This function initiates the process of finding all paths from the start vertex to the end vertex using
     * depth-first search. It then prints each path and its associated total weight.
     * 
     * @param startName The name of the starting vertex.
     * @param endName The name of the destination vertex.
     */
    void printAllPaths(const std::string& startName, const std::string& endName);

    /**
     * @brief Function to reroute an emergency vehicle around a blocked road.
     *
     * This function finds an alternate path for an emergency vehicle to reach its destination
     * by avoiding a blocked road. It uses the printAllPaths function to find all possible paths
     * and selects the shortest path that avoids the blocked road.
     * 
     * @param startName The name of the starting intersection.
     * @param endName The name of the destination intersection.
     * @return A string representing the alternate path.
     */
    string rerouteEmergencyVehicle(const string& startName, const string& endName);

    /**
     * @brief Function to get the path as a string between two vertices.
     * 
     * This function returns a string representation of the path from the start vertex to the end vertex.
     * 
     * @param startName The name of the starting vertex.
     * @param endName The name of the destination vertex.
     * @return A string representing the path.
     */
    string getPathAsString(const string& startName, const string& endName);

    /**
     * @brief Helper function to find all optimal paths between two vertices.
     * 
     * This function uses DFS to find all optimal paths between the start and end vertices, considering path weights.
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
    void findAllOptimalPaths(Vertex* start, Vertex* end, 
                             string path[], int pathIndex, 
                             string allPaths[][MAX_VERTICES], 
                             int& allPathsCount, bool visited[], 
                             int totalWeight[], int& totalWeightCount);

    /**
     * @brief Function to print all paths using Dijkstra's algorithm.
     * 
     * This function finds and prints the shortest paths between two vertices using Dijkstra's algorithm.
     * 
     * @param startName The name of the starting vertex.
     * @param endName The name of the destination vertex.
     */
    void printAllPathsDijkstra(const string& startName, const string& endName);

    /**
     * @brief Heuristic function to estimate the distance between two vertices.
     * 
     * This function calculates the heuristic value between two vertices. It is typically used for A* search.
     * 
     * @param a The first vertex.
     * @param b The second vertex.
     * @return The heuristic value between the two vertices.
     */
    int heuristic(const Vertex* a, const Vertex* b);
};

#endif
