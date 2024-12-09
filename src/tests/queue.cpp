#include <gtest/gtest.h>

#include <queue>
#include <random>

#include "../s21_containers.h"

TEST(queue_test, create_and_size) {
  s21::queue<double> A;
  EXPECT_EQ(A.size(), 0U);
  s21::queue<double> C = {1.78, 0.99, -1.53};
  EXPECT_EQ(C.size(), 3U);
  s21::queue<char> D = {'C', 'A', 'T'};
  EXPECT_EQ(D.size(), 3U);
}

TEST(queue_test, create_1) {
  s21::queue<double> A = {1.78, 0.99, -1.53};
  s21::queue<double> B = A;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
  EXPECT_EQ(A.size(), B.size());
}

TEST(queue_test, create_2) {
  const s21::queue<double> A = {1.78, 0.99, -1.53};
  s21::queue<double> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::queue<double> B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0U);
  EXPECT_EQ(A.back(), B.back());
  EXPECT_EQ(A.front(), B.front());
}

TEST(queue_test, create_and_pop) {
  s21::queue<std::string> A = {"Cats", "are", "the", "best"};
  s21::queue<std::string> B = A;
  std::string a, b;
  while (!A.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(A.size(), 0U);
  EXPECT_EQ(B.size(), 0U);
}

TEST(queue_test, create_and_pop_2) {
  s21::queue<std::string> A = {"Cats", "are", "the", "best", " ", ""};
  s21::queue<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::queue<std::string> B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0U);
  std::string a, b;
  while (!A.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(A.size(), 0U);
  EXPECT_EQ(B.size(), 0U);
}

TEST(queue_test, create_list_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::queue<double> A = L;
  std::queue<double> B(L);
  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(queue_test, create_list_2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best",
                                          " ",    "",    "!"};
  s21::queue<std::string> A = L;
  std::queue<std::string> B(L);
  EXPECT_EQ(B.size(), A.size());
  std::string a, b;
  while (!B.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(queue_test, assignment_copy_1) {
  const s21::queue<double> A = {1.78, 0.99, -1.53};
  s21::queue<double> B;
  EXPECT_EQ(B.size(), 0U);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.back(), B.back());
  EXPECT_EQ(A.front(), B.front());
}

TEST(queue_test, assignment_copy_2) {
  const s21::queue<std::string> A = {"Cats", "are", "the", "best"};
  s21::queue<std::string> B;
  EXPECT_EQ(B.size(), 0U);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.back(), B.back());
  EXPECT_EQ(A.front(), B.front());
}

TEST(queue_test, front_back_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::queue<double> A = L;
  std::queue<double> B(L);
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(queue_test, front_back_2) {
  std::initializer_list<char> L = {'C', 'A', 'T'};
  s21::queue<char> A = L;
  std::queue<char> B(L);
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(queue_test, front_back_const) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::queue<double> A = L;
  const std::queue<double> B(L);
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(queue_test, empty) {
  s21::queue<double> A;
  ASSERT_TRUE(A.empty());
  s21::queue<double> C = {1.78, 0.99, -1.53};
  ASSERT_FALSE(C.empty());
  s21::queue<char> D = {'C', 'A', 'T'};
  ASSERT_FALSE(D.empty());
  C = A;
  ASSERT_TRUE(C.empty());
}

TEST(queue_test, push_pop) {
  s21::queue<double> A;
  std::queue<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push(elem);
    B.push(elem);
  }

  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.back(), B.back());
  double a, b;
  while (!B.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(queue_test, swap_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::queue<double> A = L;
  std::queue<double> B(L);
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::queue<double> A2 = L2;
  std::queue<double> B2(L2);
  A.swap(A2);
  B.swap(B2);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.back(), B.back());
  double a, b;
  while (!B.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(queue_test, swap_2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best",
                                          " ",    "",    "!"};
  s21::queue<std::string> A = L;
  std::queue<std::string> B(L);
  std::initializer_list<std::string> L2 = {"Salamanders", "Capybaras",
                                           "Alpacas", "Honey Badgers"};
  s21::queue<std::string> A2 = L2;
  std::queue<std::string> B2(L2);
  A.swap(A2);
  B.swap(B2);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.back(), B.back());
  std::string a, b;
  while (!B.empty()) {
    a = A.front();
    b = B.front();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(queue_test, push_pop_1) {
  s21::queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  std::queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
  a.pop();
  a.pop();
  b.pop();
  b.pop();
  EXPECT_EQ(a.back(), b.back());
  a.pop();
  b.pop();
  EXPECT_TRUE(a.empty());

  auto test = std::move(a);
  s21::queue<int> c;
  c.push(1);
  c.push(2);
  c.push(3);
  a = c;
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 3);
}

TEST(queue_test, test) {
  s21::queue<int> a{1, 2, 3};
  s21::queue<int> a2{1, 2, 3};
  s21::queue<int> a3{1, 2, 3};
  s21::queue<int> c = a;
  s21::queue<int> d;
  const s21::queue<int> test_const{1, 2, 3};
  EXPECT_EQ(test_const.front(), 1);
  EXPECT_EQ(test_const.back(), 3);
  d.swap(a3);
  d = std::move(a2);
  auto it = a.size();
  EXPECT_EQ(3U, it);
  s21::queue<int> b;
  auto it2 = b.size();
  EXPECT_EQ(0U, it2);
}

TEST(queue_test, size) {
  s21::queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.push(4);
  a.push(5);
  auto it = a.size();
  EXPECT_EQ(5U, it);
  s21::queue<int> b;
  auto it2 = b.size();
  EXPECT_EQ(0U, it2);
}

TEST(queue_test, insert_many_back) {
  s21::queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.insert_many_back(1, 1, 2, 5, 6);
  auto it = a.size();
  EXPECT_EQ(8U, it);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 6);
}
