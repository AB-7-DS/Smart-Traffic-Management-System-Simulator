#include "graph.h"
#include <fstream>
#include<sstream>
#include <iostream>
#include <string>

// Vertex class definition
Vertex::Vertex(const std::string& name) : name(name), blocked(false), edges(nullptr) {}

bool Vertex::isBlocked() const {
    return blocked;
}

void Vertex::setBlocked(bool status) {
    blocked = status;
}

// Edge class definition
Edge::Edge(Vertex* destination, int travelTime) : destination(destination), travelTime(travelTime) {}

// EdgeNode class definition
EdgeNode::EdgeNode(Edge* edge) : edge(edge), next(nullptr) {}

// VertexNode class definition
VertexNode::VertexNode(Vertex* vertex) : vertex(vertex), next(nullptr) {}

// Graph constructor
Graph::Graph() : headVertex(nullptr) {}

// Graph destructor
Graph::~Graph() {
    // Delete all vertices and edges from memory
    VertexNode* current = headVertex;
    while (current) {
        VertexNode* temp = current;
        current = current->next;

        // Delete all the edges of the vertex
        EdgeNode* edgeCurrent = temp->vertex->edges;
        while (edgeCurrent) {
            EdgeNode* edgeTemp = edgeCurrent;
            edgeCurrent = edgeCurrent->next;
            delete edgeTemp;
        }

        delete temp->vertex;  // Delete the vertex itself
        delete temp;          // Delete the vertex node
    }
}

// Add a vertex to the graph
void Graph::addVertex(const std::string& name) {
    if (findVertex(name)) {
        std::cerr << "Vertex " << name << " already exists!" << std::endl;
        return;
    }

    Vertex* newVertex = new Vertex(name);
    VertexNode* newNode = new VertexNode(newVertex);

    if (!headVertex) {
        headVertex = newNode; // First vertex
    } else {
        VertexNode* current = headVertex;
        while (current->next) {
            current = current->next; // Traverse to the end
        }
        current->next = newNode; // Add at the end
    }
}


// Find a vertex by name
Vertex* Graph::findVertex(const std::string& name) {
    VertexNode* current = headVertex;
    while (current) {
        if (current->vertex->name == name) {
            return current->vertex;
        }
        current = current->next;
    }
    return nullptr;  // Vertex not found
}

// Add an edge between two vertices
void Graph::addEdge(const std::string& start, const std::string& end, int travelTime) {
    Vertex* startVertex = findVertex(start);
    Vertex* endVertex = findVertex(end);

    if (!startVertex || !endVertex) {
        std::cerr << "Error: One or both vertices not found!" << std::endl;
        return;
    }

    // Create a new edge and add it to the end of the start vertex's edge list
    Edge* newEdge = new Edge(endVertex, travelTime);
    EdgeNode* newEdgeNode = new EdgeNode(newEdge);
    if (!startVertex->edges) {
        // If no edges exist, add as the first edge
        startVertex->edges = newEdgeNode;
    } else {
        // Traverse to the end of the edge list
        EdgeNode* current = startVertex->edges;
        while (current->next) {
            current = current->next;
        }
        current->next = newEdgeNode;
    }

    // If the graph is undirected, add the reverse edge at the end of the end vertex's edge list
    newEdge = new Edge(startVertex, travelTime);
    newEdgeNode = new EdgeNode(newEdge);
    if (!endVertex->edges) {
        endVertex->edges = newEdgeNode;
    } else {
        EdgeNode* current = endVertex->edges;
        while (current->next) {
            current = current->next;
        }
        current->next = newEdgeNode;
    }
}
void Graph::loadRoadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // Reading each subsequent line in the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string start, end;
        int travelTime;

        // Extract the values (comma-separated)
        std::getline(ss, start, ',');
        std::getline(ss, end, ',');
        ss >> travelTime;

        // Add vertices if they don't exist
        if (!findVertex(start)) {
            addVertex(start);
        }
        if (!findVertex(end)) {
            addVertex(end);
        }

        // Add the edge between the two vertices
        addEdge(start, end, travelTime);
    }

    file.close();
}
// Display the status of all roads (edges) in the graph
void Graph::displayRoadStatuses() {
    VertexNode* currentVertexNode = headVertex;
    while (currentVertexNode) {
        Vertex* vertex = currentVertexNode->vertex;
        std::cout << "Vertex: " << vertex->name << "\n";
        EdgeNode* currentEdgeNode = vertex->edges;
        while (currentEdgeNode) {
            Edge* edge = currentEdgeNode->edge;
            std::cout << "  -> " << edge->destination->name << " (Travel time: " << edge->travelTime << ")\n";
            currentEdgeNode = currentEdgeNode->next;
        }
        currentVertexNode = currentVertexNode->next;
    }
}

// Add an edge to a vertex's adjacency list
void Graph::addEdgeToVertex(Vertex* vertex, Edge* edge) {
    EdgeNode* newEdgeNode = new EdgeNode(edge);
    newEdgeNode->next = vertex->edges;
    vertex->edges = newEdgeNode;
}

// Mark intersections as blocked in the graph
void Graph::markIntersectionsAsBlocked(const std::string& intersection1, const std::string& intersection2, bool isBlocked) {
    Vertex* v1 = findVertex(intersection1);
    Vertex* v2 = findVertex(intersection2);

    // Mark both intersections as blocked if applicable
    if (v1) v1->setBlocked(isBlocked);
    if (v2) v2->setBlocked(isBlocked);
}

// Display the blocked intersections
void Graph::displayBlockedIntersections() {
    std::cout << "Blocked Intersections:\n";

    // Traverse the linked list of vertices
    VertexNode* current = headVertex;
    bool foundBlocked = false;  // To track if any blocked intersection is found

    while (current) {
        if (current->vertex->isBlocked()) {
            std::cout << "- " << current->vertex->name << " is blocked.\n";
            foundBlocked = true;
        }
        current = current->next;  // Move to the next vertex
    }

    if (!foundBlocked) {
        std::cout << "No intersections are currently blocked.\n";
    }
}
/////////////////////////////////////////////////////////////////////////

void Graph::displayIntersectionStatus()  {
    // Traverse through all vertices and display their status
    VertexNode* current = headVertex;  // Assuming headVertex is the starting point of the vertices linked list
    
    std::cout << "Intersection Status:\n";
    while (current != nullptr) {
        // Check if the current vertex is blocked
        std::cout << "Intersection: " << current->vertex->name << " - ";
        if (current->vertex->isBlocked()) {
            std::cout << "Blocked\n";
        } else {
            std::cout << "Open\n";
        }
        current = current->next;  // Move to the next vertex
    }
    
}
void Graph::printAdjacencyList() {
    VertexNode* currentVertexNode = headVertex;

    // Iterate through each vertex in the graph
    while (currentVertexNode) {
        Vertex* vertex = currentVertexNode->vertex;
        std::cout << vertex->name << " -> ";

        EdgeNode* currentEdgeNode = vertex->edges;

        // Print all edges for the current vertex
        while (currentEdgeNode) {
            Edge* edge = currentEdgeNode->edge;
            std::cout << "(" << edge->destination->name << ", " << edge->travelTime << " min)";
            currentEdgeNode = currentEdgeNode->next;
            if (currentEdgeNode) std::cout << ", ";
        }
        std::cout << std::endl;

        currentVertexNode = currentVertexNode->next;
    }
}
// Checks if a vertex (node) is blocked
bool Graph::isBlocked(const std::string& nodeName) {
    Vertex* vertex = findVertex(nodeName); // Find the vertex
    if (vertex) {
        return vertex->isBlocked();  // Return the blocked status of the vertex
    }
    return false; // If the vertex is not found, return false
}

int Graph::getVertexCount() {
    int count = 0;
    VertexNode* current = headVertex;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}
// Gets all the neighbors of a specific vertex
void Graph::getNeighbors(const std::string& nodeName, std::string* neighbors, int& count) {
    Vertex* vertex = findVertex(nodeName); // Find the vertex
    if (vertex) {
        count = 0;
        EdgeNode* temp = vertex->edges;  // Start with the adjacency list (edges)
        while (temp) {
            neighbors[count++] = temp->edge->destination->name; // Add neighbor's name
            temp = temp->next;  // Move to the next edge
        }
    } else {
        count = 0; // If the vertex is not found, set count to 0
    }
}

// Gets the weight of the edge between two vertices
int Graph::getEdgeWeight(const std::string& start, const std::string& end) {
    Vertex* startVertex = findVertex(start);
    Vertex* endVertex = findVertex(end);
    
    if (startVertex && endVertex) {
        EdgeNode* temp = startVertex->edges;
        while (temp) {
            if (temp->edge->destination == endVertex) {
                return temp->edge->travelTime; // Return the travel time if edge found
            }
            temp = temp->next;
        }
    }
    return -1; // Return -1 if no edge exists between the two vertices
}

// Gets all the vertices in the graph
void Graph::getVertices(std::string* vertices, int& count) {
    count = 0;
    VertexNode* temp = headVertex;
    while (temp) {
        vertices[count++] = temp->vertex->name; // Add vertex name to the list
        temp = temp->next;  // Move to the next vertex
    }
}
