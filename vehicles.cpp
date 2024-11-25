#include<iostream>
#include <fstream>
#include <sstream>
#include "vehicles.h"
using namespace std;

/**
 * @brief Constructs an empty Vehicles list.
 */
Vehicles::Vehicles(){
    head = NULL;
}

/**
 * @brief Destroys the Vehicles list, releasing allocated memory.
 */
Vehicles::~Vehicles(){
    // Traverse Vehicles and delete each Vehicle until reaching NULL
    Vehicle* current = head;
    while (current != NULL) {
        Vehicle* nextVehicle = current->next;
        delete current;
        current = nextVehicle;  
    }
    head = NULL;
}

/**
 * @brief Inserts a new Vehicle at the head of the list.
 * @param VehicleID The unique identifier for the vehicle.
 * @param startIntersection The starting intersection for the vehicle.
 * @param endIntersection The ending intersection for the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
void Vehicles::insertAtHead(string VehicleID, string startIntersection, string endIntersection, string priorityLevel){
    // Create new Vehicle and set its attributes
    Vehicle* newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);

    if(isEmpty()){
        head = newVehicle;
    }
    else{
        // When head isn't NULL, store its address in the new Vehicle
        newVehicle->next = head;
        head = newVehicle;
    }
}

/**
 * @brief Enqueues a new Vehicle at the end of the list or at the head if priority is high.
 * @param VehicleID The unique identifier for the vehicle.
 * @param startIntersection The starting intersection for the vehicle.
 * @param endIntersection The ending intersection for the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 */
void Vehicles::enqueue(string VehicleID, string startIntersection, string endIntersection, string priorityLevel){
    // Create the Vehicle
    Vehicle *temp = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);
    // If the Vehicles list is empty
    if(isEmpty()){
        head = temp;
        return;
    }
    if(priorityLevel == "High"){
        insertAtHead(VehicleID, startIntersection, endIntersection, priorityLevel);
        return;
    }
    else{
        Vehicle *current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = temp;
    }
}

/**
 * @brief Inserts a new Vehicle after a specified position in the list.
 * @param position The position after which the new Vehicle should be inserted.
 * @param VehicleID The unique identifier for the vehicle.
 * @param startIntersection The starting intersection for the vehicle.
 * @param endIntersection The ending intersection for the vehicle.
 * @param priorityLevel The priority level of the vehicle.
 * @return True if the insertion was successful, false otherwise.
 */
bool Vehicles::insertAfterPosition(int position, string VehicleID, string startIntersection, string endIntersection, string priorityLevel){
    Vehicle *newVehicle = new Vehicle(VehicleID, startIntersection, endIntersection, priorityLevel);
    if(position < 0){
        return false;
    }
    if(position == 0){
        insertAtHead(VehicleID, startIntersection, endIntersection, priorityLevel);
    }
    else{
        int index = 0;
        Vehicle *current = head;
        Vehicle *next;
        while(current->next != NULL && index < position){
            current = current->next;
            index++;
        }
        next = current->next;
        current->next = newVehicle;
        newVehicle->next = next;
    }
    return true;
}

/**
 * @brief Inserts a new Vehicle after an existing vehicle with a specific ID.
 * @param ID The ID of the vehicle after which the new vehicle should be inserted.
 * @param VehicleID The unique identifier for the new vehicle.
 * @param startIntersection The starting intersection for the new vehicle.
 * @param endIntersection The ending intersection for the new vehicle.
 * @param priorityLevel The priority level of the new vehicle.
 * @return True if the insertion was successful, false otherwise.
 */
bool Vehicles::insertAfterID(string ID, string VehicleID, string startIntersection, string endIntersection, string priorityLevel){
    int index = 0;
    index = findIDInVehicles(ID);
    if(index != -1){
        insertAfterPosition(index, VehicleID, startIntersection, endIntersection, priorityLevel);
        return true;
    }
    return false;
}

/**
 * @brief Deletes the first Vehicle in the list.
 */
void Vehicles::deleteAtStart(){
    if(!isEmpty()){
        Vehicle *temp = head; // Store old head/first Vehicle
        head = head->next; // New head is the next Vehicle
        delete temp; // Delete old head/first Vehicle
    }
}

/**
 * @brief Deletes the last Vehicle in the list.
 * @return True if the deletion was successful, false otherwise.
 */
bool Vehicles::deleteAtEnd() {
    if (isEmpty()) {
        return false;
    }
    // Only one Vehicle in the list
    if (head->next == NULL) {
        deleteAtStart();
        return true;
    }
    // Delete from end when Vehicles > 1
    Vehicle* secondLast = head;
    while (secondLast->next->next != NULL) {
        secondLast = secondLast->next;
    }

    // Delete the last Vehicle
    delete (secondLast->next);
    secondLast->next = NULL;
    return true;
}

/**
 * @brief Deletes a Vehicle at a specific index.
 * @param position The index of the Vehicle to delete.
 * @return True if the deletion was successful, false otherwise.
 */
bool Vehicles::deleteAtIndex(int position){
    if(position < 0){
        return false;
    }
    if(position == 0){
        deleteAtStart();
        return true;
    }
    Vehicle *current = head;
    Vehicle *previous = NULL;
    int index = 0;
    while (current->next->next != NULL && index < position) {
        previous = current;
        current = current->next;
        index++;
    }
    previous->next = current->next;
    // Delete the Vehicle
    delete current;
    return true;
}

/**
 * @brief Deletes a Vehicle by its ID.
 * @param ID The ID of the Vehicle to delete.
 * @return True if the deletion was successful, false otherwise.
 */
bool Vehicles::deleteAtID(string ID){
    if(head->vehicleID == ID){
        deleteAtStart();
        return true;
    }
    Vehicle *current = head;
    Vehicle *previous = NULL;

    while (current->next->next != NULL && current->vehicleID != ID) {
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
    // Delete the Vehicle
    delete current;
    return true;
}

/**
 * @brief Checks if the Vehicles list is empty.
 * @return True if the list is empty, false otherwise.
 */
bool Vehicles::isEmpty(){
    return head == NULL;
}

/**
 * @brief Prints the details of all Vehicles in the list.
 */
void Vehicles::printVehicles(){
    cout << endl;
    Vehicle *temp = head;
    while(temp != NULL){
        cout << temp->vehicleID << " " << temp->priorityLevel << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

/**
 * @brief Finds if a Vehicle ID exists in the list.
 * @param vehicleID The ID of the Vehicle to find.
 * @return The index of the Vehicle in the list, or -1 if not found.
 */
int Vehicles::findIDInVehicles(string vehicleID){
    Vehicle *temp = head;
    int index = -1;
    while(temp != NULL){
        index++;
        if(temp->vehicleID == vehicleID){
            break;
        }
        temp = temp->next;
    }
    if(temp != NULL)
       return index; 
    return -1;
}

/**
 * @brief Loads and reads vehicle data from CSV files.
 */
void Vehicles::loadAndReadCSVs() {
    ifstream vehiclesFile("dataset/vehicles.csv");
    ifstream emergencyVehiclesFile("dataset/emergency_vehicles.csv");

    string line, vehicleID, startIntersection, endIntersection, priorityLevel;

    // Read vehicles.csv
    if (vehiclesFile.is_open()) {
        getline(vehiclesFile, line); // Skip the header
        while (getline(vehiclesFile, line)) {
            stringstream ss(line);
            getline(ss, vehicleID, ',');
            getline(ss, startIntersection, ',');
            getline(ss, endIntersection, ',');
            enqueue(vehicleID, startIntersection, endIntersection, "low");
        }
        vehiclesFile.close();
    }

    // Read emergency_vehicles.csv
    if (emergencyVehiclesFile.is_open()) {
        getline(emergencyVehiclesFile, line); // Skip the header
        while (getline(emergencyVehiclesFile, line)) {
            stringstream ss(line);
            getline(ss, vehicleID, ',');
            getline(ss, startIntersection, ',');
            getline(ss, endIntersection, ',');
            getline(ss, priorityLevel, ',');
            if(findIDInVehicles(vehicleID) == -1){
                enqueue(vehicleID, startIntersection, endIntersection, priorityLevel);
            }
        }
        emergencyVehiclesFile.close();
    }
}

/**
 * @brief Returns a copy of the head of the Vehicles list.
 * @return The head of the Vehicles list.
 */
Vehicle* Vehicles::getHead() {
    Vehicle* copyHead = new Vehicle(head->vehicleID, head->startIntersection, head->endIntersection, head->priorityLevel);
    return copyHead;
}
