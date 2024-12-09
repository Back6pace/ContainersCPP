#include <gtest/gtest.h>

#include <array>

#include "../s21_containersplus.h"

TEST(ARRAY, defaultConstructor) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(ARRAY, initializerListInt) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(ARRAY, initializerListChar) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  std::array<char, 3> std_array = {'a', 'b', 'c'};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(ARRAY, initializerListFloat) {
  s21::array<float, 3> s21_array = {1.234, 5.678, 9.123};
  std::array<float, 3> std_array = {1.234, 5.678, 9.123};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(ARRAY, initializerListBigSize) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  std::array<int, 10> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 10; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(ARRAY, initializerListThrow) {
  try {
    s21::array<int, 3> s21_array = {1, 2, 3, 4};
  } catch (std::out_of_range &ex) {
    EXPECT_EQ(ex.what(), std::string("Out of range. To many args"));
  }
}

TEST(ARRAY, copyConstrucorInt) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(ARRAY, copyConstructorChar) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  s21::array<char, 3> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(ARRAY, copyConstructorFloat) {
  s21::array<float, 3> s21_array = {1.234, 5.678, 9.123};
  s21::array<float, 3> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(ARRAY, copyconstructorBigSize) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  s21::array<int, 10> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 10; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(ARRAY, moveConstructorInt) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test(std::move(s21_array));
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

TEST(ARRAY, moveConstructorChar) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  s21::array<char, 3> s21_test(std::move(s21_array));
  std::array<char, 3> std_array = {'a', 'b', 'c'};
  std::array<char, 3> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

TEST(ARRAY, moveConstructorFloat) {
  s21::array<float, 3> s21_array = {1.234, 5.678, 9.123};
  s21::array<float, 3> s21_test(std::move(s21_array));
  std::array<float, 3> std_array = {1.234, 5.678, 9.123};
  std::array<float, 3> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

TEST(ARRAY, moveConstructorBigSize) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  s21::array<int, 10> s21_test(std::move(s21_array));
  std::array<int, 10> std_array = {1, 2, 3};
  std::array<int, 10> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

// -----------Array Element access---------------------

TEST(ARRAY, at) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array.at(0), 1);
  EXPECT_EQ(s21_array.at(1), 2);
  EXPECT_EQ(s21_array.at(2), 3);
}

TEST(ARRAY, atCHarConst) {
  const s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  EXPECT_EQ(s21_array.at(0), 'a');
  EXPECT_EQ(s21_array.at(1), 'b');
  EXPECT_EQ(s21_array.at(2), 'c');
}

TEST(ARRAY, atDouble) {
  s21::array<double, 3> s21_array = {1.23, 2.13, 3.12};
  EXPECT_EQ(s21_array.at(0), 1.23);
  EXPECT_EQ(s21_array.at(1), 2.13);
  EXPECT_EQ(s21_array.at(2), 3.12);
}

TEST(ARRAY, atInsert) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21_array.at(1) = 777;
  EXPECT_EQ(s21_array.at(0), 1);
  EXPECT_EQ(s21_array.at(1), 777);
  EXPECT_EQ(s21_array.at(2), 3);
}

TEST(ARRAY, atThrow) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_ANY_THROW(s21_array.at(3));
}

TEST(ARRAY, atThrowConst) {
  const s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_ANY_THROW(s21_array.at(3));
}

TEST(ARRAY, operatorSqBrackets) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array[0], 1);
  EXPECT_EQ(s21_array[1], 2);
  EXPECT_EQ(s21_array[2], 3);
}

TEST(ARRAY, operatorSqBracketsCharConst) {
  const s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  EXPECT_EQ(s21_array[0], 'a');
  EXPECT_EQ(s21_array[1], 'b');
  EXPECT_EQ(s21_array[2], 'c');
}

TEST(ARRAY, operatorSqBracketsInsert) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21_array[1] = 777;
  EXPECT_EQ(s21_array[0], 1);
  EXPECT_EQ(s21_array[1], 777);
  EXPECT_EQ(s21_array[2], 3);
}

TEST(ARRAY, front) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array.front(), 1);
}

TEST(ARRAY, back) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array.back(), 3);
}

TEST(ARRAY, data) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto example = s21_array.data();
  EXPECT_EQ(s21_array.front(), *example);
}

TEST(ARRAY, dataConst) {
  const s21::array<int, 3> s21_array = {1, 2, 3};
  const auto example = s21_array.data();
  EXPECT_EQ(s21_array.front(), *example);
}

// ------------Array Iterators-----------------------

TEST(ARRAY, begin) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto it = s21_array.begin();
  auto it1 = it;
  it1++;
  auto it2 = it1;
  it2++;
  EXPECT_EQ(*it, s21_array[0]);
  EXPECT_EQ(*it1, s21_array[1]);
  EXPECT_EQ(*it2, s21_array[2]);
}

TEST(ARRAY, beginFront) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto example = s21_array.begin();
  EXPECT_EQ(s21_array.front(), *example);
}

TEST(ARRAY, end) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto it = s21_array.end() - 1;
  auto it1 = it;
  it1--;
  auto it2 = it1;
  it2--;
  EXPECT_EQ(*it, s21_array[2]);
  EXPECT_EQ(*it1, s21_array[1]);
  EXPECT_EQ(*it2, s21_array[0]);
}

TEST(ARRAY, endBack) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto example = s21_array.end() - 1;
  EXPECT_EQ(s21_array.back(), *example);
}

// -----------Array Capacity---------------------

TEST(ARRAY, empty) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(ARRAY, empty2) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(ARRAY, size) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.size(), std_array.size());
}

TEST(ARRAY, size2) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
}

TEST(ARRAY, size3) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  std::array<int, 10> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
}

TEST(ARRAY, maxSize) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
}

TEST(ARRAY, maxSize2) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
}

TEST(ARRAY, maxSize3) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  std::array<int, 10> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
}

// -------------Array Modifiers--------------------------

TEST(ARRAY, swap) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test = {5, 4, 3};
  s21_array.swap(s21_test);
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3> std_test = {5, 4, 3};
  std_array.swap(std_test);
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }

  auto j = 0;
  for (auto it = std_test.begin(); it != std_test.end(); it++) {
    EXPECT_EQ(s21_test.at(j), *it);
    j++;
  }
}

TEST(ARRAY, swapEmpty) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test = {};
  s21_array.swap(s21_test);
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3> std_test = {};
  std_array.swap(std_test);
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }

  auto j = 0;
  for (auto it = std_test.begin(); it != std_test.end(); it++) {
    EXPECT_EQ(s21_test.at(j), *it);
    j++;
  }
}

TEST(ARRAY, fill) {
  s21::array<int, 3> s21_array;
  s21_array.fill(1);
  std::array<int, 3> std_array;
  std_array.fill(1);
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}

TEST(ARRAY, fill2) {
  s21::array<int, 3> s21_array = {1};
  s21_array.fill(2);
  std::array<int, 3> std_array = {1};
  std_array.fill(2);
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}

TEST(ARRAY, fillDouble) {
  s21::array<double, 3> s21_array = {1.23, 2.13, 3.12};
  s21_array.fill(1);
  std::array<double, 3> std_array = {1.23, 2.13, 3.12};
  std_array.fill(1);
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}

TEST(ARRAY, fillChar) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  s21_array.fill('a');
  std::array<char, 3> std_array = {'a', 'b', 'c'};
  std_array.fill('a');
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}