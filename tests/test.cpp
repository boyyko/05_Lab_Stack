// Copyright 2021 RomanovVladislav

#include <gtest/gtest.h>
#include <string>
#include "Ex1.hpp"
#include "Ex2.hpp"

TEST(Stack, push_lvalue)
{
  Stack<unsigned> buffer;
  EXPECT_THROW(buffer.head(), std::runtime_error);
  unsigned value_1 = 10;
  unsigned value_2 = 20;
  unsigned value_3 = 30;
  buffer.push(value_1);
  buffer.push(value_2);
  buffer.push(value_3);
  EXPECT_EQ(buffer.head(),value_3);
}

TEST(Stack, push_rvalue)
{
  Stack<unsigned> buffer;
  EXPECT_THROW(buffer.head(), std::runtime_error);
  unsigned value_1 = 10;
  buffer.push(10);
  buffer.push(20);
  EXPECT_EQ(buffer.head(),20);
  buffer.push(std::move(value_1));
  EXPECT_EQ(buffer.head(),10);
}

TEST(Stack, test_pop)
{
  Stack<unsigned> buffer;
  EXPECT_THROW(buffer.pop(), std::runtime_error);
  unsigned value_1 = 10;
  unsigned value_2 = 20;
  unsigned value_3 = 30;
  buffer.push(value_1);
  buffer.push(value_2);
  buffer.push(value_3);
  buffer.pop();
  EXPECT_EQ(buffer.head(),value_2);
  buffer.pop();
  EXPECT_EQ(buffer.head(),value_1);
  buffer.pop();
  EXPECT_THROW(buffer.head(),std::runtime_error);
}

TEST(Stack, test_head)
{
  Stack<unsigned> buffer;
  EXPECT_THROW(buffer.head(), std::runtime_error);
  buffer.push(10);
  EXPECT_EQ(buffer.head(), 10);
  buffer.push(20);
  EXPECT_EQ(buffer.head(), 20);
  buffer.push(30);
  EXPECT_EQ(buffer.head(), 30);
  buffer.pop();
  EXPECT_EQ(buffer.head(), 20);
}

template <typename T>
struct big_data
{
  T value_1;
  T value_2;
  T value_3;
};

TEST(Stack, push_rvalue_string)
{
  big_data<std::string> buffer_1;
  buffer_1.value_1 = "dog";
  buffer_1.value_2 = "cat";
  buffer_1.value_3 = "bird";
  Stack<big_data<std::string>> buffer_2;
  buffer_2.push(std::move(buffer_1));
  EXPECT_EQ(buffer_2.head().value_1, buffer_1.value_1);
  EXPECT_EQ(buffer_2.head().value_2, buffer_1.value_2);
  EXPECT_EQ(buffer_2.head().value_3, buffer_1.value_3);
}

TEST(Stack, test_move)
{
  EXPECT_EQ(std::is_move_constructible<Stack<unsigned>>::value, true);
  EXPECT_EQ(std::is_move_assignable<Stack<unsigned>>::value, true);
  EXPECT_TRUE(std::is_move_constructible
                  <Stack<big_data<std::string>>>::value);
  EXPECT_TRUE(std::is_move_assignable
                  <Stack<big_data<std::string>>>::value);
}

TEST(Stack, test_copy)
{
  EXPECT_FALSE(std::is_copy_constructible<Stack<unsigned>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<unsigned>>::value);
  EXPECT_FALSE(std::is_copy_constructible
                   <Stack<big_data<std::string>>>::value);
  EXPECT_FALSE(std::is_copy_assignable
                   <Stack<big_data<std::string>>>::value);
}

template<typename T>
struct big_data_no_copy
{
  big_data_no_copy(T v1, T v2, T v3) : value_1(v1),value_2(v2),value_3(v3) {};
  big_data_no_copy(const big_data_no_copy& big_data_no_copy) =
      delete; // конструктор копирования (запрещен)
  big_data_no_copy(big_data_no_copy&& big_data_no_copy) =
      default; // конструктор перемещения
  big_data_no_copy &operator=(const big_data_no_copy& big_data_no_copy) =
      delete; //перегрузка копирования
  big_data_no_copy &operator=(big_data_no_copy && big_data_no_copy)  =
      default; //перегрузка перемещения
  T value_1;
  T value_2;
  T value_3;
};

TEST(big_data_no_copy, test_check)
{
  EXPECT_TRUE(std::is_move_constructible
      <big_data_no_copy<unsigned>>::value);
  EXPECT_TRUE(std::is_move_assignable
      <big_data_no_copy<unsigned>>::value);
  EXPECT_FALSE(std::is_copy_constructible
      <big_data_no_copy<unsigned>>::value);
  EXPECT_FALSE(std::is_copy_assignable
      <big_data_no_copy<unsigned>>::value);
}

TEST(UncopyableStack, test_push_head)
{
  UncopyableStack<int> buffer_2;
  EXPECT_THROW(buffer_2.head(), std::runtime_error);
  UncopyableStack<big_data_no_copy<unsigned>> buf;
  big_data_no_copy<unsigned> test_1 (1, 7, 7);
  big_data_no_copy<unsigned> test_2 (4, 8, 9);
  big_data_no_copy<unsigned> test_3 (5, 5, 5);
  buf.push(std::move(test_1));
  buf.push(std::move(test_2));
  buf.push(std::move(test_3));
  EXPECT_EQ(buf.head().value_3, test_3.value_3);
  EXPECT_EQ(buf.head().value_2, test_3.value_2);
  EXPECT_EQ(buf.head().value_1, test_3.value_1);
}

TEST(UncopyableStack, test_pop_head)
{
  UncopyableStack<int> buffer_2;
  EXPECT_THROW(buffer_2.head(), std::runtime_error);
  UncopyableStack<big_data_no_copy<unsigned>> buf;
  big_data_no_copy<unsigned> test_1 (1, 7, 7);
  big_data_no_copy<unsigned> test_2 (4, 8, 9);
  big_data_no_copy<unsigned> test_3 (5, 5, 5);
  buf.push(std::move(test_1));
  buf.push(std::move(test_2));
  buf.push(std::move(test_3));
  buf.pop();
  EXPECT_EQ(buf.head().value_3, test_2.value_3);
  EXPECT_EQ(buf.head().value_2, test_2.value_2);
  EXPECT_EQ(buf.head().value_1, test_2.value_1);
}

TEST(no_copy_stack, test_push_emplace_head)
{
  UncopyableStack<int> buffer_2;
  EXPECT_THROW(buffer_2.head(), std::runtime_error);
  UncopyableStack<big_data_no_copy<int>> buf;
  big_data_no_copy<int> test_1 (1, 7, 7);
  big_data_no_copy<int> test_2 (4, 8, 9);
  big_data_no_copy<int> test_3 (5, 5, 5);
  buf.push_emplace(1, 7, 7);
  buf.push_emplace(4, 8, 9);
  buf.push_emplace(5, 5, 5);
  EXPECT_EQ(buf.head().value_3, test_3.value_3);
  EXPECT_EQ(buf.head().value_2, test_3.value_2);
  EXPECT_EQ(buf.head().value_1, test_3.value_1);
}

TEST(UncopyableStack, test_move)
{
  EXPECT_EQ(std::is_move_constructible
      <UncopyableStack<unsigned>>::value, true);
  EXPECT_EQ(std::is_move_assignable
      <UncopyableStack<unsigned>>::value, true);
  EXPECT_TRUE(std::is_move_constructible
      <UncopyableStack<big_data_no_copy<std::string>>>::value);
  EXPECT_TRUE(std::is_move_assignable
      <UncopyableStack<big_data_no_copy<std::string>>>::value);
  EXPECT_TRUE(std::is_move_constructible
      <UncopyableStack<big_data_no_copy<unsigned>>>::value);
  EXPECT_TRUE(std::is_move_assignable
      <UncopyableStack<big_data_no_copy<unsigned>>>::value);
}

TEST(UncopyableStack, test_copy)
{
  EXPECT_FALSE(std::is_copy_constructible
      <UncopyableStack<unsigned>>::value);
  EXPECT_FALSE(std::is_copy_assignable
      <UncopyableStack<unsigned>>::value);
  EXPECT_FALSE(std::is_copy_constructible
      <UncopyableStack<double>>::value);
  EXPECT_FALSE(std::is_copy_assignable
      <UncopyableStack<double>>::value);
  EXPECT_FALSE(std::is_copy_constructible
      <UncopyableStack<big_data_no_copy<std::string>>>::value);
  EXPECT_FALSE(std::is_copy_assignable
      <UncopyableStack<big_data_no_copy<std::string>>>::value);
  EXPECT_FALSE(std::is_copy_constructible
      <UncopyableStack<big_data_no_copy<unsigned>>>::value);
  EXPECT_FALSE(std::is_copy_assignable
      <UncopyableStack<big_data_no_copy<unsigned>>>::value);
}