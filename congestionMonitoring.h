# ifndef CONGESTION_MONITORING_H
# define CONGESTION_MONITORING_H
# include "vehicles.h"
# include "vehicle.h"
# include "graph.h"
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
        int getTravelTime(char start, char end, Graph& cityGraph);
        int numberOfCongestionEvents();
        // ~CongestionMonitoring();
       
        
};


#endif