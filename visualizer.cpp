#include "visualizer.h"
#include<cmath>

// Function to calculate the position of a vertex in a circular layout
sf::Vector2f calculatePosition(int index, int totalVertices, float radius) {
    float angle = 2 * 3.14159f * index / totalVertices;
    float x = radius * cos(angle) + WINDOW_WIDTH / 2;
    float y = radius * sin(angle) + WINDOW_HEIGHT / 2;
    return sf::Vector2f(x, y);
}
Visualizer::Visualizer()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Traffic Simulation") {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    // Load textures
    if (!trafficLightTextureRed.loadFromFile("sprites/redLight.png") ||
        !trafficLightTextureGreen.loadFromFile("sprites/greenLight.png") ||
        !trafficLightTextureYellow.loadFromFile("sprites/yellowLight.png") ||
        !roadTexture.loadFromFile("sprites/road.png") ||
        !vipCarTexture.loadFromFile("sprites/ambulance.png")||
        !carTexture.loadFromFile("sprites/redCar.png")) {
        std::cerr << "Error loading textures" << std::endl;
    }

    // Setup sprites
    trafficLightRed.setTexture(trafficLightTextureRed);
    trafficLightGreen.setTexture(trafficLightTextureGreen);
    trafficLightYellow.setTexture(trafficLightTextureYellow);

    roadSprite.setTexture(roadTexture);
    carSprite.setTexture(carTexture);
    vipCarSprite.setTexture(vipCarTexture);
}

// Draw a vehicle at a given position using a sprite, with optional rotation
void Visualizer::drawVehicle(const sf::Vector2f& position,float rotationAngle) {
    carSprite.setPosition(position);
    carSprite.setRotation(rotationAngle);
    carSprite.setScale(0.1f, 0.1f);  // Scale down the sprite to half its size
    window.draw(carSprite);
}
void Visualizer::drawVIPVehicle(const sf::Vector2f& position,float rotationAngle) {
    vipCarSprite.setPosition(position);
    vipCarSprite.setRotation(rotationAngle);
    vipCarSprite.setScale(0.1f, 0.1f);  // Scale down the sprite to half its size
    window.draw(vipCarSprite);
}



// Main render loop for visualization
void Visualizer::renderLoop(Vehicles & vehicles,Graph& graph) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        Vehicle *temp = vehicles.getHead();
        int x=500,y=400;
        while(temp!=NULL){
            if(temp->priorityLevel=="High")
            drawVIPVehicle(sf::Vector2f(x,y));  // Draw a car
            else drawVehicle(sf::Vector2f(x,y));
            temp = temp->next;
            x-=100;

        }
        drawTrafficSignal(sf::Vector2f(550,100),0);
        //drawVehicle(sf::Vector2f(100, 400), 90.0f);  // Draw a rotated car

        window.display();
    }

}
 

void Visualizer::drawTrafficSignal(const sf::Vector2f& position, int signalState) {
    sf::Sprite* trafficLightSprite;

    switch (signalState) {
        case 0:
            trafficLightSprite = &trafficLightRed;
            break;
        case 1:
            trafficLightSprite = &trafficLightGreen;
            break;
        case 2:
            trafficLightSprite = &trafficLightYellow;
            break;
        default:
            std::cerr << "Invalid signal state" << std::endl;
            return;
    }

    trafficLightSprite->setPosition(position);
    trafficLightSprite->setScale(0.1f, 0.1f);  // Scale down the sprite to half its size
    window.draw(*trafficLightSprite);
}

float Visualizer::getElapsedTimeInSeconds() {
    return clock.getElapsedTime().asSeconds();
}