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
      head = head->next;      
      return temp;
}

void RoadQueue::enqueue(RoadNode*& newNode){
      if(newNode->carCount == 0)
            return;
      newNode->next = nullptr;
      if (head == NULL){
            head = newNode;
            head->next = tail;
            tail = newNode;
            return;
      }
      tail->next = newNode;
      tail = newNode;
      tail->next = nullptr;
}

void RoadQueue::printQueue(){
      RoadNode* temp = head;
      while(temp != NULL){
            std::cout << temp->path[0] << " to " << temp->path[1] << "\t";
            temp = temp->next;
      }
      std::cout << std::endl;
}

bool RoadQueue::isEmpty(){
      return head == NULL;
}





