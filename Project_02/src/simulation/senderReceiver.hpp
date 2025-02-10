/**
 * @file senderReceiver.hpp
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @brief  Functions to send and receive data from the master process
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SENDER_RECEIVER_HPP
#define SENDER_RECEIVER_HPP

#include <mpi.h>
#include <fstream>
#include <string>
#include <vector>

#include "errorCodes.hpp"
#include "plateData.hpp"
#include "reportWriter.hpp"

void sendStopCondition(int platesSize, int processCount, int next_process,
int available_process, int asigned_jobs_copy);
void mapping(int asigned_jobs, int platesSize, int & error);
void allProcess(std::vector<plateData> plates, std::string folder,
int threadCount, std::ofstream * reportFile, std::string OUTPUTDIR);


#endif
