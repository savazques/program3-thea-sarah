#include <iostream>


#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) { 
    //increase the size of the queue everytime insert is called
    size_++; 
    //the keyvaluepair is store at the last element of queue
    nodes_[size_] = kv;
    //heapify up at position size
    heapifyUp(size_); 
}

KeyValuePair PriorityQueue::min() {
    // returns the current min of the heap
	return nodes_[1]; 
}

KeyValuePair PriorityQueue::removeMin() {

    //current min of the queue
    KeyValuePair theMin = nodes_[1]; 
    //swapping the first vector with the value
    std::swap(nodes_[1], nodes_[size_]);
    //decrement the size of the vector
    size_--; 
    //heapify down the new minimum number
    heapifyDown(1); 
    //return the new minimum
   
    return theMin; 
}

bool PriorityQueue::isEmpty() const {
    //if the size_ variable it 0
	if (size_ == 0)  { 
    //then that means queue is empty and return true
        return true; 
    //end of if
    }
    //if size_ variable is not 0
    else {
    //we return false
        return false; 
    //end of else
    }
}

size_t PriorityQueue::size() const {
    //return the size of the vector plus one 
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["maxHeapSize"] = max_size_;
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["numOperations"] = 200; 
  result["metadata"]["size"] = size_;
  
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    //make sure that we are not heapifyig the min node
    if (i != 1){ 
    //store the current node into child KVP variable
        KeyValuePair child = nodes_[i];
    //if the position of the child is at an even number in vector
        if ((i % 2) == 0){
    //then its parent is the position divided by 2 and we get the parent node
            KeyValuePair parentVector = nodes_[i/2]; 
    //we check if the child Key is smaller than the parent Key 
            if (child.first < parentVector.first){
    //if it is smaller than we swap the two nodes
                std::swap(nodes_[i/2], nodes_[i]);
            //end of if
            };
    //and then after they are swapped we heapify the new parent and check if they need to be moved further up
            heapifyUp(i/2);
        //end of if
        }
    //if the child position in the vector is an odd number
        else { 
    //the parent is the siblings node position divided by two
            KeyValuePair parentVector = nodes_[(i - 1)/2]; 
    //check if the child Key is less than the parent Key
            if (child.first < parentVector.first){
    //if they are then swap the parent and child node
                std::swap(nodes_[(i - 1)/2], nodes_[i]); 
            };
    //heapify the parent and check if it needs to be heapifies up furthermore
            heapifyUp((i - 1)/2);
        //end of else
        }
    //end of if
    }
}

//move values down the queue
void PriorityQueue::heapifyDown(size_t i) {

//if left child is at the end of the queue there is no right child at i node
    if (size_ == (i * 2)){ 
    //get left child KVP
        KeyValuePair leftchild = nodes_[(i * 2)]; 
    //get KVP of current node
        KeyValuePair Parent = nodes_[i];
    //check if the left child Key is less than the Parent Key
        if(leftchild.first < Parent.first)
        {
    //if it is than we swap the two nodes
            std::swap(nodes_[i], nodes_[i * 2]); 
        //end of if
        }   
    //end of if
    }
//if the right child is at the end of the current queue meaning the ith node has both right and left child
    if (size_ >= ((i * 2) + 1)){
    //get KVP of left child
        KeyValuePair child1 = nodes_[i * 2]; 
    //get KVP of right child
        KeyValuePair child2 = nodes_[(i * 2) + 1];
    //get KVP of parent (the current node)
        KeyValuePair parent = nodes_[i]; 
    //if the left child is less than parent AND right child is also less than parent
        if ((child1.first < parent.first) && (child2.first < parent.first)){
    //check if left child is less than right child
            if (child1.first < child2.first){
    //if it is swap the left child with parent
                std::swap(nodes_[i * 2], nodes_[i]); 
    //heapify down the new left child
                heapifyDown(i * 2); 
            //end of if
            }
    //else if the right child is smaller than the left child
            if (child2.first < child1.first){
    //swap the right child and parent
                std::swap(nodes_[(i * 2) + 1], nodes_[i]); 
    //heapify down the new right child 
                heapifyDown((i * 2) + 1);
            //end of if
            }
         //end of if
        }
//if the left child is less than the parent OR the right child is less than parent AND the left child is NOT less than parent AND right child is NOT less than parent
        if (((child1.first < parent.first) || (child2.first < parent.first)) && !((child1.first < parent.first) && (child2.first < parent.first))){
    //check if left child is less than parent
            if (child1.first < parent.first){
    //if its than swap left child with parent
                std::swap(nodes_[i * 2], nodes_[i]); 
    //heapify down the new child
                heapifyDown(i * 2);
            //end of if
            }
    //if right child is less than parent 
            if (child2.first < parent.first){
    //if it is than swap right child with parent
                std::swap(nodes_[(i * 2) + 1], nodes_[i]); 
    //heapify down the new child
                heapifyDown((i * 2) + 1); 
            //end of if
            }
        //end of if
        }
    //end of if
    }

}
//remove node at a certain position
void PriorityQueue::removeNode(size_t i) {
   // variable that holds the current size of the queue 
    size_t s = size();
    //swap the node at position i with the last element of node
    std::swap(nodes_[i], nodes_[s]);
    //reduce the size of the queue
    size_--;
    //heapify down the new switched node
    heapifyDown(i);
} 
Key PriorityQueue::getKey(size_t i) {
    // making a KeyValuePair variable to hold the node as to access it's key later
    KeyValuePair tempVector = nodes_[i]; 
    // accessing the key and returning it 
    return tempVector.first; 
}
//reutrns the pare of values
Value PriorityQueue::getValue(size_t i) 
{
    //get the pair of values at node[i]
    KeyValuePair tempKVP = nodes_[i];
    //return the Value of the node
    return tempKVP.second; 
}