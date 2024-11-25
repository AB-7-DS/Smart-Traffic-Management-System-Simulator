#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "graph.h"
#include "vehicles.h"

// Constants for visualization
const float WINDOW_WIDTH = 1000;
const float WINDOW_HEIGHT = 800;

// Helper function to convert degrees to radians
float toRadians(float degrees) {
    return degrees * 3.14159f / 180.0f;
}

class Visualizer {
private:
    sf::RenderWindow window;
    sf::Font font;

    // Textures
    sf::Texture trafficLightTextureRed;
    sf::Texture trafficLightTextureGreen;
    sf::Texture trafficLightTextureYellow;
    sf::Texture roadTexture;
    sf::Texture carTexture;
    sf::Texture vipCarTexture;

    // Sprites
    sf::Sprite trafficLightRed;
    sf::Sprite trafficLightGreen;
    sf::Sprite trafficLightYellow;
    sf::Sprite roadSprite;
    sf::Sprite carSprite;
    sf::Sprite vipCarSprite;

public:
    Visualizer();
    void drawGraph(Graph& graph);
    //0 = red, 1= yellow, 2 = green
    void drawTrafficSignal(const sf::Vector2f& position, int signalState);
    void drawVehicle(const sf::Vector2f& position, float rotationAngle = 0.0f);
    void renderLoop(Vehicles & vehicles,Graph& graph);
    void drawVIPVehicle(const sf::Vector2f& position,float rotationAngle = 0.0f);
};
#endif