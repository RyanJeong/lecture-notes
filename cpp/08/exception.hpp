#pragma once

void AnyException();  // can throw any exception or none

#include <stdexcept>  // for std::invalid_argument, std::out_of_range

void PreDefinedExceptions() throw(std::invalid_argument, std::out_of_range);

void NoExceptionNotRecommended() throw();  // not recommended in C++11 and later
void NoExceptionRecommended() noexcept;    // recommended in C++11 and later
