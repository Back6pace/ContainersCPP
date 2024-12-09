#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>

class vector {
 public:
  // Типы элементов
  using value_type = T;  // T - параметр шаблона
  using reference = T &;  // T & определяет тип ссылки на элемент
  using const_reference =
      const T &;  // const T & определяет тип константной ссылки
  using iterator = T *;  // итератор, который в данном случае является обычным
                         // указателем на элемент массива T.
  using const_iterator =
      const T *;  // константный итератор, который позволяет только читать
                  // элементы массива, но не изменять их.
  using size_type = std::size_t;  // size_t определяет тип размера контейнера

  // Констуруктор по умолчанию
  vector() : m_size(0), m_capacity(0), arr(nullptr) {}
  // Конструктор с параметрами
  explicit vector(size_type n) : vector() {
    m_size = m_capacity = n;
    if (n > 0) {
      arr = new value_type[m_capacity];
    }
  }
  // Конструктор создает вектор инициализированный с помощью
  // std::initializer_list
  vector(std::initializer_list<value_type> const &items)
      : vector(items.size()) {
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
  }
  // Конструктор копирования
  vector(const vector &v)
      : m_size(v.m_size),
        m_capacity(v.m_capacity),
        arr(new value_type[m_capacity]) {
    for (size_type i = 0; i < m_size; i++) {
      arr[i] = v.arr[i];
    }
  }
  // Конструктор перемещения
  vector(vector &&v) : vector() { operator=(std::move(v)); }
  // Деструктор
  ~vector() { delete[] arr; }

  // Перегрузка оператора присваивания
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] arr;
      m_size = v.m_size;
      m_capacity = v.m_capacity;
      arr = v.arr;

      v = vector();
    }
    return *this;
  }

  // Vector Element access

  // Доступ к элементу по индексу с проверкой выхода за пределы массива
  reference at(size_type pos) {
    if (pos >= m_size) {
      throw std::out_of_range("Index is out of range");
    }
    return arr[pos];
  }
  // Доступ к элементу по индексу
  reference operator[](size_type pos) { return arr[pos]; }

  // Доступ к первому элементу
  const_reference front() const {
    if (empty()) {
      throw std::logic_error("The vector is empty");
    }

    return arr[0];
  }
  // Доступ к последнему элементу
  const_reference back() const {
    if (empty()) {
      throw std::logic_error("The vector is empty");
    }

    return arr[m_size - 1];
  };
  // Прямой доступ к массиву
  iterator data() noexcept { return arr; }

  const_reference operator[](size_type pos) const { return arr[pos]; }
  const_iterator data() const noexcept { return arr; }
  const_reference at(size_type pos) const {
    if (pos >= m_size) {
      throw std::out_of_range("Index is out of range");
    }
    return arr[pos];
  }

  // Vector Iterators
  // begin() возвращает указатель на первый элемент вектора
  // end() возвращает указатель на следующий за последним элементом
  iterator begin() noexcept { return arr; }
  iterator end() noexcept { return arr + m_size; }

  const_iterator begin() const noexcept { return arr; }
  const_iterator end() const noexcept { return arr + m_size; }

  // Vector Modifiers

  // Очистка вектора
  void clear() noexcept { m_size = 0; };
  // Вставка элемента по позиции и возращение итератора на новый элемент
  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator out of range");
    }

    // индекс вставляемого элемента
    size_type index = pos - begin();

    // Если нет места, расширяем емкость в 2 раза, если емкость 0, то увеличим
    // емкость до 1
    if (m_size >= m_capacity) {
      reserve(m_capacity > 0 ? m_capacity * 2 : 1);
    }

    // Перемещаем элементы вправо, до позиции index начиная с конца
    for (size_type i = m_size; i > index; --i) {
      arr[i] = std::move(arr[i - 1]);
    }

    // Вставляем новый элемент и увеличиваем размер
    arr[index] = value;
    ++m_size;

    return begin() + index;  // Возвращаем итератор на вставленный элемент
  }
  // Удаление элемента по позиции
  void erase(iterator pos) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator out of range");
    }
    // индекс удаляемого элемента
    size_type index = pos - begin();

    // Перемещаем элементы влево, начиная с позиции index
    for (size_type i = index; i < m_size - 1; ++i) {
      arr[i] = std::move(arr[i + 1]);
    }
    --m_size;
  }
  // Добавление элемента в конец вектора
  void push_back(const_reference value) { insert(end(), value); }
  // Удаление последнего элемента
  void pop_back() {
    if (empty()) {
      throw std::logic_error("Vector is empty!");
    }
    m_size--;
  }
  // Обменивает содержимое двух векторов
  void swap(vector &other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(arr, other.arr);
  }

  // Vector Capacity

  // Возвращает true, если вектор пустой
  bool empty() const noexcept { return begin() == end(); }
  // Возвращает текущий размер вектора
  size_type size() const noexcept { return m_size; }

  // Максимальный возможный размер вектора в зависимости от доступной памяти
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 2);
  }

  // Резервирует память и копирует текущие элементы массива в новый массив
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Overflow! Enter a smaller size!");
    } else {
      if (size > m_capacity) {
        memory_allocation(size);
      }
    }
  }

  // Возвращает текущую емкость вектора
  size_type capacity() const noexcept { return m_capacity; }

  // Сокращает емкость вектора до его размера
  void shrink_to_fit() {
    if (m_capacity > m_size) {
      memory_allocation(m_size);
    }
  }

 private:
  size_type m_size;  // переменная для хранения текущего количества элементов
                     // в векторе
  size_type m_capacity;  // переменная, которая хранит текущую емкость вектора
  T *arr;  // указатель на массив, который хранит элементы вектора

  // Перераспределяет память для увеличения ёмкости вектора, перемещая
  // существующие элементы в новый массив
  void memory_allocation(size_type size) {
    iterator temp = new value_type[size];
    for (size_type i = 0; i < m_size; ++i) {
      temp[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = temp;
    m_capacity = size;
  }
};

}  // namespace s21

#endif