#ifndef VEHICLES_H
#define VEHICLES_H

#include<string>
#include "vehicle.h"

/**
 * @class Vehicles
 * @brief A linked list implementation to manage Vehicle objects.
 */
class Vehicles {
private:
    /**
     * @brief Pointer to the head of the linked list of Vehicles.
     */
    Vehicle *head;

public:
    /**
     * @brief Constructor for Vehicles class. Initializes an empty list of vehicles.
     */
    Vehicles();

    /**
     * @brief Destructor for Vehicles class. Cleans up the linked list.
     */
    ~Vehicles();

    /**
     * @brief Inserts a new Vehicle at the beginning of the list.
     * @param VehicleID The unique identifier for the vehicle.
     * @param startIntersection The starting intersection for the vehicle.
     * @param endIntersection The ending intersection for the vehicle.
     * @param priorityLevel The priority level of the vehicle.
     */
    void insertAtHead(string VehicleID, string startIntersection, string endIntersection, string priorityLevel);

    /**
     * @brief Adds a new Vehicle to the end of the list (queue behavior).
     * @param VehicleID The unique identifier for the vehicle.
     * @param startIntersection The starting intersection for the vehicle.
     * @param endIntersection The ending intersection for the vehicle.
     * @param priorityLevel The priority level of the vehicle.
     */
    void enqueue(string VehicleID, string startIntersection, string endIntersection, string priorityLevel);

    /**
     * @brief Inserts a new Vehicle after a specified position in the list.
     * @param position The position after which the new vehicle should be inserted.
     * @param VehicleID The unique identifier for the vehicle.
     * @param startIntersection The starting intersection for the vehicle.
     * @param endIntersection The ending intersection for the vehicle.
     * @param priorityLevel The priority level of the vehicle.
     * @return True if the insertion was successful, false otherwise.
     */
    bool insertAfterPosition(int position, string VehicleID, string startIntersection, string endIntersection, string priorityLevel);

    /**
     * @brief Inserts a new Vehicle after an existing vehicle with a specific ID.
     * @param ID The ID of the vehicle after which the new vehicle should be inserted.
     * @param VehicleID The unique identifier for the new vehicle.
     * @param startIntersection The starting intersection for the new vehicle.
     * @param endIntersection The ending intersection for the new vehicle.
     * @param priorityLevel The priority level of the new vehicle.
     * @return True if the insertion was successful, false otherwise.
     */
    bool insertAfterID(string ID, string VehicleID, string startIntersection, string endIntersection, string priorityLevel);

    /**
     * @brief Deletes the first vehicle in the list.
     */
    void deleteAtStart();

    /**
     * @brief Deletes the last vehicle in the list.
     * @return True if the deletion was successful, false otherwise.
     */
    bool deleteAtEnd();

    /**
     * @brief Deletes a vehicle at a specific index.
     * @param position The index of the vehicle to delete.
     * @return True if the deletion was successful, false otherwise.
     */
    bool deleteAtIndex(int position);

    /**
     * @brief Deletes a vehicle by its ID.
     * @param ID The ID of the vehicle to delete.
     * @return True if the deletion was successful, false otherwise.
     */
    bool deleteAtID(string ID);

    /**
     * @brief Checks if the list of vehicles is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Prints the details of all vehicles in the list.
     */
    void printVehicles();

    /**
     * @brief Finds a vehicle in the list by its ID.
     * @param vehicleID The ID of the vehicle to find.
     * @return The position of the vehicle in the list, or -1 if not found.
     */
    int findIDInVehicles(string vehicleID);

    /**
     * @brief Loads and reads vehicle data from CSV files.
     */
    void loadAndReadCSVs();
};

#endif
