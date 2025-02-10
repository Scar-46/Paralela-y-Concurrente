// Copyright [2023] <Fernando Arce Castillo>
#ifndef GOLDBACH_SERIE
#define GOLDBACH_SERIE
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include "GQueue.hpp"
class GoldbachSerie{
 private:
  /*attr*/

 public:
  /**
   * @brief Construct a new Goldbach Serie object
   */
  GoldbachSerie() {}
  /**
   * @brief Destroy the Goldbach Serie object
   */
  ~GoldbachSerie() {}
  /**
   * @brief Calculates Goldbach serie
   * @param num Number whose Goldbach serie will be calculated
   * @param sign Sign, if is 0 then the number is negative
   * @param my_queue Queue where the Goldbach serie will be calculated
   * @return Number of posible Goldbach sums
  */
  int64_t goldbach_serie(int64_t num, short sign,
    GQueue * my_queue);  // TODO(Fernando) Cambiar a goldbach queue
  /**
   * @brief Calculates whether a number is prime or not
   * @details Primality test https://en.wikipedia.org/wiki/Primality_test#C,_C++,_C#_&_D
   * @param number Number that we want to verify if is prime
   * @return Boolean, if the given number is prime it will be true
  */
  bool is_prime(int64_t number);
  /**
   * @brief Aditional case of Goldbach Serie for odd numbers
   * 
   * @param num  Number whose Goldbach serie will be calculated
   * @param first  First number of the Goldbach serie
   * @param sums  Number of posible Goldbach sums
   * @param sign  Sign, if is 0 then the number is negative
   * @param my_Gqueue  Queue where the Goldbach serie will be calculated
   */
  void odd_num(int64_t num, int64_t first, int64_t * sums, short sign,
  GQueue * my_Gqueue);
};

#endif
