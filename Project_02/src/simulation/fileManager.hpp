/**
 * @file fileManager.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora>
 * @brief Functions to manipulate binary and plain text files
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "errorCodes.hpp"
#include "matrixData.hpp"
#include "plateData.hpp"

/**
 * @brief creates a matrixData struct from a binary file
 * 
 * @param input  input binary file
 * @param error  error control int
 * @return matrixData  matrixData struct generated from the binary file
 */
matrixData readMatrixFromBinaryStream(std::ifstream& input, int& error);

/**
 * @brief writes a matrixData struct to a binary file
 * 
 * @param output  output binary file generated from the matrixData struct
 * @param matrix  matrixData struct to be written to the binary file
 */
void writeMatrixToBinaryStream(std::ofstream& output, matrixData& matrix    
  , int& error);

/**
 * @brief reads all the plates from a .txt file
 * 
 * @param inputFileName  name of the .txt file
 * @return std::vector<plateData>  vector containing all the plates
 */
std::vector<plateData> readAllPlates(std::string inputFileName, int* error);


#endif
