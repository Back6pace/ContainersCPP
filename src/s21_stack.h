#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class stack {
  // -------- Stack Member type ----------
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 public:
  // -------- Stack Member functions ----------
  stack() : list_() {}
  stack(std::initializer_list<value_type> const& items) : list_(items) {}
  stack(const stack& s) : list_(s.list_) {}
  stack(stack&& s) : list_(std::move(s.list_)) {}
  ~stack() = default;

  stack& operator=(const stack& s) {
    list_ = s.list_;
    return *this;
  }

  stack& operator=(stack&& s) {
    list_ = std::move(s.list_);
    return *this;
  }

  // -------- Stack Element access --------
  //   reference top() noexcept { return list_.back(); }
  const_reference top() const noexcept { return list_.back(); }

  // -------- Stack Capacity -----------
  bool empty() const noexcept { return list_.empty(); }
  size_type size() const noexcept { return list_.size(); }

  // -------- Stack Modifiers -----------
  void push(const_reference value) { list_.push_back(value); }
  void pop() { list_.pop_back(); }
  void swap(stack& other) { list_.swap(other.list_); }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    list_.insert_many_front(std::forward<Args>(args)...);
  }

 private:
  s21::list<value_type> list_;
};
}  // namespace s21

#endif