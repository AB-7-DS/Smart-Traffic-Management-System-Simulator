#ifndef VEHICLES_H
#define VEHICLES_H

#include <string> // Ensure string header is included
#include<limits>
#include "vehicle.h"
#include "Route.h"

// All functions in this class should use std::string as parameter types.
class Vehicles {
private:
    Vehicle* head; // Pointer to the head of the linked list

public:
    Vehicles(); // Constructor for Vehicles class.
    ~Vehicles(); // Destructor for Vehicles class.

    // Function declarations that use std::string
    void insertAtHead(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);
    void enqueue(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);
    bool insertAfterPosition(int position, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);
    bool insertAfterID(std::string ID, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);
    void deleteAtStart();
    bool deleteAtEnd();
    bool deleteAtIndex(int position);
    bool deleteAtID(std::string ID);
    bool isEmpty();
    void printVehicles();
    int findIDInVehicles(std::string vehicleID);
    void loadAndReadCSVs();
    Vehicle*& getHead();
    // bool rerouteVehicleByID(const std::string& vehicleID, RerouteManager& rerouteManager);
    // void recalculatePaths(RerouteManager& rerouteManager);
    // bool updatePathForVehicle(const std::string& vehicleID, const std::string& newPath);

    void addPaths(GPS& gps);

};

#endif
