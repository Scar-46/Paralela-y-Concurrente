/**
 * @file matrixData.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora>
 * @brief Struct made to contain data about a matrix
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MATRIX_DATA_HPP
#define MATRIX_DATA_HPP

#include <stdlib.h>
#include <vector>

/**
 * @brief Struct made to contain data about a matrix
 * @struct matrixData
 */
struct matrixData {
  /// @brief number of rows in the matrix
  uint64_t rows;
  /// @brief number of columns in the matrix
  uint64_t columns;
  /// @brief temperatures of every cell in the matrix
  std::vector<std::vector<double>> temperatures;
};

#endif  // MATRIX_DATA_HPP
