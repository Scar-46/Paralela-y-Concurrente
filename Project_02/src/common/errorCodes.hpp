/**
 * @file errorCodes.hpp
 * @author Alexander Sánchez Zamora <alexander.sanchezzamora>
 * @brief Enum to manipulate binary and plain text files errors
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ERROR_CODES_HPP
#define ERROR_CODES_HPP

enum errorCodes : int{
  E_CANT_INIT_MPI = 10,
  E_WRONG_ARG_COUNT,
  E_CANT_OPEN_IN_FILE,
  E_CANT_OPEN_REP_FILE,
  E_CANT_SEND_MPI,
  E_CANT_READ_BIN,
  E_CANT_WRITE_BIN
};

#endif
