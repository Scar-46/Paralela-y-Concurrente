// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GoldbachWebApp_HPP
#define GoldbachWebApp_HPP

#include <unistd.h>
#include <vector>
#include <string>

#include "HttpApp.hpp"
#include "Assembler.hpp"
#include "Gcalculator.hpp"
#include "ResponseProducer.hpp"
#include "Packer.hpp"

///  @brief A web application that calculates goldbach sums
class GoldbachWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 public:
  /// Constructor
  GoldbachWebApp();
  /// Destructor
  ~GoldbachWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;
  /// Called by the web server when the web server is started
  int run() override;
  /// Changes the consumeForever in order to set the stop conditions
  void consumeForever() override;
  /// Called by the web server when the web server is started
  /// @param request pair of request and response consume by the application
  void consume(responsePair request) override;
  /// Gives the URI of the application
  std::string getApplicationURI() const override;

 protected:
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Handle a HTTP request that starts with "/gold"
  /// @param httpRequest the HTTP request use to get the numbers
  /// @param httpResponse the HTTP response use to send the answer
  /// @return true if the Goldbach was handled, false if it must be
  /// handled by another application
  bool serveGoldbachSerie(HttpRequest* httpRequest, HttpResponse* httpResponse);

  /// Queue of celds to be handled by the solvers
  Queue<NumData<Celd*>*>* solversQueue;
  // Queue of elements to be handled by the dispatcher
  Queue<std::vector<NumData<Celd*>*>*> * responseProducerQueue;
  /// Queue of elements to be handled by the packer
  Queue<NumData<Celd*>*>* packerQueue;
  /// Number of solvers
  const int solversCount = sysconf(_SC_NPROCESSORS_ONLN);
  /// Vector of solvers
  std::vector<Gcalculator*> solvers;
  /// packer
  Packer<Celd*> * packer;
  /// Response producer
  ResponseProducer<Celd*> * responseProducer;
  /// Boolean to stop the solvers
  bool stopSolvers;
  /// String to store the URI use to access the application
  const std::string applicationURI = "/gold";
};

#endif  // GoldbachWebApp_HPP
