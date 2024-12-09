#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "s21_tree.h"

/*
    Реализация множества
    Множество - это ассоциативный контейнер уникальных элементов. Это означает,
   что один и тот же элемент не может быть добавлен в множество дважды.
   Контейнер множества является ассоциативным, потому что он также представлен в
   виде дерева, как контейнер map, и, следовательно, также хранит элементы в
   отсортированном порядке. Разница между map и set заключается в том, что в
   множестве само значение уникально, а не ключ, а значение в дереве проверяется
   не ключом, а самим значением. Существует соответствующее исключение, когда вы
   добавляете уже существующий элемент в множество.
*/

namespace s21 {
template <typename Key>
class set {
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
  set() : tree_() {};

  // Конструктор списка инициализации, создает множество, инициализированное с
  // помощью std::initializer_list
  set(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  };

  // Конструктор копирования
  set(const set& s) : tree_(s.tree_) {};

  // Конструктор перемещения
  set(set&& s) : tree_(std::move(s.tree_)) {};

  // Деструктор
  ~set() = default;

  // Перегрузка оператора присваивания для копирования объекта
  set& operator=(const set& other) {
    tree_ = other.tree_;
    return *this;
  };

  // Перегрузка оператора присваивания для перемещения объекта
  set& operator=(set&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  // Вставляет узел и возвращает итератор туда, где находится элемент в
  // контейнере и bool, указывающий, произошло ли вставка
  std::pair<iterator, bool> insert(const_reference key) {
    return tree_.insert(key);
  };

  // Удаляет элемент в позиции pos
  void erase(iterator pos) { tree_.erase(pos); };

  // Проверяет, пуст ли контейнер
  bool empty() const noexcept { return tree_.empty(); };

  // Возвращает количество элементов
  size_type size() const noexcept { return tree_.size(); };

  // Возвращает максимально возможное количество элементов
  size_type max_size() const noexcept { return tree_.max_size(); };

  // Очищает содержимое
  void clear() { tree_.clear(); };

  // Меняет содержимое местами
  void swap(set& other) { tree_.swap(other.tree_); };

  // Присоединяет узлы из другого контейнера
  void merge(set& other) noexcept { tree_.merge(other.tree_); };

  // Находит элемент с определенным ключом
  iterator find(const_reference key) { return tree_.find(key); };

  // Находит элемент с определенным ключом для константного множества
  const_iterator find(const_reference key) const { return tree_.find(key); };

  // Проверяет, содержит ли контейнер элемент с определенным ключом
  bool contains(const_reference key) const { return tree_.contains(key); };

  // Возвращает итератор в начало
  iterator begin() noexcept { return tree_.begin(); };

  // Возвращает итератор в начало для константного множества
  const_iterator begin() const noexcept { return tree_.begin(); };

  // Возвращает итератор в конец
  iterator end() noexcept { return tree_.end(); };

  // Возвращает итератор в конец для константного множества
  const_iterator end() const noexcept { return tree_.end(); };

  // Вставляет новые элементы в контейнер
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_.insert_many(std::forward<Args>(args)...);
  };

 private:
  // Переменная красно-черного дерева
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_SET_H_
