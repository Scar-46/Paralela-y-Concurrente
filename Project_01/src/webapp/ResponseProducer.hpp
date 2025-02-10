/**
 * @file ResponseProducer.hpp
 * @author Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>
 * @brief  Class used to create and send the response to the client
 * @version 0.1
 * @date 2023-02-9
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef RESPONSEPRODUCER
#define RESPONSEPRODUCER
#include <vector>
#include <string>
#include <utility>

#include "Consumer.hpp"
#include "NumData.hpp"

template <typename typeStruct>
/// @brief  Class used to create and send the response to the client
/// @tparam typeStruct Type of struct used to store the data
class ResponseProducer : public Consumer<std::vector<NumData<typeStruct>*>*> {
 public:
  /// @brief Default constructor
  ResponseProducer() {
  }
  /// @brief Default destructor
  ~ResponseProducer() {
  }
  /// @brief Method used to start the forever loop to consume all the messages
  int run() override {
    // Start the forever loop to consume all the messages that arrive
    this->consumeForever();
    // If the forever loop finished, no more messages will be processed
    return EXIT_SUCCESS;
  }
  /// @brief  Method used to consume all the messages that arrive
  void consume(std::vector<NumData<typeStruct>*>* package) override {
    std::string title = "Goldbach Series";
    HttpResponse * response =  package->at(0)->getResponseAdr();
    int64_t requestSize = package->at(0)->getRequestSize();
    // this->orderVector(package);
    for (int64_t i = 0; i < requestSize; i++) {
      response->body() << * package->at(i)->getStructData();
      delete package->at(i)->getStructData();
      delete package->at(i);
    }
    response->body()
    << "  </div>"
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";
    response->send();
    delete response;
    delete package;
    // package->~vector();
  }
  /// @brief  Method used to set the consuming queue
  void setConsumingQueue(Queue<std::vector<NumData<
      typeStruct>*>*>* consumingQueue) {
    this->consumingQueue = consumingQueue;
  }
  /// @brief  consume all the messages that arrive
  void consumeForever() override {
    assert(this->consumingQueue);
    while (true) {
      // Get the next data to consume, or block while queue is empty
      std::vector<NumData<Celd*>*>* data = this->consumingQueue->dequeue();
      // If data is the stop condition, stop the loop
      if ( data->size() == 0 ) {
        delete data;
        break;
      }
      // Process this data
      this->consume(data);
    }
  }
  /// @brief Method used to order the vector
  /// @param vector  Vector to order
  void orderVector(std::vector<NumData<typeStruct>*>* vector) {
    // Swap function
    size_t i, j, min_idx;
    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < vector->size(); i++) {
      // Find the minimum element in an unsorted array
      min_idx = i;
      for (j = i+1; j < vector->size(); j++) {
        if ((*vector)[j]->getRequestPosition()
            < (*vector)[min_idx]->getRequestPosition())
          min_idx = j;
      }
      // Swap the found minimum element with the first element
      if (min_idx != i)
        swap((*vector)[min_idx], (*vector)[i]);
    }
  }
  /// @brief Method used to swap two elements
  /// @param xp  First element
  /// @param yp  Second element
  void swap(NumData<Celd*> *xp, NumData<Celd*> *yp) {
    NumData<Celd*> temp = *xp;
    *xp = *yp;
    *yp = temp;
  }
};
#endif

