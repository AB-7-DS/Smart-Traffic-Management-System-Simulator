# include "congestionMonitoring.h"
# include <iostream>
# include <string>
// private functions
int CongestionMonitoring::hashFunction(char start, char end) {
    int s, e = 0;
    if (start >= 'A' && start <= 'Z' && start >= 'A' && start <= 'Z') {
        s = start - 'A';
        e = end - 'A';
    }
    else 
        std::cerr << "Incorrect start and end intersections recieved";
    return (s*31+e)%HASH_TABLE_SIZE;
} 

char CongestionMonitoring::getStart(int index, int right) {
    // invalid param check
    if (index >= HASH_TABLE_SIZE) return '\0';

    RoadNode* temp = &hashTable[index];
    
    // right > 0 and temp->right is not a nullptr
    while( right-- && temp->right) 
        temp = temp->right;

    return temp->path[0];
}

char CongestionMonitoring::getEnd(int index, int right) {
    // invalid param check
    if (index >= HASH_TABLE_SIZE) return '\0';

    RoadNode* temp = &hashTable[index];
    
    // right > 0 and temp->right is not a nullptr
    while( right-- && temp->right) 
        temp = temp->right;

    return temp->path[1];
}

void CongestionMonitoring::addToTable(int index, char start, char end, int right) {
    // get the node at index
    RoadNode* temp = &hashTable[index];
    for (int i = 0; i<right; i++){
        if (temp->right)
            temp = temp->right;
        else {
            // add another node to the chain
            temp->right = new RoadNode();
            temp = temp->right;
            break;
        }
    }

    char s,e = '\0';
    s = getStart(index, right);
    e = getEnd(index, right);

    // case 1: the index is empty i.e it has path[0] = path[1] = '\0' and count = 0
        // make the path [0] = start and path [1] = end and count = 1
    if (s == '\0' &&  e =='\0' ) {
        temp->path[0] = start;
        temp->path[1] = end;
        temp->carCount = 1;        
    }

    // case 2: for the node and index path[0]=start and path[1]=end
        // update the count to +=1
    else if (s == start && e == end){
        temp->carCount+=1;
    }
    // case 3: for the node and index path[0]!=start or path[1]=!end
        // check the chain of the index
    else 
        addToTable(index, start, end, right+1);

}


// public functions
CongestionMonitoring::CongestionMonitoring(Vehicle* vehiclesHead) : hashTableSize(HASH_TABLE_SIZE) {
    if (!vehiclesHead) {
        std::cerr << "No vehicle found" << std::endl;
        return;
    }
    for (int i = 0; i < HASH_TABLE_SIZE; i++)         
        hashTable[i].right = nullptr;
    

    makeHashTable(vehiclesHead);
}


void CongestionMonitoring::makeHashTable(Vehicle* vehiclesHead){

    // first we need to check if the hash table is empty and make it empty if it is not
    this->deleteTable();

    Vehicle* temp = vehiclesHead;
    std::string tempstr;

    while(temp) {
        char p[] = {'\0', '\0'};
        if (temp->presetPath) {
            p[0] = temp->path[temp->currentIntersectionInPath][0];
            p[1] = temp->path[temp->currentIntersectionInPath+1][0];
        }
        // if the paht was not preset or if it is wrong
        if (p[0] == '\0') p[0] = temp->startIntersection[0];
        if (p[1] == '\0') p[1] = temp->endIntersection[0];
        
        
        if (p[0] == '\0' || p[1] == '\0') {
            std::cerr << "Incorrect path received" << std::endl;
            return;
        }

        addToTable(hashFunction(p[0], p[1]), p[0], p[1]);

        temp = temp->next;
    }
}

void CongestionMonitoring::updateHashTable(Vehicle* prevPos, Vehicle* currentPos) {
}

void CongestionMonitoring::printHashTable() {
    std::cout << std::endl;

    // Array to track visited roads
    bool visited[HASH_TABLE_SIZE] = {false};

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RoadNode* temp = &hashTable[i];

        while (temp) {
            // Check if the road (start, end) is unique
            if (temp->path[0] != '\0' && temp->path[1] != '\0') {
                // Calculate hash index for the road in reverse order
                int reverseIndex = hashFunction(temp->path[1], temp->path[0]);

                // Print road only if it hasn't been visited in forward or reverse order
                if (!visited[i] && !visited[reverseIndex]) {
                    std::cout << temp->path[0] << " to " << temp->path[1] << " -> Vehicles: " << temp->carCount << std::endl;
                    visited[i] = true;
                }
            }
            temp = temp->right;
        }
    }
}

void CongestionMonitoring::deleteTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RoadNode* temp = hashTable[i].right;
        while (temp) {
            RoadNode* temp2 = temp;
            temp = temp->right;
            delete temp2;
            temp2 = nullptr;
        }
        hashTable[i].right = nullptr;
        hashTable[i].carCount = 0;  
        hashTable[i].path[0] = '\0';
        hashTable[i].path[1] = '\0';
    }
}


int CongestionMonitoring::getTravelTime(char start, char end, int prevTime) {
    RoadNode* temp = findRoadNode(start, end);
    if (!temp) {
        return prevTime;
    }
    bool isPeakHour = false;
    if (prevTime >= 3600 && prevTime <= 7200) isPeakHour = true;
    int carCount = temp->carCount;

    int time = prevTime;
    
    if (carCount < 5) time  = time;
    else time += time*carCount;

    if (!isPeakHour) time /= 2;
    return time;
}

int CongestionMonitoring::getTravelTime(char start, char end, Graph& cityGraph) {
    RoadNode* temp = findRoadNode(start, end);
    string s = ""; s += start;
    string e = ""; e += end;
    int prevTime = cityGraph.getEdgeWeight(s, e);
    return getTravelTime(start, end, prevTime);
}

RoadNode* CongestionMonitoring::findRoadNode(char start, char end) {
    int index = hashFunction(start, end);
    RoadNode* temp = &hashTable[index];
    while(temp) {
        if (temp->path[0] == start && temp->path[1] == end) {
            return temp;
        }
        temp = temp->right;
    }
    return nullptr;
}

int CongestionMonitoring::numberOfCongestionEvents() {
    int count = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        RoadNode* temp = &hashTable[i];
        while(temp) {
            if (temp->carCount > 5) count++;
            temp = temp->right;
        }
    }
    return count;
}

