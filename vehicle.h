#ifndef VEHICLE_H
#define VEHICLE_H

#include<string>
using namespace std;

/**
 * @struct Vehicle
 * @brief A structure representing a vehicle with details about its route and priority.
 */
struct Vehicle {
    /**
     * @brief The unique identifier for the vehicle.
     */
    string vehicleID;

    /**
     * @brief The starting intersection for the vehicle's route.
     */
    string startIntersection;

    /**
     * @brief The ending intersection for the vehicle's route.
     */
    string endIntersection;

    /**
     * @brief The priority level of the vehicle (e.g., high, low).
     */
    string priorityLevel;

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
