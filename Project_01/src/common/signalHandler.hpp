/**
 * @file signalHandler.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora@ucr.ac.cr>
 * @brief Handles a given signal with a function.
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PROJECT_01_SRC_COMMON_SIGNALHANDLER_HPP_
#define PROJECT_01_SRC_COMMON_SIGNALHANDLER_HPP_

#include <csignal>

#include "http/HttpServer.hpp"
#include "common/Log.hpp"

/** @brief sends a stop signal to the HttpServer
*   @param signal_num number of the signal capted
*/
void signalHandler(int signal_num);

/** @brief Manages every possible stop signals from ctrl + c and kill comands
*/
void manageKillSignals();

#endif  //  PROJECT_01_SRC_COMMON_SIGNALHANDLER_HPP_
