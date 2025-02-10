// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER

#include "HttpServer.hpp"
#include "GoldbachWebApp.hpp"
#include "signalHandler.hpp"


/// Start the web server
int main(int argc, char* argv[]) {
  manageKillSignals();
  // Create the web server
  // Create a Goldbach web application, and other apps if you want
  GoldbachWebApp goldbachwebapp;
  goldbachwebapp.createOwnQueue();
  goldbachwebapp.startThread();
  // Register the web application(s) with the web server
  HttpServer::getInstance().chainWebApp(&goldbachwebapp);
  // Run the web server
  return HttpServer::getInstance().run(argc, argv);
}

#endif  // WEBSERVER
