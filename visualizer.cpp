#include "visualizer.h"
#include <SFML/Graphics.hpp>
#include<cmath>
Visualizer::Visualizer(){}

void Visualizer::drawSimulation(Graph &graph, Vehicles &vehicles,TrafficLightManagement &traffic,CongestionMonitoring &ht,Accident_roads &accidentManager) {
sf::RenderWindow window(sf::VideoMode(800, 800), "Graph Visualization");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

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
            sf::CircleShape circle(20);
            circle.setFillColor(sf::Color::Blue);

            // Calculate the position of the vertex
            float x = center.x + radius * cos(currentAngle);
            float y = center.y + radius * sin(currentAngle);
            circle.setPosition(x, y);
            window.draw(circle);

            positions[vertex->name] = sf::Vector2f(x + 20, y + 20);

            currentAngle += angleIncrement;
            sf::Text label;
            label.setFont(font);
            label.setString(vertex->name);
            label.setCharacterSize(47); // in pixels
            label.setFillColor(sf::Color::Black);
            label.setPosition(x, y-7); // position of the label
            window.draw(label);
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
            sf::Color color = choseColor(currentEdgeNode,vertex,traffic,ht,accidentManager);
            // if(color==sf::Color::Yellow){
            //     cout<<"Yellow color\n";
            // } // debugging statement
            sf::Vertex line[] = {
                sf::Vertex(positions[vertex->name], color),
                sf::Vertex(positions[edge->destination->name], color)
            };
            window.draw(line, 2, sf::Lines);
            currentEdgeNode = currentEdgeNode->next;
            }
            currentVertexNode = currentVertexNode->next;
        }
        window.display();
        //delay for 1 second
        sf::sleep(sf::seconds(1));
    }
}

void Visualizer::drawVehicles(Vehicles &vehicles, const std::string &intersection,const sf::Vector2f &position, sf::RenderWindow &window){
    Vehicle *currentVehicle = vehicles.getHead();
    int decrement = 0;
    while(currentVehicle!=NULL){
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
            label.setPosition(position.x, position.y - 20+decrement);
            window.draw(label);
            decrement-=20;
            currentVehicle->moveForward();
            
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
        return sf::Color::Blue;
    }
    // Check if the edge is congested
    // if (ht.findRoadNode(vertex->name[0], vertex->edges->edge->destination->name[0])->carCount > 5) {
    //     return sf::Color::Red;
    // }
    

    // Check if the edge has a green light
    string signal = traffic.getSignal(vertex->name)->getState();
    if (signal=="green") {
        cout<<"Green light"<<endl;
        return sf::Color::Green;
    }

    // Default color if none of the above conditions are met
    return sf::Color::Black;
}
