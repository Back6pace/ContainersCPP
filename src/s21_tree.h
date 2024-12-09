#ifndef SRC_S21_TREE_H_
#define SRC_S21_TREE_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/* Реализация красно-черного дерева
    Красно-черное дерево - это двоичное дерево поиска, имеющее следующие пять
   дополнительных свойств.

    1. Каждый узел в T либо красный, либо черный.
    2. Корневой узел T черный.
    3. Каждый NULL-узел черный. (NULL-узлы являются листовыми узлами. Они не
   содержат ключей. Когда мы ищем ключ, который отсутствует в дереве, мы
   достигаем NULL-узла.)
    4. Если узел красный, оба его потомка черные. Это означает, что на пути нет
   двух красных узлов.
    5. Каждый путь от корневого узла к NULL-узлу имеет одинаковое количество
   черных узлов. (черная высота)
*/

namespace s21 {
template <typename Key>
class RBTree {
  class RBNode;
  class RBIterator;
  class RBConstIterator;
  using reference = Key&;
  using const_reference = const Key&;
  using size_type = std::size_t;
  using comparator = std::less<Key>;
  using NodePtr = RBNode*;

  enum NodeColor { BLACK, RED };

  //      =============== PUBLIC ===============
 public:
  using iterator = RBIterator;
  using const_iterator = RBConstIterator;
  using value_type = Key;

  // конструктор по умолчанию. создает корневой узел
  RBTree() : root_(new RBNode), size_(0) {};

  // конструктор копирования
  RBTree(const RBTree& other) : RBTree() { *this = other; };

  // конструктор перемещения
  RBTree(RBTree&& other) : RBTree() { *this = std::move(other); };

  // деструктор
  ~RBTree() {
    clear();
    delete_node(root_);
  };

  // перегрузка оператора присваивания копирования
  RBTree& operator=(const RBTree& other) {
    if (this != &other) {
      if (other.size_ == 0) {
        clear();
      } else {
        if (root_->parent_) clear();
        NodePtr root = copy(other.root_->parent_, nullptr);
        root_->parent_ = root;
        root_->parent_->parent_ = root;
        root_->left_ = other.root_->left_;
        root_->right_ = other.root_->right_;
        size_ = other.size_;
      }
    }
    return *this;
  };

  // перегрузка оператора перемещения
  RBTree& operator=(RBTree&& other) {
    if (this != &other) {
      clear();
      std::swap(this->root_, other.root_);
      std::swap(this->size_, other.size_);
    } else {
      other.clear();
      delete_node(other.root_);
    }
    return *this;
  };

  // возвращает итератор минимального элемента
  iterator begin() noexcept { return iterator(root_->left_); };

  // то же для константного объекта
  const_iterator begin() const noexcept {
    return const_iterator(root_->left_);
  };

  // возвращает итератор на корень (конечный элемент)
  iterator end() noexcept { return iterator(root_); };

  // то же для константного объекта
  const_iterator end() const noexcept { return const_iterator(root_); };

  // проверяет, пуст ли объект
  bool empty() const noexcept { return size_ ? 0 : 1; };

  // возвращает количество элементов
  size_type size() const noexcept { return size_; };

  // возвращает максимально возможное количество элементов
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / 2 - sizeof(RBNode) -
            sizeof(RBTree)) /
           sizeof(RBNode);
  };

  // очищает содержимое объекта
  void clear() {
    delete_all(root_->parent_);
    root_->parent_ = nullptr;
    root_->left_ = nullptr;
    root_->right_ = nullptr;
    size_ = 0;
  };

  // вставляет новый элемент в объект
  // вставляются только уникальные элементы
  std::pair<iterator, bool> insert(const value_type& value) {
    NodePtr new_node = new RBNode(value);
    std::pair<iterator, bool> res = insert_node(new_node, true);
    if (!res.second) delete_node(new_node);
    return res;
  };

  // вставляет новый элемент в объект
  // допускается вставка дубликатов
  iterator insert_duplicate(const value_type& value) {
    NodePtr new_node = new RBNode(value);
    return insert_node(new_node, false).first;
  };

  // удаляет элемент на позиции
  void erase(iterator pos) { delete_node(pos); };

  // обменивает содержимое
  void swap(RBTree& other) {
    using std::swap;
    swap(root_, other.root_);
    swap(size_, other.size_);
  };

  // возвращает итератор к элементу с ключом
  iterator find(const_reference key) noexcept {
    iterator res = iterator(find_node(key));
    if (res == end() || comparator{}(*res, key)) return end();
    return res;
  };

  // то же для константного объекта
  const_iterator find(const_reference key) const noexcept {
    const_iterator res = lower_bound(key);
    if (res == end() || comparator{}(*res, key)) return end();
    return res;
  };

  // проверяет, содержит ли объект такой элемент
  bool contains(const_reference key) const noexcept {
    NodePtr node = find_node(key);
    return (node != root_);
  };

  // возвращает итератор к большему элементу
  iterator upper_bound(const_reference value) noexcept {
    iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(value, begin->data_)) {
        result = iterator(begin);
        begin = begin->left_;
      } else
        begin = begin->right_;
    }
    return result;
  };

  // то же для константного объекта
  const_iterator upper_bound(const_reference value) const noexcept {
    const_iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(value, begin->data_)) {
        result = const_iterator(begin);
        begin = begin->left_;
      } else
        begin = begin->right_;
    }
    return result;
  };

  // возвращает итератор, указывающий на первый элемент в диапазоне
  // [first,last), который не сравнивается меньше, чем ключ
  iterator lower_bound(const_reference value) noexcept {
    iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(begin->data_, value)) {
        begin = begin->right_;
      } else {
        result = iterator(begin);
        begin = begin->left_;
      }
    }
    return result;
  };

  // то же для константного объекта
  const_iterator lower_bound(const_reference value) const noexcept {
    const_iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(begin->data_, value)) {
        begin = begin->right_;
      } else {
        result = const_iterator(begin);
        begin = begin->left_;
      }
    }
    return result;
  };

  // возвращает количество элементов, равных ключу
  size_type count(const_reference key) const noexcept {
    const_iterator it = begin();
    size_type c = 0;
    for (size_type i = 0; i < size(); i++) {
      if (*it == key) c++;
      it++;
    }
    return c;
  };

  // объект пары, чей член pair::first - итератор к нижней границе поддиапазона
  // эквивалентных значений, а pair::second - его верхняя граница
  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    iterator start = lower_bound(key), end = upper_bound(key);
    return {start, end};
  };

  // то же для константного объекта
  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const noexcept {
    const_iterator start = lower_bound(key), end = upper_bound(key);
    return {start, end};
  };

  // перемещает содержимое одного объекта в другой
  void merge_duplicates(RBTree& other) noexcept {
    if (this != &other) {
      iterator it = other.begin();
      while (other.size_ > 0) {
        NodePtr node = it.node_;
        it++;
        if (node->parent_->left_ == node) node->parent_->left_ = nullptr;
        if (node->parent_->right_ == node) node->parent_->right_ = nullptr;
        if (node->right_) node->right_->parent_ = node->parent_;
        if (node->left_) node->left_->parent_ = node->parent_;
        node->left_ = nullptr;
        node->right_ = nullptr;
        node->parent_ = nullptr;
        node->color_ = RED;
        insert_node(node, false);
        other.size_--;
      }
    }
    other.root_->parent_ = nullptr;
    other.size_ = 0;
  };

  // перемещает содержимое одного объекта в другой
  // без дубликатов
  // все дубликаты остаются в другом дереве
  void merge(RBTree& other) noexcept {
    if (this != &other) {
      iterator it = other.begin();
      while (it != other.end()) {
        if (find(it.node_->data_) == end()) {
          NodePtr node = it.node_;
          it++;
          node = other.merge_node(node);
          insert_node(node, true);
        } else
          it++;
      }
    }
  };

  // вставляет новые элементы в контейнер
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vect;
    vect.reserve(sizeof...(args));
    for (auto element : {std::forward<Args>(args)...}) {
      NodePtr new_node = new RBNode(std::move(element));
      std::pair<iterator, bool> result = insert_node(new_node, true);
      if (result.second == false) {
        delete new_node;
      }
      vect.push_back(result);
    }
    return vect;
  }

  // вставляет новые элементы в контейнер с дубликатами
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many_duplicate(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vect;
    vect.reserve(sizeof...(args));
    for (auto element : {std::forward<Args>(args)...}) {
      NodePtr new_node = new RBNode(std::move(element));
      vect.push_back(insert_node(new_node, false));
    }
    return vect;
  }

  //      =============== ВЫВОД ФУНКЦИЙ ===============

  // выводит дерево
  void print() noexcept {
    if (root_->parent_ != nullptr) {
      print(root_->parent_, "", true);
    }
  };

  //      =============== PRIVATE МЕТОДЫ ===============

 private:
  // функция вывода
  // используется для проверки корректности красно-черного дерева
  void print(NodePtr node, std::string indent, bool right) noexcept {
    if (node != nullptr) {
      std::cout << indent;
      if (right) {
        std::cout << "R----";
        indent += "     ";
      } else {
        std::cout << "L----";
        indent += "|    ";
      }
      std::string color = (node->color_ == RED) ? "RED" : "BLACK";
      std::cout << node->data_ << "(" << color << ")" << std::endl;
      print(node->left_, indent, false);
      print(node->right_, indent, true);
    }
  };

  //      =============== МЕТОДЫ ДЕРЕВА ===============

  // вставляет узел в красно-черное дерево
  // если unique равно true, вставляются только элементы без дубликатов
  // в противном случае: также могут быть вставлены дубликаты
  std::pair<iterator, bool> insert_node(NodePtr new_node, bool unique) {
    // поиск места для вставки узла
    NodePtr node = root_->parent_;
    NodePtr parent = nullptr;
    while (node != nullptr) {
      parent = node;
      if (comparator{}(new_node->data_, node->data_))
        node = node->left_;
      else if (comparator{}(node->data_, new_node->data_))
        node = node->right_;
      else if (unique == false)
        node =
            node->right_;  // случай, когда можно вставить неуникальный элемент
      else
        return {iterator(node), false};  // возвращаем элемент, если наше дерево
                                         // не содержит дубликатов
    }
    // так как вставка происходит, размер увеличивается
    size_++;
    // вставка
    if (parent == nullptr) {  // случай, когда вставляется 1-й элемент (корень)
      new_node->parent_ = root_;
      root_->parent_ = new_node;
      new_node->color_ = BLACK;
    } else {
      new_node->parent_ = parent;
      comparator{}(new_node->data_, parent->data_) ? parent->left_ = new_node
                                                   : parent->right_ = new_node;
    }
    // устанавливаем указатель на максимальный элемент в корневой узел
    if (!root_->right_ || root_->right_->right_) {
      root_->right_ = new_node;
    }
    // устанавливаем указатель на минимальный элемент в корневой узел
    if (!root_->left_ || root_->left_->left_) root_->left_ = new_node;
    // балансировка после вставки
    balance_insert(new_node);
    return {iterator(new_node), true};
  };

  // освобождает узел и обнуляет все указатели
  void delete_node(NodePtr node) {
    if (node != nullptr) {
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->parent_ = nullptr;
      delete node;
      node = nullptr;
    }
  };

  // левый поворот для балансировки красно-черного дерева
  void left_rotate(NodePtr node) noexcept {
    NodePtr help_node = node->right_;
    // меняем правое поддерево узла на левое поддерево вспомогательного узла
    node->right_ = help_node->left_;
    // если не пусто, меняем указатель на родителя
    if (help_node->left_ != nullptr) {
      help_node->left_->parent_ = node;
    }
    // меняем родителя вспомогательного узла на родителя узла
    help_node->parent_ = node->parent_;
    // меняем ребенка родителя узла
    // случай, когда узел является 1-м элементом
    if (node->parent_ == root_) {
      root_->parent_ = help_node;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = help_node;
    } else {
      node->parent_->right_ = help_node;
    }
    // делаем узел левым ребенком вспомогательного узла
    help_node->left_ = node;
    node->parent_ = help_node;
  };

  // правый поворот для балансировки красно-черного дерева
  void right_rotate(NodePtr node) noexcept {
    NodePtr help_node = node->left_;
    node->left_ = help_node->right_;
    if (help_node->right_ != nullptr) {
      help_node->right_->parent_ = node;
    }
    help_node->parent_ = node->parent_;
    if (root_->parent_ == node) {
      root_->parent_ = help_node;
    } else if (node == node->parent_->right_) {
      node->parent_->right_ = help_node;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = help_node;
    }
    help_node->right_ = node;
    node->parent_ = help_node;
  };

  /*
      Функция балансировки нужна для поддержания свойств красно-черного дерева.
      Существует несколько случаев после вставки.
      P - родитель, G - дед, U - дядя, S - брат, X - вставленный узел
      Случай 1:
          Дерево пустое - вставляем X и окрашиваем его в черный цвет
      Случай 2:
          P черный - вставляем X и окрашиваем его в красный цвет
      Случай 3:
          P красный. В этом случае нужно проверить цвет U
          Случай 3.1:
              U красный - перераспределение цветов: делаем P и U черными, G
              красным
          Случай 3.2: U черный. В этом случае нужно проверить, являются ли P и
          X правыми или левыми детьми Случай 3.2.1: P правый ребенок G и X
          правый ребенок P: левый поворот в G; делаем G красным, P черным
          Случай 3.2.2: P правый ребенок G и X левый ребенок P: повторяем
          случай 3.2.1 Случай 3.2.3: P левый ребенок G и X левый ребенок P:
          правый поворот в G; делаем G красным, P черным
          Случай 3.2.4: P левый ребенок G и X правый ребенок P: повторяем
          случай 3.2.3
  */
  void balance_insert(NodePtr node) noexcept {
    NodePtr u;
    while (node->parent_->color_ == RED && node != root_->parent_) {
      if (node->parent_ == node->parent_->parent_->right_) {
        u = node->parent_->parent_->left_;
        // если цвет дяди тоже красный, то меняем цвета
        if (u != nullptr && u->color_ == RED) {  // случай 3.1
          u->color_ = BLACK;
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          // меняем указатель для следующей итерации
          node = node->parent_->parent_;
          // если дядя черный и P правый ребенок G
        } else {
          if (node == node->parent_->left_) {  // случай 3.2.2
            node = node->parent_;
            right_rotate(node);
          }
          node->parent_->color_ = BLACK;  // случай 3.2.1
          node->parent_->parent_->color_ = RED;
          left_rotate(node->parent_->parent_);
        }
      } else {
        u = node->parent_->parent_->right_;
        if (u != nullptr && u->color_ == RED) {  // случай 3.1
          u->color_ = BLACK;
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          // меняем указатель для следующей итерации
          node = node->parent_->parent_;
        } else {
          if (node == node->parent_->right_) {  // случай 3.2.4
            node = node->parent_;
            left_rotate(node);
          }
          node->parent_->color_ = BLACK;  // случай 3.2.3
          node->parent_->parent_->color_ = RED;
          right_rotate(node->parent_->parent_);
        }
      }
    }
    root_->parent_->color_ =
        BLACK;  // убеждаемся, что корневой узел остается черным
  };

  // находит минимальный узел в дереве
  NodePtr search_right(NodePtr node) noexcept {
    while (node->right_) {
      node = node->right_;
    }
    return node;
  };

  // находит максимальный узел в дереве
  NodePtr search_left(NodePtr node) noexcept {
    while (node->left_) {
      node = node->left_;
    }
    return node;
  };

  // обменивает узлы
  void swap_nodes(NodePtr one, NodePtr two) noexcept {
    two == two->parent_->left_ ? two->parent_->left_ = one
                               : two->parent_->right_ = one;
    if (one == root_->parent_)
      root_->parent_ = two;
    else
      one == one->parent_->left_ ? one->parent_->left_ = two
                                 : one->parent_->right_ = two;
    std::swap(one->left_, two->left_);
    std::swap(one->right_, two->right_);
    std::swap(one->parent_, two->parent_);
    // меняем цвета тоже, потому что меняем указатели, а не значения
    // мы меняем указатели, чтобы итераторы остались действительными
    std::swap(one->color_, two->color_);
    if (one->left_) one->left_->parent_ = one;
    if (one->right_) one->right_->parent_ = one;
    if (two->left_) two->left_->parent_ = two;
    if (two->right_) two->right_->parent_ = two;
  };

  // находит узел с ключом
  NodePtr find_node(const_reference key) const noexcept {
    NodePtr ptr = root_->parent_;
    while (ptr) {
      if (ptr->data_ == key) return ptr;
      if (comparator{}(ptr->data_, key))
        ptr = ptr->right_;
      else
        ptr = ptr->left_;
    }
    return root_;
  };

  NodePtr find_node(iterator pos) const noexcept {
    NodePtr res = find_node(*pos);
    return res;
  };

  // удаление узла
  void delete_node(iterator pos) {
    if (pos == end()) return;  // нельзя удалить корень
    NodePtr node = pos.node_;
    if (node->left_ && node->right_) {  // случай, когда узел имеет двух детей.
                                        // мы просто меняем его с максимальным
                                        // элементом в его левом поддереве
      NodePtr swap_node = search_right(node->left_);
      swap_nodes(node, swap_node);
    }
    // удаление узла с одним правым ребенком
    if (!node->left_ &&
        node->right_ !=
            nullptr) {  // случай, когда узел имеет одного правого ребенка.
                        // мы меняем его с его правым ребенком
      swap_nodes(node, node->right_);
    }
    // удаление узла с одним левым ребенком
    if (!node->right_ && node->left_ != nullptr) {
      // меняем его с его левым ребенком
      swap_nodes(node, node->left_);
    }
    // после обмена и подготовки к удалению
    // нужно проверить, черный ли узел
    // если да, то мы должны сбалансировать дерево, чтобы не нарушить черную
    // высоту
    if (node->color_ == BLACK && (!node->left_ && !node->right_)) {
      balance_delete(node);
    }
    // если узел - первый элемент
    if (root_->parent_ == node) {
      root_->parent_ = nullptr;
      root_->right_ = nullptr;
      root_->left_ = nullptr;
    } else {
      // иначе удаляем указатель на узел у его родителя
      node->parent_->left_ == node ? node->parent_->left_ = nullptr
                                   : node->parent_->right_ = nullptr;
      // если узел - минимальный элемент в дереве, мы изменяем его на другой
      // элемент
      if (root_->left_ == node) root_->left_ = search_left(root_->parent_);
      // то же самое для случая, когда это максимальный элемент
      if (root_->right_ == node) root_->right_ = search_right(root_->parent_);
    }
    // удаление
    delete_node(node);
    // так как один узел удален, размер уменьшается
    size_--;
  };

  // Извлекает узел из дерева, чтобы переместить его в другое место
  // Процесс аналогичен удалению, но узел не удаляется
  NodePtr merge_node(NodePtr node) {
    if (node != root_) {  // нельзя извлечь корень
      if (node->right_ && node->left_) {
        NodePtr swap = search_right(node->left_);
        swap_nodes(node, swap);
      }
      if (node->right_ && !node->left_) swap_nodes(node, node->right_);
      if (node->left_ && !node->right_) swap_nodes(node, node->left_);
      if (node->color_ == BLACK && (!node->right_ && !node->left_))
        balance_delete(node);
      if (root_->left_ == node) root_->left_ = node->successor();
      if (root_->right_ == node) root_->right_ = node->predecessor();
      if (root_->parent_ == node)
        root_->parent_ = nullptr;
      else
        node->parent_->left_ == node ? node->parent_->left_ = nullptr
                                     : node->parent_->right_ = nullptr;
      size_--;
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->parent_ = nullptr;
      node->color_ = RED;
      return node;
    }
    return nullptr;
  }

  /*
      Функция балансировки после процесса удаления для поддержания свойств
     красно-черного дерева Есть несколько случаев P - родитель, G - дедушка, U -
     дядя, S - сиблинг, X - удаляемый узел Case 1: S красный: меняем цвета S и
     P; левый поворот в P Case 2: S черный и оба дети S черные: Если P красный:
     меняем P на черный иначе: делаем P новым X; повторяем 1 случай Case 3: S
     черный, левый ребенок S красный, правый ребенок S черный: меняем цвета S и
     его левого ребенка; правый поворот в S, повторяем случай 4 Case 4: S
     черный, правый ребенок S красный: меняем цвет правого ребенка S на красный;
     меняем цвет P на черный; левый поворот в P

  */
  void balance_delete(NodePtr node) {
    NodePtr s = nullptr;  // сиблинг
    while (node != root_->parent_ && node->color_ == BLACK) {
      if (node == node->parent_->left_) {
        s = node->parent_->right_;
        if (s->color_ == RED) {  // случай 1
          std::swap(s->color_, node->parent_->color_);
          left_rotate(node->parent_);
          s = node->parent_->right_;  // изменяем сиблинга для следующего цикла
        }
        if (s->color_ == BLACK && (!s->left_ || s->left_->color_ == BLACK) &&
            (!s->right_ || s->right_->color_ == BLACK)) {
          s->color_ = RED;  // случай 2
          if (node->parent_->color_ == RED) {
            node->parent_->color_ = BLACK;
            break;
          }
          node = node->parent_;
        } else {  // если сиблинг черный и имеет двух детей
          if (!s->right_ || s->right_->color_ ==
                                BLACK) {  // случай, когда правый ребенок черный
                                          // (нам нужно сделать его красным)
            s->color_ = RED;  // случай 3
            s->left_->color_ = BLACK;
            right_rotate(s);
            s = node->parent_->right_;
          }  // случай 4
          s->color_ = node->parent_->color_;
          s->right_->color_ = BLACK;
          node->parent_->color_ = BLACK;
          left_rotate(node->parent_);
          break;
        }
      } else {
        s = node->parent_->left_;
        if (s->color_ == RED) {  // случай 1
          std::swap(s->color_, node->parent_->color_);
          right_rotate(node->parent_);
          s = node->parent_->left_;
        }
        if (s->color_ == BLACK && (!s->left_ || s->left_->color_ == BLACK) &&
            (!s->right_ || s->right_->color_ == BLACK)) {
          s->color_ = RED;  // случай 2
          if (node->parent_->color_ == RED) {
            node->parent_->color_ = BLACK;
            break;
          }
          node = node->parent_;
        } else {
          if (!s->left_ || s->left_->color_ == BLACK) {
            s->color_ = RED;  // случай 3
            s->right_->color_ = BLACK;
            left_rotate(s);
            s = node->parent_->left_;
          }
          s->color_ = node->parent_->color_;  // случай 4
          s->left_->color_ = BLACK;
          node->parent_->color_ = BLACK;
          right_rotate(node->parent_);
          break;
        }
      }
    }
    root_->parent_->color_ = BLACK;
  };

  // рекурсивное удаление содержимого дерева
  void delete_all(NodePtr node) {
    if (node == nullptr) return;
    delete_all(node->left_);
    delete_all(node->right_);
    delete_node(node);
  };

  // рекурсивное копирование содержимого дерева
  NodePtr copy(NodePtr copy_node, NodePtr parent) {
    NodePtr new_node = new RBNode(copy_node);
    if (copy_node->left_) new_node->left_ = copy(copy_node->left_, new_node);
    if (copy_node->right_) new_node->right_ = copy(copy_node->right_, new_node);
    new_node->parent_ = parent;
    return new_node;
  };

  //      =============== КЛАСС УЗЛА ===============

  // Класс узла
  class RBNode {
   public:
    // конструктор по умолчанию
    RBNode()
        : data_(Key{}),
          color_(RED),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr) {};

    // конструктор с значением
    RBNode(const Key& value)
        : data_(value),
          color_(RED),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr) {};

    // конструктор перемещения
    RBNode(const Key&& value)
        : data_(std::move(value)),
          color_(RED),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr) {};

    // копирует узел
    RBNode(RBNode* node)
        : data_(node->data_),
          color_(node->color_),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr) {};

    Key data_;
    NodeColor color_;
    NodePtr parent_;
    NodePtr left_;
    NodePtr right_;

    // Возвращает указатель на следующий узел
    NodePtr successor() noexcept {
      NodePtr node = this;
      // если узел - корень
      if (node->color_ == RED &&
          (node->parent_ == nullptr || node->parent_->parent_ == node)) {
        return node
            ->right_;  // я перемещаю указатель на максимальный элемент, потому
                       // что стандартная библиотека делает то же самое
      }
      // если у узла есть правый ребенок
      else if (node->right_ != nullptr) {
        node = node->right_;
        while (node->left_ != nullptr) node = node->left_;
        // если у узла нет правого ребенка
      } else {
        NodePtr parent = node->parent_;
        while (node ==
               parent->right_) {  // мы перемещаем указатель, пока не найдем
                                  // следующего левого ребенка родителя
          node = parent;
          parent = parent->parent_;
        }
        // если узел - корень
        if (node->right_ != parent) node = parent;
      }
      return node;
    };

    // возвращает указатель на предыдущий элемент
    NodePtr predecessor() noexcept {
      NodePtr node = this;
      if (node->color_ == RED &&
          (node->parent_ == nullptr || node->parent_->parent_ == node))
        return node->right_;
      else if (node->left_ != nullptr) {
        node = node->left_;
        while (node->right_ != nullptr) node = node->right_;
      } else {
        NodePtr parent = node->parent_;
        while (node == parent->left_) {
          node = parent;
          parent = parent->parent_;
        }
        if (node->left_ != parent) node = parent;
      }
      return node;
    };
  };

  //      =============== КЛАСС ИТЕРАТОРА ===============

  class RBIterator {
    friend RBTree;

   public:
    // конструктор по умолчанию
    RBIterator() : node_(nullptr) {};

    // конструктор с параметром узла
    RBIterator(NodePtr node) : node_(node) {};

    // перегрузка * возвращает данные
    reference operator*() noexcept { return node_->data_; };

    // перегрузка; проверяет, одинаковы ли узлы
    bool operator==(const iterator& other) noexcept {
      return node_ == other.node_;
    };

    // перегрузка !=; проверяет, разные ли узлы
    bool operator!=(const iterator& other) noexcept {
      return node_ != other.node_;
    };

    // перемещает итератор к следующему значению
    iterator& operator++() noexcept {
      node_ = node_->successor();
      return *this;
    };

    // то же самое для постфиксного инкремента
    iterator operator++(int) noexcept {
      iterator temp(node_);
      ++(*this);
      return temp;
    };

    // перемещается к предыдущему значению
    iterator& operator--() noexcept {
      node_ = node_->predecessor();
      return *this;
    };

    // то же самое для постфиксного декремента
    iterator operator--(int) noexcept {
      iterator temp(node_);
      --(*this);
      return temp;
    };

   private:
    // значение узла
    NodePtr node_;
  };

  // Константные итераторы
  class RBConstIterator {
    friend RBTree;

   public:
    // конструктор по умолчанию
    RBConstIterator() : node_(nullptr) {};

    RBConstIterator(const iterator& other) { node_ = other.node_; };

    const_reference operator*() const noexcept { return node_->data_; };

    const_iterator operator++() noexcept {
      node_ = node_->successor();
      return *this;
    };

    const_iterator operator++(int) noexcept {
      const_iterator temp(*this);
      ++(*this);
      return temp;
    };

    const_iterator operator--() noexcept {
      node_ = node_->predecessor();
      return *this;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp(*this);
      --(*this);
      return temp;
    };

   private:
    NodePtr node_;
    friend bool operator==(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ == it2.node_;
    };

    friend bool operator!=(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ != it2.node_;
    };
  };

  //      =============== ПЕРЕМЕННЫЕ ДЕРЕВА ===============
  NodePtr root_;    // конечный элемент
  size_type size_;  // количество элементов
};
}  // namespace s21

#endif  // SRC_S21_TREE_H_
