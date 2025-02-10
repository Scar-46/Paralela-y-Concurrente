/**
 * @file main.cpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora>
 * @author Fernando Arce <fernando.arcecastillo>
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @brief Functions to manipulate binary and plain text files
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mpi.h>
#include <omp.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "errorCodes.hpp"
#include "senderReceiver.hpp"

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  int threadCount = 1;
  std::string inputFileName;
  if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {  // Init MPI
    std::cerr << "Error: could not init MPI" << std::endl;
    error = E_CANT_INIT_MPI;
  } else {
    // Read arguments
    if (argc >=2) {
      inputFileName = argv[1];
      if (argc == 3) {
        threadCount = std::stoi(argv[2]);
      } else if (argc > 3) {
        std::cerr << "Error: invalid amount of arguments" << std::endl;
        error = E_WRONG_ARG_COUNT;
      } else {
        threadCount = omp_get_max_threads();
      }

      // Create the report file
      const std::string OUTPUTDIR = "output/";
      std::vector<plateData> plates = readAllPlates(inputFileName, &error);
      if (error == EXIT_SUCCESS) {
        int folderEnd = inputFileName.find_last_of("/");
        std::string folder = inputFileName.substr(0, folderEnd + 1);
        int lastDot = inputFileName.find_last_of(".");
        std::string reportFileName = OUTPUTDIR +
          inputFileName.substr(folderEnd + 1, lastDot - folderEnd - 1) + ".tsv";
        // Cleans the report file before writing
        std::ofstream reportFile2(reportFileName, std::ios::trunc);
        reportFile2.close();
        std::ofstream reportFile(reportFileName, std::ios::app);
        if (reportFile.is_open()) {
          // Send the data to the processes
          allProcess(plates, folder, threadCount, &reportFile, OUTPUTDIR);
          reportFile.close();
        } else {
          std::cerr << "Error: could not open report file" << std::endl;
          error = E_CANT_OPEN_REP_FILE;
        }
      }
      MPI_Finalize();
    } else {
      std::cerr << "Error: invalid amount of arguments" << std::endl;
      error = E_WRONG_ARG_COUNT;
      MPI_Finalize();
    }
  }
  return error;
}
