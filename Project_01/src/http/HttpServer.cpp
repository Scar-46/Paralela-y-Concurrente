// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>

#include "HandlerDispatcher.hpp"
#include "HttpApp.hpp"
#include "HttpConnectionHandler.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"

const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n";

HttpServer& HttpServer::getInstance() {
  static HttpServer httpserver;
  return httpserver;
}

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}

int HttpServer::run(int argc, char* argv[]) {
  bool stopApps = false;
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      Log::getInstance().start();

      // Start all web applications
      this->startApps();
      stopApps = true;

      // Create and start the connection handlers
      this->createHandlers();
      this->startHandlers();
      // Start waiting for connections
      Log::append(Log::INFO, "webserver"
        , "Main thread ID: " + std::to_string(pthread_self()));
      //  vector de handlers
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));

      // Accept all client connections. The main process will get blocked
      // running this method and will not return. When HttpServer::stop() is
      // called from another execution thread, an exception will be launched
      // that stops the acceptAllConnections() invocation and enters in the
      // catch below. Then, the main thread can continue stopping apps,
      // finishing the server and any further cleaning it requires.
      this->acceptAllConnections();
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
    this->closeServer();
  }

  // If applications were started
  if (stopApps) {
    this->stopApps();
    this->stopHandlers();
  }

  // Stop the log service
  Log::getInstance().stop();
  return EXIT_SUCCESS;
}

void HttpServer::closeServer() {
  Log::append(Log::WARNING, "webserver", "Closing conections");
  for (long unsigned int index = 0; index < this->handlers.size(); ++index) {
    Socket stopCondition;
    //  enqueue stop conditions to close threads (HttpConnnectionHandlers)
    this->socketQueue->enqueue(stopCondition);
  }
}

void HttpServer::startApps() {
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->start();
  }
}

void HttpServer::stopApps() {
  // Stop web applications. Give them an opportunity to clean up
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->stop();
    this->applications[index]->waitToFinish();
  }
}

void HttpServer::createHandlers() {
  this->socketQueue = new Queue<Socket>();
  this->requestQueue = new Queue<responsePair>();
  // Create the connection handlers
  for (int index = 0; index < this->numHandlers; ++index) {
    HttpConnectionHandler* handler
      = new HttpConnectionHandler(&this->applications);
    this->handlers.push_back(handler);
    this->handlers[index]->setConsumingQueue(this->socketQueue);
    this->handlers[index]->setProducingQueue(this->requestQueue);
  }
  HandlerDispatcher* dispatcher = new HandlerDispatcher();
  this->dispatcher = dispatcher;
  this->dispatcher->setConsumingQueue(this->requestQueue);
    // Register all the applications queues and their keys
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->dispatcher->registerRedirect
      (this->applications[index]->getApplicationURI(),
      this->applications[index]->getConsumingQueue());
  }
}

// TODO(Alex): make a createPacker and a stopPacker method

void HttpServer::startHandlers() {
  // Start the connection handlers
  for (int index = 0; index < this->numHandlers; ++index) {
    this->handlers[index]->startThread();
  }
  this->dispatcher->startThread();
}

void HttpServer::stopHandlers() {
  // Destroy the connection handlers
  for (int index = 0; index < this->numHandlers; ++index) {
    this->handlers[index]->waitToFinish();
    delete this->handlers[index];
  }
  this->dispatcher->waitToFinish();
  delete this->dispatcher;
  delete this->socketQueue;
  delete this->requestQueue;
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests. When stopListing()
  // method is called -maybe by a secondary thread-, the web server -running
  // by the main thread- will stop executing the acceptAllConnections() method.
  this->stopListening();
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      return false;
    }
  }
  if (argc == 2) {
    this->port = argv[1];
  } else if (argc >= 3) {
    this->port = argv[1];
    this->numHandlers =  std::strtol(argv[2], nullptr, 10);
  }
  return true;
}

void HttpServer::handleClientConnection(Socket& client) {
  // Store sockets into a thread-safe queue, and stop in web server
  this->socketQueue->enqueue(client);
}
