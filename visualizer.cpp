#include "visualizer.h"
#include <SFML/Graphics.hpp>
#include <cmath>

// Constructor for the Visualizer class
Visualizer::Visualizer() {
    // Empty constructor
}

// Function to draw the simulation
void Visualizer::drawSimulation(Graph &graph, Vehicles &vehicles, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager) {
    // Create a window for the simulation
    sf::RenderWindow window(sf::VideoMode(800, 800), "Graph Visualization");

    // Main loop to keep the window open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Initialize variables for drawing vertices
        VertexNode* currentVertexNode = graph.headVertex;
        std::map<std::string, sf::Vector2f> positions;
        sf::Vector2f center(400, 400); // Center of the window
        float radius = 350.0f; // Radius for circular layout
        int numVertices = 0;

        // Count the number of vertices in the graph
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            numVertices++;
            currentVertexNode = currentVertexNode->next;
        }

        // Load the font for vertex labels
        sf::Font font;
        if (!font.loadFromFile("sprites/font.ttf")) {
            std::cout << "Couldn't load font\n";
        }

        // Calculate the angle between each vertex for circular layout
        float angleIncrement = 2 * M_PI / numVertices;
        float currentAngle = 0.0f;

        // Draw vertices in a circular pattern
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;

            // Calculate the position of the vertex
            float x = center.x + radius * cos(currentAngle);
            float y = center.y + radius * sin(currentAngle);

            // Store the position for later use
            positions[vertex->name] = sf::Vector2f(x + 20, y + 20);

            // Increment the angle for the next vertex
            currentAngle += angleIncrement;

            // Draw the vertex label
            sf::Text label;
            label.setFont(font);
            label.setString(vertex->name);
            label.setCharacterSize(47);
            label.setFillColor(sf::Color::White);
            label.setPosition(x, y - 7);
            window.draw(label);

            // Draw the green time for the traffic light
            int greenTime = traffic.getSignal(vertex->name)->getDuration();
            std::string greenTimeStr = std::to_string(greenTime);
            label.setString(greenTimeStr);
            label.setPosition(x - 20, y - 20);
            drawVehicles(vehicles, vertex->name, positions[vertex->name], window);

            currentVertexNode = currentVertexNode->next;
        }

        // Draw edges as lines
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;
            EdgeNode* currentEdgeNode = vertex->edges;

            while (currentEdgeNode) {
                Edge* edge = currentEdgeNode->edge;

                // Only draw the edge if it exists as a directed path
                std::string start = vertex->name;
                std::string end = edge->destination->name;

                if (graph.getEdgeWeight(start, end) != -1) {
                    // Get the color for the edge
                    sf::Color color = choseColor(currentEdgeNode, vertex, traffic, ht, accidentManager);

                    // Create the vertex array with the correct color
                    sf::Vertex line[] = {
                        sf::Vertex(positions[start], color),
                        sf::Vertex(positions[end], color)
                    };

                    // Draw the edge
                    window.draw(line, 2, sf::Lines);
                }

                currentEdgeNode = currentEdgeNode->next;
            }

            currentVertexNode = currentVertexNode->next;
        }

        // Load the font for edge weights
        sf::Font font2;
        if (!font2.loadFromFile("sprites/font3.ttf")) {
            std::cerr << "Couldn't load font\n";
            return;
        }

        // Draw edge weights
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;
            EdgeNode* currentEdgeNode = vertex->edges;
            while (currentEdgeNode) {
                Edge* edge = currentEdgeNode->edge;
                sf::Vector2f startPos = positions[vertex->name];
                sf::Vector2f endPos = positions[edge->destination->name];
                sf::Vector2f midPos = (startPos + endPos) / 2.0f;

                // Determine the direction of the edge
                sf::Vector2f direction = endPos - startPos;
                float angle = atan2(direction.y, direction.x);
                if (angle < 0) {
                    // Offset the line position slightly if the color is blue
                    startPos += sf::Vector2f(5, 5);
                    endPos += sf::Vector2f(5, 5);
                }

                // Get the color for the edge
                sf::Color edgeColor = choseColor(currentEdgeNode, vertex, traffic, ht, accidentManager);
                sf::Vertex line[] = {
                    sf::Vertex(startPos, edgeColor),
                    sf::Vertex(endPos, edgeColor)
                };
                window.draw(line, 2, sf::Lines);

                // Draw the edge weight label
                sf::Text weightLabel;
                weightLabel.setFont(font2);
                weightLabel.setString(std::to_string(edge->travelTime));
                weightLabel.setCharacterSize(20);
                weightLabel.setFillColor(sf::Color::Blue);
                weightLabel.setPosition(midPos);
                window.draw(weightLabel);

                currentEdgeNode = currentEdgeNode->next;
            }
            currentVertexNode = currentVertexNode->next;
        }

        // Display the window contents
        window.display();
        sf::sleep(sf::seconds(1));

        // Move vehicles forward
        Vehicle *currentVehicle = vehicles.getHead();
        while (currentVehicle != NULL) {
            if (currentVehicle->presetPath)
                currentVehicle->moveForward();

            currentVehicle = currentVehicle->next;
        }
    }
}

// Function to draw vehicles at a specific intersection
void Visualizer::drawVehicles(Vehicles &vehicles, const std::string &intersection, const sf::Vector2f &position, sf::RenderWindow &window) {
    Vehicle *currentVehicle = vehicles.getHead();
    int decrement = 0;
    while (currentVehicle != NULL) {
        if (currentVehicle->path[currentVehicle->currentIntersectionInPath] == intersection) {
            // Draw vehicle label
            sf::Font font;
            if (!font.loadFromFile("sprites/font3.ttf")) {
                std::cerr << "Couldn't load font\n";
                return;
            }

            sf::Text label;
            label.setFont(font);
            label.setString(currentVehicle->vehicleID);
            label.setCharacterSize(20);
            label.setFillColor(sf::Color::Red);
            label.setPosition(position.x, position.y - 20 + decrement);
            window.draw(label);
            decrement -= 20;
        }
        currentVehicle = currentVehicle->next;
    }
}

// Function to get the elapsed time in seconds
float Visualizer::getElapsedTimeInSeconds() {
    return clock.getElapsedTime().asSeconds();
}

// Function to choose the color for an edge based on various conditions
sf::Color Visualizer::choseColor(EdgeNode *edgeNode, Vertex *vertex, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager) {
    // Check if the edge is blocked
    if (edgeNode->edge->isBlocked()) {
        return sf::Color::Magenta;
    }

    // Check if the edge has a green light
    std::string signal = traffic.getSignal(vertex->name)->state;
    if (signal == "green") {
        std::cout << "Green light" << std::endl;
        return sf::Color::Green;
    }

    // Default color if none of the above conditions are met
    return sf::Color::White;
}
