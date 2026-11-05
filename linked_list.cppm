module;

#include <cstddef>
#include <stdexcept>
#include <iostream>

export module linked_list;

export template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

export template <typename T>
class LinkedList {
 public:
  LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

  LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
    Node<T>* current = other.head_;
    while (current != nullptr) {
      push_tail(current->data);
      current = current->next;
    }
  }

  ~LinkedList() {
    clear();
  }

  LinkedList& operator=(const LinkedList& other) {
    if (this != &other) {
      clear();
      Node<T>* current = other.head_;
      while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  void clear() {
    Node<T>* current = head_;
    while (current != nullptr) {
      Node<T>* next_node = current->next;
      delete current;
      current = next_node;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  void push_tail(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    new_node->prev = tail_;
    if (tail_ != nullptr) {
      tail_->next = new_node;
    } else {
      head_ = new_node;
    }
    tail_ = new_node;
    ++size_;
  }

  void push_head(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    new_node->next = head_;
    if (head_ != nullptr) {
      head_->prev = new_node;
    } else {
      tail_ = new_node;
    }
    head_ = new_node;
    ++size_;
  }

 private:
  Node<T>* head_;
  Node<T>* tail_;
  std::size_t size_;
};