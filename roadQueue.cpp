# include "roadQueue.h"
# include<iostream>

RoadQueue::RoadQueue(){
      head = NULL;
      tail = NULL;
}

RoadNode* RoadQueue::dequeue(){
      if (isEmpty())
            return nullptr;
      RoadNode* temp = head;
      temp->right = nullptr;
      head = head->right;
      return temp;
      
}

void RoadQueue::enqueue(RoadNode*& newNode){
      RoadNode* nn = new RoadNode(newNode->path[0], newNode->path[1], newNode->carCount);
      if(nn->carCount == 0)
            return;
      nn->right = nullptr;
      if (head == NULL){
            head = nn;
            head->right = tail;
            tail = nn;
            return;
      }
      tail->right = nn;
      tail = nn;
      tail->right = nullptr;
}

void RoadQueue::printQueue(){
      RoadNode* temp = head;
      while(temp != NULL){
            std::cout << temp->path[0] << " to " << temp->path[1] << "\t";
            temp = temp->right;
      }
      std::cout << std::endl;
}

bool RoadQueue::isEmpty(){
      return head == NULL;
}





