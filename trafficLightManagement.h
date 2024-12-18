#ifndef TRAFFIC_LIGHT_MANAGEMENT_H
#define TRAFFIC_LIGHT_MANAGEMENT_H
// # include "visualizer.h" 
# include "trafficSignal.h"
# include "congestionMonitoring.h"
# include <string>
/**
 * @class TrafficLightManagement
 * @brief Manages the traffic lights at each intersection.
 * 
 * The TrafficLightManagement class is responsible for managing the traffic lights at each intersection.
 * It maintains a list of traffic signals and updates them based on the current traffic conditions.
 */

const std::string SIGNALS_FILE = "dataset/traffic_signals.csv";
class TrafficLightManagement {
      private:
            TrafficSignal* headSignal;
      public:
            /**
             * @brief Constructor for TrafficLightManagement class.
             * 
             * Initializes the headSignal pointer to NULL.
             */
            TrafficLightManagement();
            /**
             * @brief Assigns a traffic signal to each intersection. 
             * 
             * Loads the time duration for each signal from the csv file.
             * 
             * 
             */
            void makeTrafficSignals();
            /**
             * @brief Updates the traffic signals based on the congestion monitoring data.
             * 
             * @param congestionMonitoring The congestion monitoring hash table.
             */
            void updateTrafficSignals(CongestionMonitoring& ht);
            /**
             * @brief Adds a signal to the list of traffic signals.
             * 
             * @param signal The signal to be added.
             */
            void addSignal(TrafficSignal* signal);
            /**
             * @brief Prints the time the green state is to be maintained of the traffic signals.
             * 
             */
            void printGreenTimes();
            /**
             * @brief Returns the signal for a given intersection.
             * 
             * @param intersection The intersection for which the signal is to be returned.
             * @return TrafficSignal* The signal for the given intersection.
             */
            TrafficSignal* getSignal(std::string intersection);
            /**
             * @brief Manages the traffic lights at each intersection
             * 
             * Call this function continuously to automatically manage the traffic lights.
             * 
             * @param mostCongestedIntersection The intersection with the most congestion.
             * @param vs The visualizer object.
             */
            void manageTrafficLights(char mostCongestedIntersection, Visualizer* vs);
};

#endif