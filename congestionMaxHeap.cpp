# include"congestionMaxHeap.h"
# include"roadQueue.h"
# include<iostream>

CongestionMaxHeap::CongestionMaxHeap(){
      root = NULL;
}

void CongestionMaxHeap::makeHeap(RoadNode* hashTableArray, int size){
      for(int i = 0; i < size; i++){
       
            RoadNode* newNode = &hashTableArray[i];
       
            if (newNode->carCount > 0){

                  insert(newNode);

                  while(newNode->right != NULL){

                        newNode = newNode->right;
                        if (newNode->carCount > 0)
                              insert(newNode);
                        
                  }

            }
      }
}

void CongestionMaxHeap::insert(RoadNode* newNode){
      // insert keeping the heap structure property of almost complete binary tree
      newNode->left = NULL;
      newNode->right = NULL;
      if (!root){
            root = newNode;
            return;
      }

      RoadQueue* queue = new RoadQueue();
      queue->enqueue(root);
      RoadNode* temp = NULL;
      while(!queue->isEmpty()){
            temp = queue->dequeue();
            
            if (temp && temp->carCount >0){

                  if (temp->left == NULL){
                        temp->left = newNode;
                        newNode->parent = temp;
                        heapifyUp(newNode);
                        return;
                  }
                  else if (temp->right == NULL){
                        temp->right = newNode;
                        newNode->parent = temp;
                        heapifyUp(newNode);

                        return;
                  }
                  else{
                        queue->enqueue(temp->left);
                        queue->enqueue(temp->right);
                  }
            }
      }
      delete queue;
}

void CongestionMaxHeap::heapifyUp(RoadNode*& node) {
        while (node->parent) {
            std::swap(node->path[0], node->parent->path[0]);
            std::swap(node->path[1], node->parent->path[1]);
            std::swap(node->carCount, node->parent->carCount);
            node = node->parent;
    }
}
void CongestionMaxHeap::printHeap() {
    std::cout << std::endl;
    if (root == NULL) 
        return;
    RoadQueue* queue = new RoadQueue();
    queue->enqueue(root);
    RoadNode* temp = NULL;

    while (!queue->isEmpty()) {
        temp = queue->dequeue();
        std::cout << temp->path[0] << " to " << temp->path[1] 
                  << " (Car Count: " << temp->carCount << ")\n";
        if (temp->left != NULL)
            queue->enqueue(temp->left);
        if (temp->right != NULL)
            queue->enqueue(temp->right);
    }

    std::cout << std::endl;
    delete queue;
}


RoadNode* CongestionMaxHeap::mostCongested(){
      return root;
}

void CongestionMaxHeap::inorder() {
      std::cout << "\n";
      inorder(root);
}
void CongestionMaxHeap::inorder(RoadNode* root) {
      if (root == NULL)
            return;
      inorder(root->left);
      std::cout << root->path[0] << " to " << root->path[1] << "\n";
      inorder(root->right);
}

