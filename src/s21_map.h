#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "s21_tree.h"

/*
    Реализация словаря
    Словарь (map) - это ассоциативный контейнер, который хранит пары
   ключ-значение, отсортированные в порядке возрастания ключей. Это означает,
   что каждый элемент ассоциирован с некоторым уникальным ключом, и его позиция
   в словаре определяется его ключом. Словари пригодны, когда нужно
   ассоциировать элементы с каким-то другим значением (не индексом). Например,
   предприятие закупает оборудование, и каждый предмет должен быть закуплен
   более одного раза. В этом случае удобно использовать словарь с
   идентификатором позиции - парой объем покупки.
*/

namespace s21 {
template <typename Key, typename T>
class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  // Конструктор по умолчанию, создает пустой словарь
  map() : tree_() {}

  // Конструктор списка инициализации, создает словарь, инициализированный с
  // помощью std::initializer_list
  map(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  }

  // Конструктор копирования
  map(const map& m) : tree_(m.tree_) {}

  // Конструктор перемещения
  map(map&& m) : tree_(std::move(m.tree_)) {}

  // Деструктор
  ~map() = default;

  // Перегрузка оператора присваивания для копирования объекта
  map& operator=(map& m) {
    tree_ = m.tree_;
    return *this;
  }

  // Перегрузка оператора присваивания для перемещения объекта
  map& operator=(map&& m) {
    tree_ = std::move(m.tree_);
    return *this;
  }

  // Доступ к указанному элементу с проверкой границ
  T& at(const Key& key) {
    iterator it = map_find(key);
    if (it == tree_.end()) throw std::out_of_range("map::at");
    return (*it).second;
  }

  // Доступ к указанному элементу с проверкой границ для константного словаря
  const T& at(const Key& key) const {
    const_iterator it = map_find(key);
    if (it == tree_.end()) throw std::out_of_range("map::at");
    return (*it).second;
  }

  // Доступ или вставка указанного элемента
  T& operator[](const Key& key) {
    value_type value = {key, mapped_type{}};
    iterator it = map_find(key);
    if (it == tree_.end()) {
      auto res = tree_.insert(value);
      return (*res.first).second;
    }
    return (*it).second;
  }

  // Возвращает итератор в начало
  iterator begin() noexcept { return tree_.begin(); }

  // Возвращает итератор в конец
  iterator end() noexcept { return tree_.end(); }

  // Возвращает итератор в начало для константного словаря
  const_iterator begin() const noexcept { return tree_.begin(); }

  // Возвращает итератор в конец для константного словаря
  const_iterator end() const noexcept { return tree_.end(); }

  // Проверяет, пуст ли контейнер
  bool empty() const noexcept { return tree_.empty(); }

  // Возвращает количество элементов
  size_type size() const noexcept { return tree_.size(); }

  // Возвращает максимально возможное количество элементов
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Очищает содержимое
  void clear() { tree_.clear(); }

  // Вставляет узел и возвращает итератор туда, где находится элемент,
  // и флаг, указывающий, произошла ли вставка
  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = map_find(value.first);
    if (it == end()) {
      auto res = tree_.insert(value);
      return res;
    }
    return {it, false};
  }

  // Вставляет значение по ключу и возвращает итератор туда, где находится
  // элемент, и флаг, указывающий, произошла ли вставка
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    value_type value = {key, obj};
    iterator it = map_find(value.first);
    if (it == end()) {
      auto res = tree_.insert(value);
      return res;
    }
    return {it, false};
  }

  // Вставляет элемент или присваивает текущему элементу, если ключ уже
  // существует
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    value_type value = {key, obj};
    iterator it = map_find(key);
    if (it == tree_.end())
      return tree_.insert(value);
    else {
      (*it).second = obj;
      return {it, false};
    }
  }

  // Удаляет элемент в позиции pos
  void erase(iterator pos) {
    auto it = map_find((*pos).first);
    if (it != end()) tree_.erase(pos);
  }

  // Меняет содержимое местами
  void swap(map& other) { tree_.swap(other.tree_); }

  // Объединяет узлы из другого контейнера
  void merge(map& other) { tree_.merge(other.tree_); }

  // Проверяет, есть ли элемент с ключом, эквивалентным ключу, в контейнере
  bool contains(const Key& key) const noexcept {
    const_iterator it = map_find(key);
    return it == end() ? 0 : 1;
  }

  // Вставляет новые элементы в контейнер
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_.insert_many(std::forward<Args>(args)...);
  }

 private:
  // Находит элемент с заданным ключом
  iterator map_find(const Key& key) noexcept {
    iterator it = tree_.begin();
    if (it == tree_.end() || it == nullptr) return end();
    while (it != tree_.end()) {
      if ((*it).first == key) return it;
      it++;
    }
    return end();
  }

  // Находит элемент с заданным ключом для константного словаря
  const_iterator map_find(const Key& key) const noexcept {
    const_iterator it = tree_.begin();
    if (it == tree_.end()) return end();
    while (it != tree_.end()) {
      if ((*it).first == key) return it;
      it++;
    }
    return end();
  }

  // Переменная красно-черного дерева
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_MAP_H_
