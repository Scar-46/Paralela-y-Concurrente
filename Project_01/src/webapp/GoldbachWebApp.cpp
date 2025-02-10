// Copyright 2023 Oscar Fernández Jiménez <oscar.fernandezjimenez@ucr.ac.cr>.
// co-author: Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>
// Universidad de Costa Rica. CC BY 4.0]

#include <algorithm>
#include <cassert>
#include <regex>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

GoldbachWebApp::GoldbachWebApp() {
}

GoldbachWebApp::~GoldbachWebApp() {
}

int GoldbachWebApp::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachWebApp::consume(responsePair request) {
  this->serveGoldbachSerie(request.request, request.response);
}

void GoldbachWebApp::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    const responsePair& data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if ( data.stopCondition == true ) {
      NumData<Celd*>* newData = new NumData<Celd*>;
      for (int i = 0; i < solversCount; ++i) {
        this->solversQueue->enqueue(newData);
      }
      break;
    }
    // Process this data
    this->consume(data);
  }
}

void GoldbachWebApp::start() {
  // start goldbach solvers
  this->solversQueue = new Queue<NumData<Celd*>*>();
  this->packerQueue = new Queue<NumData<Celd*>*>();
  this->responseProducerQueue = new Queue<std::vector<NumData<Celd*>*>*>();
  // Create the solvers
  for (int i = 0; i < this->solversCount; i++) {
    Gcalculator* solver = new Gcalculator();
    solver->setConsumingQueue(this->solversQueue);
    solver->setProducingQueue(this->packerQueue);
    this->solvers.push_back(solver);
    this->solvers[i]->startThread();
  }
  this->packer = new Packer<Celd*>();
  packer->setConsumingQueue(this->packerQueue);
  packer->setProducingQueue(this->responseProducerQueue);
  packer->startThread();
  this->responseProducer = new ResponseProducer<Celd*>();
  responseProducer->setConsumingQueue(this->responseProducerQueue);
  responseProducer->startThread();
}

void GoldbachWebApp::stop() {
  // stop goldbach solvers
  for (int i = 0; i < this->solversCount; i++) {
    this->solvers[i]->waitToFinish();
    delete this->solvers[i];
  }
  responseProducer->waitToFinish();
  packer->waitToFinish();
  delete responseProducer;
  delete packer;
  delete this->solversQueue;
  delete this->packerQueue;
  delete this->responseProducerQueue;
}

std::string GoldbachWebApp::getApplicationURI() const {
  return this->applicationURI;
}

bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }
  // Unrecognized request
  return false;
}

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach serie";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/gold\">\n"
    << "    <label for=\"numbers\">"
    << "  Enter numbers separated by a comma:</label>\n"
    << "    <input type=\"text\" id=\"numbers\" name=\"numbers\" required/>\n"
    << "    <button type=\"submit\">Next</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  httpResponse.send();
  delete &httpRequest;
  delete &httpResponse;
  return true;
}

bool GoldbachWebApp::serveGoldbachSerie(HttpRequest* httpRequest
  , HttpResponse* httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse->setHeader("Server", "AttoServer v1.0");
  httpResponse->setHeader("Content-type", "text/html; charset=ascii");

  // If a number was asked in the form "/fact/1223"
  // or "/fact?number=1223 "
  std::smatch matches;
  std::regex inQuery("^(-?\\d+(?:%2C\\+*-?\\d+)*)$");
  std::string URICopy = httpRequest->getURI();
  if (std::regex_search(URICopy.erase(0, 14), matches
    , inQuery /*, std::regex_constants::match_continuous*/)) {
    std::string numbers = matches[1];
    numbers = std::regex_replace(numbers, std::regex("%2C\\+*"), ",");
    std::string title = "Goldbach Series for: " + numbers;
    httpResponse->body()
    << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <div>";
    delete httpRequest;
    // From here we have to send the numbers to the solvers
    std::stringstream input_stringstream(numbers);
    std::string aux;
    std::vector<Celd*> celdVector;
    int64_t requestSize = 0;
    while (std::getline(input_stringstream, aux, ',')) {
      const char* number = aux.c_str();
      int64_t new_number = atoi(number);
      errno = 0;
      if ( errno != 0 ) {
        // Input number is not valid so it is not sended to the solvers
      }
      Celd * newCeld = new Celd();
      newCeld->setNum(new_number);
      celdVector.push_back(newCeld);
      ++requestSize;
    }
    for (int64_t i = 0; i < requestSize; i++) {
      NumData<Celd*> * newData = new NumData<Celd*>;
      newData->setRequestSize(requestSize);
      newData->setStructData(celdVector[i]);
      newData->setResponseAdr(httpResponse);
      newData->setRequestPosition(i);
      solversQueue->enqueue(newData);
    }
  } else {
    // Build the body for an invalid request
    std::string title = "Invalid request";
    httpResponse->body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1 class=\"err\">" << title << "</h1>\n"
      << "  <p>Invalid request for a Goldbach Serie</p>\n"
      << "  <p>Input must be in format: Number,Number,...</p>"
      << "  <p>No other characters,"
      << "   like letters and blank spaces are allowed</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
      httpResponse->send();
      delete httpRequest;
      delete httpResponse;
  }
  return true;
}
