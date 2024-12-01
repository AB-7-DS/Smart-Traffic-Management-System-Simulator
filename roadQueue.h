#ifndef ROADQUEUE_H
#define ROADQUEUE_H
# include "RoadNode.h"

class RoadQueue{
      private:
            RoadNode* head;
            RoadNode* tail;
      public:
            RoadQueue();
            void enqueue(RoadNode*& newNode);
            RoadNode* dequeue();
            void printQueue();
            // ~RoadQueue();
            bool isEmpty();
};

#endif