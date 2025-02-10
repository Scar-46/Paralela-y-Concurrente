/**
 * @file Packer.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora@ucr.ac.cr>
 * @brief Class used to reunite all numbers studied in a sigle response
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 */
// TODO(Alex): change description to a general class
#ifndef GPACKER
#define GPACKER

#include <unistd.h>
#include <map>
#include <vector>
#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "NumData.hpp"

template <typename typeStruct>

/// @brief  Class used to reunite all numbers studied in a sigle response
/// @tparam typeStruct  Type of struct used to store the data
class Packer : public Assembler<NumData<typeStruct>*
    , std::vector<NumData<typeStruct>*>*> {
 private:
  std::map<HttpResponse*, std::vector<NumData<typeStruct>*>*> requestMap;
  std::map<HttpResponse*, int64_t> dataCount;

 public:
  /// Default constructor
  Packer() {
  }

  /// Default destructor
  ~Packer() {
  }

  /// @brief  Method used to consume all the messages that arrive
  void consumeForever() override {
    assert(this->consumingQueue);
    int stopPacks = 0;
    while (true) {
      // Get the next data to consume, or block while queue is empty
      NumData<typeStruct>* data = this->consumingQueue->dequeue();
      // If data is the stop condition, stop the loop
      if ( data->getRequestSize() == 0 ) {
        ++stopPacks;
        if (stopPacks == sysconf(_SC_NPROCESSORS_ONLN)) {
          std::vector<NumData<typeStruct>*> * newVec
            = new std::vector<NumData<typeStruct>*>();
          delete data;
          this->produce(newVec);
          break;
        }
      } else {
      // Process this data
        this->consume(data);
      }
    }
  }
  /// @brief Method used to start the forever loop to consume all the messages
  int run() override {
    // Start the forever loop to consume all the messages that arrive
    this->consumeForever();
    // If the forever loop finished, no more messages will be processed
    return EXIT_SUCCESS;
  }
  /// @brief  Method used to consume a single message
  /// @param numData  Message to be consumed
  void consume(NumData<typeStruct> * numData) override {
  // If requested more than one operation
    if (numData->getRequestSize() > 1) {
      // If the response exists in the map
      if (this->requestMap.count(numData->getResponseAdr()) == 1) {
        this->requestMap[numData->getResponseAdr()]->at(numData->getRequestPosition()) = numData;
        ++this->dataCount[numData->getResponseAdr()];
        // If all the operations of a request are packed in a single vector
        if (this->dataCount[numData->getResponseAdr()]
          == numData->getRequestSize()) {
          this->dataCount.erase(numData->getResponseAdr());
          this->produce(requestMap[numData->getResponseAdr()]);
        }
      } else {
        std::vector<NumData<typeStruct>*> * newVec =
            new std::vector<NumData<typeStruct>*>();
        newVec->resize(numData->getRequestSize(), numData);
        //newVec->at(numData->getRequestPosition()) = numData;
        this->requestMap[numData->getResponseAdr()] = newVec;
        ++this->dataCount[numData->getResponseAdr()];
      }
    } else if (numData->getRequestSize() == 1) {
      std::vector<NumData<typeStruct>*> *
          newVec = new std::vector<NumData<typeStruct>*>();
      newVec->push_back(numData);
      this->produce(newVec);
    } else {
      // TODO(Alex): throw error
    }
  }
};
#endif
