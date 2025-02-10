/**
 * @file main.cpp
 * @author Oscar Fernández jiménez -- OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr
 * @brief  Compares two files and prints if they are the same or not.
 * @version 0.1
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "matrixData.hpp"

MatrixData readMatrixFromBinaryStream(std::ifstream& inputBinary);

int main(int argc, char* argv[]) {
  std::string  firstFile = "file1.txt";
  std::string secondFile = "file2.txt";
  double sensitivity = 0.0;
  // checks the amount of arguments.
  if (argc == 4) {
    firstFile = argv[1];
    secondFile = argv[2];
    sensitivity = std::stod(argv[3]);
  } else {
    std::cerr << "Error: invalid amount of arguments" << std::endl;
    return EXIT_FAILURE;
  }
  MatrixData firstMatrix;
  MatrixData secondMatrix;
  // Reads the first file.
  std::ifstream inputBinary(firstFile, std::ios::binary);
  if (inputBinary.is_open()) {
    firstMatrix = readMatrixFromBinaryStream(inputBinary);
    inputBinary.close();
  } else {
    std::cerr << "Error: unable to open file" << std::endl;
    return EXIT_FAILURE;
  }
  // Reads the second file.
  std::ifstream inputBinary2(secondFile, std::ios::binary);
  if (inputBinary2.is_open()) {
    secondMatrix = readMatrixFromBinaryStream(inputBinary2);
    inputBinary2.close();
  } else {
    std::cerr << "Error: unable to open file" << std::endl;
    return EXIT_FAILURE;
  }
  // Compares the files.
  if (firstMatrix.rows == secondMatrix.rows &&
      firstMatrix.columns == secondMatrix.columns) {
    double file1Cell;
    double file2Cell;
    bool different = false;
    for (size_t i = 0; (i < firstMatrix.rows) && !different; i++) {
      for (size_t j = 0; (j < firstMatrix.columns) && !different; j++) {
        file1Cell = firstMatrix.temperatures[i][j];
        file2Cell = secondMatrix.temperatures[i][j];
        if (fabs(file1Cell - file2Cell) > sensitivity) {
          std::cout << "The files are differente" << std::endl;
          different = true;
        }
      }
    }
    if (!different) {
      std::cout << "The files are the same" << std::endl;
    }
  } else {
    std::cout << "The files are differente" << std::endl;
  }
  return EXIT_SUCCESS;
}

MatrixData readMatrixFromBinaryStream(std::ifstream& inputBinary) {
  MatrixData matrix;
  inputBinary.read(reinterpret_cast<char*>(&matrix.rows), sizeof(matrix.rows));
  inputBinary.read(reinterpret_cast<char*>(&matrix.columns),
    sizeof(matrix.columns));
  for (size_t i = 0; i < matrix.rows; i++) {
    std::vector<double> row;
    for (size_t j = 0; j < matrix.columns; j++) {
      double cell;
      inputBinary.read(reinterpret_cast<char*>(&cell), sizeof(cell));
      row.push_back(cell);
    }
    matrix.temperatures.push_back(row);
  }
  return matrix;
}
