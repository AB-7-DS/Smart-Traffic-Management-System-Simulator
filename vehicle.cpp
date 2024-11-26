#include<string>
#include "vehicle.h"
using namespace std;
Vehicle::Vehicle(string vehicleID, string startIntersection, string endIntersection, string priorityLevel)
    : startIntersection(startIntersection), endIntersection(endIntersection)
{
    this->vehicleID = vehicleID;
    this->priorityLevel = priorityLevel;
    this->next = NULL;
    // Initialize currentIntersectionId to startIntersection
    this->currentIntersectionId = startIntersection; 
    // Initialize nextIntersectionId to an empty string
    this->nextIntersectionId = ""; 
}
void Vehicle::moveVehicle(string currentIntersectionId, string nextIntersectionId){
    if (currentIntersectionId == endIntersection)
        return;
    this->currentIntersectionId = currentIntersectionId;
    this->nextIntersectionId = nextIntersectionId;
}
