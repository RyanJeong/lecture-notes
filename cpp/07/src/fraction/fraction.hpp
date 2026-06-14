#pragma once

#include <iostream>

class Fraction {
 public:
  explicit Fraction(int num, int den = 1);
  explicit Fraction(double value);
  Fraction(const Fraction& right) = default;

  // Unary operators
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  const Fraction operator+() const;
  const Fraction operator-() const;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Pre-increment and pre-decrement
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction& operator++();
  Fraction& operator--();
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Post-increment and post-decrement
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  const Fraction operator++(int);
  const Fraction operator--(int);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Assignment and compound assignment operators
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction& operator=(const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction& operator+=(const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction& operator-=(const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction& operator*=(const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction& operator/=(const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Conversion operator
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  explicit operator double() const;
  operator int() const;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Friend binary operators
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend const Fraction operator+(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend const Fraction operator-(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend const Fraction operator*(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend const Fraction operator/(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Friend comparison operators
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend bool operator==(const Fraction& left, const Fraction& right);
  friend bool operator!=(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend bool operator<(const Fraction& left, const Fraction& right);
  friend bool operator<=(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend bool operator>(const Fraction& left, const Fraction& right);
  friend bool operator>=(const Fraction& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Friend stream operators
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  friend std::istream& operator>>(std::istream& left, Fraction& right);
  friend std::ostream& operator<<(std::ostream& left, const Fraction& right);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

 private:
  int numer_;
  int denom_;

  void Normalize();
};
