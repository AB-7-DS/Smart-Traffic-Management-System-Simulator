# ifndef CONGESTION_MONITORING_H
# define CONGESTION_MONITORING_H
# include "vehicles.h"
# include "vehicle.h"
# include "graph.h"
# include "RoadNode.h"
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


#endif // CONGESTION_MONITORING_H