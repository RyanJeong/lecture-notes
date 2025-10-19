#pragma once

#include <iostream>

class Fraction {
 public:
  explicit Fraction(int num, int den = 1);
  explicit Fraction(double value);

  // Unary operators
  const Fraction operator+() const;
  const Fraction operator-() const;

  // Pre-increment and pre-decrement
  Fraction& operator++();
  Fraction& operator--();

  // Post-increment and post-decrement
  const Fraction operator++(int);
  const Fraction operator--(int);

  // Assignment and compound assignment operators
  Fraction& operator=(const Fraction& right);
  Fraction& operator+=(const Fraction& right);
  Fraction& operator-=(const Fraction& right);
  Fraction& operator*=(const Fraction& right);
  Fraction& operator/=(const Fraction& right);

  // Conversion operator
  explicit operator double() const;
  operator int() const;

  // Friend binary operators
  friend const Fraction operator+(const Fraction& left, const Fraction& right);
  friend const Fraction operator-(const Fraction& left, const Fraction& right);
  friend const Fraction operator*(const Fraction& left, const Fraction& right);
  friend const Fraction operator/(const Fraction& left, const Fraction& right);

  // Friend comparison operators
  friend bool operator==(const Fraction& left, const Fraction& right);
  friend bool operator!=(const Fraction& left, const Fraction& right);
  friend bool operator<(const Fraction& left, const Fraction& right);
  friend bool operator<=(const Fraction& left, const Fraction& right);
  friend bool operator>(const Fraction& left, const Fraction& right);
  friend bool operator>=(const Fraction& left, const Fraction& right);

  // Friend stream operators
  friend std::istream& operator>>(std::istream& left, Fraction& right);
  friend std::ostream& operator<<(std::ostream& left, const Fraction& right);

 private:
  int numer_;
  int denom_;

  void Normalize();
};
