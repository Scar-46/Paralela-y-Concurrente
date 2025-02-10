// Copyright 2023 OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr

#include "HandlerDispatcher.hpp"
#include "HttpApp.hpp"

HandlerDispatcher::HandlerDispatcher() {
}

HandlerDispatcher::~HandlerDispatcher() {
}

/// Consume the messages in its own execution thread
int HandlerDispatcher::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  return EXIT_SUCCESS;
}

void HandlerDispatcher::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    const responsePair data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if (data.stopCondition == true) {
      // If we exited from the forever loop, the finish message was received
      for ( const auto& pair : this->toQueues ) {
        pair.second->enqueue(this->stopCondition);
      }
      break;
    }
    // Process this data
    this->consume(data);
  }
}

std::string HandlerDispatcher::extractKey(const responsePair& data) const {
  int end = data.request->getURI().find_first_of('?');
  std::string key = data.request->getURI().substr(0, end);
  return key;
}
