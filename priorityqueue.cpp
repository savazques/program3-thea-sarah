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
    size_++; 
    nodes_[size_] = kv;
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
    size_--; 
    //get Keyvalue of new minimum 
    KeyValuePair newMin = nodes_[1]; 
    //heapify down the new minimum number
    heapifyDown(1); 
    //return the new minimum
    return newMin; 
}

bool PriorityQueue::isEmpty() const {
	if (size_ == 0)  { 
        return true; 
    }
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
    if (i != 1){ 
        KeyValuePair child = nodes_[i];
        if ((i % 2) == 0){
            KeyValuePair parentVector = nodes_[i/2]; 
            if (child.first < parentVector.first){
                std::swap(nodes_[i/2], nodes_[i]);
            };
            heapifyUp(i/2);
        }
        else { 
            KeyValuePair parentVector = nodes_[(i - 1)/2]; 
            if (child.first < parentVector.first){
                std::swap(nodes_[(i - 1)/2], nodes_[i]); 
            };
            heapifyUp((i - 1)/2);
        }
    }
}

void PriorityQueue::heapifyDown(size_t i) {

    if (size_ == (i * 2)){ 
        KeyValuePair leftchild = nodes_[(i * 2)]; 
        KeyValuePair Parent = nodes_[i];
        if(leftchild.first < Parent.first)
        {
            std::swap(nodes_[i], nodes_[i * 2]); 
        }   
    }
    if (size_ >= ((i * 2) + 1)){
        KeyValuePair child1 = nodes_[i * 2]; 
        KeyValuePair child2 = nodes_[(i * 2) + 1];
        KeyValuePair parent = nodes_[i]; 
        if ((child1.first < parent.first) && (child2.first < parent.first)){
            if (child1.first < child2.first){
                std::swap(nodes_[i * 2], nodes_[i]); 
                heapifyDown(i * 2); 
            }
            if (child2.first < child1.first){
                std::swap(nodes_[(i * 2) + 1], nodes_[i]); 
                heapifyDown((i * 2) + 1);
            }
        }
        if (((child1.first < parent.first) || (child2.first < parent.first)) && !((child1.first < parent.first) && (child2.first < parent.first))){
            if (child1.first < parent.first){
                std::swap(nodes_[i * 2], nodes_[i]); 
                heapifyDown(i * 2);
            }
            if (child2.first < parent.first){
                std::swap(nodes_[(i * 2) + 1], nodes_[i]); 
                heapifyDown((i * 2) + 1); 
            }
        }
    }
}

void PriorityQueue::removeNode(size_t i) {
   // variable that holds the size of the node
    size_t s = size();
    std::swap(nodes_[i], nodes_[s]);
    size_--;
    heapifyDown(i);
} 
Key PriorityQueue::getKey(size_t i) {
    // making a KeyValuePair variable to hold the node as to access it's key later
    KeyValuePair tempVector = nodes_[i]; 
    // accessing the key and returning it 
    return tempVector.first; 
}
