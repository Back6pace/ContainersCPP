#ifndef SRC_S21_MULTISET_H
#define SRC_S21_MULTISET_H

#include "s21_tree.h"

/*
    Реализация мультимножества
    Мультимножество - это ассоциативный контейнер, который следует логике
   множества, но позволяет хранить идентичные элементы. Этот контейнер
   отличается от списка или вектора тем, что элементы в мультимножестве
   сортируются мгновенно, также как в множестве. Но, как и в множестве,
   мультимножество не позволяет обращаться к элементу по его индексу, а требует
   обращаться к его значению, которое может повторяться в мультимножестве.
*/

namespace s21 {
template <typename Key>
class multiset {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  // Конструктор по умолчанию, создает пустое множество
  multiset() : tree_() {}

  // Конструктор списка инициализации, создает множество, инициализированное с
  // помощью std::initializer_list
  multiset(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert_duplicate(it);
    }
  }

  // Конструктор копирования
  multiset(const multiset& s) : tree_(s.tree_) {}

  // Конструктор перемещения
  multiset(multiset&& s) : tree_(std::move(s.tree_)) {}

  // Деструктор
  ~multiset() = default;

  // Перегрузка оператора присваивания для копирования объекта
  multiset& operator=(const multiset& other) {
    tree_ = other.tree_;
    return *this;
  }

  // Перегрузка оператора присваивания для перемещения объекта
  multiset& operator=(multiset&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  // Вставляет узел и возвращает итератор туда, где находится элемент в
  // контейнере
  iterator insert(const_reference key) { return tree_.insert_duplicate(key); }

  // Удаляет элемент в позиции pos
  void erase(iterator pos) { tree_.erase(pos); }

  // Проверяет, пуст ли контейнер
  bool empty() const noexcept { return tree_.empty(); }

  // Возвращает количество элементов
  size_type size() const noexcept { return tree_.size(); }

  // Возвращает максимально возможное количество элементов
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Очищает содержимое
  void clear() { tree_.clear(); }

  // Меняет содержимое местами
  void swap(multiset& other) { tree_.swap(other.tree_); }

  // Объединяет узлы из другого контейнера
  void merge(multiset& other) { tree_.merge_duplicates(other.tree_); }

  // Находит элемент с заданным ключом
  iterator find(const_reference key) noexcept { return tree_.find(key); }

  // Находит элемент с заданным ключом для константного мультимножества
  const_iterator find(const_reference key) const noexcept {
    return tree_.find(key);
  }

  // Проверяет, содержит ли контейнер элемент с заданным ключом
  bool contains(const_reference key) const noexcept {
    return tree_.contains(key);
  }

  // Возвращает итератор в начало
  iterator begin() noexcept { return tree_.begin(); }

  // Возвращает итератор в начало для константного мультимножества
  const_iterator begin() const noexcept { return tree_.begin(); }

  // Возвращает итератор в конец
  iterator end() noexcept { return tree_.end(); }

  // Возвращает итератор в конец для константного мультимножества
  const_iterator end() const noexcept { return tree_.end(); }

  // Возвращает количество элементов, совпадающих с заданным ключом
  size_type count(const_reference key) const noexcept {
    return tree_.count(key);
  }

  // Возвращает диапазон элементов, совпадающих с заданным ключом
  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    return tree_.equal_range(key);
  }

  // Возвращает итератор к первому элементу, не меньшему заданному ключу
  iterator lower_bound(const_reference key) noexcept {
    return tree_.lower_bound(key);
  }

  // Возвращает итератор к первому элементу, большему заданного ключа
  iterator upper_bound(const_reference key) noexcept {
    return tree_.upper_bound(key);
  }

  // Возвращает диапазон элементов, совпадающих с заданным ключом
  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const noexcept {
    return tree_.equal_range(key);
  }

  // Возвращает итератор к первому элементу, не меньшему заданному ключу для
  // константного объекта
  const_iterator lower_bound(const_reference key) const noexcept {
    return tree_.lower_bound(key);
  }

  // Возвращает итератор к первому элементу, большему заданного ключа для
  // константного объекта
  const_iterator upper_bound(const_reference key) const noexcept {
    return tree_.upper_bound(key);
  }

  // Вставляет новые элементы в контейнер
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_.insert_many_duplicate(std::forward<Args>(args)...);
  }

 private:
  // Переменная красно-черного дерева
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_MULTISET_H
