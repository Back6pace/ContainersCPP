#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, std::size_t S>
class array {
  // -------- Member type --------
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = T *;
  using const_iterator = const T *;

 public:
  array() {}
  array(std::initializer_list<value_type> const &items) {
    if (S < items.size()) {
      throw std::out_of_range("Out of range. To many args");
    }
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
  }

  array(const array &other) {
    for (size_type i = 0; i < S; i++) {
      arr[i] = other.arr[i];
    }
  }

  array(array &&other) { operator=(std::move(other)); }

  ~array() {}

  array &operator=(array &&other) {
    if (this != &other) {
      for (size_type i = 0; i < S; i++) {
        arr[i] = std::move(other[i]);
      }
    }
    return *this;
  }

  // -------- Array Element access --------
  reference at(size_type pos) {
    if (pos >= S) {
      throw std::out_of_range("Index is out of range");
    }
    return arr[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= S) {
      throw std::out_of_range("Index is out of range");
    }
    return arr[pos];
  }

  reference operator[](size_type pos) { return arr[pos]; }
  const_reference operator[](size_type pos) const { return arr[pos]; }
  const_reference front() const {
    if (S == 0) {
      throw std::logic_error(
          "Cannot access front element because array is empty");
    }
    return arr[0];
  }
  const_reference back() const {
    if (S == 0) {
      throw std::logic_error(
          "Cannot access back element because array is empty");
    }
    return arr[S - 1];
  }
  iterator data() noexcept { return arr; }
  const_iterator data() const noexcept { return arr; }

  // -------- Array Iterators --------

  iterator begin() noexcept { return arr; }
  const_iterator begin() const noexcept { return arr; }
  iterator end() noexcept { return arr + S; }
  const_iterator end() const noexcept { return arr + S; }

  // -------- Array Capacity --------
  bool empty() const noexcept { return begin() == end(); }
  size_type size() const noexcept { return S; }
  size_type max_size() const noexcept { return S; }

  // -------- Array Modifiers --------
  void swap(array &other) { std::swap(arr, other.arr); }
  void fill(const_reference value) {
    for (size_type i = 0; i < S; i++) {
      arr[i] = value;
    }
  }

 private:
  value_type arr[S] = {};
};
}  // namespace s21

#endif