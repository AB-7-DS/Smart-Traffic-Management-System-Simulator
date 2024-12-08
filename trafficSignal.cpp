#include "trafficSignal.h"
#include "visualizer.h"
#include <cmath>
#include <cctype>
#include <iostream>

class Visualizer;

TrafficSignal::TrafficSignal(std::string state, char intersectionId, int duration, int transitionTime) {
      // Convert the state to lowercase
      for (int i = 0; i < state.length(); i++)
            state[i] = static_cast<char>(std::tolower(state[i]));

      // Check if the state is red, yellow or green otherwise set it to red
      (state == "red" || state == "yellow" || state == "green") ? this->state = state : this->state = "red";
      
      // the duration should be positive
      duration > 0 ? this->duration = duration : this->duration = duration * -1;
      
      duration > 0 ? this->transitionTime = transitionTime : this->transitionTime = transitionTime * -1;

      this->intersectionId = intersectionId;

      next = NULL;
}

std::string TrafficSignal::getState() {
      return state;
}

void TrafficSignal::setState(std::string state) {
      // Convert the state to lowercase
      for (int i = 0; i < state.length(); i++)
            state[i] = static_cast<char>(std::tolower(state[i]));

      // Check if the state is red, yellow or green otherwise set it to red
      (state == "red" || state == "yellow" || state == "green") ? this->state = state : this->state = "red";
}

void TrafficSignal::display() {
      // TO DO: Implement this method after the graphics utility class is implementeasd
}

void TrafficSignal::print() {
      std::cout << "State: " << state  << ", ";
      std::cout << "Intersection ID: " << intersectionId  << ", ";
      std::cout << "Duration: " << duration << std::endl;
}

int TrafficSignal::getIntersectionId() {
      return intersectionId;
}

int TrafficSignal::getDuration() {
      return duration;
}

void TrafficSignal::advanceState(Visualizer* visualizer) {

      // to advance from red to yellow, call the turn green method

      // this->temp = visualizer->getElapsedTimeInSeconds();
      if (state == "yellow") {
            if (abs(this->temp-visualizer->getElapsedTimeInSeconds()) >= transitionTime) {
                  state = "green";
                  this->temp = visualizer->getElapsedTimeInSeconds();
            }
      }
      if (state == "green") {
            if (abs(this->temp-visualizer->getElapsedTimeInSeconds()) >= this->duration) {
                  state = "red";
                  this->temp = visualizer->getElapsedTimeInSeconds();
            }
      }

}

int TrafficSignal::getTransitionTime() {
      return transitionTime;
}

void TrafficSignal::turnGreen(Visualizer* visualizer) {
      state = "yellow";
      this->temp = visualizer->getElapsedTimeInSeconds();
}

