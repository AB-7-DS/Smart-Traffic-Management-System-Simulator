#include "graph.cpp"
#include "accidents.cpp"
#include "vehicle.cpp"
#include <iostream>

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

    // Display the initial road network status
    std::cout << "Initial Road Network Status:\n";
    cityGraph.displayRoadStatuses();

    // Create an instance of the Accident_roads class
    Accident_roads accidentManager;

    // Load accident or blocked road data and update the graph
    accidentManager.loadRoadData(cityGraph);

    // Mark blocked intersections in the graph
    cityGraph.displayBlockedIntersections();

    // Display the updated road network with blocked intersections
    std::cout << "\nUpdated Road Network Status:\n";
    cityGraph.displayRoadStatuses();
     // Display the status of all intersections for debugging purposes
    cityGraph.displayIntersectionStatus();

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
