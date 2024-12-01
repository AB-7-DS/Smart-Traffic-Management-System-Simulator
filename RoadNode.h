#ifndef ROADNODE_H
#define ROADNODE_H

/**
 * @brief The node for the Hash Table containing a key-value pair and a pointer for chaining
 */
struct RoadNode {
    char path[2]; //< Start and end Intersection
    int carCount; //< The number of cars on the road
    RoadNode* right; //< Pointer for chaining in case of collisions in hashtables. Points to right child in minheap
    RoadNode* left; //< Pointer for the left child in minheap
    RoadNode* parent; //< Pointer to the parent node in minheap
    RoadNode* next; //< Pointer to the next node in the queue
    /**
     * @brief Constructor to initialize a RoadNode
     * @param s Start intersection
     * @param e End intersection
     * @param v Number of cars on the road
     */
    RoadNode(char s = '\0', char e = '\0', int v = 0) {
        path[0] = s;
        path[1] = e;
        carCount = v;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
        next = nullptr;
    }
};

#endif 