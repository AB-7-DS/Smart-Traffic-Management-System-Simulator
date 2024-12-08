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
#include <cmath>
using namespace std;

// Forward declarations
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
