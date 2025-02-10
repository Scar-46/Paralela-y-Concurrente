/**
 * @file senderReceiver.cpp
 * @author Oscar Fernández jiménez <oscar.fernandezjimenez>
 * @author Fernando Arce Castillo <fernando.arcecastillo>
 * @brief  Functions to send and receive data from the master process
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "senderReceiver.hpp"

void sendStopCondition(int platesSize, int processCount, int next_process,
int available_process, int asigned_jobs_copy) {
  if (next_process >= platesSize) {
    // Send stop condition
    for (int i = 1; i < processCount; i++) {
      if (i == available_process) {
        int stop_condition = platesSize + 1;
        if (MPI_Send(&stop_condition, 1, MPI_INT, i, 2, MPI_COMM_WORLD)
          != MPI_SUCCESS) {
          std::cerr << "Error: could not send stop condition" << std::endl;
          // error = E_CANT_SEND_MPI;
        }
      } else {
        if (MPI_Send(& (platesSize), 1, MPI_INT, i, 2, MPI_COMM_WORLD)
          != MPI_SUCCESS) {
          std::cerr << "Error: could not send stop condition" << std::endl;
        }
      }
    }
  } else {
  // Send asigned_jobs
    if (MPI_Send(&asigned_jobs_copy, 1, MPI_INT, available_process, 2
      , MPI_COMM_WORLD) != MPI_SUCCESS) {
      std::cerr << "Error: could not send asigned_jobs_copy" << std::endl;
    }
  }
}

void mapping(int asigned_jobs, int platesSize, int & error) {
  int processCount = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  if (processCount <=1) {
    std::cerr << "Error: Invalid number of processes, must be at least two"
     << std::endl;
    error =  EXIT_FAILURE;
    return;
  }
  if (asigned_jobs+1 < processCount) {
    // Since process 0 wont give work to itself
    int next_process = asigned_jobs + 1;
    // Send number of process
    if (MPI_Send(&next_process, 1, MPI_INT, next_process, 0, MPI_COMM_WORLD)
      != MPI_SUCCESS) {
      std::cerr << "Error: could not send next_process" << std::endl;
    }

    // Send "task"
    if (MPI_Send(&asigned_jobs, 1, MPI_INT, next_process, 1, MPI_COMM_WORLD)
      != MPI_SUCCESS) {
      std::cerr << "Error: could not send asigned_jobs" << std::endl;
    }

    // Send stop condition
    sendStopCondition(platesSize, processCount, next_process,
    next_process, asigned_jobs + 1);
  } else {
    int available_process;
    // Recive available process
    if (MPI_Recv(&available_process, 1, MPI_INT, MPI_ANY_SOURCE, 3
      , MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      std::cerr << "Error: could not receive available_process" << std::endl;
    } else {
      // Send number of process
      if (MPI_Send(&available_process, 1, MPI_INT, available_process, 0
        , MPI_COMM_WORLD) != MPI_SUCCESS) {
        std::cerr << "Error: could not send available_process" << std::endl;
      }
      // Send "task"
      if (MPI_Send(&asigned_jobs, 1, MPI_INT, available_process, 1
        , MPI_COMM_WORLD) != MPI_SUCCESS) {
        std::cerr << "Error: could not send asigned_jobs" << std::endl;
      }
      int next_process = asigned_jobs + 1;
      int asigned_jobs_copy = asigned_jobs + 1;
      // So it doesnt overflow processCount
      if (asigned_jobs_copy >= processCount) {
        asigned_jobs_copy = 1;
      }
      // Send stop condition
      sendStopCondition(platesSize, processCount, next_process,
      available_process, asigned_jobs_copy);
    }
  }
}

void allProcess(std::vector<plateData> plates, std::string folder,
int threadCount, std::ofstream * reportFile, std::string OUTPUTDIR) {
  int asigned_jobs = 0;
  int platesSize = plates.size();
  int processNumber = -1;
  int error = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &processNumber);
  for (asigned_jobs = 0; asigned_jobs < platesSize; asigned_jobs++) {
    if (processNumber == 0) {
      // Send asigned_jobs
      mapping(asigned_jobs, platesSize, error);
      if (error == EXIT_FAILURE) {
        break;
      }
    } else {
      // Recive asigned_jobs
      if (MPI_Recv(&asigned_jobs, 1, MPI_INT, 0, 2, MPI_COMM_WORLD,
        MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        std::cerr << "Error: could not receive asigned_jobs" << std::endl;
      }
      if (asigned_jobs == platesSize) {
        break;
      }
      int calculate_process;
      // Recives number of the process that will calculate
      if (MPI_Recv(&calculate_process, 1, MPI_INT, 0, 0, MPI_COMM_WORLD
        , MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        std::cerr << "Error: could not receive calculate_process" << std::endl;
      }
      if (calculate_process == processNumber) {
        int calculated_number;

        if (MPI_Recv(&calculated_number, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,
          MPI_STATUS_IGNORE) != MPI_SUCCESS) {
          std::cerr << "Error: could not receive calculated_number"<< std::endl;
        }
        // Calculate the plate and make the report
        makeReport(plates, calculated_number, folder,
        threadCount, reportFile, OUTPUTDIR);

        if (MPI_Send(&processNumber, 1, MPI_INT, 0, 3, MPI_COMM_WORLD)
          != MPI_SUCCESS) {
          std::cerr << "Error: could not send processNumber" << std::endl;
        }
      }
    }
  }
}
