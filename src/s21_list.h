#ifndef S21_LIST_H_
#define S21_LIST_H_
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
  // --------- Member types ---------
  class ListIterator;
  class ListConstIterator;
  class ListNode;
  // --------- PUBLIC ---------
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // --------- Constructors & Destructors ---------
  list() {
    size_ = 0;
    head_ = new ListNode;
  }

  explicit list(size_type count) : list() {
    for (size_type i = 0; i < count; i++) {
      push_back(value_type{});
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (auto& item : items) {
      push_back(item);
    }
  }

  list(const list& other) : list() { *this = other; }

  list(list&& other) : list() { *this = std::move(other); }

  ~list() {
    clear();
    delete head_;
  }

  // --------- Public methods ---------

  list& operator=(const list& other) {
    if (this != &other) {
      size_type count = other.size_ < size_ ? other.size_ : size_;
      iterator iter = begin();
      const_iterator iter_other = other.begin();
      while (count > 0) {
        *iter++ = *iter_other++;
        count--;
      }
      while (other.size_ < size_) {
        pop_back();
      }
      while (other.size_ > size_) {
        push_back(*iter_other++);
      }
    }
    return *this;
  }

  list& operator=(list&& other) {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }
  const_reference front() const noexcept { return head_->next_->data_; }

  const_reference back() const noexcept { return head_->prev_->data_; }

  iterator begin() noexcept { return iterator(head_->next_); }
  const_iterator begin() const noexcept { return const_iterator(head_->next_); }
  iterator end() noexcept { return iterator(head_); }
  const_iterator end() const noexcept { return const_iterator(head_); }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const {
    return ((std::numeric_limits<size_type>::max() / 2) / sizeof(ListNode));
  }

  void clear() noexcept {
    while (!empty()) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const value_type& value) {
    ListNode* newNode = new ListNode;
    newNode->data_ = value;
    newNode->next_ = pos.currentNode_;
    newNode->prev_ = pos.currentNode_->prev_;

    if (pos.currentNode_->prev_ != nullptr) {
      pos.currentNode_->prev_->next_ = newNode;
    }
    pos.currentNode_->prev_ = newNode;
    size_++;
    return iterator(newNode);
  }

  void erase(iterator pos) {
    if (pos.currentNode_ != head_) {
      pos.currentNode_->prev_->next_ = pos.currentNode_->next_;
      pos.currentNode_->next_->prev_ = pos.currentNode_->prev_;

      delete pos.currentNode_;
      size_--;
    }
  }

  void push_back(const_reference value) { insert(end(), value); }
  void pop_back() {
    if (empty()) {
      throw std::out_of_range("list is empty");
    }
    erase(--end());
  }

  void push_front(const_reference value) { insert(begin(), value); }
  void pop_front() {
    if (empty()) {
      throw std::out_of_range("list is empty");
    }
    erase(begin());
  }
  void swap(list& other) {
    if (this != &other) {
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
    }
  }

  void merge(list& other) {
    if (this != &other) {
      iterator iter = begin();
      iterator iter_other = other.begin();

      while (iter != end() && iter_other != other.end()) {
        if (*iter_other < *iter) {
          iterator temp = iter_other;
          ++iter_other;
          insert(iter, *temp);
          other.erase(temp);
        } else {
          ++iter;
        }
      }
      if (iter_other != other.end()) {
        splice(end(), other);
      }
    }
  }

  void splice(const_iterator pos, list& other) noexcept {
    if (!other.empty()) {
      iterator iter_begin = other.begin();
      iterator iter_end = --other.end();
      pos.currentNode_->prev_->next_ = iter_begin.currentNode_;
      iter_begin.currentNode_->prev_ = pos.currentNode_->prev_;

      pos.currentNode_->prev_ = iter_end.currentNode_;
      iter_end.currentNode_->next_ = pos.currentNode_;

      size_ += other.size_;
      other.size_ = 0;
      other.head_->next_ = other.head_;
      other.head_->prev_ = other.head_;
    }
  }

  void reverse() {
    iterator iter = begin();
    iterator iter_final = iter;
    do {
      std::swap(iter.currentNode_->next_, iter.currentNode_->prev_);
      ++iter;
    } while (iter != iter_final);
  }
  void unique() {
    if (size_ > 1) {
      iterator iter_begin = begin();
      iterator iter = iter_begin;
      ++iter;
      iterator iter_end = end();
      while (iter != iter_end) {
        if (*iter == *iter_begin) {
          erase(iter);
          iter = iter_begin;
        } else {
          ++iter_begin;
        }
        ++iter;
      }
    }
  }

  void sort() {
    if (size_ > 1) {
      qsort(begin(), size_);
    }
  }

  void qsort(iterator iter_begin, size_type size) {
    if (size > 1) {
      long long i = 0;
      long long j = size - 1;
      iterator iter_i = iter_begin;
      iterator iter_j = iter_begin;
      for (long long k = 0; k < j; k++, ++iter_j) {
      }
      iterator iter_pivot = iter_begin;
      for (size_type k = 0; k < size / 2; k++, ++iter_pivot) {
      }
      value_type pivot = *iter_pivot;
      do {
        while (*iter_i < pivot) {
          ++i;
          ++iter_i;
        }
        while (*iter_j > pivot) {
          --j;
          --iter_j;
        }
        if (i <= j) {
          std::swap(*iter_i, *iter_j);
          ++i;
          ++iter_i;
          --j;
          --iter_j;
        }
      } while (i <= j);
      if (j > 0) {
        qsort(iter_begin, j + 1);
      }
      if (i < static_cast<long long>(size)) {
        qsort(iter_i, size - i);
      }
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator iter(pos.currentNode_);
    for (auto elem : {std::forward<Args>(args)...}) {
      insert(iter, elem);
    }
    return iter;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(end(), std::forward<Args>(args)...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    insert_many(begin(), std::forward<Args>(args)...);
  }
  // --------- PRIVATE ---------
 private:
  // --------- Node class ---------

  class ListNode {
   public:
    value_type data_;
    ListNode* next_;
    ListNode* prev_;
    ListNode() {
      data_ = value_type{};
      next_ = this;
      prev_ = this;
    }
  };

  class ListIterator {
   private:
    ListNode* currentNode_;
    friend class list;

   public:
    ListIterator() { currentNode_ = nullptr; }
    ListIterator(ListNode* node) { currentNode_ = node; }
    ListIterator(const iterator& other) { currentNode_ = other.currentNode_; }

    // --------- Operators ---------
    iterator& operator=(const iterator& other) {
      if (this != &other) {
        currentNode_ = other.currentNode_;
      }
      return *this;
    }

    iterator& operator++() {
      currentNode_ = currentNode_->next_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      currentNode_ = currentNode_->prev_;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    reference operator*() { return currentNode_->data_; }

    bool operator==(const iterator& other) const {
      return currentNode_ == other.currentNode_;
    }

    bool operator!=(const iterator& other) const {
      return currentNode_ != other.currentNode_;
    }
  };

  class ListConstIterator {
   private:
    ListNode* currentNode_;
    friend list;

    friend bool operator==(const const_iterator& iter1,
                           const const_iterator& iter2) {
      return iter1.currentNode_ == iter2.currentNode_;
    }
    friend bool operator!=(const const_iterator& iter1,
                           const const_iterator& iter2) {
      return iter1.currentNode_ != iter2.currentNode_;
    }

   public:
    ListConstIterator() { currentNode_ = nullptr; }
    ListConstIterator(ListNode* node) { currentNode_ = node; }
    ListConstIterator(const const_iterator& other) {
      currentNode_ = other.currentNode_;
    }
    ListConstIterator(const ListIterator& it) {
      currentNode_ = it.currentNode_;
    }
    const_reference operator*() { return currentNode_->data_; }

    const_iterator& operator=(const const_iterator& other) {
      if (this != &other) {
        currentNode_ = other.currentNode_;
      }
      return *this;
    }

    const_iterator& operator++() {
      currentNode_ = currentNode_->next_;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator& operator--() {
      currentNode_ = currentNode_->prev_;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
  };
  // --------- Private fields ---------
  size_type size_;
  ListNode* head_;
};
}  // namespace s21

#endif