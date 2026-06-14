#include <iostream>
#include <string>
#include <unordered_map>  // for std::unordered_map

// `Student` can be a struct even though it has an operator== defined.
// "Constructors, destructors, and helper methods may be present; however, these
// methods must not require or enforce any invariants." - Google C++ Style Guide
struct Student {
  int student_id;
  std::string name;

  // Helper method for equality comparison
  // 1. To use std::unordered_map with custom types, we need to define equality
  // operator
  bool operator==(const Student& other) const {
    return student_id == other.student_id && name == other.name;
  }
};

// Custom hash function for Student
struct StudentHash {
  // Helper method for hashing a Student object
  // 2. To use std::unordered_map with custom types, we need to define a hash
  // function
  size_t operator()(const Student& s) const;
};

size_t StudentHash::operator()(const Student& s) const {
  // Method 1: Simple hash using `student_id`
  // Knuth's multiplicative hash constant using approximate prime number of
  // 2^32 / golden ratio
  size_t hash_id = s.student_id * 2654435761U;  // 2^32 / 1.6180339887...

  // Method 2: DJB2 string hash (hash * 33 + c)
  size_t hash_name = 5381;  // DJB2 offset basis, prime number
  for (char c : s.name)
    hash_name = ((hash_name << 5) + hash_name) + c;  // hash * 33 + c

  // Combine both hashes using XOR with bit shifting to avoid collisions when
  // the `hash_id` and `hash_name` are the same
  return hash_id ^ (hash_name << 1);
}

int main() {
  // unordered_map with custom hash function
  // Template: unordered_map<Key, Value, HashFunction, EqualityComparator>
  std::unordered_map<Student, std::string, StudentHash> grades;

  // Insert - average O(1)
  grades[{101, "Alice"}] = "A";
  grades[{102, "Bob"}] = "B";
  grades[{103, "Charlie"}] = "A+";

  std::cout << "Student Grades (Hash-based, unsorted):" << std::endl;
  std::cout << "=========================================" << std::endl;

  // Fast lookup - average O(1)
  Student query{102, "Bob"};
  if (grades.find(query) != grades.end()) {
    std::cout << "Found: " << query.name << " - Grade: " << grades[query]
              << std::endl;
  }

  // Iteration order is undefined (hash-based)
  std::cout << "\nAll records (order undefined):" << std::endl;
  for (const auto& p : grades) {
    std::cout << "ID: " << p.first.student_id << " (" << p.first.name
              << ") = " << p.second << std::endl;
  }
  return 0;
}