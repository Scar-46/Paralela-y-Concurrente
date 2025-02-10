// Copyright 2023 Fernando Jose Arce Castillo. Universidad de Costa Rica.

#include "Gcalculator.hpp"

int Gcalculator::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  // If the forever loop finished, no more messages will arrive
  return EXIT_SUCCESS;
}

void Gcalculator::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    NumData<Celd*> * data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if ( data->getRequestSize() == 0 ) {
      this->produce(data);
      break;
    }
    // Process this data
    this->consume(data);
  }
}

void Gcalculator::consume(NumData<Celd*>* consumedData) {
  Celd * producedCeld = consumedData->getStructData();
  if (producedCeld == NULL) {  // Stop condition
    this->produce(consumedData);
  } else {
    this->mySolver.Goldbachmain(*producedCeld);
    NumData<Celd*> * producedData = consumedData;
    producedData->setStructData(producedCeld);
    this->produce(producedData);
  }
}
