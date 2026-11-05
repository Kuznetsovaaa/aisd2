module;

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <random>

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

  // Конструктор со случайными значениями (size - кол-во элементов, min/max - диапазон)
  LinkedList(std::size_t size, int min_val, int max_val) : head_(nullptr), tail_(nullptr), size_(0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_val, max_val);
    for (std::size_t i = 0; i < size; ++i) {
      push_tail(dist(gen));
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

  // Перегрузка: добавление другого списка в конец
  void push_tail(const LinkedList& other) {
    Node<T>* current = other.head_;
    while (current != nullptr) {
      push_tail(current->data);
      current = current->next;
    }
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

  // Перегрузка: добавление другого списка в начало
  void push_head(const LinkedList& other) {
    Node<T>* current = other.tail_;
    while (current != nullptr) {
      push_head(current->data);
      current = current->prev;
    }
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

  // Чтение по индексу (возвращает копию)
  T operator[](std::size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head_;
    for (std::size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

  // Запись по индексу (возвращает ссылку)
  T& operator[](std::size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head_;
    for (std::size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

  std::size_t get_size() const {
    return size_;
  }

 private:
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

// Перегрузка вывода в консоль
export template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
  std::size_t count = list.get_size();
  for (std::size_t i = 0; i < count; ++i) {
    os << list[i];
    if (i + 1 < count) {
      os << " ";
    }
  }
  return os;
}