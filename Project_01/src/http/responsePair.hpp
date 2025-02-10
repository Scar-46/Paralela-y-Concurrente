///  @copyright 2023 CC-BY 4.0
///  @author Oscar Fernández Jiménez <OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr>

#ifndef RESPONSEPAIR_HPP
#define RESPONSEPAIR_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

/// @brief Class to store a pair of request and response
struct responsePair {
 public:
  HttpRequest * request;
  HttpResponse * response;
  bool stopCondition = false;

 public:
  /// @brief Construct a new response Pair object
  responsePair()
    : request(nullptr)
    , response(nullptr)
    , stopCondition(true) {
  }
  /// @brief Destroy the response Pair object
  ~responsePair() {
    // These objects are not owned by this class
    // and therefore should not be deleted here
  }

  /// @brief Construct a new response Pair object
  /// @param request pointer to the request
  /// @param response  pointer to the response
  responsePair(HttpRequest * request, HttpResponse * response)
      : request(request)
      , response(response) {
  }

  /// @brief operator == to compare two responsePair
  /// @param other responsePair to compare
  /// @return true if both are equal, false otherwise
  inline bool operator==(const responsePair& other) const {
    return this->request == other.request
      && this->response == other.response;
  }
};

#endif  // RESPONSEPAIR_HPP
