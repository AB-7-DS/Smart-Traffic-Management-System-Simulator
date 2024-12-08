#ifndef CONGESTIONMAXHEAP_H
#define CONGESTIONMAXHEAP_H

# include "RoadNode.h"
# include "congestionMonitoring.h"

/**
 * @class CongestionMaxHeap
 * @brief A class to represent a max heap specifically for managing road congestion data.
 * 
 * This class provides functionalities to create and manage a max heap of RoadNode objects,
 * which are used to monitor and manage road congestion.
 */

class CongestionMaxHeap{
    private:
        RoadNode* root; //< Pointer to the root of the heap
        
        /**
         * @brief Performs an inorder traversal of the heap.
         * 
         * This is a helper function used for debugging and visualization purposes.
         * 
         * @param root The root node of the heap/subtree.
         */
        void inorder(RoadNode* root);
    public:
        /**
         * @brief Construct a new Congestion Max Heap object
         * 
         * Initializes root to nullptr
         * 
         */
        CongestionMaxHeap();
        /**
         * @brief Makes a max heap from the roads in the hashtable array
         * 
         * @param hashTableArray hashTableArray is from the congestion monitoring class
         * @param size size of the hashtable array
         */
        void makeHeap(RoadNode* hashTableArray, int size);
        /**
         * @brief Inserts a new RoadNode into the heap
         * 
         * inserts preserving the structure property of the heap and heapifies up after insertion
         * 
         * @param newNode The RoadNode to be inserted
         */
        void insert(RoadNode* newNode);
        /**
         * @brief Heapifies up the heap after insertion
         * 
         * @param newNode The RoadNode to be heapified up
         */
        void heapifyUp(RoadNode*& newNode);
        /**
         * @brief Prints the heap 
         * 
         * Uses BFS to print the heap
         * 
         */
        void printHeap();
        /**
         * @brief returns root of the heap without removing it
         * 
         * @return RoadNode* 
         */
        RoadNode* mostCongested();
        /**
         * @brief Prints the heap inorder
         * 
         * 
         */
        void inorder();
        /**
         * @brief Function to heapify down the heap
         * 
         * @param node 
         */
        void heapifyDown(RoadNode* node);

};
#endif  // CONGESTIONMAXHEAP_H