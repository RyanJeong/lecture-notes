#include "invoice.hpp"

int main() {
  Product product1("Table", 150.00);
  Product product2("Chair", 80.00);

  Invoice invoice(1001);
  invoice.Add(1, product1);
  invoice.Add(6, product2);
  invoice.Print();
  return 0;
}
