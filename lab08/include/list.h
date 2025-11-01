#include <iostream>
template <typename T> struct Node {
  T data;
  struct Node *next;
};

template <typename T> class List {
private:
  Node<T> *head;
  int size;

public:
  List<T>() : head(nullptr), size(0) {}
  void add(T element, int index) {
    if (index > size || index < 0) {
      throw std::out_of_range("list: out of bounds");
    }
    Node<T> *newNode = new Node<T>{element, nullptr};

    if (index == 0) {
      newNode->next = head;
      head = newNode;
    } else {
      Node<T> *current = head;
      for (int i = 0; i < index - 1; i++) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }

    size++;
  }

  void add(T element) { add(element, size); }

  void remove(int index) {
    if (index >= size || index < 0) {
      throw std::out_of_range("list: out of bounds");
    }
    Node<T> *toDelete = nullptr;

    if (index == 0) {
      toDelete = head;
      head = head->next;
    } else {
      Node<T> *current = head;
      for (int i = 0; i < index - 1; i++) {
        current = current->next;
      }
      toDelete = current->next;
      current->next = toDelete->next;
    }

    delete toDelete;
    size--;
  }

  T get(int index) {
    if (index >= size || index < 0) {
      throw std::out_of_range("list: out of bounds");
    }
    Node<T> *current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  int sizeOf() { return size; }

  int display() {
    Node<T> *current = head;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
    return 0;
  }
};
