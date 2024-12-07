#include "graph.cpp"
#include "accidents.cpp"
#include "vehicle.cpp"
#include "vehicles.cpp"
#include "route.cpp"
#include "roadQueue.cpp"
#include "congestionMonitoring.cpp"
#include "trafficSignal.cpp"
#include "trafficLightsManagement.cpp"

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
    CongestionMonitoring ht(vehicles.getHead());
    TrafficLightManagement traffic;
    traffic.makeTrafficSignals();
   
    string start,end;
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
                gps.rerouteEmergencyVehicle(start, end);
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
    
    //Visualizer visualizer;
   // visualizer.drawSimulation(cityGraph, vehicles);
    
     
    return 0;
}


