///  @copyright 2023 CC-BY 4.0
///  @author Oscar Fernández Jiménez <OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr>

#ifndef HandlerDispatcher_HPP
#define HandlerDispatcher_HPP

#include <vector>
#include <string>

#include "Dispatcher.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "Socket.hpp"
#include "responsePair.hpp"

class HttpApp;

/**
 * @brief A dispatcher that dispatches responsePairs to the corresponding HttpApp
 */
class HandlerDispatcher : public Dispatcher<std::string, responsePair> {
  DISABLE_COPY(HandlerDispatcher);

 public:
  /// @brief Constructor
  HandlerDispatcher();
  /// @brief Destructor
  ~HandlerDispatcher();
  /// @brief Override this method to start consuming and processing the messages
  /// @return  EXIT_SUCCESS if the loop finished correctly, EXIT_FAILURE
  /// otherwise
  int run() override;
  /// @brief Override this method to process any data extracted from the queue
  void consumeForever() override;
  /// @brief Override this method to process any data extracted from the queue
  /// @param data  Data to be processed
  /// @return  key  Key to identify the application that will process the data
  std::string extractKey(const responsePair& data) const override;
};

#endif  // CONSUMERTEST_HPP
