#include "graph.cpp"
#include "accidents.cpp"
#include "vehicle.cpp"
#include <iostream>
using namespace std;
/**
 * @brief Main entry point of the program.
 *
 * This function creates a graph representing a city's road network, loads road data from a CSV file,
 * marks intersections as blocked based on accident data, and displays the updated road status.
 * It demonstrates how to interact with the Graph and Accident_roads classes.
 */
int main() {
    // Create a graph for the road network
    Graph cityGraph;

    // Load the road network from a CSV file
    cityGraph.loadRoadData("dataset/road_network.csv");

    

    // Create an instance of the Accident_roads class
    Accident_roads accidentManager;

    // Load accident or blocked road data and update the graph
    accidentManager.loadRoadData(cityGraph);
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
                break;
            case 2:
                
                break;
            case 3:
              
                break;
            case 4:
               accidentManager.displayBlockedRoads();
               accidentManager.displayUnderRepairRoads();

                break;
            case 5:
               
                break;
            case 6:
              
                break;
            case 7:
               
                break;
            case 8:
                cout << "Exiting Simulation. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

        cout << endl; // Line break for better readability
    } while (choice != 8);

 





    std::cout << "\n\nVehicle Simulation\n";
    Vehicle v("V1", "A", "D", "high");
    v.printVehicle();
    std::cout << "\nMoving to next intersection...\n";
    v.moveForward("B");
    v.printVehicle();
    std::cout << "\nMoving forward without specifying the next intersection...\n";
    v.moveForward();
    v.printVehicle();
    std::cout << "\nNothing happens if the path is not preset...\n";
    std::cout << "\nMoving to next intersection...\n";
    v.moveForward("C");
    v.printVehicle();


    std::cout << "\nNow making another vehicle with a preset path...\n";
    Vehicle v2("V2", "A", "C", "low");
    v2.setPath("ABC");
    std::cout << "Vehicle 2's path is preset to A -> B -> C\n";
    v2.printPath();
    v2.printVehicle();
    std::cout << "\nMoving to next intersection...\n";
    v2.moveForward();
    v2.printVehicle();

    std::cout << "\nThe vehicle with a preset path will not deviate from the path even if you specify the next intersection...\n";
    std::cout << "Moving to the next intersection (D)...\n";
    v2.moveForward("D");
    v2.printVehicle();

    return 0;
}
