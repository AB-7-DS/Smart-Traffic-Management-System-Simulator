#ifndef ROADQUEUE_H
#define ROADQUEUE_H
# include "RoadNode.h"
/**
 * @class RoadQueue
 * @brief A class to represent a queue specifically for managing RoadNode objects.
 * 
 * This class provides functionalities to create and manage a queue of RoadNode objects,
 * which can be used for various purposes such as managing road segments in a traffic system.
 */
class RoadQueue{
      private:
            RoadNode* head; ///< Pointer to the head of the queue
            RoadNode* tail; ///< Pointer to the tail of the queue
    public:
        /**
         * @brief Construct a new RoadQueue object.
         * 
         * Initializes the head and tail to nullptr, indicating an empty queue.
         */
        RoadQueue();

        /**
         * @brief Adds a new RoadNode to the end of the queue.
         * 
         * This function inserts a new RoadNode at the tail of the queue.
         * 
         * @param newNode The RoadNode to be added to the queue.
         */
        void enqueue(RoadNode*& newNode);

        /**
         * @brief Removes and returns the RoadNode at the front of the queue.
         * 
         * This function removes the RoadNode at the head of the queue and returns it.
         * 
         * @return The RoadNode at the front of the queue.
         */
        RoadNode* dequeue();

        /**
         * @brief Prints the contents of the queue.
         * 
         * This function prints the current state of the queue for debugging and visualization purposes.
         */
        void printQueue();

        /**
         * @brief Checks if the queue is empty.
         * 
         * This function checks whether the queue is empty.
         * 
         * @return true if the queue is empty, false otherwise.
         */
        bool isEmpty();
};

#endif