#include "graph.h"
#include "accidents.h"
#include "vehicle.h"
#include "vehicles.h"
#include "Route.h"
#include "roadQueue.h"
#include "congestionMonitoring.h"
#include "congestionMaxHeap.h"
#include "trafficSignal.h"
#include "trafficLightManagement.h"
#include "visualizer.h"
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Main entry point of the program.
 *
 * This function creates a graph representing a city's road network, loads road data from a CSV file,
 * marks intersections as blocked based on accident data, and displays the updated road status.
 * It demonstrates how to interact with the Graph and Accident_roads classes.
 */

int main() {
    // Object Initialization
    Graph cityGraph;
    Vehicles vehicles;
    Accident_roads accidentManager;
    GPS gps(&cityGraph);
    // Loading Data from a CSV file
    cityGraph.loadRoadData("dataset/road_network.csv");
    accidentManager.loadRoadData(cityGraph);
    vehicles.loadAndReadCSVs();
    vehicles.addPaths(gps);
    CongestionMonitoring ht(vehicles.getHead());
    ht.makeHashTable(vehicles.getHead());
    ht.makeHashTable(vehicles.getHead());

    TrafficLightManagement traffic;
    traffic.makeTrafficSignals();
    CongestionMaxHeap maxHeap;
    maxHeap.makeHeap(ht.hashTable, HASH_TABLE_SIZE);    
    
    cout << "\nmost congested road: " << maxHeap.mostCongested()->path[0] << maxHeap.mostCongested()->path[1]<< endl;
    string start,end,path;
    int choice;
    do {
        // Display the menu
        cout << "------ Simulation Dashboard ------\n";
        cout << "1. Display City Traffic Network\n";
        cout << "2. Display Traffic Signal Status\n";
        cout << "3. Display Congestion Status\n";
        cout << "4. Display Blocked Roads\n";
        cout << "5. Handle Emergency Vehicle Routing\n";
        cout << "6. Block Road due to Accident\n";
        cout << "7. Simulate Vehicle Routing\n";
        cout << "8. Exit Simulation\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle menu choices using switch-case
        switch (choice) {
            case 1:
                cityGraph.printAdjacencyList();
                cityGraph.displayRoadStatuses();
                break;
            case 2:
                traffic.printGreenTimes();
                break;
            case 3:
                ht.printHashTable();
                break;
            case 4:
                accidentManager.displayBlockedRoads();
                accidentManager.displayUnderRepairRoads();
                break;
            case 5:
                cout << "Enter the start intersection to block: ";
                cin >> start;
                cout << "Enter the end intersection to block: ";
                cin >> end;
                //will added check function to check if vehicle is emergency
                path = gps.rerouteEmergencyVehicle(start, end);
                cout << "The new path for the emergency vehicle is: " << path << endl;
                break;
            case 6: {
                cout << "Enter the start intersection to block: ";
                cin >> start;
                cout << "Enter the end intersection to block: ";
                cin >> end;

                // Use the Accident_roads member function to block the road
                accidentManager.blockRoad(start, end, cityGraph);
                break;
            }
            case 7:
                cout << "Enter the start intersection : ";
                cin >> start;
                cout << "Enter the end intersection : ";
                cin >> end;
                gps.printAllPaths(start, end);

                break;
            case 8:
                cout << "Exiting Simulation. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

        cout << endl; // Line break for better readability
    } while (choice != 8);
    
    Visualizer visualizer;
    Vehicle *temp = vehicles.getHead();
    while(temp!=NULL){
        //find best path for all vehicles
        string start = temp->startIntersection;
        string end = temp->endIntersection;
        string path = (gps.rerouteEmergencyVehicle(start,end));
        if(path!=""){
        temp->setPath(path);
        }
        temp = temp->next;
    }
    visualizer.drawSimulation(cityGraph, vehicles);
    return 0;
}


