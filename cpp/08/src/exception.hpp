#pragma once

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void AnyException();  // can throw any exception or none
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <stdexcept>  // for std::invalid_argument, std::out_of_range

void PreDefinedExceptions() throw(std::invalid_argument, std::out_of_range);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void NoExceptionNotRecommended() throw();  // not recommended in C++11 and later
void NoExceptionRecommended() noexcept;    // recommended in C++11 and later
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
