#include <string>
#include <iostream>
#include "vehicle.h"

Vehicle::Vehicle(std::string vehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel)
    : startIntersection(startIntersection), endIntersection(endIntersection)
{
    this->vehicleID = vehicleID;
    this->priorityLevel = priorityLevel;
    this->next = NULL;
    this->path = new std::string[1000];
    this->currentIntersectionInPath = 0;
    this->path[currentIntersectionInPath] = startIntersection;
    this->pathLength = 1;
    this->presetPath = false;
}
void Vehicle::moveForward(std::string nextIntersectionId){
    if (path[currentIntersectionInPath] == endIntersection)        
        return;
    
    if (presetPath){
        currentIntersectionInPath++;
        return;
    }
    currentIntersectionInPath++;
    path[currentIntersectionInPath] = nextIntersectionId;
    pathLength++;
}

void Vehicle::printVehicle(){
    std::cout << "Vehicle ID: " << vehicleID << std::endl;
    std::cout << "Start Intersection: " << startIntersection << std::endl;
    std::cout << "End Intersection: " << endIntersection << std::endl;
    std::cout << "Priority Level: " << priorityLevel << std::endl;
    std::cout << "Path Traversed: ";
    for(int i = 0; i <= currentIntersectionInPath; i++){
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}

void Vehicle::setPath(std::string path){
    this->presetPath = true;
    for (int i= 0; i< path.length(); i++){
        this->path[i] = path[i];
    }
    this->pathLength = path.length();
}
void Vehicle::printPath(){
    std::cout << "Path: ";
    for(int i = 0; i < pathLength; i++){
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}
