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
    string currentIntersectionId; //<The current intersection the vehicle is at. This will be updated as the vehicle moves.
    string nextIntersectionId; //<The next intersection the vehicle will move to. This will be updated as the vehicle moves.
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
};

#endif
