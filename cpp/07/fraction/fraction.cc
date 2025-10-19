#include "fraction.hpp"

#include <cmath>
#include <iostream>

// Helper function to compute GCD using Euclidean algorithm
static int ComputeGcd(int a, int b) {
  a = (a < 0) ? -a : a;
  b = (b < 0) ? -b : b;
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Private helper function to normalize fraction
void Fraction::Normalize() {
  if (denom_ == 0) {
    throw std::invalid_argument("Denominator cannot be zero");
  }

  // Ensure denominator is positive
  if (denom_ < 0) {
    numer_ = -numer_;
    denom_ = -denom_;
  }

  // Reduce to lowest terms
  int gcd_value = ComputeGcd(numer_, denom_);
  numer_ /= gcd_value;
  denom_ /= gcd_value;
}

// Constructors
Fraction::Fraction(int num, int den) : numer_(num), denom_(den) { Normalize(); }

Fraction::Fraction(double value) : denom_(1) {
  if (value == 0.0) {
    numer_ = 0;
    return;
  }

  double temp = value;
  while ((temp - std::floor(temp)) > 1e-9) {
    temp *= 10.0;
    denom_ *= 10;
  }
  numer_ = static_cast<int>(std::round(temp));
  Normalize();
}

// Unary operators
const Fraction Fraction::operator+() const { return Fraction(numer_, denom_); }

const Fraction Fraction::operator-() const { return Fraction(-numer_, denom_); }

// Pre-increment operator
Fraction& Fraction::operator++() {
  numer_ = numer_ + denom_;
  Normalize();
  return *this;
}

// Pre-decrement operator
Fraction& Fraction::operator--() {
  numer_ = numer_ - denom_;
  Normalize();
  return *this;
}

// Post-increment operator
const Fraction Fraction::operator++(int) {
  Fraction temp(numer_, denom_);
  ++(*this);
  return temp;
}

// Post-decrement operator
const Fraction Fraction::operator--(int) {
  Fraction temp(numer_, denom_);
  --(*this);
  return temp;
}

// Assignment operator
Fraction& Fraction::operator=(const Fraction& right) {
  if (*this != right) {
    numer_ = right.numer_;
    denom_ = right.denom_;
  }
  return *this;
}

// Compound assignment operators
Fraction& Fraction::operator+=(const Fraction& right) {
  numer_ = numer_ * right.denom_ + denom_ * right.numer_;
  denom_ = denom_ * right.denom_;
  Normalize();
  return *this;
}

Fraction& Fraction::operator-=(const Fraction& right) {
  numer_ = numer_ * right.denom_ - denom_ * right.numer_;
  denom_ = denom_ * right.denom_;
  Normalize();
  return *this;
}

Fraction& Fraction::operator*=(const Fraction& right) {
  numer_ = numer_ * right.numer_;
  denom_ = denom_ * right.denom_;
  Normalize();
  return *this;
}

Fraction& Fraction::operator/=(const Fraction& right) {
  if (right.numer_ == 0) throw std::invalid_argument("Division by zero");

  numer_ = numer_ * right.denom_;
  denom_ = denom_ * right.numer_;
  Normalize();
  return *this;
}

// Conversion operator
Fraction::operator double() const {
  return static_cast<double>(numer_) / denom_;
}

// Binary arithmetic operators (friend functions)
const Fraction operator+(const Fraction& left, const Fraction& right) {
  int new_numer = left.numer_ * right.denom_ + right.numer_ * left.denom_;
  int new_denom = left.denom_ * right.denom_;
  return Fraction(new_numer, new_denom);
}

const Fraction operator-(const Fraction& left, const Fraction& right) {
  int new_numer = left.numer_ * right.denom_ - right.numer_ * left.denom_;
  int new_denom = left.denom_ * right.denom_;
  return Fraction(new_numer, new_denom);
}

const Fraction operator*(const Fraction& left, const Fraction& right) {
  int new_numer = left.numer_ * right.numer_;
  int new_denom = left.denom_ * right.denom_;
  return Fraction(new_numer, new_denom);
}

const Fraction operator/(const Fraction& left, const Fraction& right) {
  if (right.numer_ == 0) throw std::invalid_argument("Division by zero");

  int new_numer = left.numer_ * right.denom_;
  int new_denom = left.denom_ * right.numer_;
  return Fraction(new_numer, new_denom);
}

// Comparison operators (friend functions)
bool operator==(const Fraction& left, const Fraction& right) {
  return (left.numer_ * right.denom_ == right.numer_ * left.denom_);
}

bool operator!=(const Fraction& left, const Fraction& right) {
  return (left.numer_ * right.denom_ != right.numer_ * left.denom_);
}

bool operator<(const Fraction& left, const Fraction& right) {
  return (left.numer_ * right.denom_ < right.numer_ * left.denom_);
}

bool operator<=(const Fraction& left, const Fraction& right) {
  return (left.numer_ * right.denom_ <= right.numer_ * left.denom_);
}

bool operator>(const Fraction& left, const Fraction& right) {
  return (left.numer_ * right.denom_ > right.numer_ * left.denom_);
}

bool operator>=(const Fraction& left, const Fraction& right) {
  return (left.numer_ * right.denom_ >= right.numer_ * left.denom_);
}

// Stream operators (friend functions)
std::istream& operator>>(std::istream& left, Fraction& right) {
  std::cout << "Enter the value of numerator: ";
  left >> right.numer_;
  std::cout << "Enter the value of denominator: ";
  left >> right.denom_;
  right.Normalize();
  return left;
}

std::ostream& operator<<(std::ostream& left, const Fraction& right) {
  left << right.numer_ << "/" << right.denom_;
  return left;
}
