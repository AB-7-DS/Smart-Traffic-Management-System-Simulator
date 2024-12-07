# ifndef CONGESTION_MONITORING_H
# define CONGESTION_MONITORING_H
# include "vehicles.h"
# include "vehicle.h"
# include "RoadNode.h"
const int HASH_TABLE_SIZE = 100;

/**
 * @brief HashTable for tracking number of vehicles on a road
 * 
 */
class CongestionMonitoring { 
    
    private:
        const int hashTableSize; //< Hash table array size

        // private functions -----------------------------------------------------------
        void addToTable(int index, char start, char end, int right = 0);
        int hashFunction(char start, char end);
        char getStart(int index, int right);
        char getEnd(int index, int right);
        // ----------------------------------------------------------------------------
    
    public:
        RoadNode hashTable[HASH_TABLE_SIZE]; //< RoadNode array
        CongestionMonitoring(Vehicle* vehiclesHead);
        void makeHashTable(Vehicle* vehiclesHead);
        void updateHashTable(Vehicle* prevPos, Vehicle* currentPos);
        void printHashTable();
        void deleteTable();
        ~CongestionMonitoring();
};


#endif