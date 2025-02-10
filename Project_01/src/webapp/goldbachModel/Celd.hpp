/**
 * @file Celd.hpp
 * @author Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>
 * @brief Celd used to contain data in the GQueue
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CELDGOLDBACH
#define CELDGOLDBACH

#include <string>

#include "GQueue.hpp"

/// @brief Celd used to contain each number and its Goldbach sums
class Celd{
  friend class List;

 private:
  int64_t num;  /// Indicates the number stored in the list
  GQueue* myGQueue;  /// Pointer to the sums Gqueue
  Celd * next;  /// Pointer to next celd

 public:
  /// @brief Construct a new Celd object
  Celd() {
    this->myGQueue = new GQueue();
  }
  /// @brief Destroy the Celd object
  ~Celd() {
    delete myGQueue;
  }
  /// @brief  Returns the number stored in the celd
  /// @return int64_t Number stored in the celd
  int64_t getNum() {
    return this->num;
  }
  /// @brief  Returns the GQueue stored in the celd
  /// @return  GQueue* Pointer to the GQueue stored in the celd
  GQueue * getGQueue() {
    return this->myGQueue;
  }
  /// @brief Sets the number stored in the celd
  /// @param num  Number to be stored in the celd
  void setNum(int64_t num) {
    this->num = num;
  }
  /// @brief  overload << operator to display the celd in the web page
  /// @param out  ostream to be displayed in the web page
  /// @param celd  Celd to be displayed in the web page
  /// @return  std::ostream& ostream to be displayed in the web page
  friend inline std::ostream& operator<<(std::ostream& out, Celd& celd) {
    // Model Goldbach is overloaded, so its containers must be overloaded.
    // This metod returns an ostream with HTML sintax,
    // in order to display it in the web page
    // <p> tag indicates the begining of a new line in HTML page,
    // and </p> indicates end of line
    // <b> tag indicates bold letter format,
    // and </b> indicates end of bold letter
    if (celd.myGQueue->getCounter() == 0) {
      // if the "displayed" celd contains a number with 0 sums (1-5),
      // it displays the number followed by : NA in the web page
      std::string textLine
        = "<p> <b>" + std::to_string(celd.num) + "</b>: NA </p>";
      return out << textLine;
    } else if (celd.num >= 6) {
      // If the "displayed" celd contains a number greater than five,
      // it displays the number followed by : (quantity of sums) sums
      std::string textLine
        = "<p> <b>" + std::to_string(celd.num) + "</b>: "
        + std::to_string(celd.myGQueue->getCounter()) + " sums </p>";
      return out << textLine;
    } else {
      // If the "displayed" celd contains a negative number,
      // it displays the number followed by : (quantity of sums) sums
      // and the serie of numbers, displaying the Gqueue contained by the celd
      std::string textLine = "<p> <b>" + std::to_string(celd.num) + "</b>: "
        + std::to_string(celd.myGQueue->getCounter()) + " sums: "
        + celd.myGQueue->printQueue() + "</p>";
      return out<< textLine;
    }
    return out;
  }
};

#endif
