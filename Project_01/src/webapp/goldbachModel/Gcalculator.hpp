// Copyright 2023 Fernando Jose Arce Castillo. Universidad de Costa Rica.

#ifndef GOLDBACHSOLVER
#define GOLDBACHSOLVER
#include "../prodcons/Assembler.hpp"
#include "../common/common.hpp"
#include "GoldbachSolver.hpp"
#include "NumData.hpp"
/// @brief Starts  consuming messages from the calculator queue
class Gcalculator:public Assembler<NumData<Celd*>*, NumData<Celd*>*> {
  DISABLE_COPY(Gcalculator);
 private:
  GoldbachSolver mySolver;
 public:
  /// @brief  Constructor
  Gcalculator() {}
  /// @brief  Destructor
  ~Gcalculator() {}
  /// @brief  Consumes the data from the queue
  /// @param num_data  Data to be consumed
  void consume(NumData<Celd*>* num_data) override;
  /// @brief  Starts the thread that consumes the data from the queue
  /// @return  EXIT_SUCCESS if the thread was started successfully
  int run() override;
  /// @brief  Starts the forever loop to consume all the messages that arrive
  void consumeForever() override;
};
#endif
