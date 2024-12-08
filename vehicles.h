#ifndef VEHICLES_H
#define VEHICLES_H

#include <string> // Ensure string header is included
#include<limits>
#include "vehicle.h"
#include "Route.h"


// All functions in this class should use std::string as parameter types.
/**
 * @class Vehicles
 * @brief A class to manage a linked list of vehicles.
 */
class Vehicles {
private:
    Vehicle* head; // Pointer to the head of the linked list

public:
/**
 * @brief Constructor for Vehicles class.
 */
Vehicles();

/**
 * @brief Destructor for Vehicles class.
 */
~Vehicles();

/**
 * @brief Inserts a vehicle at the head of the linked list.
 * @param VehicleID The ID of the vehicle.
 * @param startIntersection The starting intersection of the vehicle.
 * @param endIntersection The ending intersection of the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
void insertAtHead(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Enqueues a vehicle at the end of the linked list.
 * @param VehicleID The ID of the vehicle.
 * @param startIntersection The starting intersection of the vehicle.
 * @param endIntersection The ending intersection of the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
void enqueue(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Inserts a vehicle after a specific position in the linked list.
 * @param position The position after which the vehicle will be inserted.
 * @param VehicleID The ID of the vehicle.
 * @param startIntersection The starting intersection of the vehicle.
 * @param endIntersection The ending intersection of the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 * @return True if the insertion was successful, false otherwise.
 */
bool insertAfterPosition(int position, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Inserts a vehicle after a specific vehicle ID in the linked list.
 * @param ID The ID of the vehicle after which the new vehicle will be inserted.
 * @param VehicleID The ID of the new vehicle.
 * @param startIntersection The starting intersection of the new vehicle.
 * @param endIntersection The ending intersection of the new vehicle.
 * @param priorityLevel The priority level of the new vehicle.
 * @return True if the insertion was successful, false otherwise.
 */
bool insertAfterID(std::string ID, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);

/**
 * @brief Deletes the vehicle at the start of the linked list.
 */
void deleteAtStart();

/**
 * @brief Deletes the vehicle at the end of the linked list.
 * @return True if the deletion was successful, false otherwise.
 */
bool deleteAtEnd();

/**
 * @brief Deletes the vehicle at a specific index in the linked list.
 * @param position The index of the vehicle to be deleted.
 * @return True if the deletion was successful, false otherwise.
 */
bool deleteAtIndex(int position);

/**
 * @brief Deletes the vehicle with a specific ID in the linked list.
 * @param ID The ID of the vehicle to be deleted.
 * @return True if the deletion was successful, false otherwise.
 */
bool deleteAtID(std::string ID);

/**
 * @brief Checks if the linked list is empty.
 * @return True if the linked list is empty, false otherwise.
 */
bool isEmpty();

/**
 * @brief Prints the details of all vehicles in the linked list.
 */
void printVehicles();

/**
 * @brief Finds the position of a vehicle with a specific ID in the linked list.
 * @param vehicleID The ID of the vehicle to be found.
 * @return The position of the vehicle in the linked list, or -1 if not found.
 */
int findIDInVehicles(std::string vehicleID);

/**
 * @brief Loads and reads vehicle data from CSV files.
 */
void loadAndReadCSVs();

/**
 * @brief Gets the head of the linked list.
 * @return A reference to the pointer to the head of the linked list.
 */
Vehicle*& getHead();

/**
 * @brief Adds paths to the vehicles using GPS data.
 * @param gps The GPS object containing path data.
 */
void addPaths(GPS& gps);

    
};

#endif
