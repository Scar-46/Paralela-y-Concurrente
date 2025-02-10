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
#ifndef HEAT_CALC
#define HEAT_CALC
#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

/**
 * @brief Calculates the heat for the simulation
 * 
 * @param matrix  matrix with the temperatures
 * @param duration  duration of the simulation
 * @param difusitivity  difusitivity of the material
 * @param celdDimentions  dimentions of the cells
 * @param sensitivity  sensitivity of the simulation
 * @param rows  number of rows in the matrix
 * @param colums  number of columns in the matrix
 * @param state  state of the simulation
 * @param threadCount  number of threads to use
 * @return int  time in seconds
 */
int calculateHeat(std::vector<std::vector<double>>& matrix,
double duration, double difusitivity,
double celdDimentions, double sensitivity, int rows, int colums,
int& state, int threadCount);

/**
 * @brief Formats time to a string
 * 
 * @param seconds  time in seconds
 * @return std::string  time in string format
 */
std::string format_time(time_t seconds);

#endif
