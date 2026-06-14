#include <algorithm>  // for std::sort
#include <iostream>
#include <string>
#include <vector>  // for std::vector

struct Person {
  std::string name;
  int age;
};

int main() {
  std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

  std::sort(people.begin(), people.end(),
            [](const Person& a, const Person& b) { return a.age < b.age; });

  for (const auto& person : people)
    std::cout << person.name << " (" << person.age << ")" << std::endl;
  return 0;
}
