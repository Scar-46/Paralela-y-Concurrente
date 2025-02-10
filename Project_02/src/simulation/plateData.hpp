/**
 * @file plateData.hpp
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @brief  Struct made to the information about plate test
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PLATE_DATA_HPP
#define PLATE_DATA_HPP

#include <vector>
#include <string>

/**
 * @brief Struct made to the information about plate test
 * @struct plateData
 */
struct plateData {
    /// @brief path to the file
    std::string path;
    /// @brief seconds to run each stage
    double seconds;
    /// @brief difusion constant
    double difu;
    /// @brief dimension of each cell in the matrix
    double dimension;
    /// @brief sensitivity of the equilibrium point
    double sensitivity;
    /// @brief number of stages runned in the test
    int stages;
    /// @brief time elapsed in the test
    std::string elapsed;
};
#endif  // PLATE_DATA_HPP
