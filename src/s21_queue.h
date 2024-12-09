#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_
#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // Конструктор по умолчанию
  queue() : list() {}

  // Конструктор списка инициализации, создает список, инициализированный с
  // помощью std::initializer_list
  queue(std::initializer_list<value_type> const &items) : list(items) {}

  // Конструктор копирования
  queue(const queue &q) : list(q.list) {}

  // Конструктор перемещения
  queue(queue &&q) : list(std::move(q.list)) {}

  // Деструктор
  ~queue() = default;

  queue &operator=(const queue &q) {
    list = q.list;

    return *this;
  }

  // Element access

  // Доступ к первому константному элементу
  const_reference front() const noexcept { return list.front(); }

  // Доступ к последнему константному элементу
  const_reference back() const noexcept { return list.back(); }

  // Queue Capacity

  // Проверяет, пуст ли контейнер
  bool empty() const noexcept { return list.empty(); }

  // Возвращает количество элементов
  size_type size() const noexcept { return list.size(); }

  // Modifiers

  // Вставляет элемент в конец
  void push(const_reference value) { list.push_back(value); }

  // Удаляет первый элемент
  void pop() { list.pop_front(); }

  // Меняет содержимое местами
  void swap(queue &other) { list.swap(other.list); }

  // Добавляет новые элементы в конец контейнера
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    list.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> list;
};
}  // namespace s21

#endif