#pragma once

#include <iostream>

#include "product.hpp"

class Invoice {
  int number_;
  double total_;

 public:
  explicit Invoice(int number) : number_(number), total_(0.0) {}

  void Add(int qty, const Product& prod) { total_ += qty * prod.unit_price(); }

  void Print() const {
    std::cout << "Invoice Number: " << number_ << std::endl;
    std::cout << "Invoice Total: " << total_ << std::endl;
  }
};
