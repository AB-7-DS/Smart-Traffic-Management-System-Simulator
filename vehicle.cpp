#include<string>
#include "vehicle.h"
using namespace std;

/**
 * @brief Constructs a Vehicle with given attributes.
 * @param vehicleID The unique identifier for the vehicle.
 * @param startIntersection The starting intersection for the vehicle.
 * @param endIntersection The ending intersection for the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
Vehicle::Vehicle(string vehicleID, string startIntersection, string endIntersection, string priorityLevel){
    this->vehicleID = vehicleID;
    this->startIntersection = startIntersection;
    this->endIntersection = endIntersection;
    this->priorityLevel = priorityLevel;
    this->next = NULL;
}
