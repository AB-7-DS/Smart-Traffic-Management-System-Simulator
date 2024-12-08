#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "graph.h"
#include "vehicle.h"
#include "vehicles.h"
#include "accidents.h"
#include "trafficLightManagement.h"
#include "congestionMonitoring.h"

class Visualizer {
private:
    sf::RenderWindow window;  
    sf::Sprite roadSprite;
    sf::Sprite vehicleSprite;
    sf::Font font;
    sf::Texture roadTexture;
    sf::Texture vehicleTexture;
    sf::Clock clock; //<Measures elapsed time

public:
/**
 * @class Visualizer
 * @brief A class to handle the visualization of the traffic management system.
 *
 * This class is responsible for rendering the simulation of the traffic management system,
 * including roads and vehicles, using the SFML library.
 */
 
/**
 * @brief Constructor for the Visualizer class.
 *
 * Initializes the render window, loads textures, and sets up sprites.
 */
    Visualizer();

/**
 * @brief Draws the entire simulation graph.
 *
 * @param graph The graph representing the traffic network.
 * @param vehicles The collection of vehicles to be drawn.
 */
    void drawSimulation(Graph &graph, Vehicles &vehicles,TrafficLightManagement &traffic,CongestionMonitoring &ht,Accident_roads &accidentManager);

    /**
 * @brief Draws vehicles at the specified intersection.
 *
 * @param vehicles The collection of vehicles to be drawn.
 * @param intersection The name of the intersection where vehicles are to be drawn.
 * @param position The position where the vehicles should be drawn.
 * @param window The render window where the vehicles will be drawn.
 */
   void drawVehicles(Vehicles &vehicles, const std::string &intersection,
                            const sf::Vector2f &position, sf::RenderWindow &window);


   float getElapsedTimeInSeconds();
   sf::Color choseColor(EdgeNode *edge,Vertex *vertex,TrafficLightManagement &traffic,CongestionMonitoring &ht,Accident_roads &accidentManager);
 
};
#endif // VISUALIZER_H
