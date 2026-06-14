#pragma once

#if 1  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
// Basic list structure (conceptual)
template <typename T>
class list {
 private:
  struct Node {
    T data;
    Node* prev;
    Node* next;
  };
  Node* head;
  Node* tail;
  size_t size_;

 public:
  void insert(iterator pos, const T& val) {  // Only pointer modification - O(1)
    Node* newNode = new Node{val, pos.node->prev, pos.node};
    pos.node->prev->next = newNode;
    pos.node->prev = newNode;
    size_++;
  }
  iterator begin() { return iterator(head); }
};
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
