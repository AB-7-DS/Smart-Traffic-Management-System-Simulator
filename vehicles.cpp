#include <iostream>
#include<fstream>
#include <sstream>
#include "vehicles.h"  // Include the correct header file
#include"graph.h"

// Constructor initializes an empty list
Vehicles::Vehicles() {
    head = nullptr;
   
}

// Destructor cleans up the list by deleting all vehicles
Vehicles::~Vehicles() {
    Vehicle* current = head;
    while (current != nullptr) {
        Vehicle* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

// Inserts a new vehicle at the beginning of the list
void Vehicles::insertAtHead(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);
    if (isEmpty()) {
        head = newVehicle;
    } else {
        newVehicle->next = head;
        head = newVehicle;
    }
}

void Vehicles::enqueue(std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    // Create the new Vehicle object
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);

    if (isEmpty()) {
        head = newVehicle;  // If list is empty, just add the new vehicle as the head
    } else if (priorityLevel == "High") {
        // If priority is High, insert at the head of the list
        insertAtHead(VehicleID, startIntersection, endIntersection, priorityLevel);
    } else if (priorityLevel == "Medium") {
        // If priority is Medium, insert after the head (just after high-priority vehicles)
        Vehicle* current = head;
        while (current->next != nullptr && current->next->priorityLevel == "Medium") {
            current = current->next;
        }
        newVehicle->next = current->next;  // Set the next of the new vehicle to the current vehicle's next
        current->next = newVehicle;        // Insert the new vehicle after the current vehicle
    } else {
        // If priority is Low, insert at the end of the list
        Vehicle* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newVehicle;  // Insert the vehicle at the end
    }
}


// Insert after a specific position in the list
bool Vehicles::insertAfterPosition(int position, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    if (position < 0) return false;
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);
    if (position == 0) {
        insertAtHead(VehicleID, startIntersection, endIntersection, priorityLevel);
        return true;
    }
    Vehicle* current = head;
    int index = 0;
    while (current != nullptr && index < position) {
        current = current->next;
        index++;
    }
    if (current == nullptr) return false;

    newVehicle->next = current->next;
    current->next = newVehicle;
    return true;
}

// Insert after a specific vehicle ID
bool Vehicles::insertAfterID(std::string ID, std::string VehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel) {
    int position = findIDInVehicles(ID);
    if (position == -1) return false;
    return insertAfterPosition(position, VehicleID, startIntersection, endIntersection, priorityLevel);
}

// Delete the first vehicle in the list
void Vehicles::deleteAtStart() {
    if (!isEmpty()) {
        Vehicle* temp = head;
        head = head->next;
        delete temp;
    }
}

// Delete the last vehicle in the list
bool Vehicles::deleteAtEnd() {
    if (isEmpty()) return false;
    if (head->next == nullptr) {
        deleteAtStart();
        return true;
    }
    Vehicle* secondLast = head;
    while (secondLast->next && secondLast->next->next != nullptr) {
        secondLast = secondLast->next;
    }
    delete secondLast->next;
    secondLast->next = nullptr;
    return true;
}

// Delete a vehicle by its ID
bool Vehicles::deleteAtID(std::string ID) {
    if (head == nullptr) return false;
    if (head->vehicleID == ID) {
        deleteAtStart();
        return true;
    }
    Vehicle* current = head;
    while (current->next != nullptr && current->next->vehicleID != ID) {
        current = current->next;
    }
    if (current->next == nullptr) return false;
    Vehicle* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

// Checks if the list is empty
bool Vehicles::isEmpty() {
    return head == nullptr;
}

// Print all vehicles in the list
void Vehicles::printVehicles() {
    Vehicle* current = head;
    while (current != nullptr) {
        std::cout << "Vehicle ID: " << current->vehicleID << ", Priority: " << current->priorityLevel << std::endl;
        current = current->next;
    }
}

// Finds a vehicle in the list by its ID
int Vehicles::findIDInVehicles(std::string vehicleID) {
    Vehicle* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->vehicleID == vehicleID) return index;
        current = current->next;
        index++;
    }
    return -1;
}

// Loads vehicle data from CSV files
void Vehicles::loadAndReadCSVs() {
    std::ifstream vehiclesFile("dataset/vehicles.csv");
    std::ifstream emergencyVehiclesFile("dataset/emergency_vehicles.csv");

    std::string line, vehicleID, startIntersection, endIntersection, priorityLevel;

   
    if (vehiclesFile.is_open()) {
        getline(vehiclesFile, line); // Skip the header
        while (getline(vehiclesFile, line)) {
            std::stringstream ss(line);
            getline(ss, vehicleID, ',');
            getline(ss, startIntersection, ',');
            getline(ss, endIntersection, ',');
            
            
            enqueue(vehicleID, startIntersection, endIntersection, "low");
        }
        vehiclesFile.close();
    }

  
    if (emergencyVehiclesFile.is_open()) {
        getline(emergencyVehiclesFile, line); // Skip the header
        while (getline(emergencyVehiclesFile, line)) {
            std::stringstream ss(line);
            getline(ss, vehicleID, ',');
            getline(ss, startIntersection, ',');
            getline(ss, endIntersection, ',');
            getline(ss, priorityLevel, ',');
            
          
            if (findIDInVehicles(vehicleID) == -1) {
                enqueue(vehicleID, startIntersection, endIntersection, priorityLevel);
            }
        }
        emergencyVehiclesFile.close();
    }
}


// Returns the head vehicle
Vehicle* Vehicles::getHead() {
    return head;
}


