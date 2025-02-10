/**
 * @file GoldbachSolver.hpp
 * @author Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>
 * @brief Calls functions to execute the Goldbach calculations
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef GOLDBACHMAIN
#define GOLDBACHMAIN

#include <cctype>
#include <cerrno>
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <sstream>
#include <string>
#include "GoldbachSerial.hpp"
#include "Celd.hpp"
/// @brief  Calls functions to execute the Goldbach calculations
class GoldbachSolver {
 private:
    GoldbachSerie goldbach;

 public:
    /**
     * @brief Construct a new Goldbach Solver object
     */
    GoldbachSolver(/* args */) {}
    /**
     * @brief Destroy the Goldbach Solver object
     */
    ~GoldbachSolver() {}
    /**
     * @brief Validates if the input is a number
     * @param input_data Char array to be validated as a number
     * @return true if input is a numeric, false otherwise
    */
    bool validate_input(char input_data[]);

    /**
     * @brief Calls functions to execute the Goldbach calculations
     * @param celd  cCeld object with the number to be calculated
     * @return List* 
     */
    void *  Goldbachmain(Celd & celd);
};
#endif
