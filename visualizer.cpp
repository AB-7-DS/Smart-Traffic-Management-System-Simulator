#include "visualizer.h"
#include <SFML/Graphics.hpp>
#include<cmath>
Visualizer::Visualizer(){

    
}

void Visualizer::drawSimulation(Graph &graph, Vehicles &vehicles,TrafficLightManagement &traffic,CongestionMonitoring &ht,Accident_roads &accidentManager) {
sf::RenderWindow window(sf::VideoMode(800, 800), "Graph Visualization");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        VertexNode* currentVertexNode = graph.headVertex;
        std::map<std::string, sf::Vector2f> positions;

        // Calculate the center and radius of the circle
        sf::Vector2f center(400, 400);
        float radius = 350.0f;
        int numVertices = 0;

        // Count the number of vertices
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            numVertices++;
            currentVertexNode = currentVertexNode->next;
        }
        sf::Font font;
        if (!font.loadFromFile("sprites/font.ttf")) {
            // handle error
            std::cout << "Couldn't load font\n";
        }
        // Calculate the angle between each vertex
        float angleIncrement = 2 * M_PI / numVertices;
        float currentAngle = 0.0f;

        // draw vertices in a circular pattern
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;

            // Calculate the position of the vertex
            float x = center.x + radius * cos(currentAngle);
            float y = center.y + radius * sin(currentAngle);

            positions[vertex->name] = sf::Vector2f(x + 20, y + 20);

            currentAngle += angleIncrement;
            sf::Text label;
            label.setFont(font);
            label.setString(vertex->name);
            label.setCharacterSize(47); // in pixels
            label.setFillColor(sf::Color::White);
            label.setPosition(x, y-7); // position of the label
            window.draw(label);
            int greenTime = traffic.getSignal(vertex->name)->getDuration();
            string greenTimeStr = to_string(greenTime);
            label.setString(greenTimeStr);
            label.setPosition(x - 20, y - 20); // position of the label
            drawVehicles(vehicles, vertex->name, positions[vertex->name], window);
            currentVertexNode = currentVertexNode->next;
        }
        

        // Second pass: draw edges as lines
        currentVertexNode = graph.headVertex;
        while (currentVertexNode) {
            Vertex* vertex = currentVertexNode->vertex;
            EdgeNode* currentEdgeNode = vertex->edges;

            while (currentEdgeNode) {
                Edge* edge = currentEdgeNode->edge;

                // Only draw the edge if it exists as a directed path
                std::string start = vertex->name;
                std::string end = edge->destination->name;

                // Check if the edge exists in the adjacency list (directed A -> B only)
                if (graph.getEdgeWeight(start, end) != -1) {
                    // Get the color for the edge
                    sf::Color color = choseColor(currentEdgeNode, vertex, traffic, ht, accidentManager);
                   // Create the vertex array with the correct color
                    sf::Vertex line[] = {
                        sf::Vertex(positions[start], color), // Start vertex
                        sf::Vertex(positions[end], color)   // End vertex
                    };

                    // Draw the edge
                    window.draw(line, 2, sf::Lines);
                }

                currentEdgeNode = currentEdgeNode->next;
            }

            currentVertexNode = currentVertexNode->next;
        }

        sf::Font font2;
        if (!font2.loadFromFile("sprites/font3.ttf")) {
            std::cerr << "Couldn't load font\n";
            return;
        }
        // Third pass: draw edge weights
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
            sf::Color edgeColor = choseColor(currentEdgeNode, vertex, traffic, ht, accidentManager);
            sf::Vertex line[] = {
                sf::Vertex(startPos, edgeColor),
                sf::Vertex(endPos, edgeColor)
            };
            window.draw(line, 2, sf::Lines);

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
        
        window.display();
        sf::sleep(sf::seconds(1));
        Vehicle *currentVehicle = vehicles.getHead();
        while (currentVehicle != NULL) {
            if(currentVehicle->presetPath)
            currentVehicle->moveForward();
            
            currentVehicle = currentVehicle->next;
        }
    }
}

void Visualizer::drawVehicles(Vehicles &vehicles, const std::string &intersection, const sf::Vector2f &position, sf::RenderWindow &window) {
    Vehicle *currentVehicle = vehicles.getHead();
    int decrement = 0;
    while (currentVehicle != NULL) {
        if (currentVehicle->path[currentVehicle->currentIntersectionInPath] == intersection) { // Match vehicle start point
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
 
float Visualizer::getElapsedTimeInSeconds() {
    return clock.getElapsedTime().asSeconds();
}
sf::Color Visualizer::choseColor(EdgeNode *edgeNode, Vertex *vertex, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager) {
    
    //Check if the edge is blocked
    if(edgeNode->edge->isBlocked()){
        return sf::Color::Magenta;
    }
    // Check if the edge is congested
    // if (ht.findRoadNode(vertex->name[0], vertex->edges->edge->destination->name[0])->carCount > 5) {
    //     return sf::Color::Red;
    // }
    

    // Check if the edge has a green light
    string signal = traffic.getSignal(vertex->name)->state;
    if (signal=="green") {
        cout<<"Green light"<<endl;
        return sf::Color::Green;
    }

    // Default color if none of the above conditions are met
    return sf::Color::White;
}
