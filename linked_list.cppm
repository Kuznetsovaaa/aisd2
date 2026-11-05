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