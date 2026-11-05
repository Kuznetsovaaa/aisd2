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

  void pop_heads() {
    if (head_ == nullptr) {
      throw std::out_of_range("pop_heads: list is empty");
    }
    Node<T>* old_head = head_;
    head_ = head_->next;
    if (head_ != nullptr) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete old_head;
    --size_;
  }

  void pop_tails() {
    if (tail_ == nullptr) {
      throw std::out_of_range("pop_tails: list is empty");
    }
    Node<T>* old_tail = tail_;
    tail_ = tail_->prev;
    if (tail_ != nullptr) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete old_tail;
    --size_;
  }

  void delete_node(const T& value) {
    Node<T>* current = head_;
    while (current != nullptr) {
      Node<T>* next_node = current->next;
      if (current->data == value) {
        unlink_node(current);
        delete current;
        --size_;
      }
      current = next_node;
    }
  }

  std::size_t get_size() const {
    return size_;
  }

 private:
  struct NodeWrapper {}; // Заглушка (не обращай внимания, просто для красоты не нужна, я убрал)
  
  void unlink_node(Node<T>* node) {
    if (node->prev != nullptr) {
      node->prev->next = node->next;
    } else {
      head_ = node->next;
    }
    if (node->next != nullptr) {
      node->next->prev = node->prev;
    } else {
      tail_ = node->prev;
    }
  }

  Node<T>* head_;
  Node<T>* tail_;
  std::size_t size_;
};