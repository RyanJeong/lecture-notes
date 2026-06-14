#include "person.hpp"

int main() {
  // Here's the instantiation part. Notice that the lifetime of the aggregatee
  // is INDEPENDENT of the lifetime of the aggregator.
  Date date1(5, 6, 1980);
  Person person1(123456789L, date1);
  Date date2(4, 23, 1978);
  Person person2(987654321L, date2);

  person1.Print();
  person2.Print();
  return 0;
}
