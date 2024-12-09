#include <gtest/gtest.h>

#include <string>

#include "../s21_containers.h"

// Тесты для вектора
TEST(VectorTest, Default) {
  s21::vector<int> s21_vector_int;
  s21::vector<double> s21_vector_double;
  s21::vector<std::string> s21_vector_string;

  EXPECT_EQ(s21_vector_int.size(), 0U);
  EXPECT_EQ(s21_vector_double.size(), 0U);
  EXPECT_EQ(s21_vector_string.size(), 0U);
}

TEST(VectorTest, Parametr) {
  s21::vector<int> s21_vector_int(5);
  s21::vector<double> s21_vector_double(5);
  s21::vector<std::string> s21_vector_string(5);

  EXPECT_EQ(s21_vector_int.size(), 5U);
  EXPECT_EQ(s21_vector_double.size(), 5U);
  EXPECT_EQ(s21_vector_string.size(), 5U);
}

TEST(VectorTest, NegativeParametr) {
  EXPECT_THROW(s21::vector<int> s21_vector_int(-5), std::bad_alloc);
}

TEST(VectorTest, Reserve_Small_Capacity) {
  s21::vector<int> s21_vector_int(10);
  s21::vector<double> s21_vector_double(10);
  s21::vector<std::string> s21_vector_string(10);

  s21_vector_int.reserve(5);
  s21_vector_double.reserve(5);
  s21_vector_string.reserve(5);

  EXPECT_EQ(s21_vector_int.capacity(), 10U);
  EXPECT_EQ(s21_vector_double.capacity(), 10U);
  EXPECT_EQ(s21_vector_string.capacity(), 10U);
}

TEST(VectorTest, ReserveOverflowCapacity) {
  s21::vector<int> s21_vector_int(5);
  s21::vector<double> s21_vector_double(5);
  s21::vector<std::string> s21_vector_string(5);

  s21_vector_int.reserve(20);
  s21_vector_double.reserve(20);
  s21_vector_string.reserve(20);

  EXPECT_EQ(s21_vector_int.capacity(), 20U);
  EXPECT_EQ(s21_vector_double.capacity(), 20U);
  EXPECT_EQ(s21_vector_string.capacity(), 20U);
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> s21_vector_int;
  s21::vector<double> s21_vector_double;
  s21::vector<std::string> s21_vector_string;
  EXPECT_THROW(s21_vector_int.reserve(s21_vector_int.max_size() + 1),
               std::length_error);
  EXPECT_THROW(s21_vector_double.reserve(s21_vector_double.max_size() + 1),
               std::length_error);
  EXPECT_THROW(s21_vector_string.reserve(s21_vector_string.max_size() + 1),
               std::length_error);
}

// Тест на резервирование нулевой ёмкости
TEST(VectorTest, ZeroCapacity) {
  s21::vector<int> s21_vector_int(5);
  s21::vector<double> s21_vector_double(5);
  s21::vector<std::string> s21_vector_string(5);

  s21_vector_int.reserve(0);
  s21_vector_double.reserve(0);
  s21_vector_string.reserve(0);

  EXPECT_EQ(s21_vector_int.capacity(), 5U);
  EXPECT_EQ(s21_vector_double.capacity(), 5U);
  EXPECT_EQ(s21_vector_string.capacity(), 5U);
}

TEST(VectorTest, ReserveMany) {
  s21::vector<int> s21_vector_int(5);
  s21::vector<double> s21_vector_double(5);
  s21::vector<std::string> s21_vector_string(5);

  s21_vector_int.reserve(15);
  s21_vector_double.reserve(15);
  s21_vector_string.reserve(15);

  EXPECT_EQ(s21_vector_int.capacity(), 15U);
  EXPECT_EQ(s21_vector_double.capacity(), 15U);
  EXPECT_EQ(s21_vector_string.capacity(), 15U);

  s21_vector_int.reserve(50);
  s21_vector_double.reserve(50);
  s21_vector_string.reserve(50);

  EXPECT_EQ(s21_vector_int.capacity(), 50U);
  EXPECT_EQ(s21_vector_double.capacity(), 50U);
  EXPECT_EQ(s21_vector_string.capacity(), 50U);
}

// Тест на сохранение данных при увеличении ёмкости
TEST(VectorTest, SaveData) {
  s21::vector<int> s21_vector_int = {1, 2, 3};
  s21::vector<double> s21_vector_double = {1.1, 2.2, 3.3};
  s21::vector<std::string> s21_vector_string = {"1", "2", "3"};

  s21_vector_int.reserve(50);
  s21_vector_double.reserve(50);
  s21_vector_string.reserve(50);

  EXPECT_EQ(s21_vector_int.capacity(), 50U);
  EXPECT_EQ(s21_vector_double.capacity(), 50U);
  EXPECT_EQ(s21_vector_string.capacity(), 50U);

  EXPECT_EQ(s21_vector_int[0], 1);
  EXPECT_EQ(s21_vector_int[1], 2);
  EXPECT_EQ(s21_vector_int[2], 3);
}

TEST(VectorTest, Empty) {
  s21::vector<int> empty_vector_int;
  s21::vector<double> empty_vector_double;
  s21::vector<std::string> empty_vector_string;

  s21::vector<int> non_empty_vector_int = {1, 2, 3};
  s21::vector<double> non_empty_vector_double = {1.1, 2.2, 3.3};
  s21::vector<std::string> non_empty_vector_string = {"1", "2", "3"};

  EXPECT_TRUE(empty_vector_int.empty());
  EXPECT_FALSE(non_empty_vector_int.empty());

  EXPECT_TRUE(empty_vector_double.empty());
  EXPECT_FALSE(non_empty_vector_double.empty());

  EXPECT_TRUE(empty_vector_string.empty());
  EXPECT_FALSE(non_empty_vector_string.empty());
}

TEST(VectorTest, ConstEmpty) {
  const s21::vector<int> empty_vector_int;
  const s21::vector<double> empty_vector_double;
  const s21::vector<std::string> empty_vector_string;

  const s21::vector<int> non_empty_vector_int = {1, 2, 3};
  const s21::vector<double> non_empty_vector_double = {1.1, 2.2, 3.3};
  const s21::vector<std::string> non_empty_vector_string = {"1", "2", "3"};

  EXPECT_TRUE(empty_vector_int.empty());
  EXPECT_FALSE(non_empty_vector_int.empty());

  EXPECT_TRUE(empty_vector_double.empty());
  EXPECT_FALSE(non_empty_vector_double.empty());

  EXPECT_TRUE(empty_vector_string.empty());
  EXPECT_FALSE(non_empty_vector_string.empty());
}

TEST(VectorTest, ShrinkToFitInt) {
  s21::vector<int> vector_int = {1, 2, 3, 4, 5};

  vector_int.reserve(10);

  EXPECT_EQ(vector_int.capacity(), 10U);
  EXPECT_EQ(vector_int.size(), 5U);

  vector_int.shrink_to_fit();
  EXPECT_EQ(vector_int.capacity(), vector_int.size());
  EXPECT_EQ(vector_int.capacity(), 5U);

  EXPECT_EQ(vector_int[0], 1);
  EXPECT_EQ(vector_int[1], 2);
  EXPECT_EQ(vector_int[2], 3);
  EXPECT_EQ(vector_int[3], 4);
  EXPECT_EQ(vector_int[4], 5);
}

TEST(VectorTest, ShrinkToFitDouble) {
  s21::vector<double> vector_double = {1.1, 2.2, 3.3, 4.4, 5.5};
  vector_double.reserve(10);
  EXPECT_EQ(vector_double.capacity(), 10U);
  EXPECT_EQ(vector_double.size(), 5U);

  vector_double.shrink_to_fit();
  EXPECT_EQ(vector_double.capacity(), vector_double.size());
  EXPECT_EQ(vector_double.capacity(), 5U);

  EXPECT_DOUBLE_EQ(vector_double[0], 1.1);
  EXPECT_DOUBLE_EQ(vector_double[1], 2.2);
  EXPECT_DOUBLE_EQ(vector_double[2], 3.3);
  EXPECT_DOUBLE_EQ(vector_double[3], 4.4);
  EXPECT_DOUBLE_EQ(vector_double[4], 5.5);
}

TEST(VectorTest, ShrinkToFitString) {
  s21::vector<std::string> vector_string = {"1", "2", "3", "4", "5"};
  vector_string.reserve(10);
  EXPECT_EQ(vector_string.capacity(), 10U);
  EXPECT_EQ(vector_string.size(), 5U);

  vector_string.shrink_to_fit();
  EXPECT_EQ(vector_string.capacity(), vector_string.size());
  EXPECT_EQ(vector_string.capacity(), 5U);

  EXPECT_EQ(vector_string[0], "1");
  EXPECT_EQ(vector_string[1], "2");
  EXPECT_EQ(vector_string[2], "3");
  EXPECT_EQ(vector_string[3], "4");
  EXPECT_EQ(vector_string[4], "5");
}

// Тестирование метода at() для типа int
TEST(VectorTest, AtInt) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.at(2), 3);

  // Проверка выброса исключения при выходе за границы
  EXPECT_THROW(vec.at(3), std::out_of_range);
  EXPECT_THROW(vec.at(10), std::out_of_range);
}

// Тестирование метода at() для типа double
TEST(VectorTest, AtDouble) {
  s21::vector<double> vec = {1.1, 2.2, 3.3};
  EXPECT_DOUBLE_EQ(vec.at(0), 1.1);
  EXPECT_DOUBLE_EQ(vec.at(1), 2.2);
  EXPECT_DOUBLE_EQ(vec.at(2), 3.3);

  // Проверка выброса исключения при выходе за границы
  EXPECT_THROW(vec.at(3), std::out_of_range);
  EXPECT_THROW(vec.at(10), std::out_of_range);
}

// Тестирование метода at() для типа std::string
TEST(VectorTest, AtString) {
  s21::vector<std::string> vec = {"one", "two", "three"};
  EXPECT_EQ(vec.at(0), "one");
  EXPECT_EQ(vec.at(1), "two");
  EXPECT_EQ(vec.at(2), "three");

  // Проверка выброса исключения при выходе за границы
  EXPECT_THROW(vec.at(3), std::out_of_range);
  EXPECT_THROW(vec.at(10), std::out_of_range);
}

TEST(VectorTest, ConstAt) {
  const s21::vector<int> vec = {1, 2, 3};
  const s21::vector<double> vec_d = {1.1, 2.2, 3.3};
  const s21::vector<std::string> vec_s = {"one", "two", "three"};

  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.at(2), 3);

  EXPECT_DOUBLE_EQ(vec_d.at(0), 1.1);
  EXPECT_DOUBLE_EQ(vec_d.at(1), 2.2);
  EXPECT_DOUBLE_EQ(vec_d.at(2), 3.3);

  EXPECT_EQ(vec_s.at(0), "one");
  EXPECT_EQ(vec_s.at(1), "two");
  EXPECT_EQ(vec_s.at(2), "three");

  // Проверка выброса исключения при выходе за границы
  EXPECT_THROW(vec.at(3), std::out_of_range);
  EXPECT_THROW(vec.at(10), std::out_of_range);

  EXPECT_THROW(vec_d.at(3), std::out_of_range);
  EXPECT_THROW(vec_d.at(10), std::out_of_range);

  EXPECT_THROW(vec_s.at(3), std::out_of_range);
  EXPECT_THROW(vec_s.at(10), std::out_of_range);
}

TEST(VectorTest, OperatorBracketInt) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);

  // Проверка изменения значений
  vec[0] = 10;
  vec[1] = 20;
  vec[2] = 30;
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec[2], 30);
}

// Тестирование оператора [] для типа double
TEST(VectorTest, OperatorBracketDouble) {
  s21::vector<double> vec = {1.1, 2.2, 3.3};
  EXPECT_DOUBLE_EQ(vec[0], 1.1);
  EXPECT_DOUBLE_EQ(vec[1], 2.2);
  EXPECT_DOUBLE_EQ(vec[2], 3.3);

  // Проверка изменения значений
  vec[0] = 10.1;
  vec[1] = 20.2;
  vec[2] = 30.3;
  EXPECT_DOUBLE_EQ(vec[0], 10.1);
  EXPECT_DOUBLE_EQ(vec[1], 20.2);
  EXPECT_DOUBLE_EQ(vec[2], 30.3);
}

// Тестирование оператора [] для типа std::string
TEST(VectorTest, OperatorBracketString) {
  s21::vector<std::string> vec = {"one", "two", "three"};
  EXPECT_EQ(vec[0], "one");
  EXPECT_EQ(vec[1], "two");
  EXPECT_EQ(vec[2], "three");

  // Проверка изменения значений
  vec[0] = "ten";
  vec[1] = "twenty";
  vec[2] = "thirty";
  EXPECT_EQ(vec[0], "ten");
  EXPECT_EQ(vec[1], "twenty");
  EXPECT_EQ(vec[2], "thirty");
}

TEST(VectorTest, ConstSubscriptOperator) {
  // Создаем const векторы для проверки const operator[]
  const s21::vector<int> vector_int = {10, 20, 30};
  const s21::vector<double> vector_double = {1.1, 2.2, 3.3};
  const s21::vector<std::string> vector_string = {"one", "two", "three"};

  // Проверяем доступ к элементам для каждого типа данных
  EXPECT_EQ(vector_int[0], 10);
  EXPECT_EQ(vector_int[1], 20);
  EXPECT_EQ(vector_int[2], 30);

  EXPECT_DOUBLE_EQ(vector_double[0], 1.1);
  EXPECT_DOUBLE_EQ(vector_double[1], 2.2);
  EXPECT_DOUBLE_EQ(vector_double[2], 3.3);

  EXPECT_EQ(vector_string[0], "one");
  EXPECT_EQ(vector_string[1], "two");
  EXPECT_EQ(vector_string[2], "three");
}

TEST(VectorTest, Front) {
  s21::vector<int> vector_int = {1, 2, 3};
  s21::vector<double> vector_double = {1.1, 2.2, 3.3};
  s21::vector<std::string> vector_string = {"first", "second", "third"};

  EXPECT_EQ(vector_int.front(), 1);
  EXPECT_DOUBLE_EQ(vector_double.front(), 1.1);
  EXPECT_EQ(vector_string.front(), "first");

  s21::vector<int> empty_vector_int;
  EXPECT_THROW(empty_vector_int.front(), std::logic_error);
  s21::vector<double> empty_vector_double;
  EXPECT_THROW(empty_vector_double.front(), std::logic_error);
  s21::vector<std::string> empty_vector_string;
  EXPECT_THROW(empty_vector_string.front(), std::logic_error);
}

TEST(VectorTest, Back) {
  s21::vector<int> vector_int = {1, 2, 3};
  s21::vector<double> vector_double = {1.1, 2.2, 3.3};
  s21::vector<std::string> vector_string = {"first", "second", "third"};

  EXPECT_EQ(vector_int.back(), 3);
  EXPECT_DOUBLE_EQ(vector_double.back(), 3.3);
  EXPECT_EQ(vector_string.back(), "third");

  s21::vector<int> empty_vector_int;
  EXPECT_THROW(empty_vector_int.back(), std::logic_error);
  s21::vector<double> empty_vector_double;
  EXPECT_THROW(empty_vector_double.back(), std::logic_error);
  s21::vector<std::string> empty_vector_string;
  EXPECT_THROW(empty_vector_string.back(), std::logic_error);
}

TEST(VectorTest, Data) {
  s21::vector<int> vector_int = {10, 20, 30};
  s21::vector<double> vector_double = {1.1, 2.2, 3.3};
  s21::vector<std::string> vector_string = {"one", "two", "three"};

  EXPECT_EQ(*vector_int.data(), 10);
  EXPECT_DOUBLE_EQ(*vector_double.data(), 1.1);
  EXPECT_EQ(*vector_string.data(), "one");

  // изменяем значения через указатель
  *vector_int.data() = 15;
  *(vector_int.data() + 1) = 25;
  EXPECT_EQ(vector_int[0], 15);
  EXPECT_EQ(vector_int[1], 25);

  *vector_double.data() = 1.5;
  *(vector_double.data() + 2) = 3.5;
  EXPECT_DOUBLE_EQ(vector_double[0], 1.5);
  EXPECT_DOUBLE_EQ(vector_double[2], 3.5);

  *vector_string.data() = "first";
  *(vector_string.data() + 2) = "last";
  EXPECT_EQ(vector_string[0], "first");
  EXPECT_EQ(vector_string[2], "last");

  s21::vector<int> empty_vector_int;
  EXPECT_EQ(empty_vector_int.data(), nullptr);
}

TEST(VectorTest, ConstData) {
  const s21::vector<int> vector_int = {10, 20, 30};
  const s21::vector<double> vector_double = {1.1, 2.2, 3.3};
  const s21::vector<std::string> vector_string = {"one", "two", "three"};

  EXPECT_EQ(*vector_int.data(), 10);
  EXPECT_DOUBLE_EQ(*vector_double.data(), 1.1);
  EXPECT_EQ(*vector_string.data(), "one");

  EXPECT_EQ(*(vector_int.data() + 1), 20);
  EXPECT_EQ(*(vector_int.data() + 2), 30);
  EXPECT_DOUBLE_EQ(*(vector_double.data() + 1), 2.2);
  EXPECT_DOUBLE_EQ(*(vector_double.data() + 2), 3.3);
  EXPECT_EQ(*(vector_string.data() + 1), "two");
  EXPECT_EQ(*(vector_string.data() + 2), "three");

  // Проверка, что data() возвращает nullptr для пустого вектора
  const s21::vector<int> empty_vector_int;
  EXPECT_EQ(empty_vector_int.data(), nullptr);
}

TEST(VectorTest, BeginEndInt) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(*vec.begin(), 1);
  EXPECT_EQ(*(vec.end() - 1), 5);

  // Проверка итерации по элементам через begin() и end()
  vec[0] = 0;
  vec[4] = 6;

  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 6);
}

TEST(VectorTest, BeginEndDouble) {
  s21::vector<double> vec = {1.1, 2.2, 3.3};

  EXPECT_DOUBLE_EQ(*vec.begin(), 1.1);
  EXPECT_DOUBLE_EQ(*(vec.end() - 1), 3.3);

  // Проверка итерации и изменения значений
  vec[0] = 0.1;
  vec[2] = 4.4;

  EXPECT_DOUBLE_EQ(vec[0], 0.1);
  EXPECT_DOUBLE_EQ(vec[1], 2.2);
  EXPECT_DOUBLE_EQ(vec[2], 4.4);
}

TEST(VectorTest, BeginEndString) {
  s21::vector<std::string> vec = {"one", "two", "three"};

  EXPECT_EQ(*vec.begin(), "one");
  EXPECT_EQ(*(vec.end() - 1), "three");

  // Проверка итерации и изменения значений
  vec[0] = "one!";
  vec[2] = "three!";

  EXPECT_EQ(vec[0], "one!");
  EXPECT_EQ(vec[1], "two");
  EXPECT_EQ(vec[2], "three!");
}

TEST(VectorTest, Clear) {
  s21::vector<int> vec_int = {1, 2, 3, 4, 5};
  size_t initial_capacity_int = vec_int.capacity();
  vec_int.clear();
  EXPECT_EQ(vec_int.size(), 0U);  // Размер должен быть 0 после очистки
  EXPECT_EQ(vec_int.capacity(),
            initial_capacity_int);  // Ёмкость остаётся прежней

  s21::vector<double> vec_double = {1.1, 2.2, 3.3, 4.4, 5.5};
  size_t initial_capacity_double = vec_double.capacity();
  vec_double.clear();
  EXPECT_EQ(vec_double.size(), 0U);
  EXPECT_EQ(vec_double.capacity(), initial_capacity_double);

  s21::vector<std::string> vec_string = {"one", "two", "three", "four", "five"};
  size_t initial_capacity_string = vec_string.capacity();
  vec_string.clear();
  EXPECT_EQ(vec_string.size(), 0U);
  EXPECT_EQ(vec_string.capacity(), initial_capacity_string);
}

TEST(VectorTest, Insert) {
  s21::vector<int> vec_int = {1, 2, 4, 5};
  auto pos_int = vec_int.insert(vec_int.begin() + 2,
                                3);  // Вставляем "3" на позицию с индексом 2
  EXPECT_EQ(*pos_int, 3);
  EXPECT_EQ(vec_int.size(), 5U);
  EXPECT_EQ(vec_int[0], 1);
  EXPECT_EQ(vec_int[1], 2);
  EXPECT_EQ(vec_int[2], 3);
  EXPECT_EQ(vec_int[3], 4);
  EXPECT_EQ(vec_int[4], 5);

  s21::vector<double> vec_double = {1.1, 2.2, 4.4, 5.5};
  auto pos_double = vec_double.insert(
      vec_double.begin() + 2, 3.3);  // Вставляем "3.3" на позицию с индексом 2
  EXPECT_EQ(*pos_double, 3.3);
  EXPECT_EQ(vec_double.size(), 5U);
  EXPECT_EQ(vec_double[0], 1.1);
  EXPECT_EQ(vec_double[1], 2.2);
  EXPECT_EQ(vec_double[2], 3.3);
  EXPECT_EQ(vec_double[3], 4.4);
  EXPECT_EQ(vec_double[4], 5.5);

  s21::vector<std::string> vec_string = {"one", "two", "four", "five"};
  auto pos_string =
      vec_string.insert(vec_string.begin() + 2,
                        "three");  // Вставляем "three" на позицию с индексом 2
  EXPECT_EQ(*pos_string, "three");
  EXPECT_EQ(vec_string.size(), 5U);
  EXPECT_EQ(vec_string[0], "one");
  EXPECT_EQ(vec_string[1], "two");
  EXPECT_EQ(vec_string[2], "three");
  EXPECT_EQ(vec_string[3], "four");
  EXPECT_EQ(vec_string[4], "five");
}

TEST(VectorTest, InsertOut) {
  s21::vector<int> vec = {1, 2, 3};

  EXPECT_THROW(vec.insert(vec.end() + 1, 777),
               std::out_of_range);  // Попытка вставить за пределами вектора
  EXPECT_THROW(vec.insert(vec.begin() - 1, 777),
               std::out_of_range);  // Попытка вставить до начала вектора
}

TEST(VectorTest, EraseInt) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  auto it = vec.begin() + 2;  // Указатель на третий элемент (значение 3)
  vec.erase(it);

  EXPECT_EQ(vec.size(), 4U);  // Размер вектора должен уменьшиться
  EXPECT_EQ(vec[0], 1);  // Первый элемент остается
  EXPECT_EQ(vec[1], 2);  // Второй элемент остается
  EXPECT_EQ(vec[2], 4);  // Третий элемент теперь 4 (3 удален)
  EXPECT_EQ(vec[3], 5);  // Четвертый элемент остается
}

TEST(VectorTest, EraseDouble) {
  s21::vector<double> vec = {1.1, 2.2, 3.3, 4.4, 5.5};

  auto it = vec.begin() + 1;  // Указатель на второй элемент (значение 2.2)
  vec.erase(it);

  EXPECT_EQ(vec.size(), 4U);  // Размер вектора должен уменьшиться
  EXPECT_EQ(vec[0], 1.1);  // Первый элемент остается
  EXPECT_EQ(vec[1], 3.3);  // Второй элемент теперь 3.3 (2.2 удален)
  EXPECT_EQ(vec[2], 4.4);  // Третий элемент остается
  EXPECT_EQ(vec[3], 5.5);  // Четвертый элемент остается
}

TEST(VectorTest, EraseString) {
  s21::vector<std::string> vec = {"one", "two", "three", "four", "five"};

  auto it =
      vec.begin() + 3;  // Указатель на четвертый элемент (значение "four")
  vec.erase(it);

  EXPECT_EQ(vec.size(), 4U);  // Размер вектора должен уменьшиться
  EXPECT_EQ(vec[0], "one");    // Первый элемент остается
  EXPECT_EQ(vec[1], "two");    // Второй элемент остается
  EXPECT_EQ(vec[2], "three");  // Третий элемент остается
  EXPECT_EQ(vec[3], "five");  // Четвертый элемент остается
}

TEST(VectorTest, EraseOut) {
  s21::vector<int> vec = {1, 2, 3};

  EXPECT_THROW(vec.erase(vec.end() + 1),
               std::out_of_range);  // Попытка удалить за пределами вектора
  EXPECT_THROW(vec.erase(vec.begin() - 1),
               std::out_of_range);  // Попытка удалить до начала вектора
}

TEST(VectorTest, PushBack) {
  s21::vector<int> vec = {1, 2, 3};

  vec.push_back(4);
  EXPECT_EQ(vec.size(), 4U);  // Размер вектора увеличивается на 1
  EXPECT_EQ(vec[3], 4);  // Последний элемент получает значение 4

  s21::vector<double> vec_double = {1.1, 2.2, 3.3};
  vec_double.push_back(4.4);
  EXPECT_EQ(vec_double.size(), 4U);  // Размер вектора увеличивается на 1
  EXPECT_EQ(vec_double[3], 4.4);  // Последний элемент получает значение 4

  s21::vector<std::string> vec_string = {"one", "two", "three"};
  vec_string.push_back("four");
  EXPECT_EQ(vec_string.size(), 4U);  // Размер вектора увеличивается на 1
  EXPECT_EQ(vec_string[3], "four");  // Последний элемент получает значение 4
}

TEST(VectorTest, PopBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2U);  // Размер вектора уменьшается на 1
  EXPECT_EQ(vec[1], 2);  // Второй элемент остается

  s21::vector<double> vec_double = {1.1, 2.2, 3.3};
  vec_double.pop_back();
  EXPECT_EQ(vec_double.size(), 2U);  // Размер вектора уменьшается на 1
  EXPECT_EQ(vec_double[1], 2.2);  // Второй элемент остается

  s21::vector<std::string> vec_string = {"one", "two", "three"};
  vec_string.pop_back();
  EXPECT_EQ(vec_string.size(), 2U);  // Размер вектора уменьшается на 1
  EXPECT_EQ(vec_string[1], "two");  // Второй элемент остается
}

TEST(VectorTest, PopBackOut) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.pop_back(), std::logic_error);

  s21::vector<double> vec_double;
  EXPECT_THROW(vec_double.pop_back(), std::logic_error);

  s21::vector<std::string> vec_string;
  EXPECT_THROW(vec_string.pop_back(), std::logic_error);
}

TEST(VectorTest, SwapInt) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = {4, 5, 6};

  EXPECT_EQ(vec1.size(), 3U);
  EXPECT_EQ(vec2.size(), 3U);
  EXPECT_EQ(vec1[0], 1);
  EXPECT_EQ(vec2[0], 4);

  vec1.swap(vec2);

  EXPECT_EQ(vec1.size(), 3U);
  EXPECT_EQ(vec2.size(), 3U);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec2[0], 1);
}

TEST(VectorTest, SwapDouble) {
  s21::vector<double> vec1 = {1.1, 2.2, 3.3};
  s21::vector<double> vec2 = {4.4, 5.5, 6.6};

  EXPECT_EQ(vec1.size(), 3U);
  EXPECT_EQ(vec2.size(), 3U);
  EXPECT_EQ(vec1[0], 1.1);
  EXPECT_EQ(vec2[0], 4.4);

  vec1.swap(vec2);

  EXPECT_EQ(vec1.size(), 3U);
  EXPECT_EQ(vec2.size(), 3U);
  EXPECT_EQ(vec1[0], 4.4);
  EXPECT_EQ(vec2[0], 1.1);
}

TEST(VectorTest, SwapEmpty) {
  s21::vector<int> vec1;
  s21::vector<int> vec2 = {1, 2, 3};

  EXPECT_EQ(vec1.size(), 0U);
  EXPECT_EQ(vec2.size(), 3U);

  vec1.swap(vec2);

  EXPECT_EQ(vec1.size(), 3U);
  EXPECT_EQ(vec2.size(), 0U);
}

TEST(VectorTest, SwapSelf) {
  s21::vector<int> vec = {1, 2, 3};

  vec.swap(vec);

  EXPECT_EQ(vec.size(), 3U);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}
