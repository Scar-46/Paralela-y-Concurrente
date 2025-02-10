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

#include <vector>

/**
 * @brief Struct made to contain data about a matrix
 * 
 */
struct MatrixData {
    /// @brief number of rows in the matrix
    unsigned int rows;
    /// @brief number of columns in the matrix
    unsigned int columns;
    /// @brief temperatures of every cell in the matrix
    std::vector<std::vector<double>> temperatures;
};

