#pragma once

#include <string>

class Product {
  std::string name_;
  double unit_price_;

 public:
  Product(const std::string& name, double unit_price)
      : name_(name), unit_price_(unit_price) {}

  double unit_price() const { return unit_price_; }
};
