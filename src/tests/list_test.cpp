#include <gtest/gtest.h>

#include <list>
#include <random>

#include "../s21_containers.h"  // Подключение вашего заголовочного файла

// Тесты для списка
TEST(LIST, Size) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(LIST, Size2) {
  s21::list<int> s21_list_int(5);
  s21::list<double> s21_list_double(5);
  s21::list<std::string> s21_list_string(5);

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_string.size(), 5U);
}

TEST(LIST, CreateAndSize) {
  s21::list<int> s21_list_int = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21_list_int.size(), 5U);
  s21::list<double> s21_list_double = {1.1, 2.2, 3.3, 4.4, 5.5};
  EXPECT_EQ(s21_list_double.size(), 5U);
  s21::list<std::string> s21_list_string = {"1", "2", "3", "4", "5"};
  EXPECT_EQ(s21_list_string.size(), 5U);
}

TEST(LIST, createAndIterator) {
  s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> B = A;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, createAndIterator2) {
  const s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> A2 = A;
  EXPECT_EQ(A2.size(), 3U);
  s21::list<double> B = std::move(A2);
  EXPECT_EQ(B.size(), 3U);
  EXPECT_EQ(A2.size(), 0U);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, createAndIterator3) {
  s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> B = A;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, createAndIterator4) {
  const s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> A2 = A;
  EXPECT_EQ(A2.size(), 4U);
  s21::list<std::string> B = std::move(A2);
  EXPECT_EQ(B.size(), 4U);
  EXPECT_EQ(A2.size(), 0U);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < 4; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, createList) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  std::list<double> B = L;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, createList2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best"};
  s21::list<std::string> A = L;
  std::list<std::string> B = L;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, assignmentCopy1) {
  const s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> B;
  EXPECT_EQ(B.size(), 0U);
  B = A;
  EXPECT_EQ(B.size(), 3U);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, assignmentCopy2) {
  const s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> B;
  EXPECT_EQ(B.size(), 0U);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, assignmentMove) {
  s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> A2 = A;
  EXPECT_EQ(A2.size(), 3U);
  s21::list<double> B;
  EXPECT_EQ(B.size(), 0U);
  B = std::move(A2);
  EXPECT_EQ(B.size(), 3U);
  EXPECT_EQ(A2.size(), 0U);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, assignmentMove2) {
  s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::list<std::string> B;
  EXPECT_EQ(B.size(), 0U);
  B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0U);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, frontBack1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  std::list<double> B = L;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(LIST, frontBack2) {
  std::initializer_list<char> L = {'C', 'A', 'T'};
  s21::list<char> A = L;
  std::list<char> B = L;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(LIST, frontBackConst) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::list<double> A = L;
  const std::list<double> B = L;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(LIST, beginEnd1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  std::list<double> B = L;
  EXPECT_EQ(*A.begin(), *B.begin());
  EXPECT_EQ(*(--A.end()), *(--B.end()));
}

TEST(LIST, beginEnd2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best"};
  s21::list<std::string> A = L;
  std::list<std::string> B = L;
  EXPECT_EQ(*A.begin(), *B.begin());
  EXPECT_EQ(*(--A.end()), *(--B.end()));
}

TEST(LIST, constBeginEnd) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::list<double> A = L;
  const std::list<double> B = L;
  EXPECT_EQ(*(++A.begin()), *(++B.begin()));
  EXPECT_EQ(*(--A.end()), *(--B.end()));
}

TEST(LIST, empty) {
  s21::list<double> A;
  ASSERT_TRUE(A.empty());
  const s21::list<double> B(7);
  ASSERT_FALSE(B.empty());
  s21::list<double> C = {1.78, 0.99, -1.53};
  ASSERT_FALSE(C.empty());
  C = A;
  ASSERT_TRUE(C.empty());
}

// TEST(LIST, maxSize) {
//   const s21::list<int> A;
//   const std::list<int> B;
//   EXPECT_EQ(A.max_size(), B.max_size());

//   s21::list<double> A1;
//   std::list<double> B1;
//   EXPECT_EQ(A1.max_size(), B1.max_size());

//   s21::list<std::string> A2;
//   std::list<std::string> B2;
//   EXPECT_EQ(A1.max_size(), B1.max_size());
// }

TEST(LIST, clear) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  A.clear();
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0U);
}

TEST(LIST, insert1) {
  s21::list<int> A;
  std::list<int> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 100000);
  int elem;
  for (int n = 0; n < 10; ++n) {
    elem = dist(gen);
    A.insert(A.begin(), elem);
    B.insert(B.begin(), elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, insert2) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.insert(A.begin(), elem);
    B.insert(B.begin(), elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, erase) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.erase(++A.begin());
  A.erase(--(--A.end()));
  B.erase(++B.begin());
  B.erase(--(--B.end()));

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() - 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, pushBack) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_back(elem);
    B.push_back(elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, pushFront) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_front(elem);
    B.push_front(elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, popBackAndPopFront) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.pop_back();
  A.pop_front();
  B.pop_back();
  B.pop_front();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() - 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, swap) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::list<double> A2 = L2;
  std::list<double> B2 = L2;
  A.swap(A2);
  B.swap(B2);

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  auto iter_A2 = A2.begin();
  auto iter_B2 = B2.begin();
  for (std::size_t i = 0; i < L.size();
       i++, ++iter_A, ++iter_B, ++iter_A2, ++iter_B2) {
    EXPECT_EQ(*iter_A, *iter_B);
    EXPECT_EQ(*iter_A2, *iter_B2);
  }
}

TEST(LIST, merge) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::list<double> A2 = L2;
  std::list<double> B2 = L2;
  A.merge(A2);
  B.merge(B2);

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() * 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, splice) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::list<double> A2 = L2;
  std::list<double> B2 = L2;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() / 2; i++, ++iter_A, ++iter_B) {
  }
  A.splice(iter_A, A2);
  B.splice(iter_B, B2);

  iter_A = A.begin();
  iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() * 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, reverse) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_back(elem);
    B.push_back(elem);
  }
  A.reverse();
  B.reverse();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, unique) {
  std::initializer_list<double> L = {1.78,    0.99,    -1.53, -1.53,
                                     4.88,    4.88,    0.99,  111.303,
                                     111.303, 111.303, -1.53, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.unique();
  B.unique();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < B.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, sort) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_back(elem);
    B.push_back(elem);
  }
  A.sort();
  B.sort();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, sort2) {
  std::initializer_list<double> L = {1.78,    0.99,    -1.53, -1.53,
                                     4.88,    4.88,    0.99,  111.303,
                                     111.303, 111.303, -1.53, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.sort();
  B.sort();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < B.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(LIST, front) {
  s21::list<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};
  auto it1 = a.front();
  auto i = b.front();
  EXPECT_EQ(it1, i);
}

TEST(LIST, size) {
  s21::list<int> a = {1, 2, 3, 5, 6};
  s21::list<int> b(5);
  s21::list<int> c = a;
  auto a1 = a.size();
  EXPECT_EQ(a1, 5U);
  s21::list<int> d = {1, 2, 3, 5, 6, 9, 0};
  d = a;
  s21::list<int> test1 = {1, 2, 3, 5, 6};
  s21::list<int> test2(5);
  test1 = test2;
  EXPECT_EQ(test1.size(), test2.size());
}

TEST(LIST, size1) {
  s21::list<int> a;
  auto a1 = a.size();
  EXPECT_EQ(a1, 0U);
}

TEST(LIST, isEmptyTrue) {
  s21::list<int> a;
  auto a1 = a.empty();
  ASSERT_TRUE(a1);
}

TEST(LIST, isEmptyFalse) {
  s21::list<int> a = {1, 23, 43};
  auto a1 = a.empty();
  ASSERT_FALSE(a1);
}

TEST(LIST, back) {
  s21::list<int> a = {1, 23, 43, 3};
  auto a1 = a.back();
  EXPECT_EQ(a1, 3);
}

TEST(LIST, back2) {
  s21::list<int> a = {};
  auto a1 = a.back();
  EXPECT_EQ(a1, 0);
}

TEST(LIST, pushFront1) {
  s21::list<int> a = {};
  a.push_front(1);
  a.push_front(3);
  a.push_front(5);
  std::list<int> b = {5, 3, 1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
}

TEST(LIST, pushBackPop1) {
  s21::list<int> a = {};
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  std::list<int> b = {1, 2, 3};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
  a.pop_back();
  b = {1, 2};
  auto it3 = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *it3);
    ++it3;
  }
}

TEST(LIST, pushBackPop2) {
  s21::list<int> a;
  a.push_back(1);
  std::list<int> b = {1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
  a.pop_back();
  EXPECT_EQ(a.empty(), true);
}

TEST(LIST, swap2) {
  s21::list<int> a1 = {0, 2, 4, 6};
  s21::list<int> a2 = {6, 4, 2, 0};
  a1.swap(a2);
  std::list<int> a3 = {0, 2, 4, 6};
  std::list<int> a4 = {6, 4, 2, 0};
  a4.swap(a3);
  auto it_original = a3.begin();
  for (auto it = a1.begin(); it != a1.end(); ++it) {
    EXPECT_EQ(*it_original, *it);
    it_original++;
  }
}

TEST(LIST, reverse2) {
  s21::list<int> a1 = {0, 2, 4, 6};
  std::list<int> a2 = {0, 2, 4, 6};
  a1.reverse();
  a2.reverse();
  auto it = a1.begin();
  for (auto it_original = a2.begin(); it_original != a2.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it);
    it++;
  }
}

// TEST(LIST, maxSize2) {
//   s21::list<int> a1;
//   std::list<int> a2;
//   EXPECT_EQ(a1.max_size(), a2.max_size());
// }

TEST(LIST, unique2) {
  s21::list<int> a = {0, 1, 254, 333, 333, 12, 1};
  std::list<int> b = {0, 1, 254, 333, 333, 12, 1};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(LIST, unique3) {
  s21::list<int> a = {0, 0, 0, 0, 0, 0};
  std::list<int> b = {0, 0, 0, 0, 0, 0};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(LIST, unique4) {
  s21::list<int> a = {5, 4, 3, 2, 1, 5};
  std::list<int> b = {5, 4, 3, 2, 1, 5};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(LIST, operatorCopy) {
  s21::list<int> a = {1, 2, 3, 4};
  s21::list<int> b = {1, 2};
  b = a;
  EXPECT_EQ(b.size(), 4U);
}

TEST(LIST, constructorMove) {
  s21::list<int> a = {1, 2, 3, 4};
  s21::list<int> b = std::move(a);
  EXPECT_FALSE(a.begin() != a.end());
}

TEST(LIST, splice2) {
  s21::list<int> a = {0, 1, 3};
  s21::list<int> b = {4, 5};
  auto i = a.begin();
  ++i;
  ++i;
  ++i;
  a.splice(i, b);
  auto it = a.begin();

  std::list<int> a1 = {0, 1, 3};
  std::list<int> b1 = {4, 5};
  auto i_res = a1.begin();
  ++i_res;
  ++i_res;
  ++i_res;
  a1.splice(i_res, b1);

  for (auto it_res = a1.begin(); it_res != a1.end(); it_res++, it++) {
    EXPECT_EQ(*it, *it_res);
  }
}

TEST(LIST, insertManyFront) {
  s21::list<int> a = {6, 7, 8};
  a.insert_many_front(1, 2, 3, 4, 5);
  auto it = a.begin();
  for (int i = 1; i <= 8; i++, ++it) {
    EXPECT_EQ(*it, i);
  }

  EXPECT_FALSE(a.begin() == a.end());
  it--;
  it--;
  EXPECT_EQ(*it, 7);
}

TEST(LIST, insertManyBack) {
  s21::list<int> a = {1, 2, 3, 4};
  a.insert_many_back(1, 1, 2, 5, 6);
  auto it = a.size();
  EXPECT_EQ(9U, it);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 6);
}