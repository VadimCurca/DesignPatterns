#include <initializer_list>
#include <iostream>
#include <memory>
#include <numeric>

template <class T> class Node {
  public:
    Node() : value(0), next(nullptr){};
    Node(T value) : value(value), next(nullptr) {}
    Node<T> operator+(const Node<T> &rhs) { return Node<T>(value + rhs.value); }
    Node<T> &operator++() {
        value++;
        return *this;
    }

  public:
    T value;
    Node<T> *next;
};

template <class T> class ListIterator;

template <class T> class List {
  public:
    typedef ListIterator<Node<T>> Iterator;
    List(std::initializer_list<T> lst) : _first(nullptr), _last(nullptr) {

        auto it = lst.begin();
        _first = new Node(*it);

        it++;
        _last = _first;
        for (; it != lst.end(); it++) {
            _last->next = new Node(*it);
            _last = _last->next;
        }
    }

    ~List() {
        while (_first != nullptr) {
            auto next = _first->next;
            delete _first;
            _first = next;
        }
    }

    void push_back(T value) {
        _last->next = new Node(value);
        _last = _last->next;
    }

    void pop_front() {
        auto temp = _first;
        _first = _first->next;
        delete temp;
    }

    Iterator begin() { return Iterator(_first); }
    Iterator end() { return Iterator(); }

  private:
    Node<T> *_first;
    Node<T> *_last;
};

template <class T> class ListIterator {
  public:
    ListIterator() : _current(nullptr) {}
    ListIterator(T *current) : _current(current) {}
    ListIterator<T> &operator++() {
        _current = _current->next;
        return *this;
    }
    ListIterator<T> operator++(int) {
        ListIterator<T> temp = *this;
        _current = _current->next;
        return temp;
    }
    T &operator*() { return *_current; }
    bool operator!=(const ListIterator<T> &other) {
        return _current != other._current;
    }
    bool operator==(const ListIterator<T> &other) {
        return _current == other._current;
    }

  private:
    T *_current;
};

int main() {
    List<int> l = {1, 2, 3, 4};
    l.push_back(3);
    l.push_back(2);

    List<int>::Iterator it = l.begin();
    List<int>::Iterator it1 = it++;
    List<int>::Iterator it2 = ++it;
    std::cout << (*it1).value << ' ' << (*it2).value << std::endl;
    // 1 3

    for (auto x : l) {
        std::cout << x.value << ' ';
    }
    std::cout << std::endl;

    std::for_each(l.begin(), l.end(), [](Node<int> &n) { ++n; });
    for (auto it = l.begin(); it != l.end(); it++) {
        std::cout << (*it).value << ' ';
    }
    std::cout << std::endl;

    auto sum = std::accumulate(l.begin(), l.end(), Node(0));
    std::cout << "sum: " << sum.value << std::endl;

    std::cout << std::endl;
}
