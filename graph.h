#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>

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
    bool blocked;             /**< Whether the intersection is blocked or not */
    struct EdgeNode* edges;   /**< Linked list of edges (adjacency list) */

    /**
     * @brief Constructs a Vertex object.
     * 
     * @param name The name of the intersection.
     */
    Vertex(const std::string& name);

    /**
     * @brief Checks if the intersection is blocked.
     * 
     * @return true if the intersection is blocked, false otherwise.
     */
    bool isBlocked() const;

    /**
     * @brief Sets the blocked status of the intersection.
     * 
     * @param status The new blocked status (true for blocked, false for not blocked).
     */
    void setBlocked(bool status);
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

    /**
     * @brief Constructs an Edge object.
     * 
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
     * 
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
     * 
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
     * 
     * Initializes an empty graph with no vertices or edges.
     */
    Graph();

    /**
     * @brief Destructor for the Graph object.
     * 
     * Deletes all the vertices and edges in the graph to free memory.
     */
    ~Graph();

    /**
     * @brief Adds a vertex (intersection) to the graph.
     * 
     * If a vertex with the same name doesn't already exist, it is created and added to the graph.
     * 
     * @param name The name of the new intersection.
     */
    void addVertex(const std::string& name);

    /**
     * @brief Finds a vertex by its name.
     * 
     * Searches the graph for a vertex with the given name.
     * 
     * @param name The name of the vertex to find.
     * @return A pointer to the Vertex object if found, or nullptr if not found.
     */
    Vertex* findVertex(const std::string& name);

    /**
     * @brief Adds a road (edge) between two intersections.
     * 
     * Adds an edge between two vertices, connecting them with the specified travel time.
     * 
     * @param start The name of the starting intersection.
     * @param end The name of the destination intersection.
     * @param travelTime The travel time between the two intersections.
     */
    void addEdge(const std::string& start, const std::string& end, int travelTime);

    /**
     * @brief Loads road network data from a file.
     * 
     * Reads road data (intersections and travel times) from a CSV file and adds vertices and edges to the graph.
     * The default file name is "road_network.csv", but another file name can be specified.
     * 
     * @param filename The name of the CSV file to load road data from (default is "road_network.csv").
     */
    void loadRoadData(const std::string& filename = "road_network.csv");

    /**
     * @brief Displays the current statuses of all roads in the graph.
     * 
     * Prints out the vertices and the edges connecting them, including the travel times.
     */
    void displayRoadStatuses();

    /**
     * @brief Marks the specified intersections as blocked or unblocked.
     * 
     * Updates the blocked status of the two intersections in the graph.
     * 
     * @param intersection1 The name of the first intersection.
     * @param intersection2 The name of the second intersection.
     * @param isBlocked The new blocked status (true if blocked, false if unblocked).
     */
    void markIntersectionsAsBlocked(const std::string& intersection1, const std::string& intersection2, bool isBlocked);

    /**
     * @brief Displays the blocked intersections in the graph.
     * 
     * Prints the names of all intersections that are currently blocked.
     */
    void displayBlockedIntersections();

    /**
     * @brief Displays the status of each intersection in the graph.
     * 
     * Prints the name of each intersection and its current blocked status.
     */
    void displayIntersectionStatus();

private:
    /**
     * @brief Adds an edge to the specified vertex.
     * 
     * Adds an Edge object to the adjacency list of the specified vertex.
     * 
     * @param vertex The vertex to which the edge will be added.
     * @param edge The edge to add to the vertex.
     */
    void addEdgeToVertex(Vertex* vertex, Edge* edge);
};

#endif // GRAPH_H
