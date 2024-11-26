#ifndef VEHICLE_H
#define VEHICLE_H

#include<string>
using namespace std;

/**
 * @struct Vehicle
 * @brief A structure representing a vehicle with details about its route and priority.
 */
struct Vehicle {
    string vehicleID; //<The unique identifier for the vehicle
    const string startIntersection; //<The starting intersection for the vehicle's route never to be changed
    const string endIntersection; //<The ending intersection for the vehicle's route never to be changed
    string priorityLevel; //<The priority level of the vehicle (e.g., high, low)
    string* path; //<The path the vehicle will take to reach its destination.
    int currentIntersectionInPath; //< an index in the path array that represents the current intersection the vehicle is at. the next intersection is at currentIntersectionInPath + 1
    int pathLength; //<The length of the path array
    
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
    Vehicle(string vehicleID, string startIntersection, string endIntersection, string priorityLevel);
    /**
     * @brief updates the currentIntersectionId and nextIntersectionId of the vehicle
     * 
     * @param currentIntersectionId 
     * @param nextIntersectionId 
     */
    void moveForward(string nextIntersectionId);
    void printVehicle();
};

#endif
