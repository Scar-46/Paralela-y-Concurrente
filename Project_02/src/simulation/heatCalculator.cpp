/**
 * @file heatCalculator.hpp
 * @author Fernando Arce <fernando.arcecastillo>
 * @brief Methods needed to calculate heat for the simulation
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <math.h>
#include <time.h>
#include <omp.h>
#include <cstring>
#include <iostream>
#include <ctime>
#include <vector>
#include "heatCalculator.hpp"
int calculateHeat(std::vector<std::vector<double>>& matrix, double duration,
double difusitivity, double celdDimentions, double sensitivity,
int rows, int colums, int& state, int threadCount) {
  int transcurredTime = duration;
  state = 1;
  bool stopCondition = false;
  std::vector<std::vector<double>> matrixCopy;
  matrixCopy.resize(rows, std::vector<double>(colums));
  std::copy(matrix.begin(), matrix.end(), matrixCopy.begin());
  while (!stopCondition) {
    stopCondition = true;
    #pragma omp parallel num_threads(threadCount) default(none)\
      shared(stopCondition, matrix, matrixCopy, rows, colums, \
      sensitivity, celdDimentions, duration, difusitivity)
      { int myStop = 1;
      #pragma omp for schedule(static) collapse(2)
      for (int i = 1; i < rows -1 ; i++) {
        for (int j = 1; j < colums -1; j++) {
          double currentTemperature = matrix[i][j];
          matrix[i][j] = matrix[i][j] +
          (((duration*difusitivity)/(celdDimentions*celdDimentions))
          * (matrixCopy[i-1][j]+matrixCopy[i][j+1]+matrixCopy[i+1][j]+
          matrixCopy[i][j-1]-(4*matrixCopy[i][j])));
          currentTemperature = fabs(currentTemperature - matrix[i][j]);
          if (currentTemperature > sensitivity) {
            myStop *= 0;
          }
        }
      }
      if (!myStop) {
        #pragma omp atomic write
        stopCondition = false;
      }
    }
    if (!stopCondition) {
      ++state;
      transcurredTime += duration;
      std::copy(matrix.begin(), matrix.end(), matrixCopy.begin());
    }
  }
  return transcurredTime;
}

std::string format_time(time_t seconds) {
  // TODO(any): Using C until C++20 std::format() is implemented by compilers
  char text[48];  // YYYY/MM/DD hh:mm:ss
  const std::tm& gmt = * std::gmtime(&seconds);
  snprintf(text, sizeof text, "%04d/%02d/%02d\t%02d:%02d:%02d", gmt.tm_year
    - 70, gmt.tm_mon, gmt.tm_mday - 1, gmt.tm_hour, gmt.tm_min, gmt.tm_sec);
  return text;
}
