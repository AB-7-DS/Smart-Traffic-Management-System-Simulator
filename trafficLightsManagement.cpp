#include "trafficLightManagement.h"
#include "trafficSignal.h"
#include <iostream>
#include <fstream>
TrafficLightManagement::TrafficLightManagement(){
      headSignal = NULL;
}

void TrafficLightManagement::makeTrafficSignals(){
      // load the data from the signals file
      std::ifstream file(SIGNALS_FILE);

      if (!file.is_open()){
            std::cerr << "Error: Unable to open file " << SIGNALS_FILE << std::endl;
            return;
      }
      std::string line;
      std::getline(file, line); // skip the header
      while (std::getline(file, line)){
            TrafficSignal* signal = new TrafficSignal();

            std::string intersection = "";
            std::string duration = "";
            intersection = line.substr(0, line.find(","));
            duration = line.substr(line.find(",") + 1);
            signal->intersectionId = intersection[0];
            signal->duration = std::stoi(duration);


            addSignal(signal);
      }
}     

void TrafficLightManagement::addSignal( TrafficSignal* signal){
      signal->next = NULL;
      if (headSignal == NULL){
            headSignal = signal;
            return;
      }
      TrafficSignal* temp = headSignal;
      while (temp->next != NULL){
            temp = temp->next;
      }
      temp->next = signal;
}

void TrafficLightManagement::updateTrafficSignals(CongestionMonitoring& ht){
      for(int i = 0; i< HASH_TABLE_SIZE; i++) {
            RoadNode* temp = &ht.hashTable[i];
            while(temp) {
                  // only chagnge the signal time if the car count is greater than 5
                  if(temp->carCount > 5)
                  if (temp->path[0] != '\0' && temp->path[1] != '\0') {
                        string intersection = "";
                        intersection += temp->path[0];
                        TrafficSignal* signal = getSignal(intersection);
                        if (signal != NULL) {
                              signal->duration = signal->duration + temp->carCount;
                              cout << "Intersection " << intersection << " Green Time: " << signal->duration << "s (updated)" << endl;
                        }
                        
                  }
                  temp = temp->right;
            }
      }
}


void TrafficLightManagement::printGreenTimes(){
      TrafficSignal* temp = headSignal;
      while (temp != NULL){
            std::cout << "Intersection " << temp->intersectionId << " Green Time: " << temp->duration << "s" << std::endl;
            temp = temp->next;
      }
     
}
TrafficSignal* TrafficLightManagement::getSignal(string intersection) {
      TrafficSignal* temp = headSignal;
      while (temp) {
            if (temp->intersectionId == intersection[0])
                  return temp;
            temp = temp->next;
      }
      return nullptr;
}

void TrafficLightManagement::manageTrafficLights(char mostCongestedRoad, Visualizer* vs){
      TrafficSignal* temp = headSignal;
      while (temp) {
            if (temp->intersectionId == mostCongestedRoad) {
                  temp->turnGreen(vs);
            }
            temp = temp->next;
            temp->advanceState(vs);
      }
}








