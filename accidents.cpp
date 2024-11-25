#include "accidents.h"
#include "graph.h"
#include <fstream>
#include <iostream>

// Constructor
Accident_roads::Accident_roads() : head(nullptr) {}

// Destructor
Accident_roads::~Accident_roads() {
    AccidentNode* current = head;
    while (current) {
        AccidentNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void Accident_roads::loadRoadData(Graph& graph) {
    std::ifstream file("dataset/accidents_or_closures.csv"); // Hardcoded file name
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file accidents_or_closures.csv" << std::endl;
        return;
    }

    std::string intersection1, intersection2, status;
    while (file.good()) {
        std::getline(file, intersection1, ',');
        std::getline(file, intersection2, ',');
        std::getline(file, status);

        if (!intersection1.empty() && !intersection2.empty() && !status.empty()) {
            bool isBlocked = (status == "Blocked");

            // Update the graph's vertices' blocked status
            graph.markIntersectionsAsBlocked(intersection1, intersection2, isBlocked);
        }
    }

    file.close();
}
