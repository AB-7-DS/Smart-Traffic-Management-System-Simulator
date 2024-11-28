#ifndef VEHICLE_H
#define VEHICLE_H

#include<string>

/**
 * @struct Vehicle
 * @brief A structure representing a vehicle with details about its route and priority.
 */
struct Vehicle {
    std::string vehicleID; //<The unique identifier for the vehicle
    const std::string startIntersection; //<The starting intersection for the vehicle's route never to be changed
    const std::string endIntersection; //<The ending intersection for the vehicle's route never to be changed
    std::string priorityLevel; //<The priority level of the vehicle (e.g., high, low)
    std::string* path; //<The path the vehicle will take to reach its destination.
    int currentIntersectionInPath; //< an index in the path array that represents the current intersection the vehicle is at. the next intersection is at currentIntersectionInPath + 1
    int pathLength; //<The length of the path array
    bool presetPath; //<A boolean to check if the path is preset or not    
    /**
     * @brief Pointer to the next vehicle in a linked list.
     */
    Vehicle *next;

    
    /**
     * @brief Constructs a Vehicle with given attributes.
     * @param vehicleID The unique identifier for the vehicle.
     * @param startIntersection The starting intersection for the vehicle.
     * @param endIntersection The ending intersection for the vehicle.
     * @param priorityLevel The priority level of the vehicle.
     */
    Vehicle(std::string vehicleID, std::string startIntersection, std::string endIntersection, std::string priorityLevel);
    /**
     * @brief updates the currentIntersectionId of the vehicle
     * @param nextIntersectionId  The id of the next intersection the vehicle will move to
     * if the nextIntersectionId is not provided, the vehicle will move to the next intersection in the path only if it is preset
     * 
     */
    void moveForward(std::string nextIntersectionId = "");
    /**
     * @brief prints the details of the vehicle
     * 
     */
    void printVehicle();
    /**
     * @brief sets the path of the vehicle
     * 
     * @param path the path the vehicle will take
     * @note if the initial intersection of the vehicle is "A" the path must be "ABC.."
     * but it cannot be "BC.."
     * 
     * @note the path must be preset before the vehicle starts moving
     * 
     */
    void setPath(std::string path);
    /**
     * @brief prints the path of the vehicle
     * 
     */
    void printPath();
    
};

#endif
