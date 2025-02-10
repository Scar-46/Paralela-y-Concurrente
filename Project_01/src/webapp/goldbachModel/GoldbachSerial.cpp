// Copyright [2023] <Fernando Arce Castillo>
#include "GoldbachSerial.hpp"

/**
 * @brief Aditional case of Goldbach Serie
 * @see goldbach_serie
 * 
 * Adapted from https://en.wikipedia.org/wiki/Primality_test#C,_C++,_C#_&_D
*/
void GoldbachSerie::odd_num(int64_t num, int64_t first, int64_t * sums,
  short sign, GQueue * my_Gqueue) {
  for (int64_t i = 2; i <= num/2; ++i) {
    if (is_prime(i)) {
      int64_t j = num - i;
      if (is_prime(j)) {
        if (first <= i && i <= j) {
          if (sign == 0) {  // Negative
            my_Gqueue->push(first, i, j);
          } else {
            my_Gqueue->incrementCounter();
          }
          ++(*sums);
        }
      }
    }
  }
}

int64_t GoldbachSerie::goldbach_serie(int64_t num,
  short sign, GQueue * my_Gqueue) {
  int64_t sums = 0;
  if (num < 6) {
    return 0;
  }
  for (int64_t i = 2; i <= num/2; ++i) {
    if (is_prime(i)) {
      int64_t j = num - i;
      if (num%2 == 0) {
        if (is_prime(j)) {
          if (i <= j) {
            if (sign == 0) {  // Negative
              my_Gqueue->push(i, j, 0);
            } else {
              my_Gqueue->incrementCounter();
            }
            ++sums;
          }
        }
      } else {
        odd_num(j, i, &sums, sign, my_Gqueue);
      }
    }
  }
  return sums;
}

bool GoldbachSerie::is_prime(int64_t number) {
  if (number == 2 || number == 3)
    return true;

  if (number <= 1 || number % 2 == 0 || number % 3 == 0)
    return false;

  for (int i = 5; i * i <= number; i += 6) {
    if (number % i == 0 || number % (i + 2) == 0)
      return false;
  }

  return true;
}
