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

    HashNode* temp = &hashTable[index];
    
    // right > 0 and temp->right is not a nullptr
    while( right-- && temp->right) 
        temp = temp->right;

    return temp->path[0];
}

char CongestionMonitoring::getEnd(int index, int right) {
    // invalid param check
    if (index >= HASH_TABLE_SIZE) return '\0';

    HashNode* temp = &hashTable[index];
    
    // right > 0 and temp->right is not a nullptr
    while( right-- && temp->right) 
        temp = temp->right;

    return temp->path[1];
}

void CongestionMonitoring::addToTable(int index, char start, char end, int right) {
    // get the node at index
    HashNode* temp = &hashTable[index];
    for (int i = 0; i<right; i++){
        if (temp->right)
            temp = temp->right;
        else {
            // add another node to the chain
            temp->right = new HashNode();
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
    makeHashTable(vehiclesHead);
}

void CongestionMonitoring::makeHashTable(Vehicle* vehiclesHead){
    Vehicle* temp = vehiclesHead;
    std::string tempstr;

    while(temp) {
        char p[] = {'\0', '\0'};
        p[0] = temp->path[temp->currentIntersectionInPath][0];
        p[1] = temp->path[temp->currentIntersectionInPath+1][0];

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
    // To do
}

void CongestionMonitoring::printHashTable() {
    std::cout << std::endl;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* temp = &hashTable[i];
        while(temp) {
            if (temp->path[0] != '\0' && temp->path[1] != '\0') 
                std::cout << temp->path[0] << " to  " << temp->path[1] << " -> Vehicles: " << temp->carCount << std::endl;
            temp = temp->right;
        }
    }
}


CongestionMonitoring::~CongestionMonitoring() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* temp = &hashTable[i];
        HashNode* temp2 = temp->right;
        while(temp2) {
            HashNode* del = temp2;
            temp2 = temp2->right;
            delete del;
        }
    }
}