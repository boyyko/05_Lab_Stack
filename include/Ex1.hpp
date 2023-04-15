// Copyright 2021 RomanovVladislav

#ifndef INCLUDE_EX1_HPP_
#define INCLUDE_EX1_HPP_

#include <iostream>

template <typename T>
struct node
{
  T data;
  node* element_next;
};

template <typename T>
class Stack
{
 public:
  Stack() : element_top(nullptr) {}
  Stack(const Stack& stack) = delete;
  Stack(Stack&& stack) = default;
  Stack &operator=(const Stack& stack) = delete;
  Stack &operator=(Stack && stack)  = default;

  void push(T&& value)
  {
    node<T>* new_node = new node<T>;
    new_node->data = value;
    new_node->element_next = element_top;
    element_top = new_node;
  }

  void push(const T& value)
  {
    node<T>* new_node = new node<T>;
    new_node->data = value;
    new_node->element_next = element_top;
    element_top = new_node;
  }

  void pop()
  {
    if (empty()) throw std::runtime_error("Stack is empty!");
    node<T> *delete_node = element_top;
    element_top = delete_node->element_next;
    delete delete_node;
  }

  const T& head() const
  {
    if (empty()) throw std::runtime_error("Stack is empty!");
    return element_top->data;
  }

  ~Stack()
  {
    while (element_top)
    {
      node<T> *delete_node = element_top;
      element_top = delete_node->element_next;
      delete delete_node;
    }
  }

  bool empty() const
  {
    return element_top == nullptr;
  }
 private:
  node<T> *element_top;
};

#endif  // INCLUDE_EX1_HPP_
