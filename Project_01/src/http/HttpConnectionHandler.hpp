///  @copyright 2023 CC-BY 4.0
///  @author Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> co-created by
///  @author Oscar Fernández Jiménez <OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr>

#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <vector>
#include <utility>

#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "Socket.hpp"

class HttpApp;

/**
 * @brief A HttpConnectionHandler class example
 */
class HttpConnectionHandler : public Assembler<Socket, responsePair> {
  DISABLE_COPY(HttpConnectionHandler);

 protected:
  /// Vector with all the posible web applications
  std::vector<HttpApp*>* applications;

 public:
  /// Constructor
  /// @param applications vector with all the posible web applications
  explicit HttpConnectionHandler(std::vector<HttpApp*>* applications);
  /// Consume the messages in its own execution thread
  int run() override;
  /// Consume the messages in the current thread
  void consumeForever() override;
  /// Override this method to process any data extracted from the queue
  /// @param data the data to be processed
  void consume(Socket data) override;
  /// Called each time an HTTP request is received. Web server should analyze
  /// the request object and assemble a response with the response object.
  /// Finally send the response calling the httpResponse.send() method.
  /// @return true on success and the server will continue handling further
  /// HTTP requests, or false if server should stop accepting requests from
  /// this client (e.g: HTTP/1.0)
  virtual bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse);
  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // CONSUMERTEST_HPP
