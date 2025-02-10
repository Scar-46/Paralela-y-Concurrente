/**
 * @file Node.hpp
 * @author Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>
 * @brief Node class for queue
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef NODEGOLDBACH
#define NODEGOLDBACH

#include <inttypes.h>
/**
* @class Node
* @brief Container for Node, necesary for Queue @see Queue.hpp
*/
class Node {
  friend class GQueue;
 private:
  int64_t nums[3];  /// Array with Goldbach sum operands
  Node * next;  /// Next node pointer
 public:
  /// @brief Construct a new Node object
  Node() {}
  /// @brief Destroy the Node object
  ~Node() {}
};

#endif
