// Copyright 2023 OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr

#include <vector>
#include <string>

#include "GoldbachWebApp.hpp"
#include "HandlerDispatcher.hpp"
#include "HttpApp.hpp"
#include "HttpConnectionHandler.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "responsePair.hpp"

HttpConnectionHandler::HttpConnectionHandler(std::vector<HttpApp*>*
  applications)
  : applications(applications) {
}

int HttpConnectionHandler::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  // If the forever loop finished, no more messages will arrive
  return EXIT_SUCCESS;
}

void HttpConnectionHandler::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    Socket data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if ( data == this->stopCondition ) {
      responsePair response;
      this->produce(response);
      break;
    }
    // Process this data
    this->consume(data);
  }
}

void HttpConnectionHandler::consume(Socket data) {
  // While the same client asks for HTTP requests in the same connection
  Log::append(Log::INFO, "webserver"
    , "New request at thread: " + std::to_string(pthread_self()));
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest * httpRequest = new HttpRequest(data);
    // If the request is not valid or an error happened
    if (!httpRequest->parse()) {
      delete httpRequest;
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse * httpResponse = new HttpResponse(data);
    // Give subclass a chance to respond the HTTP request
    std::string version = httpRequest->getHttpVersion();
    const bool handled = this->handleHttpRequest(*httpRequest, *httpResponse);
    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || version == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      delete httpRequest;
      delete httpResponse;
      data.close();
    }
  }
}

bool HttpConnectionHandler::handleHttpRequest(HttpRequest& httpRequest,
  HttpResponse& httpResponse) {
// Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
  std::string("connection established with client ") + address.getIP()
    + " port " + std::to_string(address.getPort()));

// Print HTTP request
  Log::append(Log::INFO, "request", httpRequest.getMethod()
    + ' ' + httpRequest.getURI()
    + ' ' + httpRequest.getHttpVersion());

return this->route(httpRequest, httpResponse);
}

bool HttpConnectionHandler::route(HttpRequest& httpRequest
    , HttpResponse& httpResponse) {
  const responsePair data = {&httpRequest, &httpResponse};
  // If the request is for the home page
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    HttpApp* app = this->applications->at(0);
    return app->handleHttpRequest(httpRequest, httpResponse);
    // If the request is for a specific application
  } else if (httpRequest.getMethod() == "GET"
      && httpRequest.getURI() != "/favicon.ico") {
    this->produce(data);
  } else {
    return false;
  }
  return true;
}

