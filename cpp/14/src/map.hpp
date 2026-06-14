#pragma once

#if 1  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
template <typename K, typename V>
class map {
 private:
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
    int height;  // for balancing
  };
  Node* root;

 public:
  V& operator[](const K& key) {
    // 1. If key exists, return the corresponding value
    // 2. If key does not exist, create it (value is default-initialized)
    Node* n = find_or_insert(root, key);
    return n->value;
  }
};
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
