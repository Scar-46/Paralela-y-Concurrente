/**
 * @file NumData.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora@ucr.ac.cr>
 * @brief Struct to hold information about a goldbach sum package
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef NUMDATAG
#define NUMDATAG
#include "HttpResponse.hpp"

template <typename typeStruct>
/// @brief  Struct to hold information about a goldbach sum package
/// @tparam typeStruct  Type of struct to be used
class NumData {
 private:
  /// Data used by the WebApp to make a response
  typeStruct data;
  /// Address of response, used as an ID of this specific struct
  HttpResponse* responseAdr;
  /// Amount of numbers introduced by the user in a sigle request
  int64_t requestSize;
  /// Position of the number in the request
  int64_t requestPosition;

 public:
  /// @brief Construct a new Num Data object
  NumData()
  : responseAdr(nullptr)
  , requestSize(0) {
  }
  /// @brief Destroy the Num Data object
  ~NumData() {
  }
  /// @brief  Get the Struct Data object
  /// @return  typeStruct Struct with the data
  typeStruct getStructData() {
    return this->data;
  }
  /// @brief  Get the Response Adr object
  /// @return  HttpResponse* Address of the response
  HttpResponse* getResponseAdr() {
    return this->responseAdr;
  }
  /// @brief  Get the Request Size object
  int getRequestSize() {
    return this->requestSize;
  }
  /// @brief  Get the Request Position object
  int64_t getRequestPosition() {
    return this->requestPosition;
  }
  /// @brief  Set the Struct Data object
  void setStructData(typeStruct structure) {
    this->data = structure;
  }
  /// @brief  Set the Response Adr object
  /// @param response  Address of the response
  void setResponseAdr(HttpResponse* response) {
    this->responseAdr = response;
  }
  /// @brief  Set the Request Size object
  void setRequestSize(int size) {
    this->requestSize = size;
  }
  /// @brief  Set the Request Position object
  void setRequestPosition(int64_t position) {
    this->requestPosition = position;
  }
  /// @brief  Operator == overload
  /// @param struct2  Struct to compare
  /// @return  true if the structs are equal, false otherwise
  bool operator == (const NumData<typeStruct> struct2) const{
    return this->data == struct2.data;
  }
};
#endif
