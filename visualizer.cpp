#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "graph.h"
#include "vehicle.h"
#include "vehicles.h"
#include "trafficSignal.h"
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
 * @param traffic The traffic light management system.
 * @param ht The congestion monitoring system.
 * @param accidentManager The accident management system.
 */
void drawSimulation(Graph &graph, Vehicles &vehicles, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager);

/**
 * @brief Draws vehicles at the specified intersection.
 *
 * @param vehicles The collection of vehicles to be drawn.
 * @param intersection The name of the intersection where vehicles are to be drawn.
 * @param position The position where the vehicles should be drawn.
 * @param window The render window where the vehicles will be drawn.
 */
void drawVehicles(Vehicles &vehicles, const std::string &intersection, const sf::Vector2f &position, sf::RenderWindow &window);

/**
 * @brief Gets the elapsed time in seconds since the last clock reset.
 *
 * @return The elapsed time in seconds.
 */
float getElapsedTimeInSeconds();

/**
 * @brief Chooses a color for the edge and vertex based on traffic conditions.
 *
 * @param edge The edge node representing the road segment.
 * @param vertex The vertex representing the intersection.
 * @param traffic The traffic light management system.
 * @param ht The congestion monitoring system.
 * @param accidentManager The accident management system.
 * @return The chosen color.
 */
sf::Color choseColor(EdgeNode *edge, Vertex *vertex, TrafficLightManagement &traffic, CongestionMonitoring &ht, Accident_roads &accidentManager);

   
};
#endif // VISUALIZER_H
