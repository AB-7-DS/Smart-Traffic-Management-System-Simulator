#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
using namespace std;

// Forward declaration of the Accident_roads class
class Accident_roads;

/**
 * @class Vertex
 * @brief Represents an intersection in the road network.
 * 
 * The Vertex class stores the details of an intersection (such as its name and blockage status)
 * and maintains a list of outgoing edges representing the roads connecting the intersection to others.
 */
class Vertex {
public:
    std::string name;         /**< Intersection name */
    
    struct EdgeNode* edges;   /**< Linked list of edges (adjacency list) */

    /**
     * @brief Constructs a Vertex object.
     * @param name The name of the intersection.
     */
    Vertex(const std::string& name);
  
};

/**
 * @class Edge
 * @brief Represents a road between two intersections.
 * 
 * An Edge object stores information about a road between two intersections, including the 
 * destination intersection and the travel time between them.
 */
class Edge {
public:
    Vertex* destination;      /**< Destination vertex (intersection) */
    int travelTime;           /**< Travel time to the destination */
    bool blocked;             /**< Whether the Edge is blocked or not */
    bool underRepaired;       /**< Whether the Edge is under repair */

    /**
     * @brief Checks if the edge is blocked.
     * @return true if the edge is blocked, false otherwise.
     */
    bool isBlocked() const;

    /**
     * @brief Checks if the Edge is under repair.
     * @return true if the edge is under repair, false otherwise.
     */
    bool isUnderRepaired() const;

    /**
     * @brief Sets the blocked status of the edge.
     * @param status The new blocked status (true for blocked, false for not blocked).
     */
    void setBlocked(bool status);

    /**
     * @brief Sets the under-repair status of the edge.
     * @param status The new under-repair status (true for under repair, false for not under repair).
     */
    void setUnderRepaired(bool status);
    
    /**
     * @brief Constructs an Edge object.
     * @param destination The destination intersection.
     * @param travelTime The travel time to the destination.
     */
    Edge(Vertex* destination, int travelTime);
};

/**
 * @class EdgeNode
 * @brief Represents a node in the adjacency list for edges.
 * 
 * An EdgeNode is used to store an Edge in the adjacency list of a vertex. It also maintains 
 * a pointer to the next EdgeNode in the list, allowing multiple edges to be linked together.
 */
class EdgeNode {
public:
    Edge* edge;              /**< The edge */
    EdgeNode* next;          /**< Pointer to the next edge */

    /**
     * @brief Constructs an EdgeNode object.
     * @param edge The edge that this node will represent.
     */
    EdgeNode(Edge* edge);
};

/**
 * @class VertexNode
 * @brief Represents a node in the adjacency list for vertices.
 * 
 * A VertexNode is used to store a Vertex in the adjacency list of the graph. It also maintains 
 * a pointer to the next VertexNode, allowing multiple vertices to be linked together in the graph.
 */
class VertexNode {
public:
    Vertex* vertex;          /**< The vertex */
    VertexNode* next;        /**< Pointer to the next vertex */

    /**
     * @brief Constructs a VertexNode object.
     * @param vertex The vertex that this node will represent.
     */
    VertexNode(Vertex* vertex);
};

/**
 * @class Graph
 * @brief Represents the road network as a graph.
 * 
 * The Graph class manages the entire road network, consisting of vertices (intersections) and edges 
 * (roads connecting the intersections). It provides methods for adding vertices and edges, 
 * displaying the road statuses, and marking intersections as blocked.
 */
class Graph {
public:
    VertexNode* headVertex;  /**< Head of the linked list for vertices */

    /**
     * @brief Constructs an empty Graph object.
     */
    Graph();

    /**
     * @brief Destructor for the Graph object.
     */
    ~Graph();

    /**
     * @brief Adds a vertex (intersection) to the graph.
     * @param name The name of the new intersection.
     */
    void addVertex(const std::string& name);

    /**
     * @brief Finds a vertex by its name.
     * @param name The name of the vertex to find.
     * @return A pointer to the Vertex object if found, or nullptr if not found.
     */
    Vertex* findVertex(const std::string& name);

    /**
     * @brief Removes a vertex (intersection) from the graph.
     * @param name The name of the vertex to remove.
     */
    void removeVertex(const string& name);

    /**
     * @brief Adds a road (edge) between two intersections.
     * @param start The name of the starting intersection.
     * @param end The name of the destination intersection.
     * @param travelTime The travel time between the two intersections.
     */
    void addEdge(const std::string& start, const std::string& end, int travelTime);

    /**
     * @brief Removes a road (edge) between two intersections.
     * @param start The name of the starting intersection.
     * @param end The name of the destination intersection.
     */
    void removeEdge(const string& start, const string& end);

    /**
     * @brief Loads road network data from a file.
     * @param filename The name of the CSV file to load road data from (default is "road_network.csv").
     */
    void loadRoadData(const std::string& filename = "road_network.csv");

    /**
     * @brief Displays the current statuses of all roads in the graph.
     */
    void displayRoadStatuses();

    /**
     * @brief Marks the specified intersections as blocked or unblocked.
     * @param intersection1 The name of the first intersection.
     * @param intersection2 The name of the second intersection.
     * @param isBlocked The new blocked status (true if blocked, false if unblocked).
     */
    void markEdgeAsBlocked(const string& intersection1, const string& intersection2, bool isBlocked);

    /**
     * @brief Marks the specified Edges as under repair or not.
     * @param intersection1 The name of the first intersection.
     * @param intersection2 The name of the second intersection.
     * @param isUnderRepaired The new under-repair status (true if under repair, false if not).
     */
    void markEdgesAsUnderRepaired(const string& intersection1, const string& intersection2, bool isUnderRepaired);

    /**
     * @brief Displays the blocked intersections in the graph.
     */
    void displayBlockedEdges();

    /**
     * @brief Adds an edge to the specified vertex.
     * @param vertex The vertex to which the edge will be added.
     * @param edge The edge to add to the vertex.
     */
    void addEdgeToVertex(Vertex* vertex, Edge* edge);

    /**
     * @brief Prints the adjacency list representation of the graph.
     */
    void printAdjacencyList();

    /**
     * @brief Checks if a vertex is blocked.
     * @param nodeName The name of the vertex to check.
     * @return true if the vertex is blocked, false otherwise.
     */
    bool isBlocked(const std::string& nodeName1, const std::string& nodeName2);

    /**
     * @brief Gets the neighbors of a specified vertex.
     * @param nodeName The name of the vertex.
     * @param neighbors Array to store the names of neighboring vertices.
     * @param count The number of neighbors found.
     */
    void getNeighbors(const std::string& nodeName, std::string* neighbors, int& count);

    /**
     * @brief Gets the travel time between two vertices.
     * @param start The starting vertex name.
     * @param end The destination vertex name.
     * @return The travel time between the two vertices, or -1 if no edge exists.
     */
    int getEdgeWeight(const std::string& start, const std::string& end);

    /**
     * @brief Gets all vertices in the graph.
     * @param vertices Array to store the names of vertices.
     * @param count The number of vertices found.
     */
    void getVertices(std::string* vertices, int& count);

    /**
     * @brief Gets the total number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    int getVertexCount();

    /**
     * @brief Gets all edges in the graph.
     * @param vertices Array to store the names of edges.
     * @param count The number of edges found.
     */
    void getAllEdges(std::string edges[][3], int& count);
};

#endif // GRAPH_H
