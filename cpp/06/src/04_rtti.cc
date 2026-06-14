#include <iostream>
#include <typeinfo>

class Animal {
 public:
  // Virtual destructor enables RTTI and proper polymorphic behavior.
  // Derived class destructors automatically become virtual too.
  virtual ~Animal() = default;
};

class Horse : public Animal {
  // The destructor is implicitly virtual because Animal's is virtual
};

int main() {
  Animal* p_animal = new Animal();
  Animal* p_horse = new Horse();

  std::cout << "'p_animal' and 'p_horse' are of the same type: "
            << std::boolalpha << (typeid(*p_animal) == typeid(*p_horse))
            << std::endl;

  std::cout << "'p_animal' and 'p_horse' are of different types: "
            << std::boolalpha << (typeid(*p_animal) != typeid(*p_horse))
            << std::endl;

  std::cout << "Type name of p_animal: " << typeid(*p_animal).name()
            << std::endl;

  std::cout << "'p_horse' is the derived type of 'p_animal': " << std::boolalpha
            << (typeid(*p_horse).before(typeid(*p_animal))) << std::endl;

  delete p_animal;
  delete p_horse;
  return 0;
}
