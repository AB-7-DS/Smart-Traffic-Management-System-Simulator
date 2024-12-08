// order:

// vehicle.h

// accidents.h

// roadnode.h

// congestionMaxHeap.h

// congestionMonitoring.h

// graph.h

// roadQueue.h

// route.h

// trafficsignal.h

// trafficlightmanagement

// vehicles.h

// visualizer.h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

// Forward declarations
class Visualizer;
class Graph;
class Accident_roads;
class RoadNode;


 
// VEHICLE ################################################################################

/**
 * @struct Vehicle
 * @brief A structure representing a vehicle with details about its route and priority.
 */
struct Vehicle {
    std::string vehicleID; //<The unique identifier for the vehicle
    const std::string startIntersection; //<The starting intersection for the vehicle's route never to be changed
    const std::string endIntersection; //<The ending intersection for the vehicle's route never to be changed
    std::string priorityLevel; //<The priority level of the vehicle (e.g., high, low)
    std::string* path; //<The path the vehicle will take to reach its destination.
    int currentIntersectionInPath; //< an index in the path array that represents the current intersection the vehicle is at. the next intersection is at currentIntersectionInPath + 1
    int pathLength; //<The length of the path array
    bool presetPath; //<A boolean to check if the path is preset or not    
    /**
     * @brief Pointer to the next vehicle in a linked list.
     */
    Vehicle *next;

    
    /**
     * @brief Constructs a Vehicle with given attributes.
     * @param vehicleID The unique identifier for the vehicle.
     * @param startIntersection The starting intersection for the vehicle.
     * @param endIntersection The ending intersection for the vehicle.
     * @param priorityLevel The priority level of the vehicle.
     */
    Vehicle(std::string vehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);
    /**
     * @brief updates the currentIntersectionId of the vehicle
     * @param nextIntersectionId  The id of the next intersection the vehicle will move to
     * if the nextIntersectionId is not provided, the vehicle will move to the next intersection in the path only if it is preset
     * 
     */
    void moveForward(std::string nextIntersectionId = "");
    /**
     * @brief prints the details of the vehicle
     * 
     */
    void printVehicle();
    /**
     * @brief sets the path of the vehicle
     * 
     * @param path the path the vehicle will take
     * @note if the initial intersection of the vehicle is "A" the path must be "ABC.."
     * but it cannot be "BC.."
     * 
     * @note the path must be preset before the vehicle starts moving
     * 
     */
    void setPath(std::string path);
    /**
     * @brief prints the path of the vehicle
     * 
     */
    void printPath();
    
};




// ACCIDENTS ########################################################################33

/**
 * @class Accident_roads
 * @brief Class to handle accidents and road closures.
 * 
 * This class manages the data related to accidents or road closures that affect the road network. 
 * It maintains a linked list of accident records and provides methods to load, mark, and display blocked intersections.
 */
class Accident_roads {
private:
    /**
     * @struct AccidentNode
     * @brief Represents a record of an accident or road closure.
     * 
     * Each node in the linked list stores information about an accident/road closure, including the 
     * affected intersections and whether the road is blocked or not.
     */
    struct AccidentNode {
        std::string intersection1;  /**< The name of the first intersection involved in the incident */
        std::string intersection2;  /**< The name of the second intersection involved in the incident */
        bool isBlocked;            /**< Whether the road between the intersections is blocked or not */
        AccidentNode* next;        /**< Pointer to the next accident node in the list */

        /**
         * @brief Constructor for an AccidentNode.
         * 
         * @param i1 The name of the first intersection.
         * @param i2 The name of the second intersection.
         * @param blocked Whether the road between the two intersections is blocked.
         */
        AccidentNode(const std::string& i1, const std::string& i2, bool blocked)
            : intersection1(i1), intersection2(i2), isBlocked(blocked), next(nullptr) {}
    };

    AccidentNode* head;  /**< Head of the linked list of blocked accident nodes */
    AccidentNode* underRepairHead;  /**< Head of the linked list of under repair accident nodes */

public:
    void blockRoad(const std::string& start, const std::string& end, Graph& cityGraph);
    /**
     * @brief Default constructor for the Accident_roads class.
     * 
     * Initializes an empty list of accident records.
     */
    Accident_roads();

    /**
     * @brief Destructor for the Accident_roads class.
     * 
     * Frees any memory used by the linked list of accident records.
     */
    ~Accident_roads();

    /**
     * @brief Load road closure data from a file and update the graph.
     * 
     * This function reads road closure data from a file (such as a CSV file) and updates the 
     * given graph by marking the affected intersections as blocked or unblocked.
     * 
     * @param graph The graph containing intersections and roads to be updated with road closures.
     */
    void loadRoadData(Graph& graph);

    /**
     * @brief Mark intersections as blocked or unblocked in the graph.
     * 
     * This function updates the blocked status of the roads between the specified intersections 
     * in the given graph. It ensures that the affected roads are marked as either blocked or unblocked.
     * 
     * @param graph The graph containing the intersections and roads.
     * @param intersection1 The name of the first intersection involved in the road closure.
     * @param intersection2 The name of the second intersection involved in the road closure.
     * @param isBlocked The new status of the road (true if blocked, false if unblocked).
     */
    void markIntersectionsAsBlocked(Graph& graph, const std::string& intersection1, const std::string& intersection2, bool isBlocked);

    /**
     * @brief Display the blocked intersections in the graph.
     * 
     * This function prints the names of all intersections that are currently blocked in the graph.
     * 
     * @param graph The graph containing the intersections and their blocked status.
     */
    void displayBlockedIntersections(Graph& graph);

    /**
     * @brief Display the under-repair intersections in the graph.
     * 
     * This function prints the names of all intersections that are currently under repair in the graph.
     * 
     * @param graph The graph containing the intersections and their under-repair status.
     */
    void displayUnderRepairIntersections(Graph& graph);

    /**
     * @brief Display the blocked roads in the network.
     * 
     * This function prints the list of roads that are currently blocked.
     */
    void displayBlockedRoads();

    /**
     * @brief Display the under-repair roads in the network.
     * 
     * This function prints the list of roads that are currently under repair.
     */
    void displayUnderRepairRoads();

    
};


// ROADNODE ####################################################################

/**
 * @brief The node for the Hash Table containing a key-value pair and a pointer for chaining
 */
struct RoadNode {
    char path[2]; //< Start and end Intersection
    int carCount; //< The number of cars on the road
    RoadNode* right; //< Pointer for chaining in case of collisions in hashtables. Points to right child in minheap
    RoadNode* left; //< Pointer for the left child in minheap
    RoadNode* parent; //< Pointer to the parent node in minheap
    RoadNode* next; //< Pointer to the next node in the queue
    /**
     * @brief Constructor to initialize a RoadNode
     * @param s Start intersection
     * @param e End intersection
     * @param v Number of cars on the road
     */
    RoadNode(char s = '\0', char e = '\0', int v = 0) {
        path[0] = s;
        path[1] = e;
        carCount = v;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
        next = nullptr;
    }
};


// CONGESTIONMAXHEAP ####################################################################
/**
 * @class CongestionMaxHeap
 * @brief A class to represent a max heap specifically for managing road congestion data.
 * 
 * This class provides functionalities to create and manage a max heap of RoadNode objects,
 * which are used to monitor and manage road congestion.
 */
class CongestionMaxHeap{
    private:
        RoadNode* root; //< Pointer to the root of the heap
        
        /**
         * @brief Performs an inorder traversal of the heap.
         * 
         * This is a helper function used for debugging and visualization purposes.
         * 
         * @param root The root node of the heap/subtree.
         */
        void inorder(RoadNode* root);
    public:
        /**
         * @brief Construct a new Congestion Max Heap object
         * 
         * Initializes root to nullptr
         * 
         */
        CongestionMaxHeap();
        /**
         * @brief Makes a max heap from the roads in the hashtable array
         * 
         * @param hashTableArray hashTableArray is from the congestion monitoring class
         * @param size size of the hashtable array
         */
        void makeHeap(RoadNode* hashTableArray, int size);
        /**
         * @brief Inserts a new RoadNode into the heap
         * 
         * inserts preserving the structure property of the heap and heapifies up after insertion
         * 
         * @param newNode The RoadNode to be inserted
         */
        void insert(RoadNode* newNode);
        /**
         * @brief Heapifies up the heap after insertion
         * 
         * @param newNode The RoadNode to be heapified up
         */
        void heapifyUp(RoadNode*& newNode);
        /**
         * @brief Prints the heap 
         * 
         * Uses BFS to print the heap
         * 
         */
        void printHeap();
        /**
         * @brief returns root of the heap without removing it
         * 
         * @return RoadNode* 
         */
        RoadNode* mostCongested();
        /**
         * @brief Prints the heap inorder
         * 
         * 
         */
        void inorder();
        /**
         * @brief Function to heapify down the heap
         * 
         * @param node 
         */
        void heapifyDown(RoadNode* node);

};



// CONGESTIONMONITORING ####################################################################

const int HASH_TABLE_SIZE = 100;

/**
 * @class CongestionMonitoring
 * @brief A class for tracking the number of vehicles on a road using a hash table.
 * 
 * This class provides functionalities to create, update, and manage a hash table
 * that tracks the number of vehicles on different roads.
 */
class CongestionMonitoring { 
    
    private:
        const int hashTableSize; //< Hash table array size

        // private functions -----------------------------------------------------------
        /**
         * @brief Adds a road segment to the hash table.
         * 
         * This function adds a road segment defined by the start and end points to the hash table.
         * 
         * @param index The index in the hash table.
         * @param start The starting point of the road segment.
         * @param end The ending point of the road segment.
         * @param right An optional parameter for additional data (default is 0).
         */
        void addToTable(int index, char start, char end, int right = 0);

        /**
         * @brief Computes the hash value for a road segment.
         * 
         * This function computes a hash value for a road segment defined by the start and end points.
         * 
         * @param start The starting point of the road segment.
         * @param end The ending point of the road segment.
         * @return The computed hash value.
         */
        int hashFunction(char start, char end);
        /**
         * @brief Retrieves the starting point of a road segment from the hash table.
         * 
         * This function retrieves the starting point of a road segment from the hash table using the index.
         * 
         * @param index The index in the hash table.
         * @param right An optional parameter for additional data (default is 0).
         * @return The starting point of the road segment.
         */
        char getStart(int index, int right);

        /**
         * @brief Retrieves the ending point of a road segment from the hash table.
         * 
         * This function retrieves the ending point of a road segment from the hash table using the index.
         * 
         * @param index The index in the hash table.
         * @param right An optional parameter for additional data (default is 0).
         * @return The ending point of the road segment.
         */
        char getEnd(int index, int right);
        // ----------------------------------------------------------------------------
    
    public:
        RoadNode hashTable[HASH_TABLE_SIZE]; //< RoadNode array
        
        /**
         * @brief Construct a new Congestion Monitoring object.
         * 
         * Initializes the hash table and populates it using the provided list of vehicles.
         * 
         * @param vehiclesHead Pointer to the head of the linked list of vehicles.
         */
        CongestionMonitoring(Vehicle* vehiclesHead);
         /**
         * @brief Creates the hash table from the list of vehicles.
         * 
         * This function populates the hash table with road segments based on the provided list of vehicles.
         * 
         * @param vehiclesHead Pointer to the head of the linked list of vehicles.
         */
        void makeHashTable(Vehicle* vehiclesHead);
           /**
         * @brief Updates the hash table with the new position of a vehicle.
         * 
         * This function updates the hash table to reflect the new position of a vehicle.
         * 
         * @param prevPos Pointer to the previous position of the vehicle.
         * @param currentPos Pointer to the current position of the vehicle.
         */
        void updateHashTable(Vehicle* prevPos, Vehicle* currentPos);

        /**
         * @brief Prints the contents of the hash table.
         * 
         */
        void printHashTable();
        /**
         * @brief Deletes the hash table.
         * 
         * This function clears the hash table, removing all road segments.
         */
        void deleteTable();

        /**
         * @brief Finds a road segment in the hash table.
         * 
         * This function searches for a road segment defined by the start and end points in the hash table.
         * 
         * @param start The starting point of the road segment.
         * @param end The ending point of the road segment.
         * @return Pointer to the RoadNode representing the road segment, or nullptr if not found.
         */
        RoadNode* findRoadNode(char start, char end);

        /**
         * @brief Get the updated Travel Time in seconds after considering the congestion and the time of the day (time elapsed)
         * 
         * @param start 
         * @param end 
         * @param prevTime 
         * @return int 
         */
        int getTravelTime(char start, char end, int prevTime);
        /**
         * @brief Get the Travel Time in seconds between two points
         * 
         * this reutrns the travel time between two points in seconds after considering the congestion and the time of the day
         * 
         * @param start 
         * @param end 
         * @param cityGraph 
         * @return int 
         */
        int getTravelTime(char start, char end, Graph& cityGraph);
        /**
         * @brief Returns the performance metric number of congestion events
         * 
         * @return int 
         */
        int numberOfCongestionEvents();
       
        
};



// GRAPH #################################################################################


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



// ROADQUEUE ####################################################################
/**
 * @class RoadQueue
 * @brief A class to represent a queue specifically for managing RoadNode objects.
 * 
 * This class provides functionalities to create and manage a queue of RoadNode objects,
 * which can be used for various purposes such as managing road segments in a traffic system.
 */
class RoadQueue{
      private:
            RoadNode* head; ///< Pointer to the head of the queue
            RoadNode* tail; ///< Pointer to the tail of the queue
    public:
        /**
         * @brief Construct a new RoadQueue object.
         * 
         * Initializes the head and tail to nullptr, indicating an empty queue.
         */
        RoadQueue();

        /**
         * @brief Adds a new RoadNode to the end of the queue.
         * 
         * This function inserts a new RoadNode at the tail of the queue.
         * 
         * @param newNode The RoadNode to be added to the queue.
         */
        void enqueue(RoadNode*& newNode);

        /**
         * @brief Removes and returns the RoadNode at the front of the queue.
         * 
         * This function removes the RoadNode at the head of the queue and returns it.
         * 
         * @return The RoadNode at the front of the queue.
         */
        RoadNode* dequeue();

        /**
         * @brief Prints the contents of the queue.
         * 
         * This function prints the current state of the queue for debugging and visualization purposes.
         */
        void printQueue();

        /**
         * @brief Checks if the queue is empty.
         * 
         * This function checks whether the queue is empty.
         * 
         * @return true if the queue is empty, false otherwise.
         */
        bool isEmpty();
};


// ROUTE ####################################################################
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

// TRAFFICSIGNAL ####################################################################
/**
 * @class TrafficSignal
 * @brief A class to represent a traffic signal at an intersection.
 * 
 * This class models a traffic signal at an intersection, 
 * providing functionality to manage its state ("red", "yellow", or "green"), 
 * the associated Intersection ID, and the duration for which each state is maintained. 
 * It also offers methods for displaying and printing the signal's information.
 * 
 * @details The TrafficSignal class maintains the state of the signal ( "red", "yellow", or "green"),
 * the ID of the intersection it belongs to, and the duration for which the signal state is maintained.
 * 
 * @note The display method is intended for future implementation to show the signal on a graphical interface.
 * 
 * @var std::string TrafficSignal::state
 * The current state of the traffic signal ("red", "yellow", or "green").
 * 
 * @var int TrafficSignal::intersectionId
 * The ID of the intersection for which the signal is.
 * 
 * @var int TrafficSignal::duration
 * The duration for which the signal state is maintained, in seconds.
 * 
 * @var int TrafficSignal::transitionTime
 * The time the "yellow" state is maintained, in seconds.
 * 
 * @fn TrafficSignal::TrafficSignal(std::string state, int intersectionId, int duration, int transitionTime)
 * @brief Constructor to initialize the TrafficSignal object with the given state, intersectionId, and duration.
 * @param state The initial state of the signal ("red", "yellow", or "green"). Default value is "red".
 * @param intersectionId The ID of the intersection for which the signal is. Default value is -1.
 * @param duration The duration for which the signal state is maintained, in seconds. Default value is 60.
 * @param transitionTime The time the "yellow" state is maintained, in seconds. Default value is 5.
 * 
 * @fn std::string TrafficSignal::getState()
 * @brief Get the current state of the signal.
 * @return The current state of the signal as a string.
 * 
 * @fn void TrafficSignal::setState(std::string state)
 * @brief Set the state of the signal.
 * @param state The new state of the signal ("red", "yellow", or "green").
 * 
 * @fn void TrafficSignal::display()
 * @brief Displays the signal on the graphical interface.
 * @note This method will be implemented in the future.
 * 
 * @fn void TrafficSignal::print()
 * @brief Print the signal state, intersectionId, and duration on the console.
 * 
 * @fn int TrafficSignal::getIntersectionId()
 * @brief Get the Intersection ID of the signal.
 * @return The Intersection ID as an integer.
 * 
 * @fn int TrafficSignal::getDuration()
 * @brief Get the duration for which the signal state is maintained.
 * @return The duration in seconds.
 * 
 * @fn int TrafficSignal::getTransitionTime()
 * @brief Get the time the "yellow" state is maintained.
 * @return The transition time in seconds.
 * 
 * @fn void TrafficSignal::advanceState()
 * @brief Advance the state of the traffic signal to the next state in the sequence "red" -> "yellow" -> "green" -> "yellow" -> "red".
 */
class TrafficSignal {
      public:
            std::string state; //<  "red", "yellow", "green"
            int transitionTime; //< the time the "yellow" state is maintained

            char intersectionId; //< ID of the intersection for which the signal is
            int duration; //< duration a state is to be maintained in seconds
            TrafficSignal* next; //< pointer to the next signal in the list
            int temp; //< temporary variable to store the duration the current state has been maintained



            /**
             * @brief Initializes a TrafficSignal instance with the specified state ("red", "yellow", or "green"), 
             * Intersection ID, and duration. 
             * Defaults to "red" state, -1 Intersection ID, and 60 seconds duration.
             * 
             * @param state string "red", "yellow" or "green". Default value is "red"
             * @param intersectionId char ID of the intersection for which the signal is. Default value is '-'
             * @param duration int duration a state is to be maintained in seconds. Default value is 60
             * @param transitionTime int the time the "yellow" state is maintained. Default value is 5
             */
            TrafficSignal(std::string state = "red", char intersectionId = '-', int duration = 60, int transitionTime = 5);

            /**
             * @brief Retrieves the current state of the traffic signal
             * @return string "red", "yellow" or "green" 
             */
            std::string getState();

            /**
             * @brief Updates the state of the traffic signal
             * @param state A string representing the new state ("red", "yellow" or "green")
             */
            void setState(std::string state);

            /**
             * @brief Intended for displaying the traffic signal on a graphical user interface (GUI). This method is currently not implemented.
             */
            void display();

            /**
             * @brief Outputs the traffic signal's state, Intersection ID, and duration in a human-readable format. 
             * 
             * Example output: "Signal State: red, Intersection ID: 1, Duration: 60s"
             * 
             */
            void print();

            /**
             * @brief Retrieve the ID of the intersection for which the signal is
             * @return int Intersection ID
             * 
             */
            int getIntersectionId();

            /**
             * @brief Retrieve the duration for which a signal state is maintained
             * @return int Duration in seconds
             */
            int getDuration();

            /**
             * @brief Retrieve the time the "yellow" state is maintained
             * @return int Transition time in seconds
             */
            int getTransitionTime();

            /**
             * @brief Advance the state of the traffic signal to the next state in the sequence "red" -> "yellow" -> "green" -> "red"
             * 
             * this function must be called continuously in the mainloop to change the state of the signal
             */
            void advanceState(Visualizer* visualizer);

            /**
             * @brief Turn the traffic signal from red to green
             */
            void turnGreen(Visualizer* visualizer);
};



// TRAFFICLIGHTMANAGEMENT ####################################################################
/**
 * @class TrafficLightManagement
 * @brief Manages the traffic lights at each intersection.
 * 
 * The TrafficLightManagement class is responsible for managing the traffic lights at each intersection.
 * It maintains a list of traffic signals and updates them based on the current traffic conditions.
 */

const std::string SIGNALS_FILE = "dataset/traffic_signals.csv";
class TrafficLightManagement {
      private:
            TrafficSignal* headSignal;
      public:
            /**
             * @brief Constructor for TrafficLightManagement class.
             * 
             * Initializes the headSignal pointer to NULL.
             */
            TrafficLightManagement();
            /**
             * @brief Assigns a traffic signal to each intersection. 
             * 
             * Loads the time duration for each signal from the csv file.
             * 
             * 
             */
            void makeTrafficSignals();
            /**
             * @brief Updates the traffic signals based on the congestion monitoring data.
             * 
             * @param congestionMonitoring The congestion monitoring hash table.
             */
            void updateTrafficSignals(CongestionMonitoring& ht);
            /**
             * @brief Adds a signal to the list of traffic signals.
             * 
             * @param signal The signal to be added.
             */
            void addSignal(TrafficSignal* signal);
            /**
             * @brief Prints the time the green state is to be maintained of the traffic signals.
             * 
             */
            void printGreenTimes();
            /**
             * @brief Returns the signal for a given intersection.
             * 
             * @param intersection The intersection for which the signal is to be returned.
             * @return TrafficSignal* The signal for the given intersection.
             */
            TrafficSignal* getSignal(std::string intersection);
            /**
             * @brief Manages the traffic lights at each intersection
             * 
             * Call this function continuously to automatically manage the traffic lights.
             * 
             * @param mostCongestedIntersection The intersection with the most congestion.
             * @param vs The visualizer object.
             */
            void manageTrafficLights(char mostCongestedIntersection, Visualizer* vs);
};

// VEHICLES ####################################################################
/**
 * @class Vehicles
 * @brief A class to manage a linked list of vehicles.
 */
class Vehicles {
private:
    Vehicle* head; // Pointer to the head of the linked list

public:
/**
 * @brief Constructor for Vehicles class.
 */
Vehicles();

/**
 * @brief Destructor for Vehicles class.
 */
~Vehicles();

/**
 * @brief Inserts a vehicle at the head of the linked list.
 * @param VehicleID The ID of the vehicle.
 * @param startIntersection The starting intersection of the vehicle.
 * @param endIntersection The ending intersection of the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
void insertAtHead(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Enqueues a vehicle at the end of the linked list.
 * @param VehicleID The ID of the vehicle.
 * @param startIntersection The starting intersection of the vehicle.
 * @param endIntersection The ending intersection of the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
void enqueue(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Inserts a vehicle after a specific position in the linked list.
 * @param position The position after which the vehicle will be inserted.
 * @param VehicleID The ID of the vehicle.
 * @param startIntersection The starting intersection of the vehicle.
 * @param endIntersection The ending intersection of the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 * @return True if the insertion was successful, false otherwise.
 */
bool insertAfterPosition(int position, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Inserts a vehicle after a specific vehicle ID in the linked list.
 * @param ID The ID of the vehicle after which the new vehicle will be inserted.
 * @param VehicleID The ID of the new vehicle.
 * @param startIntersection The starting intersection of the new vehicle.
 * @param endIntersection The ending intersection of the new vehicle.
 * @param priorityLevel The priority level of the new vehicle.
 * @return True if the insertion was successful, false otherwise.
 */
bool insertAfterID(std::string ID, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Deletes the vehicle at the start of the linked list.
 */
void deleteAtStart();

/**
 * @brief Deletes the vehicle at the end of the linked list.
 * @return True if the deletion was successful, false otherwise.
 */
bool deleteAtEnd();

/**
 * @brief Deletes the vehicle at a specific index in the linked list.
 * @param position The index of the vehicle to be deleted.
 * @return True if the deletion was successful, false otherwise.
 */
bool deleteAtIndex(int position);

/**
 * @brief Deletes the vehicle with a specific ID in the linked list.
 * @param ID The ID of the vehicle to be deleted.
 * @return True if the deletion was successful, false otherwise.
 */
bool deleteAtID(std::string ID);

/**
 * @brief Checks if the linked list is empty.
 * @return True if the linked list is empty, false otherwise.
 */
bool isEmpty();

/**
 * @brief Prints the details of all vehicles in the linked list.
 */
void printVehicles();

/**
 * @brief Finds the position of a vehicle with a specific ID in the linked list.
 * @param vehicleID The ID of the vehicle to be found.
 * @return The position of the vehicle in the linked list, or -1 if not found.
 */
int findIDInVehicles(std::string vehicleID);

/**
 * @brief Loads and reads vehicle data from CSV files.
 */
void loadAndReadCSVs();

/**
 * @brief Gets the head of the linked list.
 * @return A reference to the pointer to the head of the linked list.
 */
Vehicle*& getHead();

/**
 * @brief Adds paths to the vehicles using GPS data.
 * @param gps The GPS object containing path data.
 */
void addPaths(GPS& gps);

    
};

// VISUALIZER ####################################################################

class Visualizer {
private:
    sf::RenderWindow window;  
    sf::Sprite roadSprite;
    sf::Sprite vehicleSprite;
    sf::Font font;
    sf::Texture roadTexture;
    sf::Texture vehicleTexture;
    sf::Clock clock; //<Measures elapsed time

public:
/**
 * @class Visualizer
 * @brief A class to handle the visualization of the traffic management system.
 *
 * This class is responsible for rendering the simulation of the traffic management system,
 * including roads and vehicles, using the SFML library.
 */

/**
 * @brief Constructor for the Visualizer class.
 *
 * Initializes the render window, loads textures, and sets up sprites.
 */
Visualizer();

/**
 * @brief Draws the entire simulation graph.
 *
 * @param graph The graph representing the traffic network.
 * @param vehicles The collection of vehicles to be drawn.
 * @param traffic The traffic light management system.
 * @param ht The congestion monitoring system.
 * @param accidentManager The accident management system.
 */
void drawSimulation(Graph &graph, Vehicles &vehicles, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager);

/**
 * @brief Draws vehicles at the specified intersection.
 *
 * @param vehicles The collection of vehicles to be drawn.
 * @param intersection The name of the intersection where vehicles are to be drawn.
 * @param position The position where the vehicles should be drawn.
 * @param window The render window where the vehicles will be drawn.
 */
void drawVehicles(Vehicles &vehicles, const std::string &intersection, const sf::Vector2f &position, sf::RenderWindow &window);

/**
 * @brief Gets the elapsed time in seconds since the last clock reset.
 *
 * @return The elapsed time in seconds.
 */
float getElapsedTimeInSeconds();

/**
 * @brief Chooses a color for the edge and vertex based on traffic conditions.
 *
 * @param edge The edge node representing the road segment.
 * @param vertex The vertex representing the intersection.
 * @param traffic The traffic light management system.
 * @param ht The congestion monitoring system.
 * @param accidentManager The accident management system.
 * @return The chosen color.
 */
sf::Color choseColor(EdgeNode *edge, Vertex *vertex, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager);

   
};



/**
 * @brief Main entry point of the program.
 *
 * This function creates a graph representing a city's road network, loads road data from a CSV file,
 * marks intersections as blocked based on accident data, and displays the updated road status.
 * It demonstrates how to interact with the Graph and Accident_roads classes.
 */

int main() {
    // Object Initialization
    Graph cityGraph;
    Vehicles vehicles;
    Accident_roads accidentManager;
    GPS gps(&cityGraph);
    // Loading Data from a CSV file
    cityGraph.loadRoadData("dataset/road_network.csv");
    accidentManager.loadRoadData(cityGraph);
    vehicles.loadAndReadCSVs();
    vehicles.addPaths(gps);
    CongestionMonitoring ht(vehicles.getHead());
    ht.makeHashTable(vehicles.getHead());
  
    TrafficLightManagement traffic;
    traffic.makeTrafficSignals();
    CongestionMaxHeap maxHeap;
    maxHeap.makeHeap(ht.hashTable, HASH_TABLE_SIZE);    
   
   


    string start,end,path;
    int choice,c;
    do {
        // Display the menu
        cout << "------ Simulation Dashboard ------\n";
        cout << "1. Display City Traffic Network\n";
        cout << "2. Display Traffic Signal Status\n";
        cout << "3. Display Congestion Status\n";
        cout << "4. Display Blocked Roads\n";
        cout << "5. Handle Emergency Vehicle Routing\n";
        cout << "6. Block Road due to Accident\n";
        cout << "7. Simulate Vehicle Routing\n";
        cout << "8. Add Intersection\n";
        cout << "9. Remove Intersection\n";
        cout << "10. Add Road\n";
        cout << "11. Remove Road\n";
        cout << "12. Exit Simulation\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle menu choices using switch-case
        switch (choice) {
            case 1:
              
                do{
                    cout << "Enter your Choice :\n 1.Road Network\t2.Road Status\t0.Exit\nYour choice: ";
                    cin >> c;
                    if(c==1)
                    {
                       cityGraph.printAdjacencyList();
                    }
                    else if(c==2)
                    {
                        cityGraph.displayRoadStatuses();
                    }
                    else if(c==0)
                    {

                        cout << "Exiting ......";
                       
                    }
                    else
                        cout<<"Invalid Choice!. Try again!\n";
                }while(c!=0);    
                break;
            case 2:
                traffic.printGreenTimes();
                break;
            case 3:
                ht.printHashTable();
            cout << "\nMost congested road: " << maxHeap.mostCongested()->path[0] <<" to "<< maxHeap.mostCongested()->path[1]<< endl;
                break;
            case 4:
             
                do{
                    cout << "Which Road to display?:\n 1.Blocked roads\t2.Under Repair Roads\t0.Exit\nYour choice: ";
                    cin >> c;
                    if(c==1)
                    {
                        accidentManager.displayBlockedRoads();
                    }
                    else if(c==2)
                    {
                        accidentManager.displayUnderRepairRoads();
                    }
                    else if(c==0)
                    {

                        cout << "Exiting ......";
                       
                    }
                    else
                        cout<<"Invalid Choice!. Try again!\n";
                }while(c!=0);    
                break;
               
                
                break;
            case 5:
                cout << "Enter the start intersection : ";
                cin >> start;
                cout << "Enter the end intersection : ";
                cin >> end;
                //will added check function to check if vehicle is emergency
                path = gps.rerouteEmergencyVehicle(start, end);
                  cout << "Emergency Vehicle is being routed...... " <<  endl;
                cout << "Emergency Vehicle Path: " << path << endl;
                break;
            case 6: {
                cout << "Enter the start intersection to block: ";
                cin >> start;
                cout << "Enter the end intersection to block: ";
                cin >> end;

                // Use the Accident_roads member function to block the road
                accidentManager.blockRoad(start, end, cityGraph);
                break;
            }
            case 7:
                
                do{
                    cout << "Enter Type of Algorithm :\n 1.DFS\t2.Dijkstra\t0.Exit\nYour choice: ";
                    cin >> c;
                    if(c==1)
                    {
                        cout << "Enter the start intersection : ";
                        cin >> start;
                        cout << "Enter the end intersection : ";
                        cin >> end;
                        gps.printAllPaths(start, end);
                    }
                    else if(c==2)
                    {

                        cout << "Enter the start intersection : ";
                        cin >> start;
                        cout << "Enter the end intersection : ";
                        cin >> end;
                        
                    gps.printAllPathsDijkstra(start,end);
                    }
                    else if(c==0)
                    {

                        cout << "Exiting ......";
                       
                    }
                    else
                        cout<<"Invalid Choice!. Try again!\n";
                }while(c!=0);    
                break;
                   case 8: {
            string intersection;
            cout << "Enter the name of the intersection to add: ";
            cin >> intersection;
            cityGraph.addVertex(intersection);
            break;
        }
        case 9: {
            string intersection;
            cout << "Enter the name of the intersection to remove: ";
            cin >> intersection;
            cityGraph.removeVertex(intersection);
            break;
        }
        case 10: {
            string start, end;
            int travelTime;
            cout << "Enter the start intersection: ";
            cin >> start;
            cout << "Enter the end intersection: ";
            cin >> end;
            cout << "Enter the travel time: ";
            cin >> travelTime;
            cityGraph.addEdge(start, end, travelTime);
            break;
        }
        case 11: {
            string start, end;
            cout << "Enter the start intersection to remove the road: ";
            cin >> start;
            cout << "Enter the end intersection to remove the road: ";
            cin >> end;
            cityGraph.removeEdge(start, end);
            break;
        }
        case 12:
            cout << "Exiting Simulation. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
    }

    cout << endl;
} while (choice != 12);
    
    Visualizer visualizer;
    Vehicle *temp = vehicles.getHead();
    while(temp!=NULL){
        //find best path for all vehicles
        string start = temp->startIntersection;
        string end = temp->endIntersection;
        string path = (gps.rerouteEmergencyVehicle(start,end));
        if(path!=""){
        temp->setPath(path);
        }
        else temp->presetPath = false;
        temp = temp->next;
    }
    visualizer.drawSimulation(cityGraph, vehicles,traffic,ht,accidentManager);
    
    return 0;
}




















// IMPLEMENTATION ####################################################################

// ###################################################################################
// -----------------------------------------------------------------------------------


// VEHICLE CLASS IMPLEMENTATION -----------------------------------------------------

Vehicle::Vehicle(std::string vehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel)
    : startIntersection(startIntersection), endIntersection(endIntersection)
{
    this->vehicleID = vehicleID;
    this->priorityLevel = priorityLevel;
    this->next = NULL;
    this->path = new std::string[1000];
    this->currentIntersectionInPath = 0;
    this->path[currentIntersectionInPath] = startIntersection;
    this->pathLength = 1;
    this->presetPath = false;
}
void Vehicle::moveForward(std::string nextIntersectionId){
    if (path[currentIntersectionInPath] == endIntersection)        
        return;
    
    if (presetPath){
        currentIntersectionInPath++;
        return;
    }
    currentIntersectionInPath++;
    path[currentIntersectionInPath] = nextIntersectionId;
    pathLength++;
}

void Vehicle::printVehicle(){
    std::cout << "Vehicle ID: " << vehicleID << std::endl;
    std::cout << "Start Intersection: " << startIntersection << std::endl;
    std::cout << "End Intersection: " << endIntersection << std::endl;
    std::cout << "Priority Level: " << priorityLevel << std::endl;
    std::cout << "Path Traversed: ";
    for(int i = 0; i <= currentIntersectionInPath; i++){
        std::cout << path[i] << " ";
    }
    std::cout << "Path: ";
    for(int i = 0; i <= pathLength; i++){
        std::cout << path[i] << " ";
    }

    std::cout << std::endl;

}

void Vehicle::setPath(std::string path){
    this->presetPath = true;
    this->pathLength = 0;
    for (int i= 0; i< path.length(); i++){
        this->path[i] = path[i];
        this->pathLength++;
    }
    this->pathLength = path.length();
}
void Vehicle::printPath(){
    std::cout << "Path: ";
    for(int i = 0; i < pathLength; i++){
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}

// -----------------------------------------------------------------------------------

// ACCIDENTS CLASS IMPLEMENTATION ##############################################################

// Constructor
Accident_roads::Accident_roads() : head(nullptr), underRepairHead(nullptr) {}

// Destructor
Accident_roads::~Accident_roads() {
    // Delete accident nodes (Blocked)
    AccidentNode* current = head;
    while (current) {
        AccidentNode* temp = current;
        current = current->next;
        delete temp;
    }

    // Delete under repair nodes
    AccidentNode* repairCurrent = underRepairHead;
    while (repairCurrent) {
        AccidentNode* temp = repairCurrent;
        repairCurrent = repairCurrent->next;
        delete temp;
    }
}

void Accident_roads::loadRoadData(Graph& graph) {
    std::ifstream file("dataset/road_closures.csv"); 
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file road_closures.csv" << std::endl;
        return;
    }

    std::string intersection1, intersection2, status;
    while (file.good()) {
        std::getline(file, intersection1, ','); 
        std::getline(file, intersection2, ',');
        std::getline(file, status);

        if (!intersection1.empty() && !intersection2.empty() && !status.empty()) {
            bool isBlocked = (status == "Blocked");

            // Create a new node for this road closure
            AccidentNode* newNode = new AccidentNode(intersection1, intersection2, isBlocked);
            
            // Insert the new node at the end of the blocked list
            if (isBlocked) {
                if (head == nullptr) {
                    head = newNode;  // If the list is empty, the new node is the first node
                } else {
                    AccidentNode* temp = head;
                    while (temp->next != nullptr) {
                        temp = temp->next;  // Traverse to the end of the list
                    }
                    temp->next = newNode;  // Insert the new node at the end
                    graph.markEdgeAsBlocked(intersection1, intersection2, true);
                }
            } else if (status == "Under Repair") {
                // Insert under repair intersections in the separate list at the end
                if (underRepairHead == nullptr) {
                    underRepairHead = newNode;  // If the list is empty, the new node is the first node
                } else {
                    AccidentNode* temp = underRepairHead;
                    while (temp->next != nullptr) {
                        temp = temp->next;  // Traverse to the end of the list
                    }
                    temp->next = newNode;  // Insert the new node at the end
                    graph.markEdgesAsUnderRepaired(intersection1, intersection2, true);
                }
                
            }

            
            
        }
    }

    file.close();
}
void Accident_roads::displayBlockedRoads() {
    std::cout << "Blocked Roads:\n";

    AccidentNode* current = head;
    if (current == nullptr) {
        std::cout << "No blocked roads.\n";
    }

    while (current) {
        std::cout << "- " << current->intersection1 << " to " << current->intersection2 << " is blocked.\n";
        current = current->next;
    }
}

void Accident_roads::displayUnderRepairRoads() {
    std::cout << "Under Repair Roads:\n";

    AccidentNode* current = underRepairHead;
    if (current == nullptr) {
        std::cout << "No roads under repair.\n";
    }

    while (current) {
        std::cout << "- " << current->intersection1 << " to " << current->intersection2 << " is under repair.\n";
        current = current->next;
    }
}

void Accident_roads::blockRoad(const std::string& start, const std::string& end, Graph& cityGraph) {
    // Check if both intersections exist in the graph
    if (cityGraph.findVertex(start) == nullptr || cityGraph.findVertex(end) == nullptr) {
        std::cout << "One or both intersections do not exist in the graph.\n";
        return;
    }

    // Mark the intersections as blocked in the graph
    cityGraph.markEdgeAsBlocked(start, end, true);

    // Add the blocked road to the accident manager
    AccidentNode* newBlockedRoad = new AccidentNode(start, end, true);
    if (head == nullptr) {
        head = newBlockedRoad;  // If the list is empty, make this the first node
    } else {
        AccidentNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;  // Traverse to the end of the list
        }
        temp->next = newBlockedRoad;  // Add the new node at the end
    }

    // Display the updated list of blocked roads
    std::cout << "\nUpdated Blocked Roads:\n";
    displayBlockedRoads();
}

// ------------------------------------------------------------------------------------------------

// CONGESTIONMAXHEAP CLASS IMPLEMENTATION ####################################################################


CongestionMaxHeap::CongestionMaxHeap(){
      root = NULL;
}

void CongestionMaxHeap::makeHeap(RoadNode* hashTableArray, int size){
      for(int i = 0; i < size; i++){
       
            RoadNode* newNode = &hashTableArray[i];
       
            if (newNode->carCount > 0){

                  insert(newNode);

                  while(newNode->right != NULL){

                        newNode = newNode->right;
                        if (newNode->carCount > 0)
                              insert(newNode);
                        
                  }

            }
      }
}

void CongestionMaxHeap::insert(RoadNode* newNode) {
    newNode->left = NULL;
    newNode->right = NULL;

    if (!root) {
        root = newNode;
        return;
    }

    RoadQueue* queue = new RoadQueue();
    queue->enqueue(root);
    RoadNode* temp = NULL;

    while (!queue->isEmpty()) {
        temp = queue->dequeue();

        if (temp->left == NULL) {
            temp->left = newNode;
            newNode->parent = temp;
            heapifyUp(newNode);
            delete queue;
            return;
        } else if (temp->right == NULL) {
            temp->right = newNode;
            newNode->parent = temp;
            heapifyUp(newNode);
            delete queue;
            return;
        } else {
            queue->enqueue(temp->left);
            queue->enqueue(temp->right);
        }
    }

    delete queue;
}

void CongestionMaxHeap::heapifyUp(RoadNode*& node) {
    while (node->parent && node->carCount > node->parent->carCount) {
        std::swap(node->path[0], node->parent->path[0]);
        std::swap(node->path[1], node->parent->path[1]);
        std::swap(node->carCount, node->parent->carCount);

        node = node->parent;
    }
}


void CongestionMaxHeap::printHeap() {
    std::cout << std::endl;
    if (root == NULL) 
        return;
    RoadQueue* queue = new RoadQueue();
    queue->enqueue(root);
    RoadNode* temp = NULL;

    while (!queue->isEmpty()) {
        temp = queue->dequeue();
        std::cout << temp->path[0] << " to " << temp->path[1] 
                  << " (Car Count: " << temp->carCount << ")\n";
        if (temp->left != NULL)
            queue->enqueue(temp->left);
        if (temp->right != NULL)
            queue->enqueue(temp->right);
    }

    std::cout << std::endl;
    delete queue;
}

void CongestionMaxHeap::heapifyDown(RoadNode* node) {
    while (node) {
        RoadNode* largest = node;

        if (node->left && node->left->carCount > largest->carCount) 
            largest = node->left;

        if (node->right && node->right->carCount > largest->carCount) 
            largest = node->right;

        if (largest != node) {
            std::swap(node->path[0], largest->path[0]);
            std::swap(node->path[1], largest->path[1]);
            std::swap(node->carCount, largest->carCount);
            node = largest;
        }
        else 
            break;
    }
}


RoadNode* CongestionMaxHeap::mostCongested(){
      return root;
}

void CongestionMaxHeap::inorder() {
      std::cout << "\n";
      inorder(root);
}
void CongestionMaxHeap::inorder(RoadNode* root) {
      if (root == NULL)
            return;
      inorder(root->left);
      std::cout << root->path[0] << " to " << root->path[1] << "\n";
      inorder(root->right);
}

// ------------------------------------------------------------------------------------------------------------


// CONGESTIONMONITORING CLASS IMPLEMENTATION ###################################################################

// private functions
int CongestionMonitoring::hashFunction(char start, char end) {
    int s, e = 0;
    if (start >= 'A' && start <= 'Z' && start >= 'A' && start <= 'Z') {
        s = start - 'A';
        e = end - 'A';
    }
    else 
        std::cerr << "Incorrect start and end intersections recieved";
    return (s*31+e)%HASH_TABLE_SIZE;
} 

char CongestionMonitoring::getStart(int index, int right) {
    // invalid param check
    if (index >= HASH_TABLE_SIZE) return '\0';

    RoadNode* temp = &hashTable[index];
    
    // right > 0 and temp->right is not a nullptr
    while( right-- && temp->right) 
        temp = temp->right;

    return temp->path[0];
}

char CongestionMonitoring::getEnd(int index, int right) {
    // invalid param check
    if (index >= HASH_TABLE_SIZE) return '\0';

    RoadNode* temp = &hashTable[index];
    
    // right > 0 and temp->right is not a nullptr
    while( right-- && temp->right) 
        temp = temp->right;

    return temp->path[1];
}

void CongestionMonitoring::addToTable(int index, char start, char end, int right) {
    // get the node at index
    RoadNode* temp = &hashTable[index];
    for (int i = 0; i<right; i++){
        if (temp->right)
            temp = temp->right;
        else {
            // add another node to the chain
            temp->right = new RoadNode();
            temp = temp->right;
            break;
        }
    }

    char s,e = '\0';
    s = getStart(index, right);
    e = getEnd(index, right);

    // case 1: the index is empty i.e it has path[0] = path[1] = '\0' and count = 0
        // make the path [0] = start and path [1] = end and count = 1
    if (s == '\0' &&  e =='\0' ) {
        temp->path[0] = start;
        temp->path[1] = end;
        temp->carCount = 1;        
    }

    // case 2: for the node and index path[0]=start and path[1]=end
        // update the count to +=1
    else if (s == start && e == end){
        temp->carCount+=1;
    }
    // case 3: for the node and index path[0]!=start or path[1]=!end
        // check the chain of the index
    else 
        addToTable(index, start, end, right+1);

}


// public functions
CongestionMonitoring::CongestionMonitoring(Vehicle* vehiclesHead) : hashTableSize(HASH_TABLE_SIZE) {
    if (!vehiclesHead) {
        std::cerr << "No vehicle found" << std::endl;
        return;
    }
    for (int i = 0; i < HASH_TABLE_SIZE; i++)         
        hashTable[i].right = nullptr;
    

    makeHashTable(vehiclesHead);
}


void CongestionMonitoring::makeHashTable(Vehicle* vehiclesHead){

    // first we need to check if the hash table is empty and make it empty if it is not
    this->deleteTable();

    Vehicle* temp = vehiclesHead;
    std::string tempstr;

    while(temp) {
        char p[] = {'\0', '\0'};
        if (temp->presetPath) {
            p[0] = temp->path[temp->currentIntersectionInPath][0];
            p[1] = temp->path[temp->currentIntersectionInPath+1][0];
        }
        // if the paht was not preset or if it is wrong
        if (p[0] == '\0') p[0] = temp->startIntersection[0];
        if (p[1] == '\0') p[1] = temp->endIntersection[0];
        
        
        if (p[0] == '\0' || p[1] == '\0') {
            std::cerr << "Incorrect path received" << std::endl;
            return;
        }

        addToTable(hashFunction(p[0], p[1]), p[0], p[1]);

        temp = temp->next;
    }
}

void CongestionMonitoring::updateHashTable(Vehicle* prevPos, Vehicle* currentPos) {
}

void CongestionMonitoring::printHashTable() {
    std::cout << std::endl;

    // Array to track visited roads
    bool visited[HASH_TABLE_SIZE] = {false};

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RoadNode* temp = &hashTable[i];

        while (temp) {
            // Check if the road (start, end) is unique
            if (temp->path[0] != '\0' && temp->path[1] != '\0') {
                // Calculate hash index for the road in reverse order
                int reverseIndex = hashFunction(temp->path[1], temp->path[0]);

                // Print road only if it hasn't been visited in forward or reverse order
                if (!visited[i] && !visited[reverseIndex]) {
                    std::cout << temp->path[0] << " to " << temp->path[1] << " -> Vehicles: " << temp->carCount << std::endl;
                    visited[i] = true;
                }
            }
            temp = temp->right;
        }
    }
}

void CongestionMonitoring::deleteTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RoadNode* temp = hashTable[i].right;
        while (temp) {
            RoadNode* temp2 = temp;
            temp = temp->right;
            delete temp2;
            temp2 = nullptr;
        }
        hashTable[i].right = nullptr;
        hashTable[i].carCount = 0;  
        hashTable[i].path[0] = '\0';
        hashTable[i].path[1] = '\0';
    }
}


int CongestionMonitoring::getTravelTime(char start, char end, int prevTime) {
    RoadNode* temp = findRoadNode(start, end);
    if (!temp) {
        return prevTime;
    }
    bool isPeakHour = false;
    if (prevTime >= 3600 && prevTime <= 7200) isPeakHour = true;
    int carCount = temp->carCount;

    int time = prevTime;
    
    if (carCount < 5) time  = time;
    else time += time*carCount;

    if (!isPeakHour) time /= 2;
    return time;
}

int CongestionMonitoring::getTravelTime(char start, char end, Graph& cityGraph) {
    RoadNode* temp = findRoadNode(start, end);
    string s = ""; s += start;
    string e = ""; e += end;
    int prevTime = cityGraph.getEdgeWeight(s, e);
    return getTravelTime(start, end, prevTime);
}

RoadNode* CongestionMonitoring::findRoadNode(char start, char end) {
    int index = hashFunction(start, end);
    RoadNode* temp = &hashTable[index];
    while(temp) {
        if (temp->path[0] == start && temp->path[1] == end) {
            return temp;
        }
        temp = temp->right;
    }
    return nullptr;
}

int CongestionMonitoring::numberOfCongestionEvents() {
    int count = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RoadNode* temp = &hashTable[i];
        while(temp) {
            if (temp->carCount > 5) count++;
            temp = temp->right;
        }
    }
    return count;
}


// ------------------------------------------------------------------------------------------------------------



// GRAPH CLASS IMPLEMENTATION #################################################################################

// Vertex class definition
Vertex::Vertex(const std::string& name) : name(name),  edges(nullptr) {}

// Edge class definition
Edge::Edge(Vertex* destination, int travelTime) : destination(destination),blocked(false),underRepaired(false), travelTime(travelTime) {}


bool Edge::isBlocked() const {
    return blocked;
}

void Edge::setBlocked(bool status) {
    blocked = status;
}

bool Edge::isUnderRepaired() const {
    return underRepaired;
}

void Edge::setUnderRepaired(bool status) {
    underRepaired = status;
}

// EdgeNode class definition
EdgeNode::EdgeNode(Edge* edge) : edge(edge), next(nullptr) {}

// VertexNode class definition
VertexNode::VertexNode(Vertex* vertex) : vertex(vertex), next(nullptr) {}

// Graph constructor
Graph::Graph() : headVertex(nullptr) {}

// Graph destructor
Graph::~Graph() {
    // Delete all vertices and edges from memory
    VertexNode* current = headVertex;
    while (current) {
        VertexNode* temp = current;
        current = current->next;

        // Delete all the edges of the vertex
        EdgeNode* edgeCurrent = temp->vertex->edges;
        while (edgeCurrent) {
            EdgeNode* edgeTemp = edgeCurrent;
            edgeCurrent = edgeCurrent->next;
            delete edgeTemp;
        }

        delete temp->vertex;  // Delete the vertex itself
        delete temp;          // Delete the vertex node
    }
}

// Add a vertex to the graph
void Graph::addVertex(const std::string& name) {
    if (findVertex(name)) {
        std::cerr << "Vertex " << name << " already exists!" << std::endl;
        return;
    }

    Vertex* newVertex = new Vertex(name);
    VertexNode* newNode = new VertexNode(newVertex);

    if (!headVertex) {
        headVertex = newNode; // First vertex
    } else {
        VertexNode* current = headVertex;
        while (current->next) {
            current = current->next; // Traverse to the end
        }
        current->next = newNode; // Add at the end
    }
}


// Find a vertex by name
Vertex* Graph::findVertex(const std::string& name) {
    VertexNode* current = headVertex;
    while (current) {
        if (current->vertex->name == name) {
            return current->vertex;
        }
        current = current->next;
    }
    return nullptr;  // Vertex not found
}

// Remove an intersection (vertex) and all connected roads (edges)
void Graph::removeVertex(const string& name) {
    VertexNode* current = headVertex;
    VertexNode* prev = nullptr;

    while (current) {
        if (current->vertex->name == name) {
            // Remove all edges connected to this vertex from the graph
            EdgeNode* edgeCurrent = current->vertex->edges;
            while (edgeCurrent) {
                EdgeNode* temp = edgeCurrent;
                edgeCurrent = edgeCurrent->next;
                delete temp;
            }
            // Remove the vertex from the linked list
            if (prev) {
                prev->next = current->next;
            } else {
                headVertex = current->next;  // Removing head vertex
            }
            delete current->vertex;
            delete current;
            cout << "Intersection " << name << " removed successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Intersection not found!" << endl;
}
// Add an edge between two vertices
void Graph::addEdge(const std::string& start, const std::string& end, int travelTime) {
    Vertex* startVertex = findVertex(start);
    Vertex* endVertex = findVertex(end);

    if (!startVertex || !endVertex) {
        std::cerr << "Error: One or both vertices not found!" << std::endl;
        return;
    }

    // Create a new edge and add it to the end of the start vertex's edge list
    Edge* newEdge = new Edge(endVertex, travelTime);
    EdgeNode* newEdgeNode = new EdgeNode(newEdge);
    if (!startVertex->edges) {
        // If no edges exist, add as the first edge
        startVertex->edges = newEdgeNode;
    } else {
        // Traverse to the end of the edge list
        EdgeNode* current = startVertex->edges;
        while (current->next) {
            current = current->next;
        }
        current->next = newEdgeNode;
    }

    
}
void Graph::removeEdge(const string& start, const string& end) {
    Vertex* startVertex = findVertex(start);
    Vertex* endVertex = findVertex(end);
    if (!startVertex || !endVertex) {
        cout << "One or both intersections not found!" << endl;
        return;
    }

    EdgeNode* current = startVertex->edges;
    EdgeNode* prev = nullptr;
    while (current) {
        if (current->edge->destination == endVertex) {
            if (prev) {
                prev->next = current->next;
            } else {
                startVertex->edges = current->next;
            }
            delete current->edge;
            delete current;
            cout << "Road between " << start << " and " << end << " removed successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Road not found!" << endl;
}
void Graph::loadRoadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // Reading each subsequent line in the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string start, end;
        int travelTime;

        // Extract the values (comma-separated)
        std::getline(ss, start, ',');
        std::getline(ss, end, ',');
        ss >> travelTime;

        // Add vertices if they don't exist
        if (!findVertex(start)) {
            addVertex(start);
        }
        if (!findVertex(end)) {
            addVertex(end);
        }

        // Add the edge between the two vertices
        addEdge(start, end, travelTime);
    }

    file.close();
}
void Graph::displayRoadStatuses() {
    VertexNode* currentVertexNode = headVertex;

    // Iterate through each vertex in the graph
    while (currentVertexNode) {
        Vertex* vertex = currentVertexNode->vertex;

        // Display the vertex name (intersection) and start the road status display
        std::cout << vertex->name << " -> ";

        EdgeNode* currentEdgeNode = vertex->edges;

        // Print all edges for the current vertex
        while (currentEdgeNode) {
            Edge* edge = currentEdgeNode->edge;

            // Display the destination vertex name and the road status (blocked or open)
            std::cout << "(" << edge->destination->name 
                      << ", " << (edge->isBlocked() ? "Blocked)" : (edge->isUnderRepaired()?"Under Repair)":"Open)"));

            currentEdgeNode = currentEdgeNode->next;

            // Print a comma if there are more edges for this vertex
            if (currentEdgeNode) std::cout << ", ";
        }
        std::cout << std::endl;

        currentVertexNode = currentVertexNode->next;
    }
}



// Add an edge to a vertex's adjacency list
void Graph::addEdgeToVertex(Vertex* vertex, Edge* edge) {
    EdgeNode* newEdgeNode = new EdgeNode(edge);
    newEdgeNode->next = vertex->edges;
    vertex->edges = newEdgeNode;
}
void Graph::markEdgesAsUnderRepaired(const std::string& intersection1, const std::string& intersection2, bool isUnderRepaired) {
    Vertex* v1 = findVertex(intersection1);
    Vertex* v2 = findVertex(intersection2);

    if (!v1 || !v2) {
        std::cerr << "One or both vertices not found!" << std::endl;
        return;
    }

    EdgeNode* edgeCurrent = v1->edges;
    while (edgeCurrent) {
        if (edgeCurrent->edge->destination == v2) {
            edgeCurrent->edge->setUnderRepaired(isUnderRepaired);
            return;
        }
        edgeCurrent = edgeCurrent->next;
    }
    std::cerr << "Edge not found between " << intersection1 << " and " << intersection2 << std::endl;
}

// Mark intersections as blocked in the graph
void Graph::markEdgeAsBlocked(const std::string& intersection1, const std::string& intersection2, bool isBlocked) {
    Vertex* v1 = findVertex(intersection1);
    Vertex* v2 = findVertex(intersection2);

    if (!v1 || !v2) {
        std::cerr << "One or both vertices not found!" << std::endl;
        return;
    }

    EdgeNode* edgeCurrent = v1->edges;
    while (edgeCurrent) {
        if (edgeCurrent->edge->destination == v2) {
            edgeCurrent->edge->blocked = isBlocked;
            return;
        }
        edgeCurrent = edgeCurrent->next;
    }
    std::cerr << "Edge not found between " << intersection1 << " and " << intersection2 << std::endl;
}

// Display the blocked intersections
void Graph::displayBlockedEdges() {
    std::cout << "Blocked Edges:\n";

    // Traverse the linked list of vertices
    VertexNode* current = headVertex;
    bool foundBlocked = false;  // To track if any blocked edge is found

    while (current) {
        Vertex* vertex = current->vertex; // Get the current vertex
        EdgeNode* edgeCurrent = vertex->edges; // Traverse the edges of the current vertex

        while (edgeCurrent) {
            // Check if the edge is blocked
            if (edgeCurrent->edge->isBlocked()) {
                std::cout << "- Edge from " << vertex->name << " to " 
                          << edgeCurrent->edge->destination->name << " is blocked.\n";
                foundBlocked = true;
            }
            edgeCurrent = edgeCurrent->next; // Move to the next edge
        }

        current = current->next;  // Move to the next vertex
    }

    if (!foundBlocked) {
        std::cout << "No edges are currently blocked.\n";
    }
}

/////////////////////////////////////////////////////////////////////////


void Graph::printAdjacencyList() {
    VertexNode* currentVertexNode = headVertex;

    // Iterate through each vertex in the graph
    while (currentVertexNode) {
        Vertex* vertex = currentVertexNode->vertex;
        std::cout << vertex->name << " -> ";

        EdgeNode* currentEdgeNode = vertex->edges;

        // Print all edges for the current vertex
        while (currentEdgeNode) {
            Edge* edge = currentEdgeNode->edge;
            std::cout << "(" << edge->destination->name << ", " << edge->travelTime << ")";
            currentEdgeNode = currentEdgeNode->next;
            if (currentEdgeNode) std::cout << ", ";
        }
        std::cout << std::endl;

        currentVertexNode = currentVertexNode->next;
    }
}
// Checks if an edge between two vertices (nodes) is blocked
bool Graph::isBlocked(const std::string& nodeName1, const std::string& nodeName2) {
    Vertex* vertex1 = findVertex(nodeName1); // Find the first vertex
    Vertex* vertex2 = findVertex(nodeName2); // Find the second vertex

    if (!vertex1 || !vertex2) {
        return false; // If either vertex is not found, return false
    }

    // Check if the edge from vertex1 to vertex2 is blocked
    EdgeNode* edgeCurrent = vertex1->edges;
    while (edgeCurrent) {
        if (edgeCurrent->edge->destination == vertex2) {
            return edgeCurrent->edge->isBlocked(); // Return the blocked status of the edge
        }
        edgeCurrent = edgeCurrent->next;
    }

    return false; // If no edge is found between the vertices, return false
}


int Graph::getVertexCount() {
    int count = 0;
    VertexNode* current = headVertex;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}
// Gets all the neighbors of a specific vertex
void Graph::getNeighbors(const std::string& nodeName, std::string* neighbors, int& count) {
    Vertex* vertex = findVertex(nodeName); // Find the vertex
    if (vertex) {
        count = 0;
        EdgeNode* temp = vertex->edges;  // Start with the adjacency list (edges)
        while (temp) {
            neighbors[count++] = temp->edge->destination->name; // Add neighbor's name
            temp = temp->next;  // Move to the next edge
        }
    } else {
        count = 0; // If the vertex is not found, set count to 0
    }
}

// Gets the weight of the edge between two vertices
int Graph::getEdgeWeight(const std::string& start, const std::string& end) {
    Vertex* startVertex = findVertex(start);
    Vertex* endVertex = findVertex(end);
    
    if (startVertex && endVertex) {
        EdgeNode* temp = startVertex->edges;
        while (temp) {
            if (temp->edge->destination == endVertex) {
                return temp->edge->travelTime; // Return the travel time if edge found
            }
            temp = temp->next;
        }
    }
    return -1; // Return -1 if no edge exists between the two vertices
}

// Gets all the vertices in the graph
void Graph::getVertices(std::string* vertices, int& count) {
    count = 0;
    VertexNode* temp = headVertex;
    while (temp) {
        vertices[count++] = temp->vertex->name; // Add vertex name to the list
        temp = temp->next;  // Move to the next vertex
    }
}


void Graph::getAllEdges(std::string edges[][3], int& count) {
    count = 0; // Initialize the edge count
    VertexNode* currentVertexNode = headVertex;

    while (currentVertexNode) {
        Vertex* vertex = currentVertexNode->vertex;
        EdgeNode* currentEdgeNode = vertex->edges;

        while (currentEdgeNode) {
            Edge* edge = currentEdgeNode->edge;

            // Add the edge details to the edges array
            edges[count][0] = vertex->name;                    // Start vertex
            edges[count][1] = edge->destination->name;         // End vertex
            edges[count][2] = std::to_string(edge->travelTime); // Edge weight

            count++; // Increment the edge count
            currentEdgeNode = currentEdgeNode->next;
        }

        currentVertexNode = currentVertexNode->next; // Move to the next vertex
    }
}

// ------------------------------------------------------------------------------------------------------------

// ROADQUEUE IMPLEMENTATION ####################################################################

RoadQueue::RoadQueue(){
      head = NULL;
      tail = NULL;
}

RoadNode* RoadQueue::dequeue(){
      if (isEmpty())
            return nullptr;
      RoadNode* temp = head;
      head = head->next;      
      return temp;
}

void RoadQueue::enqueue(RoadNode*& newNode){
      if(newNode->carCount == 0)
            return;
      newNode->next = nullptr;
      if (head == NULL){
            head = newNode;
            head->next = tail;
            tail = newNode;
            return;
      }
      tail->next = newNode;
      tail = newNode;
      tail->next = nullptr;
}

void RoadQueue::printQueue(){
      RoadNode* temp = head;
      while(temp != NULL){
            std::cout << temp->path[0] << " to " << temp->path[1] << "\t";
            temp = temp->next;
      }
      std::cout << std::endl;
}

bool RoadQueue::isEmpty(){
      return head == NULL;
}


// --------------------------------------------------------------------------------------

// ROUTE IMPLEMENTATION ####################################################################
// Constructor
GPS::GPS(Graph* graph) : graph(graph) {
    // Initialize the vertex names array
    for (int i = 0; i < MAX_VERTICES; ++i) {
        vertexNames[i] = "";
    }
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


// --------------------------------------------------------------------------------------

// TRAFFICSIGNAL IMPLEMENTATION ####################################################################

TrafficSignal::TrafficSignal(std::string state, char intersectionId, int duration, int transitionTime) {
      // Convert the state to lowercase
      for (int i = 0; i < state.length(); i++)
            state[i] = static_cast<char>(std::tolower(state[i]));

      // Check if the state is red, yellow or green otherwise set it to red
      (state == "red" || state == "yellow" || state == "green") ? this->state = state : this->state = "red";
      
      // the duration should be positive
      duration > 0 ? this->duration = duration : this->duration = duration * -1;
      
      duration > 0 ? this->transitionTime = transitionTime : this->transitionTime = transitionTime * -1;

      this->intersectionId = intersectionId;

      next = NULL;
}

std::string TrafficSignal::getState() {
      return state;
}

void TrafficSignal::setState(std::string state) {
      // Convert the state to lowercase
      for (int i = 0; i < state.length(); i++)
            state[i] = static_cast<char>(std::tolower(state[i]));

      // Check if the state is red, yellow or green otherwise set it to red
      (state == "red" || state == "yellow" || state == "green") ? this->state = state : this->state = "red";
}

void TrafficSignal::display() {
      // TO DO: Implement this method after the graphics utility class is implementeasd
}

void TrafficSignal::print() {
      std::cout << "State: " << state  << ", ";
      std::cout << "Intersection ID: " << intersectionId  << ", ";
      std::cout << "Duration: " << duration << std::endl;
}

int TrafficSignal::getIntersectionId() {
      return intersectionId;
}

int TrafficSignal::getDuration() {
      return duration;
}

void TrafficSignal::advanceState(Visualizer* visualizer) {

      // to advance from red to yellow, call the turn green method

      // this->temp = visualizer->getElapsedTimeInSeconds();
      if (state == "yellow") {
            if (abs(this->temp-visualizer->getElapsedTimeInSeconds()) >= transitionTime) {
                  state = "green";
                  this->temp = visualizer->getElapsedTimeInSeconds();
            }
      }
      if (state == "green") {
            if (abs(this->temp-visualizer->getElapsedTimeInSeconds()) >= this->duration) {
                  state = "red";
                  this->temp = visualizer->getElapsedTimeInSeconds();
            }
      }

}

int TrafficSignal::getTransitionTime() {
      return transitionTime;
}

void TrafficSignal::turnGreen(Visualizer* visualizer) {
      state = "yellow";
      this->temp = visualizer->getElapsedTimeInSeconds();
}


// --------------------------------------------------------------------------------------

// TRAFFICLIGHTMANAGEMENT IMPLEMENTATION ####################################################################

TrafficLightManagement::TrafficLightManagement(){
      headSignal = NULL;
}

void TrafficLightManagement::makeTrafficSignals(){
      // load the data from the signals file
      std::ifstream file(SIGNALS_FILE);

      if (!file.is_open()){
            std::cerr << "Error: Unable to open file " << SIGNALS_FILE << std::endl;
            return;
      }
      std::string line;
      std::getline(file, line); // skip the header
      while (std::getline(file, line)){
            TrafficSignal* signal = new TrafficSignal();

            std::string intersection = "";
            std::string duration = "";
            intersection = line.substr(0, line.find(","));
            duration = line.substr(line.find(",") + 1);
            signal->intersectionId = intersection[0];
            signal->duration = std::stoi(duration);


            addSignal(signal);
      }
}     

void TrafficLightManagement::addSignal( TrafficSignal* signal){
      signal->next = NULL;
      if (headSignal == NULL){
            headSignal = signal;
            return;
      }
      TrafficSignal* temp = headSignal;
      while (temp->next != NULL){
            temp = temp->next;
      }
      temp->next = signal;
}

void TrafficLightManagement::updateTrafficSignals(CongestionMonitoring& ht){
      for(int i = 0; i< HASH_TABLE_SIZE; i++) {
            RoadNode* temp = &ht.hashTable[i];
            while(temp) {
                  // only chagnge the signal time if the car count is greater than 5
                  if(temp->carCount > 5)
                  if (temp->path[0] != '\0' && temp->path[1] != '\0') {
                        string intersection = "";
                        intersection += temp->path[0];
                        TrafficSignal* signal = getSignal(intersection);
                        if (signal != NULL) {
                              signal->duration = signal->duration + temp->carCount;
                              cout << "Intersection " << intersection << " Green Time: " << signal->duration << "s (updated)" << endl;
                        }
                        
                  }
                  temp = temp->right;
            }
      }
}


void TrafficLightManagement::printGreenTimes(){
      TrafficSignal* temp = headSignal;
      while (temp != NULL){
            std::cout << "Intersection " << temp->intersectionId << " Green Time: " << temp->duration << "s" << std::endl;
            temp = temp->next;
      }
     
}
TrafficSignal* TrafficLightManagement::getSignal(string intersection) {
      TrafficSignal* temp = headSignal;
      while (temp) {
            if (temp->intersectionId == intersection[0])
                  return temp;
            temp = temp->next;
      }
      return nullptr;
}

void TrafficLightManagement::manageTrafficLights(char mostCongestedRoad, Visualizer* vs){
      TrafficSignal* temp = headSignal;
      while (temp) {
            if (temp->intersectionId == mostCongestedRoad) {
                  temp->turnGreen(vs);
            }
            temp = temp->next;
            temp->advanceState(vs);
      }
}






// --------------------------------------------------------------------------------------





// VEHICLES IMPLEMENTATION ####################################################################

// Constructor initializes an empty list
Vehicles::Vehicles() {
    head = nullptr;
   
}

// Destructor cleans up the list by deleting all vehicles
Vehicles::~Vehicles() {
    Vehicle* current = head;
    while (current != nullptr) {
        Vehicle* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

// Inserts a new vehicle at the beginning of the list
void Vehicles::insertAtHead(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);
    if (isEmpty()) {
        head = newVehicle;
    } else {
        newVehicle->next = head;
        head = newVehicle;
    }
}

void Vehicles::enqueue(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    // Create the new Vehicle object
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);

    if (isEmpty()) {
        head = newVehicle;  // If list is empty, just add the new vehicle as the head
    } else if (priorityLevel == "High") {
        // If priority is High, insert at the head of the list
        insertAtHead(VehicleID, startIntersection, endIntersection, priorityLevel);
    } else if (priorityLevel == "Medium") {
        // If priority is Medium, insert after the head (just after high-priority vehicles)
        Vehicle* current = head;
        while (current->next != nullptr && current->next->priorityLevel == "Medium") {
            current = current->next;
        }
        newVehicle->next = current->next;  // Set the next of the new vehicle to the current vehicle's next
        current->next = newVehicle;        // Insert the new vehicle after the current vehicle
    } else {
        // If priority is Low, insert at the end of the list
        Vehicle* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newVehicle;  // Insert the vehicle at the end
    }
}


// Insert after a specific position in the list
bool Vehicles::insertAfterPosition(int position, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    if (position < 0) return false;
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);
    if (position == 0) {
        insertAtHead(VehicleID, startIntersection, endIntersection, priorityLevel);
        return true;
    }
    Vehicle* current = head;
    int index = 0;
    while (current != nullptr && index < position) {
        current = current->next;
        index++;
    }
    if (current == nullptr) return false;

    newVehicle->next = current->next;
    current->next = newVehicle;
    return true;
}

// Insert after a specific vehicle ID
bool Vehicles::insertAfterID(std::string ID, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    int position = findIDInVehicles(ID);
    if (position == -1) return false;
    return insertAfterPosition(position, VehicleID, startIntersection, endIntersection, priorityLevel);
}

// Delete the first vehicle in the list
void Vehicles::deleteAtStart() {
    if (!isEmpty()) {
        Vehicle* temp = head;
        head = head->next;
        delete temp;
    }
}

// Delete the last vehicle in the list
bool Vehicles::deleteAtEnd() {
    if (isEmpty()) return false;
    if (head->next == nullptr) {
        deleteAtStart();
        return true;
    }
    Vehicle* secondLast = head;
    while (secondLast->next && secondLast->next->next != nullptr) {
        secondLast = secondLast->next;
    }
    delete secondLast->next;
    secondLast->next = nullptr;
    return true;
}

// Delete a vehicle by its ID
bool Vehicles::deleteAtID(std::string ID) {
    if (head == nullptr) return false;
    if (head->vehicleID == ID) {
        deleteAtStart();
        return true;
    }
    Vehicle* current = head;
    while (current->next != nullptr && current->next->vehicleID != ID) {
        current = current->next;
    }
    if (current->next == nullptr) return false;
    Vehicle* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

// Checks if the list is empty
bool Vehicles::isEmpty() {
    return head == nullptr;
}

// Print all vehicles in the list
void Vehicles::printVehicles() {
    Vehicle* current = head;
    while (current != nullptr) {
        std::cout << "Vehicle ID: " << current->vehicleID << ", Priority: " << current->priorityLevel << std::endl;
        current = current->next;
    }
}

// Finds a vehicle in the list by its ID
int Vehicles::findIDInVehicles(std::string vehicleID) {
    Vehicle* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->vehicleID == vehicleID) return index;
        current = current->next;
        index++;
    }
    return -1;
}

// Loads vehicle data from CSV files
void Vehicles::loadAndReadCSVs() {
    std::ifstream vehiclesFile("dataset/vehicles.csv");
    std::ifstream emergencyVehiclesFile("dataset/emergency_vehicles.csv");

    std::string line, vehicleID, startIntersection, endIntersection, priorityLevel;

   
    if (vehiclesFile.is_open()) {
        getline(vehiclesFile, line); // Skip the header
        while (getline(vehiclesFile, line)) {
            std::stringstream ss(line);
            getline(ss, vehicleID, ',');
            getline(ss, startIntersection, ',');
            getline(ss, endIntersection, ',');
            
            
            enqueue(vehicleID, startIntersection, endIntersection, "low");
        }
        vehiclesFile.close();
    }

  
    if (emergencyVehiclesFile.is_open()) {
        getline(emergencyVehiclesFile, line); // Skip the header
        while (getline(emergencyVehiclesFile, line)) {
            std::stringstream ss(line);
            getline(ss, vehicleID, ',');
            getline(ss, startIntersection, ',');
            getline(ss, endIntersection, ',');
            getline(ss, priorityLevel, ',');
            
          
            if (findIDInVehicles(vehicleID) == -1) {
                enqueue(vehicleID, startIntersection, endIntersection, priorityLevel);
            }
        }
        emergencyVehiclesFile.close();
    }
}


// Returns the head vehicle
Vehicle*& Vehicles::getHead() {
    return head;
}

void Vehicles::addPaths(GPS& gps) {
    Vehicle* current = head;
    while (current != nullptr) {
        string start = current->startIntersection;
        string end = current->endIntersection;  
        if (current->path[current->currentIntersectionInPath] != start)
        {
            std::cout << "\nWarning: The current intersection in the path does not match the start intersection of the vehicle. Adding a path now will reset the vehicle's position to start intersection \n" << start << endl;
            current->currentIntersectionInPath = 0;
        }
        string path = gps.getPathAsString(start, end);
        current->setPath(path);
        current = current->next;
    }
}



// ------------------------------------------------------------------------------


// VISUALIZER IMPLEMENTATION ###################################################################

// Constructor for the Visualizer class
Visualizer::Visualizer() {
    // Empty constructor
}

// Function to draw the simulation
void Visualizer::drawSimulation(Graph &graph, Vehicles &vehicles, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager) {
    // Create a window for the simulation
    sf::RenderWindow window(sf::VideoMode(800, 800), "Graph Visualization");

    // Main loop to keep the window open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Initialize variables for drawing vertices
        VertexNode* currentVertexNode = graph.headVertex;
        std::map<std::string, sf::Vector2f> positions;
        sf::Vector2f center(400, 400); // Center of the window
        float radius = 350.0f; // Radius for circular layout
        int numVertices = 0;

        // Count the number of vertices in the graph
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            numVertices++;
            currentVertexNode = currentVertexNode->next;
        }

        // Load the font for vertex labels
        sf::Font font;
        if (!font.loadFromFile("sprites/font.ttf")) {
            std::cout << "Couldn't load font\n";
        }

        // Calculate the angle between each vertex for circular layout
        float angleIncrement = 2 * M_PI / numVertices;
        float currentAngle = 0.0f;

        // Draw vertices in a circular pattern
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;

            // Calculate the position of the vertex
            float x = center.x + radius * cos(currentAngle);
            float y = center.y + radius * sin(currentAngle);

            // Store the position for later use
            positions[vertex->name] = sf::Vector2f(x + 20, y + 20);

            // Increment the angle for the next vertex
            currentAngle += angleIncrement;

            // Draw the vertex label
            sf::Text label;
            label.setFont(font);
            label.setString(vertex->name);
            label.setCharacterSize(47);
            label.setFillColor(sf::Color::White);
            label.setPosition(x, y - 7);
            window.draw(label);

            // Draw the green time for the traffic light
            int greenTime = traffic.getSignal(vertex->name)->getDuration();
            std::string greenTimeStr = std::to_string(greenTime);
            label.setString(greenTimeStr);
            label.setPosition(x - 20, y - 20);
            drawVehicles(vehicles, vertex->name, positions[vertex->name], window);

            currentVertexNode = currentVertexNode->next;
        }

        // Draw edges as lines
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;
            EdgeNode* currentEdgeNode = vertex->edges;

            while (currentEdgeNode) {
                Edge* edge = currentEdgeNode->edge;

                // Only draw the edge if it exists as a directed path
                std::string start = vertex->name;
                std::string end = edge->destination->name;

                if (graph.getEdgeWeight(start, end) != -1) {
                    // Get the color for the edge
                    sf::Color color = choseColor(currentEdgeNode, vertex, traffic, ht, accidentManager);

                    // Create the vertex array with the correct color
                    sf::Vertex line[] = {
                        sf::Vertex(positions[start], color),
                        sf::Vertex(positions[end], color)
                    };

                    // Draw the edge
                    window.draw(line, 2, sf::Lines);
                }

                currentEdgeNode = currentEdgeNode->next;
            }

            currentVertexNode = currentVertexNode->next;
        }

        // Load the font for edge weights
        sf::Font font2;
        if (!font2.loadFromFile("sprites/font3.ttf")) {
            std::cerr << "Couldn't load font\n";
            return;
        }

        // Draw edge weights
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;
            EdgeNode* currentEdgeNode = vertex->edges;
            while (currentEdgeNode) {
                Edge* edge = currentEdgeNode->edge;
                sf::Vector2f startPos = positions[vertex->name];
                sf::Vector2f endPos = positions[edge->destination->name];
                sf::Vector2f midPos = (startPos + endPos) / 2.0f;

                // Determine the direction of the edge
                sf::Vector2f direction = endPos - startPos;
                float angle = atan2(direction.y, direction.x);
                if (angle < 0) {
                    // Offset the line position slightly if the color is blue
                    startPos += sf::Vector2f(5, 5);
                    endPos += sf::Vector2f(5, 5);
                }

                // Get the color for the edge
                sf::Color edgeColor = choseColor(currentEdgeNode, vertex, traffic, ht, accidentManager);
                sf::Vertex line[] = {
                    sf::Vertex(startPos, edgeColor),
                    sf::Vertex(endPos, edgeColor)
                };
                window.draw(line, 2, sf::Lines);

                // Draw the edge weight label
                sf::Text weightLabel;
                weightLabel.setFont(font2);
                weightLabel.setString(std::to_string(edge->travelTime));
                weightLabel.setCharacterSize(20);
                weightLabel.setFillColor(sf::Color::Blue);
                weightLabel.setPosition(midPos);
                window.draw(weightLabel);

                currentEdgeNode = currentEdgeNode->next;
            }
            currentVertexNode = currentVertexNode->next;
        }

        // Display the window contents
        window.display();
        sf::sleep(sf::seconds(1));

        // Move vehicles forward
        Vehicle *currentVehicle = vehicles.getHead();
        while (currentVehicle != NULL) {
            if (currentVehicle->presetPath)
                currentVehicle->moveForward();

            currentVehicle = currentVehicle->next;
        }
    }
}

// Function to draw vehicles at a specific intersection
void Visualizer::drawVehicles(Vehicles &vehicles, const std::string &intersection, const sf::Vector2f &position, sf::RenderWindow &window) {
    Vehicle *currentVehicle = vehicles.getHead();
    int decrement = 0;
    while (currentVehicle != NULL) {
        if (currentVehicle->path[currentVehicle->currentIntersectionInPath] == intersection) {
            // Draw vehicle label
            sf::Font font;
            if (!font.loadFromFile("sprites/font3.ttf")) {
                std::cerr << "Couldn't load font\n";
                return;
            }

            sf::Text label;
            label.setFont(font);
            label.setString(currentVehicle->vehicleID);
            label.setCharacterSize(20);
            label.setFillColor(sf::Color::Red);
            label.setPosition(position.x, position.y - 20 + decrement);
            window.draw(label);
            decrement -= 20;
        }
        currentVehicle = currentVehicle->next;
    }
}

// Function to get the elapsed time in seconds
float Visualizer::getElapsedTimeInSeconds() {
    return clock.getElapsedTime().asSeconds();
}

// Function to choose the color for an edge based on various conditions
sf::Color Visualizer::choseColor(EdgeNode *edgeNode, Vertex *vertex, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager) {
    // Check if the edge is blocked
    if (edgeNode->edge->isBlocked()) {
        return sf::Color::Magenta;
    }

    // Check if the edge has a green light
    std::string signal = traffic.getSignal(vertex->name)->state;
    if (signal == "green") {
        std::cout << "Green light" << std::endl;
        return sf::Color::Green;
    }

    // Default color if none of the above conditions are met
    return sf::Color::White;
}

// ------------------------------------------------------------------------------

