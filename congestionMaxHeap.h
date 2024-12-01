#ifndef CONGESTIONMAXHEAP_H
#define CONGESTIONMAXHEAP_H
# include "RoadNode.h"
# include "congestionMonitoring.h"

class CongestionMaxHeap{
      private:
            RoadNode* root;
      public:
            CongestionMaxHeap();
            void makeHeap(RoadNode* hashTableArray, int size);
            void insert(RoadNode* newNode);
            void heapifyUp(RoadNode*& newNode);

            void printHeap();
            RoadNode* mostCongested();
            void inorder(RoadNode* root);
            void inorder();
            // void deleteMax();
            // ~CongestionMaxHeap();

};
#endif