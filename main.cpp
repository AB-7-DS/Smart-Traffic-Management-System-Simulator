#include "graph.cpp"
#include "accidents.cpp"
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
    cityGraph.loadRoadData("road_network.csv");

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
    return 0;
}
