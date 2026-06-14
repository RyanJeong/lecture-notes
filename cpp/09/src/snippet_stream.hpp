#pragma once

#ifdef CPP_09_NOBUILD
namespace std {
using istream = basic_istream<char>;
using ostream = basic_ostream<char>;
}  // namespace std

#endif  // CPP_09_NOBUILD
