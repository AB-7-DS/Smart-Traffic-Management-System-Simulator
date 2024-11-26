#include<string>
#include "vehicle.h"
using namespace std;
Vehicle::Vehicle(string vehicleID, string startIntersection, string endIntersection, string priorityLevel)
    : startIntersection(startIntersection), endIntersection(endIntersection)
{
    this->vehicleID = vehicleID;
    this->priorityLevel = priorityLevel;
    this->next = NULL;
    this->path = new string[1000];
    this->currentIntersectionInPath = 0;
    this->path[currentIntersectionInPath] = startIntersection;
    this->pathLength = 1;

}
void Vehicle::moveForward(string nextIntersectionId){
    currentIntersectionInPath++;
    path[currentIntersectionInPath] = nextIntersectionId;
    pathLength++;
}

void Vehicle::printVehicle(){
    cout << "Vehicle ID: " << vehicleID << endl;
    cout << "Start Intersection: " << startIntersection << endl;
    cout << "End Intersection: " << endIntersection << endl;
    cout << "Priority Level: " << priorityLevel << endl;
    cout << "Path Traversed: ";
    for(int i = 0; i < pathLength; i++){
        cout << path[i] << " ";
    }
    cout << endl;
}