#include <gtest/gtest.h>

#include <random>
#include <stack>

#include "../s21_containers.h"

TEST(STACK, createAndSize) {
  s21::stack<double> A;
  EXPECT_EQ(A.size(), 0U);
  s21::stack<double> C = {1.78, 0.99, -1.53};
  EXPECT_EQ(C.size(), 3U);
  s21::stack<char> D = {'C', 'A', 'T'};
  EXPECT_EQ(D.size(), 3U);
}

TEST(STACK, create2) {
  s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> B = A;
  EXPECT_EQ(A.top(), B.top());
  EXPECT_EQ(A.size(), B.size());
}

TEST(STACK, create3) {
  const s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::stack<double> B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0U);
  EXPECT_EQ(A.top(), B.top());
}

TEST(STACK, createAndPop) {
  s21::stack<std::string> A = {"Cats", "are", "the", "best"};
  s21::stack<std::string> B = A;
  std::string a, b;
  while (!A.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(A.size(), 0U);
  EXPECT_EQ(B.size(), 0U);
}

TEST(STACK, createAndPop2) {
  s21::stack<std::string> A = {"Cats", "are", "the", "best", " ", ""};
  s21::stack<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::stack<std::string> B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0U);
  std::string a, b;
  while (!A.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(A.size(), 0U);
  EXPECT_EQ(B.size(), 0U);
}

TEST(STACK, createList) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::stack<double> A = L;
  std::stack<double> B(L);
  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(STACK, createList2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best",
                                          " ",    "",    "!"};
  s21::stack<std::string> A = L;
  std::stack<std::string> B(L);
  EXPECT_EQ(B.size(), A.size());
  std::string a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(STACK, assignmentCopy) {
  const s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> B;
  EXPECT_EQ(B.size(), 0U);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.top(), B.top());
}

TEST(STACK, assignmentCopy2) {
  const s21::stack<std::string> A = {"Cats", "are", "the", "best"};
  s21::stack<std::string> B;
  EXPECT_EQ(B.size(), 0U);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.top(), B.top());
}

TEST(STACK, assignmentMove) {
  s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> A2 = A;
  EXPECT_EQ(A2.size(), 3U);
  s21::stack<double> B;
  EXPECT_EQ(B.size(), 0U);
  B = std::move(A2);
  EXPECT_EQ(B.size(), 3U);
  EXPECT_EQ(A2.size(), 0U);
  EXPECT_EQ(A.top(), B.top());
}

TEST(STACK, assignmentMove2) {
  s21::stack<std::string> A = {"Cats", "are", "the", "best"};
  s21::stack<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::stack<std::string> B;
  EXPECT_EQ(B.size(), 0U);
  B = std::move(A2);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0U);
  std::string a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(STACK, top) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::stack<double> A = L;
  std::stack<double> B(L);
  EXPECT_EQ(A.top(), B.top());
  A.pop();
  B.pop();
  EXPECT_EQ(A.top(), B.top());
}

TEST(STACK, top2) {
  std::initializer_list<char> L = {'C', 'A', 'T'};
  s21::stack<char> A = L;
  std::stack<char> B(L);
  EXPECT_EQ(A.top(), B.top());
  A.pop();
  B.pop();
  EXPECT_EQ(A.top(), B.top());
}

TEST(STACK, top3) {
  s21::stack<int> a;
  a.push(3);
  a.push(33);
  a.push(333);
  auto it = a.top();
  EXPECT_EQ(333, it);
  a.pop();
  it = a.top();
  EXPECT_EQ(33, it);
}

TEST(STACK, topConst) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::stack<double> A = L;
  const std::stack<double> B(L);
  EXPECT_EQ(A.top(), B.top());
  EXPECT_EQ(A.size(), B.size());
}

TEST(STACK, empty) {
  s21::stack<double> A;
  ASSERT_TRUE(A.empty());
  s21::stack<double> C = {1.78, 0.99, -1.53};
  ASSERT_FALSE(C.empty());
  s21::stack<char> D = {'C', 'A', 'T'};
  ASSERT_FALSE(D.empty());
  C = A;
  ASSERT_TRUE(C.empty());
}

TEST(STACK, push_pop) {
  s21::stack<double> A;
  std::stack<double> B;
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
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(STACK, swap) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::stack<double> A = L;
  std::stack<double> B(L);
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::stack<double> A2 = L2;
  std::stack<double> B2(L2);
  A.swap(A2);
  B.swap(B2);

  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(STACK, swap2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best",
                                          " ",    "",    "!"};
  s21::stack<std::string> A = L;
  std::stack<std::string> B(L);
  std::initializer_list<std::string> L2 = {"Salamanders", "Capybaras",
                                           "Alpacas", "Honey Badgers"};
  s21::stack<std::string> A2 = L2;
  std::stack<std::string> B2(L2);
  A.swap(A2);
  B.swap(B2);

  EXPECT_EQ(B.size(), A.size());
  std::string a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(STACK, swap3) {
  s21::stack<int> a;
  s21::stack<int> b;
  a.push(5);
  a.push(4);
  a.push(3);
  a.push(2);
  a.push(1);
  a.swap(b);
  int size = b.size();
  for (int i = 1; i <= size; i++) {
    EXPECT_EQ(b.top(), i);
    b.pop();
  }
  EXPECT_EQ(b.empty(), true);
}

TEST(STACK, size) {
  s21::stack<int> a;
  a.push(3);
  auto size = a.size();
  EXPECT_EQ(1U, size);

  s21::stack<int> b;
  auto size_2 = b.size();
  EXPECT_EQ(0U, size_2);
}

TEST(STACK, test) {
  s21::stack<int> a{1, 2, 4};
  a.push(3);
  auto size = a.size();
  EXPECT_EQ(4U, size);
  s21::stack<int> c = a;
  EXPECT_EQ(c.size(), a.size());
  s21::stack<int> d = std::move(a);
  EXPECT_EQ(0U, a.size());
  s21::stack<int> b;
  auto size_2 = b.size();
  EXPECT_EQ(0U, size_2);
  s21::stack<int> test1;
  test1 = std::move(d);
  EXPECT_EQ(0U, d.size());
}

TEST(STACK, test2) {
  s21::stack<int> a{1, 2, 4, 5, 6, 7};
  s21::stack<int> b;
  b = std::move(a);
  EXPECT_EQ(a.size(), 0U);
}

TEST(STACK, pushAndPop) {
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.push(4);
  a.push(5);
  int i = 5;
  size_t size = 1;
  while (size <= a.size()) {
    EXPECT_EQ(i, a.top());
    a.pop();
    i--;
    size++;
  }
  a.pop();
  a.pop();
  a.push(1);
  a.push(2);
  a.push(3);
  i = 3;
  size = 1;
  while (size <= a.size()) {
    EXPECT_EQ(i, a.top());
    a.pop();
    i--;
    size++;
  }
}

TEST(STACK, pushAndPop2) {
  s21::stack<int> a;
  a.push(1);
  a.pop();
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ(a.empty(), true);
}

TEST(STACK, eq) {
  s21::stack<int> a;
  s21::stack<int> b;
  a.push(11);
  a.push(22);
  a.push(33);
  b = a;
  size_t size = 1;
  while (size <= a.size()) {
    EXPECT_EQ(b.top(), a.top());
    a.pop();
    b.pop();
    size++;
  }
}

TEST(STACK, insertManyFront) {
  s21::stack<int> A = {1, 2, 3};
  s21::stack<int> B = {5, 1, 2, 5, 6, 1, 2, 3};
  A.insert_many_front(5, 1, 2, 5, 6);

  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}
