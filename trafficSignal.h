
#ifndef TRAFFIC_SIGNAL_H
#define TRAFFIC_SIGNAL_H
#include "visualizer.h"
#include <string>

/**
 * @class TrafficSignal
 * @brief A class to represent a traffic signal at an intersection.
 * 
 * This class models a traffic signal at an intersection, 
 * providing functionality to manage its state ("red", "yellow", or "green"), 
 * the associated Intersection ID, and the duration for which each state is maintained. 
 * It also offers methods for displaying and printing the signal's information.
 * 
 * @details The TrafficSignal class maintains the state of the signal ( "red", "yellow", or "green"),
 * the ID of the intersection it belongs to, and the duration for which the signal state is maintained.
 * 
 * @note The display method is intended for future implementation to show the signal on a graphical interface.
 * 
 * @var std::string TrafficSignal::state
 * The current state of the traffic signal ("red", "yellow", or "green").
 * 
 * @var int TrafficSignal::intersectionId
 * The ID of the intersection for which the signal is.
 * 
 * @var int TrafficSignal::duration
 * The duration for which the signal state is maintained, in seconds.
 * 
 * @var int TrafficSignal::transitionTime
 * The time the "yellow" state is maintained, in seconds.
 * 
 * @fn TrafficSignal::TrafficSignal(std::string state, int intersectionId, int duration, int transitionTime)
 * @brief Constructor to initialize the TrafficSignal object with the given state, intersectionId, and duration.
 * @param state The initial state of the signal ("red", "yellow", or "green"). Default value is "red".
 * @param intersectionId The ID of the intersection for which the signal is. Default value is -1.
 * @param duration The duration for which the signal state is maintained, in seconds. Default value is 60.
 * @param transitionTime The time the "yellow" state is maintained, in seconds. Default value is 5.
 * 
 * @fn std::string TrafficSignal::getState()
 * @brief Get the current state of the signal.
 * @return The current state of the signal as a string.
 * 
 * @fn void TrafficSignal::setState(std::string state)
 * @brief Set the state of the signal.
 * @param state The new state of the signal ("red", "yellow", or "green").
 * 
 * @fn void TrafficSignal::display()
 * @brief Displays the signal on the graphical interface.
 * @note This method will be implemented in the future.
 * 
 * @fn void TrafficSignal::print()
 * @brief Print the signal state, intersectionId, and duration on the console.
 * 
 * @fn int TrafficSignal::getIntersectionId()
 * @brief Get the Intersection ID of the signal.
 * @return The Intersection ID as an integer.
 * 
 * @fn int TrafficSignal::getDuration()
 * @brief Get the duration for which the signal state is maintained.
 * @return The duration in seconds.
 * 
 * @fn int TrafficSignal::getTransitionTime()
 * @brief Get the time the "yellow" state is maintained.
 * @return The transition time in seconds.
 * 
 * @fn void TrafficSignal::advanceState()
 * @brief Advance the state of the traffic signal to the next state in the sequence "red" -> "yellow" -> "green" -> "yellow" -> "red".
 */
class TrafficSignal {
      public:
            std::string state; //<  "red", "yellow", "green"
            int transitionTime; //< the time the "yellow" state is maintained

            char intersectionId; //< ID of the intersection for which the signal is
            int duration; //< duration a state is to be maintained in seconds
            TrafficSignal* next; //< pointer to the next signal in the list
            int temp; //< temporary variable to store the duration the current state has been maintained



            /**
             * @brief Initializes a TrafficSignal instance with the specified state ("red", "yellow", or "green"), 
             * Intersection ID, and duration. 
             * Defaults to "red" state, -1 Intersection ID, and 60 seconds duration.
             * 
             * @param state string "red", "yellow" or "green". Default value is "red"
             * @param intersectionId char ID of the intersection for which the signal is. Default value is '-'
             * @param duration int duration a state is to be maintained in seconds. Default value is 60
             * @param transitionTime int the time the "yellow" state is maintained. Default value is 5
             */
            TrafficSignal(std::string state = "red", char intersectionId = '-', int duration = 60, int transitionTime = 5);

            /**
             * @brief Retrieves the current state of the traffic signal
             * @return string "red", "yellow" or "green" 
             */
            std::string getState();

            /**
             * @brief Updates the state of the traffic signal
             * @param state A string representing the new state ("red", "yellow" or "green")
             */
            void setState(std::string state);

            /**
             * @brief Intended for displaying the traffic signal on a graphical user interface (GUI). This method is currently not implemented.
             */
            void display();

            /**
             * @brief Outputs the traffic signal's state, Intersection ID, and duration in a human-readable format. 
             * 
             * Example output: "Signal State: red, Intersection ID: 1, Duration: 60s"
             * 
             */
            void print();

            /**
             * @brief Retrieve the ID of the intersection for which the signal is
             * @return int Intersection ID
             * 
             */
            int getIntersectionId();

            /**
             * @brief Retrieve the duration for which a signal state is maintained
             * @return int Duration in seconds
             */
            int getDuration();

            /**
             * @brief Retrieve the time the "yellow" state is maintained
             * @return int Transition time in seconds
             */
            int getTransitionTime();

            /**
             * @brief Advance the state of the traffic signal to the next state in the sequence "red" -> "yellow" -> "green" -> "red"
             * 
             * this function must be called continuously in the mainloop to change the state of the signal
             */
            void advanceState(Visualizer* visualizer);

            /**
             * @brief Turn the traffic signal from red to green
             */
            void turnGreen(Visualizer* visualizer);
};

#endif