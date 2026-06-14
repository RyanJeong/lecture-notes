#pragma once

#ifdef CPP_09_NOBUILD
#include <memory>
#include <string>

namespace std {
using string = basic_string<char, std::char_traits<char>, std::allocator<char>>;

// Simplified version:
// using string = basic_string<char>;
}  // namespace std

namespace std {
using string = basic_string<char>;  // Simplified version
}  // namespace std

namespace std {
using wstring = basic_string<wchar_t>;  // Simplified version
}  // namespace std

#endif  // CPP_09_NOBUILD
