// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <unistd.h>
#include <vector>

#include "TcpServer.hpp"
#include "HandlerDispatcher.hpp"
#include "HttpConnectionHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "responsePair.hpp"

#define DEFAULT_PORT "8080"

class HttpApp;

class HttpServer : public TcpServer {
  DISABLE_COPY(HttpServer);

 protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;
  /// Number of connection handlersc
  int numHandlers = sysconf(_SC_NPROCESSORS_ONLN);
  /// Queue of sockets to be handled by the connection handlers
  Queue<Socket>* socketQueue;
  /// Queue of HTTP requests to be handled by the web applications
  Queue<responsePair>* requestQueue;
  /// Chain of registered web applications. Each time an incoming HTTP request
  /// is received, the request is provided to each application of this chain.
  /// If an application detects the request is for it, the application will
  /// call the httpResponse.send() and the chain stops. If no web app serves
  /// the request, the not found page will be served.
  std::vector<HttpApp*> applications;
  /// Vector of connection handlers
  std::vector<HttpConnectionHandler*> handlers;
  /// Dispatcher of connection handlers
  HandlerDispatcher* dispatcher;

 private:
  ///  Singleton. Constructor
  HttpServer();
  ///  Singleton. Destructor
  ~HttpServer();

 public:
  /// Get access to the unique instance of this Singleton class.
  static HttpServer& getInstance();
  /// Registers a web application to the chain
  void chainWebApp(HttpApp* application);
  /// Start the web server for listening client connections and HTTP requests
  int run(int argc, char* argv[]);
  /// Stop the web server. The server may stop not immediately. It will stop
  /// for listening further connection requests at once, but pending HTTP
  /// requests that are enqueued will be allowed to finish
  void stop();
  /// Infinetelly listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);

 protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
  /// Start all registered applications, given them a chance to build their
  /// data structures just before starting to run
  void startApps();
  /// Stop all running applications, given them a chance to clean their data
  /// structures
  void stopApps();
  /// Create the connection handlers
  void createHandlers();
  /// Start the connection handlers
  void startHandlers();
  /// Stop the connection handlers
  void stopHandlers();
  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
  ///  Send stop conditions to each handler and stop the connection with them.
  void closeServer();
};

#endif  // HTTPSERVER_H
