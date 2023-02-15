#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) { //635, (0,0)
    //store the newest value into the last position of vector
    nodes_[max_size_] = kv; 
    //increase the node size count
    size_++; 
    //swap the next node count with the new number
    std::swap(nodes_[size_], nodes_[max_size_]); 
     // FOR TESTING KeyValuePair checkKey = nodes_[size_]; 
    //heapify the next node count 
    heapifyUp(size_); 
}

KeyValuePair PriorityQueue::min() {
    // returning the top node, which is the min as the heap is a min heap
	return nodes_[1]; 
}

KeyValuePair PriorityQueue::removeMin() {
    //swapping the first vector with the value
    std::swap(nodes_[1], nodes_[size_]);
    //decrement the size of the vector
    size_ --; 
    //get Keyvalue of new minimum 
    KeyValuePair newMin = nodes_[1]; 
    //heapify down the new minimum number
    heapifyDown(1); 
    //return the new minimum
    return newMin; 
}

bool PriorityQueue::isEmpty() const {
    //if size of the vector is 0 that means it is empty and return true
    KeyValuePair checkifempty = nodes_[1];
    std::cout<<checkifempty.first<<std::endl; 
	if (checkifempty.first == 0)  { 
        return true; 
    }
    //else we return false
    else {
        return false; 
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
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    //dont heapify if you are at the root 
    if (i != 1){ 
        //variable that holds child info
        KeyValuePair child = nodes_[i];

        if ((i % 2) == 0){
            KeyValuePair parentVector = nodes_[i/2]; 
        //check if the child is smaller than the parent 
            if (child.first < parentVector.first){
                //the child becomes the parent
                std::swap(nodes_[i/2], nodes_[i]);
            };
        }
        else { 
            KeyValuePair parentVector = nodes_[(i - 1)/2]; 
        //check if the child is smaller than the parent 
            if (child.first < parentVector.first){
                //the child becomes the parent
                std::swap(nodes_[(i - 1)/2], nodes_[i]); 
            };
        };
        //varibale that hoild parent info
        KeyValuePair parentVector = nodes_[i/2]; 
        //check if the child is smaller than the parent 
        if (child.first < parentVector.first){
            //the child becomes the parent
            std::swap(nodes_[i/2], nodes_[i]);
            
        }
    }
    // using recursion to continue to check the parent if such a par
    if (i != 1){
        heapifyUp(i/2); 
    } 
}

void PriorityQueue::heapifyDown(size_t i) {
    //check if the size of nodes is equal to left child index that case that the node only has one child
    if (nodes_.size() == (i * 2)){
        //create variable that holdes the KVP of left child
        KeyValuePair leftchild = nodes_[(i*2)]; 
        //create variable that holds KVP of parent 
        KeyValuePair Parent = nodes_[i];
        //if parent is bigger than left child we switch 
        if(leftchild.first < Parent.first)
        {
            std::swap(nodes_[i], nodes_[i*2]); 
        }
        
            
     
    }
    // in the case that the ith node has two children 
	if(nodes_.size() > ((i * 2)+1)){
        // assigning a child1, a KeyValuePair variable to the value of the ith's node first child
        KeyValuePair child1 = nodes_[i * 2]; 
        // assigning a child1, a KeyValuePair variable to the value of the ith's node second child
        KeyValuePair child2 = nodes_[(i * 2) + 1];
        // assigning a child1, a KeyValuePair variable to the value of the ith node 
        KeyValuePair parent = nodes_[i]; 
        // in the case that both children are smaller than the parent 
        if ((child1.first < parent.first) && (child2.first < parent.first)){
            // in the case that the first child is smaller than the second
            if (child1.first < child2.first){
                // child node becomes parent node 
                // nodes_[i *2] = parent; 
                // // parent node becomes child node 
                // nodes_[i] = child1; 

                std::swap(nodes_[i*2], nodes_[i]); 
            }
            // in the case that the second child is smaller than the first
            if (child2.first < child1.first){
                // child node becomes parent mode 
                // nodes_[(i * 2) +1] = parent; 
                // // parent node becomes the child node 
                // nodes_[i] = child2; 

                std::swap(nodes_[i*2], nodes_[i]); 
            }
            // exit if it was both children that were smaller than the parent 
            exit(0); 
        }
        // in the case that only one child is smaller than the parent (ensured by the exit statment earlier)
        if ((child1.first < parent.first) || (child2.first < parent.first)){
            // in the case that it is the first child that is smaller 
            if (child1.first < parent.first){
                // child node becomes parent node 
                // nodes_[i *2] = parent; 
                // // parent node becomes child node 
                // nodes_[i] = child1; 
                std::swap(nodes_[i*2], nodes_[i]); 
            }
            // in the case that it is the second child that is smaller than the parent 
            if (child2.first < parent.first){
                // child node becomes parent mode 
                // nodes_[(i * 2) +1] = parent; 
                // // parent node becomes the child node 
                // nodes_[i] = child2; 

                std::swap(nodes_[i*2], nodes_[i]); 
            }
        }
    }
    // using recursion to continue to check the children of node i if such chiden exist
    if (nodes_.size() > ((i * 2) + 1)){ 
        // specifically child one (left)
        heapifyDown( i * 2); 
        // specifically child two (right) 
        heapifyDown((i * 2) + 1); 
    } 
}

void PriorityQueue::removeNode(size_t i) {
   // variable that holds the size of the node
    size_t s = size();
   //swapping the last node with the node we want to remove
    nodes_[i] = nodes_[s]; 
    //pop the last node
    nodes_.pop_back();
    //heapify down if needed
    heapifyDown(i);  
    //heapify up if needed 
    heapifyUp(i); 
} 
Key PriorityQueue::getKey(size_t i) {
    // making a KeyValuePair variable to hold the node as to access it's key later
    KeyValuePair tempVector = nodes_[i]; 
    // accessing the key and returning it 
    return tempVector.first; 
}


// del vector[index]