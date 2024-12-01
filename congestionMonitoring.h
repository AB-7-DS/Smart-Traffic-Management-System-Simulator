# ifndef CONGESTION_MONITORING_H
# define CONGESTION_MONITORING_H
# include "vehicles.h"
# include "vehicle.h"

const int HASH_TABLE_SIZE = 100;

/**
 * @brief The node for the Hash Table containing a key value pair and a pointer for chaining
 * 
 * 
 */
struct RoadNode {
    char path[2]; //< Start and end Intersection
    int carCount; //< The number of cars on the road
    RoadNode* right; //< Pointer for chaining in case of collisions

    RoadNode(char s = '\0', char e = '\0', int v = 0) {
        path[0] = s;
        path[1] = e;
        carCount = v;
        right = nullptr;
    }
};

/**
 * @brief HashTable for tracking number of vehicles on a road
 * 
 */
class CongestionMonitoring { 
    
    private:
        RoadNode hashTable[HASH_TABLE_SIZE]; //< RoadNode array
        const int hashTableSize; //< Hash table array size

        // private functions -----------------------------------------------------------
        void addToTable(int index, char start, char end, int right = 0);
        int hashFunction(char start, char end);
        char getStart(int index, int right);
        char getEnd(int index, int right);
        // ----------------------------------------------------------------------------
    
    public:
        CongestionMonitoring(Vehicle* vehiclesHead);
        void makeHashTable(Vehicle* vehiclesHead);
        void updateHashTable(Vehicle* prevPos, Vehicle* currentPos);
        void printHashTable();
        ~CongestionMonitoring();
};


#endif