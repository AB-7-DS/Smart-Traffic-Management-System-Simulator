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
  
    TrafficLightManagement traffic;
    traffic.makeTrafficSignals();
    CongestionMaxHeap maxHeap;
    maxHeap.makeHeap(ht.hashTable, HASH_TABLE_SIZE);    
   
   


    string start,end,path;
    int choice,c;
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
              
                do{
                    cout << "Enter your Choice :\n 1.Road Network\t2.Road Status\t0.Exit\nYour choice: ";
                    cin >> c;
                    if(c==1)
                    {
                       cityGraph.printAdjacencyList();
                    }
                    else if(c==2)
                    {
                        cityGraph.displayRoadStatuses();
                    }
                    else if(c==0)
                    {

                        cout << "Exiting ......";
                       
                    }
                    else
                        cout<<"Invalid Choice!. Try again!\n";
                }while(c!=0);    
                break;
            case 2:
                traffic.printGreenTimes();
                break;
            case 3:
                ht.printHashTable();
            cout << "\nMost congested road: " << maxHeap.mostCongested()->path[0] <<" to "<< maxHeap.mostCongested()->path[1]<< endl;
                break;
            case 4:
             
                do{
                    cout << "Which Road to display?:\n 1.Blocked roads\t2.Under Repair Roads\t0.Exit\nYour choice: ";
                    cin >> c;
                    if(c==1)
                    {
                        accidentManager.displayBlockedRoads();
                    }
                    else if(c==2)
                    {
                        accidentManager.displayUnderRepairRoads();
                    }
                    else if(c==0)
                    {

                        cout << "Exiting ......";
                       
                    }
                    else
                        cout<<"Invalid Choice!. Try again!\n";
                }while(c!=0);    
                break;
               
                
                break;
            case 5:
                cout << "Enter the start intersection : ";
                cin >> start;
                cout << "Enter the end intersection : ";
                cin >> end;
                //will added check function to check if vehicle is emergency
                path = gps.rerouteEmergencyVehicle(start, end);
                  cout << "Emergency Vehicle is being routed...... " << path << endl;
                cout << "Emergency Vehicle Path: " << path << endl;
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
                
                do{
                    cout << "Enter Type of Algorithm :\n 1.DFS\t2.Dijkstra\t0.Exit\nYour choice: ";
                    cin >> c;
                    if(c==1)
                    {
                        cout << "Enter the start intersection : ";
                        cin >> start;
                        cout << "Enter the end intersection : ";
                        cin >> end;
                        gps.printAllPaths(start, end);
                    }
                    else if(c==2)
                    {

                        cout << "Enter the start intersection : ";
                        cin >> start;
                        cout << "Enter the end intersection : ";
                        cin >> end;
                        
                    gps.printAllPathsDijkstra(start,end);
                    }
                    else if(c==0)
                    {

                        cout << "Exiting ......";
                       
                    }
                    else
                        cout<<"Invalid Choice!. Try again!\n";
                }while(c!=0);    
                break;
            case 8:
                cout << "Exiting Simulation. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

        cout << endl; 
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
    visualizer.drawSimulation(cityGraph, vehicles,traffic,ht,accidentManager);
    
    return 0;
}


