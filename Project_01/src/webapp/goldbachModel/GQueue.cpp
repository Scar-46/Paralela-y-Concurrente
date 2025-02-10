// Copyright 2023 Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>

#include<cstdlib>

#include "GQueue.hpp"

GQueue::GQueue() {
  this->firstNode = NULL;
  this->lastNode = NULL;
  this->counter = 0;
}
GQueue::~GQueue() {
  Node * it = this->firstNode;
  Node * aux;
  while (it != NULL) {
    aux = it;
    it = it->next;
    delete aux;
  }
}
void GQueue::push(int64_t num1, int64_t num2, int64_t num3) {
  Node * newNode;
  ++this->counter;
  newNode = new Node;
  newNode->nums[0] = num1;
  newNode->nums[1] = num2;
  newNode->nums[2] = num3;
  newNode->next = NULL;
  if (this->firstNode == NULL) {
    this->firstNode = newNode;
    this->lastNode = newNode;
  } else {
    this->lastNode->next = newNode;
    this->lastNode = newNode;
  }
}
Node GQueue::pop() {
  Node firstNodeCopy = *this->firstNode;
  Node * firstNodeRefence = this->firstNode;
  if (this->firstNode == this->lastNode) {
    this->firstNode = NULL;
    this->lastNode = NULL;
  } else {
    this->firstNode = this->firstNode->next;
  }
  delete firstNodeRefence;
  return firstNodeCopy;
}
std::string GQueue::printQueue() {
  Node * it = this->firstNode;
  std::string returnedStr;
  while (it != NULL) {
    if (it->nums[2] == 0) {  // even number
      if (it->next != NULL) {
        returnedStr+= std::to_string(it->nums[0]) + " + "
          + std::to_string(it->nums[1]);
        returnedStr+= ", ";
      } else {
        returnedStr+= std::to_string(it->nums[0]) + " + "
          + std::to_string(it->nums[1]);
      }
    } else {
      if (it->next != NULL) {
        returnedStr+= std::to_string(it->nums[0]) + " + "
          + std::to_string(it->nums[1]);
        returnedStr+= " + " + std::to_string(it->nums[2]);
        returnedStr+= ", ";
      } else {
        returnedStr+= std::to_string(it->nums[0]) + " + "
          + std::to_string(it->nums[1]);
        returnedStr+= " + " + std::to_string(it->nums[2]);
      }
    }
    it = it->next;
  }
  return returnedStr;
}  // End of GQueue
