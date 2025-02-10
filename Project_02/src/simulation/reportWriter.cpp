/**
 * @file reportWriter.cpp
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @brief  Functions to send and receive data from the master process
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "reportWriter.hpp"

void makeReport(std::vector<plateData> plates, size_t i, std::string folder,
int threadCount, std::ofstream * reportFile, std::string OUTPUTDIR) {
  plateData plate = plates[i];
  // Set path to the binary file
  std::string path = folder + plate.path;
  std::ifstream inputBinary(path, std::ios::binary);
  if (inputBinary.is_open()) {
    int error = EXIT_SUCCESS;
    matrixData matrix = readMatrixFromBinaryStream(inputBinary, error);
    if (error == EXIT_SUCCESS) {
      int duration = calculateHeat(matrix.temperatures, plate.seconds,
        plate.difu, plate.dimension, plate.sensitivity, matrix.rows,
        matrix.columns, plate.stages, threadCount);
      plate.elapsed = format_time(duration);

      std::string body = plate.path + "\t" + std::to_string(plate.seconds)
        + "\t" + std::to_string(plate.difu) + "\t"
        + std::to_string(plate.dimension) + "\t"
        + std::to_string(plate.sensitivity) + "\t"
        + std::to_string(plate.stages) + "\t"
        + plate.elapsed + "\n";
      if (reportFile->is_open()) {
        reportFile->write(body.c_str(), body.size());
        reportFile->flush();
      } else {
        std::cerr << "Error: could not open report file" << std::endl;
      }

      int lDot = plate.path.find_last_of(".");
      std::string reportBinName = OUTPUTDIR + plate.path.substr(0
        , lDot) + "-" + std::to_string(plate.stages) + ".bin";
      std::ofstream reportBin(reportBinName, std::ios::binary);
      if (reportBin.is_open()) {
        writeMatrixToBinaryStream(reportBin, matrix, error);
        reportBin.close();
      } else {
        std::cerr << "Error: could not open reportBin file" << std::endl;
      }
    } else {
      std::cerr << "Error: could not read matrix" << std::endl;
    }

    inputBinary.close();
  } else {
    std::cerr << "Error: could not open file" << std::endl;
    MPI_Finalize();
    return;
  }
}
