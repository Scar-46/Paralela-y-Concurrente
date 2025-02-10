// Copyright 2023 Alexander Sánchez Zamora <alexander.sanchezzamora@ucr.ac.cr>

#include "common/signalHandler.hpp"

///  adapted from: https://www.geeksforgeeks.org/signal-handling-in-cpp/
void signalHandler(int signal_num) {
  signal_num += signal_num;
  Log::getInstance().append(Log::getInstance().INFO, "kill"
    , "Requested thread ID: " + std::to_string(pthread_self()));
  // throws an exeption for the HttpServer to catch
  HttpServer::getInstance().stop();
}

void manageKillSignals() {
  signal(SIGINT, signalHandler);
  signal(SIGHUP, signalHandler);
  signal(SIGTERM, signalHandler);
}
