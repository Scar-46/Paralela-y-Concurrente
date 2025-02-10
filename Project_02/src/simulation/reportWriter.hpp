/**
 * @file reportWriter.hpp
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @brief  Writes the report of the simulation
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef REPORT_WRITTER_HPP
#define REPORT_WRITTER_HPP

#include <mpi.h>
#include <fstream>
#include <string>
#include <vector>

#include "plateData.hpp"
#include "matrixData.hpp"
#include "heatCalculator.hpp"
#include "fileManager.hpp"

void makeReport(std::vector<plateData> plates, size_t i, std::string folder,
int threadCount, std::ofstream * reportFile, std::string OUTPUTDIR);
#endif
