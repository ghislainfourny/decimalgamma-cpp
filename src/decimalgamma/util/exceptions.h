/*
 * decimalgamma_exceptions.h
 *
 *  Created on: 28 Mar 2017
 *      Author: ghislain
 */

#ifndef DECIMALGAMMA_UTIL_EXCEPTIONS_H_
#define DECIMALGAMMA_UTIL_EXCEPTIONS_H_

#include <exception>
#include <sstream>

class bit_sequence_exception : public std::exception
{
  public:
    bit_sequence_exception(std::string message) : _message(message){};

    const char* what() const throw() { return _message.c_str(); }

  private:
    std::string _message;
};

class decimal_decomposition_exception : public std::exception
{
  public:
    decimal_decomposition_exception(std::string message) : _message(message){};

    const char* what() const throw() { return _message.c_str(); }

  private:
    std::string _message;
};

#endif /* DECIMALGAMMA_UTIL_EXCEPTIONS_H_ */
