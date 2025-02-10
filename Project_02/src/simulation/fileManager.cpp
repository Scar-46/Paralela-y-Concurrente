/**
 * @file fileManager.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora>
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @brief Functions to manipulate binary and plain text files
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdlib.h>
#include <exception> 
#include "fileManager.hpp"

void addPlate(std::vector<plateData>* plates, std::string line);

matrixData readMatrixFromBinaryStream(std::ifstream& input, int& error) {
  matrixData matrix;
  input.read(reinterpret_cast<char*>(&matrix.rows), sizeof(matrix.rows));
  if (!input.bad()) {
    input.read(reinterpret_cast<char*>(&matrix.columns),sizeof(matrix.columns));
    if (!input.bad()) {
      for (size_t row = 0; row < matrix.rows; ++row) {
        std::vector<double> temperatures;
        for (size_t col = 0; col < matrix.columns; ++col) {
          double cell;
          input.read(reinterpret_cast<char*>(&cell), sizeof(cell));
          if (!input.bad()) {
            temperatures.push_back(cell);
          } else {
            std::cerr << "Error: could not read binary file" << std::endl;
            error = E_CANT_READ_BIN;
            break;
          }
        }
        if (!input.bad()) {
          matrix.temperatures.push_back(temperatures);
        } else {
          break;
        }
      }
    } else {
      std::cerr << "Error: could not read binary file" << std::endl;
      error = E_CANT_READ_BIN;
    }
  } else {
    std::cerr << "Error: could not read binary file" << std::endl;
    error = E_CANT_READ_BIN;
  }
  
  
  return matrix;
}

void writeMatrixToBinaryStream(std::ofstream& output
, matrixData& matrix, int& error) {
  output.write(reinterpret_cast<char const*>(&matrix.rows)
  , sizeof(matrix.rows));
  if (!output.bad()) {
    output.write(reinterpret_cast<char const*>(&matrix.columns)
    , sizeof(matrix.columns));
    if (!output.bad()) {
      for (size_t row = 0; row < matrix.rows; ++row) {
        for (size_t col = 0; col < matrix.columns; ++col) {
          output.write(reinterpret_cast<char const*>(
              &matrix.temperatures[row][col]), sizeof(double));
          if (output.bad()) {
            std::cerr << "Error: could not write binary file" << std::endl;
            error = E_CANT_WRITE_BIN;
            break;
          }
        }
        if (output.bad()) {
          break;
        }
      }
    } else {
      std::cerr << "Error: could not write binary file" << std::endl;
      error = E_CANT_WRITE_BIN;
    }
  } else {
    std::cerr << "Error: could not write binary file" << std::endl;
    error = E_CANT_WRITE_BIN;
  }
}

std::vector<plateData> readAllPlates(std::string inputFileName, int* error) {
  // Read input .txt file
  std::ifstream inputFile(inputFileName);
  std::vector<plateData> plates;
  if (inputFile.is_open()) {
    while (inputFile.good()) {
      plateData plate;
      inputFile >> plate.path;
      inputFile >> plate.seconds;
      inputFile >> plate.difu;
      inputFile >> plate.dimension;
      inputFile >> plate.sensitivity;
      if (plate.path != "") {
        plates.push_back(plate);
      }
    }
    inputFile.close();
  } else {
    std::cerr << "Error: could not open file" << std::endl;
    *error = E_CANT_OPEN_IN_FILE;
  }
  return plates;
}
