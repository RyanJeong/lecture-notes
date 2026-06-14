#include <iostream>
#include <locale>
#include <string>

int main() {
  try {
    // Set the global locale to en_US.UTF-8
    // This enables proper handling of UTF-8 encoded wide characters like Korean
    // Note: On some systems, the locale name might be "en_US.utf8"
    std::locale::global(std::locale("en_US.utf8"));
    std::wcout.imbue(std::locale());
  } catch (const std::runtime_error& e) {
    std::cerr << "Locale error: " << e.what() << std::endl;
    return 1;
  }

  // using wstring = std::basic_string<wchar_t>
  std::wstring str = L"안녕하세요, 세계!";  // L"" indicates wide string literal

  // using wcout = std::basic_ostream<wchar_t>
  std::wcout << L"Korean Wide String: " << str << std::endl;
  std::wcout << L"Length: " << str.length() << std::endl;

  // using wcin = std::basic_istream<wchar_t>
  std::wcin >> str;
  std::wcout << str << std::endl;
  return 0;
}
