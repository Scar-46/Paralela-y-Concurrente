/**
 * @file GQueue.hpp
 * @author Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>
 * @brief Data structure that forms a queue
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef GOLDBACH_QUEUE
#define GOLDBACH_QUEUE

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "Node.hpp"

class GQueue {
 private:
  Node *firstNode;  /// Pointer to the first node
  Node *lastNode;  /// Pointer to the last node
  int64_t counter;  /// Counter of sums number

 public:
  /**
   * @brief Constructor for Queue class
  */
  GQueue();
  /**
   * @brief Destructor for Queue class
  */
  ~GQueue();
      /**
   * @brief Inserts an element at  the end of the queue
   * @param num1 First operand from sum
   * @param num2 Second operand from sum
   * @param num3 Third operand from sum
  */
  void push(int64_t num1, int64_t num2, int64_t num3);
  /**
   * @brief pops an element from the queue
   * @return First node from the queue
  */
  Node pop();
  /**
   * @brief get counter from queue
   * @return int64_t Counter
  */
  int64_t getCounter() {
    return this->counter;
  }
  /**
   * @brief Increments queue counter in one unit
  */
  void incrementCounter() {
    ++this->counter;
  }
  /**
   * @brief overloads impression for Queue class
   * @param out ostream that will be modified
   * @param queue Queue that will be impress
   * @return ostream
  */
  friend inline std::ostream& operator<<(std::ostream& out, GQueue& queue) {
    for (int64_t i =0; i < queue.counter; i++) {
      out << queue.printQueue();
    }
    return out;
  }
  std::string printQueue();
};  // End of Queue
#endif
