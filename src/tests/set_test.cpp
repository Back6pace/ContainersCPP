#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(set_test, constructor_1) {
  s21::set<int> set1;
  std::set<int> set2;
  s21::set<int> set3 = {1, 2, 3};
  s21::set<int> set4 = set3;
  s21::set<int> set5 = std::move(set4);
  const s21::set<int> set_const = {1, 2, 3};
  const s21::set<int> set_const2 = {1, 2, 3};
  auto it1 = set_const.begin();
  auto it2 = set_const2.begin();
  for (size_t i = 0; i < set_const2.size(); it1++, it2++, i++) {
    EXPECT_EQ(*it1, *it2);
  }
  const std::set<int> set_const3 = {1, 2, 3};
  auto it4 = set_const.end();
  it4--;
  auto it3 = set_const3.end();
  it3--;
  EXPECT_EQ(*it4, *it3);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test2) {
  s21::set<char> set1 = {'a', '2', 'c'};
  std::set<char> set2 = {'a', '2', 'c'};
  set1.max_size();
  set2.max_size();

  EXPECT_EQ(*(set2.find('a')), *(set1.find('a')));
  const s21::set<char> set3 = {'a', '2', 'c'};
  const std::set<char> set4 = {'a', '2', 'c'};
  EXPECT_EQ(*(set3.find('a')), *(set4.find('a')));
}

TEST(set_test, test3) {
  s21::set<int> set1 = {1, 53, 6345, 123, -124};
  std::set<int> set2 = {1, 53, 6345, 123, -124};
  auto a = set1.begin();
  auto b = set2.begin();
  EXPECT_EQ(set1.size(), set2.size());
  for (; a != set1.end(); a++, b++) {
    EXPECT_EQ(*a, *b);
  }
}

TEST(set_test, test4) {
  s21::set<int> set1 = {1, 53, 6345, 123, -124};
  std::set<int> set2 = {1, 53, 6345, 123, -124};
  auto b = std::move(set1);
  auto a = std::move(set2);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test5) {
  s21::set<int> set1 = {1, 53, 6345, 123, -124};
  std::set<int> set2 = {1, 53, 6345, 123, -124};
  EXPECT_EQ(set1.empty(), set2.empty());
  set1.clear();
  set2.clear();
  EXPECT_EQ(set1.empty(), set2.empty());
}

TEST(set_test, test6) {
  const s21::set<int> set1 = {1, 53, 6345, 123, -124};
  s21::set<int> set2;
  set2 = set1;
  const std::set<int> set3 = {1, 53, 6345, 123, -124};
  auto it1 = set2.begin();
  auto it2 = set3.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, test7) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto it1 = set1.end();
  auto it2 = set2.end();
  it1--;
  it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(set_test, test8) {
  s21::set<double> set1 = {21.123, 452.124, 0.124, 6475.134};
  std::set<double> set2 = {21.123, 452.124, 0.124, 6475.134};
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.empty(), set1.empty());
  set1.clear();
  set2.clear();
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.empty(), set1.empty());
}

TEST(set_test, test9) {
  s21::set<double> set1 = {21.123, 452.124, 0.124, 6475.134};
  std::set<double> set2 = {21.123, 452.124, 0.124, 6475.134};
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.empty(), set1.empty());
  set1.clear();
  set2.clear();
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.empty(), set1.empty());
  set1.insert(1124.21);
  set2.insert(123.123);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.empty(), set1.empty());
}

TEST(set_test, test10) {
  s21::set<double> set1 = {21.123, 452.124, 0.124, 6475.134};
  std::set<double> set2 = {21.123, 452.124, 0.124, 6475.134};
  s21::set<double> set3 = {21.123, 141.765, 214, 1.24};
  std::set<double> set4 = {21.123, 141.765, 214, 1.24};
  set1.merge(set3);
  set2.merge(set4);
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  auto it3 = set3.begin();
  auto it4 = set4.begin();
  for (size_t i = 0; i < set1.size(); it1++, it2++, i++) EXPECT_EQ(*it1, *it2);
  for (size_t i = 0; i < set3.size(); it3++, it4++, i++) EXPECT_EQ(*it3, *it4);
}

TEST(set_test, test11) {
  s21::set<double> set1 = {21.123, 452.124, 0.124, 6475.134};
  EXPECT_EQ(set1.contains(21.123), true);
  EXPECT_EQ(set1.contains(212412.123), false);
  EXPECT_EQ(set1.contains(0.124), true);
  EXPECT_EQ(set1.contains(213.123), false);
}

TEST(set_test, test12) {
  s21::set<double> set1 = {21.123, 452.124, 0.124, 6475.134};
  std::set<double> set2 = {21.123, 452.124, 0.124, 6475.134};
  s21::set<double> set3 = {21.123, 141.765, 214, 1.24};
  std::set<double> set4 = {21.123, 141.765, 214, 1.24};
  set2.swap(set4);
  set1.swap(set3);
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  auto it3 = set3.begin();
  auto it4 = set4.begin();
  for (size_t i = 0; i < set1.size(); it1++, it2++, i++) EXPECT_EQ(*it1, *it2);
  for (size_t i = 0; i < set3.size(); it3++, it4++, i++) EXPECT_EQ(*it3, *it4);
}

TEST(set_test, test13) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.insert('e').second, set2.insert('e').second);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(*(set1.insert('e').first), *(set2.insert('e').first));
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test14) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  set1.erase(it1);
  set2.erase(it2);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test15) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.size(), set2.size());
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  set1.erase(it1);
  set2.erase(it2);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test16) {
  s21::set<char> set1 = {'a', '2', 'c'};
  std::set<char> set2 = {'a', '2', 'c'};
  set1.max_size();
  set2.max_size();

  EXPECT_EQ(*(set2.find('a')), *(set1.find('a')));
  const s21::set<char> set3 = {'a', '2', 'c'};
  const std::set<char> set4 = {'a', '2', 'c'};
  EXPECT_EQ(*(set3.find('a')), *(set4.find('a')));
}

TEST(set_test, test17) {
  s21::set<char> set1;
  std::set<char> set2;
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(set1.insert('e').second, set2.insert('e').second);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(*(set1.insert('e').first), *(set2.insert('e').first));
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test18) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  set1.erase(it1);
  set2.erase(it2);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test19) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.size(), set2.size());
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  set1.erase(it1);
  set2.erase(it2);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test20) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  s21::set<char> a;
  std::set<char> b;
  set1.swap(a);
  set2.swap(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
  set1 = {'a', '2', 'c', '4'};
  set2 = {'a', '2', 'c', '4'};
  set1.swap(a);
  set2.swap(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, test21) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  s21::set<char> a = {'e', '6', 'g', '8'};
  std::set<char> b = {'e', '6', 'g', '8'};
  set1.merge(a);
  set2.merge(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = set1.begin();
  for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, test22) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  s21::set<char> a = {'a', '2', 'c', '4'};
  std::set<char> b = {'a', '2', 'c', '4'};
  set1.merge(a);
  set2.merge(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = set1.begin();
  for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, test23) {
  s21::set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  s21::set<char> a = {'a', '2', 'c', '4', 'a', '2'};
  std::set<char> b = {'a', '2', 'c', '4', 'a', '2'};
  set1.merge(a);
  set2.merge(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = set1.begin();
  for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, test24) {
  s21::set<char> set1 = {'a', '2', 'c', '4', 'e', '6'};
  s21::set<char> set2 = {'a', '2', 'c', '4', 'e', '6'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  for (int i = 0; i < 6; i++) {
    it1++, it2++;
  }
  it1 = set1.end();
  it2 = set2.end();
  for (int i = 0; i < 6; i++) {
    it1--, it2--;
  }
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, test25) {
  s21::set<char> set1 = {'a', '2', 'c', '4', 'e', '6'};
  s21::set<char> set2 = {'a', '2', 'c', '4', 'e', '6'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  it1++;
  EXPECT_EQ(it1 != it2, true);
  auto it3 = set1.end();
  auto it4 = set2.end();
  for (int i = 0; i < 3; i++) {
    it3--, it4--;
  }
  EXPECT_EQ(it3 == it4, false);
  EXPECT_EQ(*it3, *it4);
}

TEST(set_test, default_constructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_test, parameterized_constructor) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  auto s21_it = s21_set.begin();
  for (auto std_it = std_set.begin(); std_it != std_set.end();
       std_it++, s21_it++) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(set_test, copy_constructor) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_set_test(s21_set);
  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_set_test(std_set);

  EXPECT_EQ(s21_set.size(), s21_set_test.size());
  EXPECT_EQ(std_set.size(), std_set_test.size());
  EXPECT_EQ(s21_set_test.size(), std_set_test.size());
  EXPECT_EQ(s21_set_test.empty(), std_set_test.empty());

  auto s21_it = s21_set.begin();
  for (auto std_it = std_set.begin(); std_it != std_set.end();
       std_it++, s21_it++) {
    EXPECT_EQ(*s21_it, *std_it);
  }

  auto t_it = s21_set_test.begin();
  for (auto s21_it = s21_set.begin(); s21_it != s21_set.end();
       t_it++, s21_it++) {
    EXPECT_EQ(*s21_it, *t_it);
  }

  auto std_t_it = std_set_test.begin();
  for (auto std_it = std_set.begin(); std_it != std_set.end();
       std_it++, std_t_it++) {
    EXPECT_EQ(*std_it, *std_t_it);
  }
}

TEST(set_test, move_constructor) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_set_test(std::move(s21_set));
  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_set_test(std::move(std_set));

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_test.size(), std_set_test.size());

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set_test.empty(), std_set_test.empty());

  auto s21_it = s21_set_test.begin();
  for (auto std_it = std_set_test.begin(); std_it != std_set_test.end();
       std_it++, s21_it++) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(set_test, empty) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_TRUE(s21_set.empty());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_test, not_empty) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  EXPECT_FALSE(s21_set.empty());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_test, empty_size) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), 0U);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set_test, size) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(s21_set.size(), 3U);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set_test, insert_many) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_exm = {0, 1, 2, 3, 4};

  s21_set.insert_many(4, 0);

  EXPECT_EQ(s21_set.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_set.begin(); s21_it != s21_set.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

TEST(set_test, insert_many_2) {
  s21::set<char> s21_set = {'b', 'f', 'e'};
  s21::set<char> s21_exm = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

  s21_set.insert_many('c', 'g', 'd', 'a');

  EXPECT_EQ(s21_set.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_set.begin(); s21_it != s21_set.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

TEST(set_test, insert_many_3) {
  s21::set<std::string> s21_set = {"Cats", "Are"};
  s21::set<std::string> s21_exm = {"Are", "Best", "Cats", "The", "!"};

  s21_set.insert_many("The", "Best", "!");

  EXPECT_EQ(s21_set.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_set.begin(); s21_it != s21_set.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

TEST(set_test, insert_many_4) {
  s21::set<double> s21_set = {2.13, 1.23};
  s21::set<double> s21_exm = {1.23, 2.13, 3.12, 4.12, 5.12};

  s21_set.insert_many(5.12, 3.12, 4.12);

  EXPECT_EQ(s21_set.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_set.begin(); s21_it != s21_set.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}
