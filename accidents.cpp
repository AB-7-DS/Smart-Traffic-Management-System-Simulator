
#include "accidents.h"
#include "graph.h"
#include <fstream>
#include <iostream>

// Constructor
Accident_roads::Accident_roads() : head(nullptr), underRepairHead(nullptr) {}

// Destructor
Accident_roads::~Accident_roads() {
    // Delete accident nodes (Blocked)
    AccidentNode* current = head;
    while (current) {
        AccidentNode* temp = current;
        current = current->next;
        delete temp;
    }

    // Delete under repair nodes
    AccidentNode* repairCurrent = underRepairHead;
    while (repairCurrent) {
        AccidentNode* temp = repairCurrent;
        repairCurrent = repairCurrent->next;
        delete temp;
    }
}

void Accident_roads::loadRoadData(Graph& graph) {
    std::ifstream file("dataset/road_closures.csv"); 
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file road_closures.csv" << std::endl;
        return;
    }

    std::string intersection1, intersection2, status;
    while (file.good()) {
        std::getline(file, intersection1, ','); 
        std::getline(file, intersection2, ',');
        std::getline(file, status);

        if (!intersection1.empty() && !intersection2.empty() && !status.empty()) {
            bool isBlocked = (status == "Blocked");

            // Create a new node for this road closure
            AccidentNode* newNode = new AccidentNode(intersection1, intersection2, isBlocked);
            
            // Insert the new node at the end of the blocked list
            if (isBlocked) {
                if (head == nullptr) {
                    head = newNode;  // If the list is empty, the new node is the first node
                } else {
                    AccidentNode* temp = head;
                    while (temp->next != nullptr) {
                        temp = temp->next;  // Traverse to the end of the list
                    }
                    temp->next = newNode;  // Insert the new node at the end
                    graph.markEdgeAsBlocked(intersection1, intersection2, true);
                }
            } else if (status == "Under Repair") {
                // Insert under repair intersections in the separate list at the end
                if (underRepairHead == nullptr) {
                    underRepairHead = newNode;  // If the list is empty, the new node is the first node
                } else {
                    AccidentNode* temp = underRepairHead;
                    while (temp->next != nullptr) {
                        temp = temp->next;  // Traverse to the end of the list
                    }
                    temp->next = newNode;  // Insert the new node at the end
                    graph.markEdgesAsUnderRepaired(intersection1, intersection2, true);
                }
                
            }

            
            
        }
    }

    file.close();
}
void Accident_roads::displayBlockedRoads() {
    std::cout << "Blocked Roads:\n";

    AccidentNode* current = head;
    if (current == nullptr) {
        std::cout << "No blocked roads.\n";
    }

    while (current) {
        std::cout << "- " << current->intersection1 << " to " << current->intersection2 << " is blocked.\n";
        current = current->next;
    }
}

void Accident_roads::displayUnderRepairRoads() {
    std::cout << "Under Repair Roads:\n";

    AccidentNode* current = underRepairHead;
    if (current == nullptr) {
        std::cout << "No roads under repair.\n";
    }

    while (current) {
        std::cout << "- " << current->intersection1 << " to " << current->intersection2 << " is under repair.\n";
        current = current->next;
    }
}

void Accident_roads::blockRoad(const std::string& start, const std::string& end, Graph& cityGraph) {
    // Check if both intersections exist in the graph
    if (cityGraph.findVertex(start) == nullptr || cityGraph.findVertex(end) == nullptr) {
        std::cout << "One or both intersections do not exist in the graph.\n";
        return;
    }

    // Mark the intersections as blocked in the graph
    cityGraph.markEdgeAsBlocked(start, end, true);

    // Add the blocked road to the accident manager
    AccidentNode* newBlockedRoad = new AccidentNode(start, end, true);
    if (head == nullptr) {
        head = newBlockedRoad;  // If the list is empty, make this the first node
    } else {
        AccidentNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;  // Traverse to the end of the list
        }
        temp->next = newBlockedRoad;  // Add the new node at the end
    }

    // Display the updated list of blocked roads
    std::cout << "\nUpdated Blocked Roads:\n";
    displayBlockedRoads();
}
