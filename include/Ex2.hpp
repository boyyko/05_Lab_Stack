// Copyright 2021 RomanovVladislav

#ifndef INCLUDE_EX2_HPP_
#define INCLUDE_EX2_HPP_

#include <utility>
#include <iostream>
#include "Ex1.hpp"

template <typename T>

class UncopyableStack
{
 public:
  UncopyableStack() : element_top(nullptr) {}
  UncopyableStack(const UncopyableStack& UncopyableStack) = delete;
  UncopyableStack(UncopyableStack&& UncopyableStack) = default;
  UncopyableStack &operator=(const UncopyableStack& UncopyableStack) = delete;
  UncopyableStack &operator=(UncopyableStack && UncopyableStack)  = default;

  template <typename... Args>
  void push_emplace(Args&&... value)
  {
    element_top = new node<T>{{std::forward<Args>(value)...}, element_top};
  }

  void push(T&& value)
  {
    element_top = new node<T> {std::forward<T>(value), element_top};
  }

  const T& head() const
  {
    if (!element_top) throw std::runtime_error("Stack is empty!");
    return element_top->data;
  }

  T pop()
  {
    if (!element_top) throw std::runtime_error("Stack is empty!");
    node<T> *delete_node = element_top;
    T data = std::move(element_top->data);
    element_top = delete_node->element_next;
    delete delete_node;
    return data;
  }

  ~UncopyableStack()
  {
    while (element_top)
    {
      node<T> *delete_node = element_top;
      element_top = delete_node->element_next;
      delete delete_node;
    }
  }

 private:
  node<T> *element_top;
};

#endif  // INCLUDE_EX2_HPP_
