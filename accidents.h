#ifndef ACCIDENTS_H
#define ACCIDENTS_H
#include <string>

// Forward declaration of Graph class
class Graph;

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

#endif // ACCIDENTS_H
