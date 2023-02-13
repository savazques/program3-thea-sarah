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

void PriorityQueue::insert(KeyValuePair kv) {
    //insert the keyvalue pair into vector
    nodes_.push_back(kv); 
    //get the size of the vector
    size_t s = size(); 
    std::cout<< s << std::endl ; 
    //heapify the last element to its correct place in heap
     heapifyUp(s); 
    
    
}

KeyValuePair PriorityQueue::min() {
    // returning the top node, which is the min as the heap is a min heap
    Key l ;
    KeyValuePair lv = nodes_[1];
    l = lv.first; 
    //std::cout<<l<<std::endl; 

	return nodes_[1]; 
}

KeyValuePair PriorityQueue::removeMin() {
    // storing the min 
    KeyValuePair tempMin = nodes_[1]; 
    //get the size of the vector
    size_t s = size(); 
    //swap the top of the heap with the last vector
	nodes_[1] = nodes_[s]; 
    //remove the last node
    nodes_.pop_back(); 
    //heapify the new number to its correct position
    heapifyDown(1); 

    return tempMin; 
}

bool PriorityQueue::isEmpty() const {
    //if size of the vector is 0 that means it is empty and return true
	if (nodes_.empty())  { 
        std::cout<<"yes is empty"<<std::endl;
        return true; 
    }
    //else we return false
    else {
        std::cout<<"not empty"<<std::endl;
        return false; 
    };
}

size_t PriorityQueue::size() const {
    //return the size of the vector 
    size_t k = nodes_.size(); 
    std::cout<< k << std::endl; 
    return nodes_.size();
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
        //varibale that hoild parent info
        KeyValuePair parentVector = nodes_[i/2]; 
        //check if the child is smaller than the parent 
        if (child.first < parentVector.first){
            //the child becomes the parent
            nodes_[i] = parentVector; 
            //the parent becomes the child
            nodes_[i/2] = child; 
            
        };
    };
    // using recursion to continue to check the parent if such a par
    if (i != 1){
        heapifyUp(i/2); 
    }; 
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
        //the parent becomes the left child 
            nodes_[i] = leftchild; 
        //the left child becomes the parent
            nodes_[i*2] = Parent;
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
                nodes_[i *2] = parent; 
                // parent node becomes child node 
                nodes_[i] = child1; 
            };
            // in the case that the second child is smaller than the first
            if (child2.first < child1.first){
                // child node becomes parent mode 
                nodes_[(i * 2) +1] = parent; 
                // parent node becomes the child node 
                nodes_[i] = child2; 
            };
            // exit if it was both children that were smaller than the parent 
            exit(0); 
        };
        // in the case that only one child is smaller than the parent (ensured by the exit statment earlier)
        if ((child1.first < parent.first) || (child2.first < parent.first)){
            // in the case that it is the first child that is smaller 
            if (child1.first < parent.first){
                // child node becomes parent node 
                nodes_[i *2] = parent; 
                // parent node becomes child node 
                nodes_[i] = child1; 
            };
            // in the case that it is the second child that is smaller than the parent 
            if (child2.first < parent.first){
                // child node becomes parent mode 
                nodes_[(i * 2) +1] = parent; 
                // parent node becomes the child node 
                nodes_[i] = child2; 
            };
        };
    };
    // using recursion to continue to check the children of node i if such chiden exist
    if (nodes_.size() > ((i * 2) + 1)){ 
        // specifically child one (left)
        heapifyDown( i * 2); 
        // specifically child two (right) 
        heapifyDown((i * 2) + 1); 
    }; 
};

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