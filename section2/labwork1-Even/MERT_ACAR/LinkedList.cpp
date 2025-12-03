// src/LinkedList.cpp
#include "LinkedList.h"

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), count(0) {}

// Basic queries
template <typename T>
bool LinkedList<T>::empty() const {
  return head == nullptr;
}

template <typename T>
size_t LinkedList<T>::size() const {
  return count;
}

// Insert at front - O(1)
template <typename T>
void LinkedList<T>::push_front(const T& value) {
  Node<T>* newNode = new Node<T>(value, head);
  head = newNode;
  count++;
}

// Insert at back - O(n)
template <typename T>
void LinkedList<T>::push_back(const T& value) {
  if (head == nullptr) {
    push_front(value);
    return;
  }

  // Traverse to last node
  Node<T>* current = head;
  while (current->next != nullptr) {
    current = current->next;
  }

  // Attach new node at end
  current->next = new Node<T>(value);
  count++;
}

// Remove from front - O(1)
template <typename T>
void LinkedList<T>::pop_front() {
  if (head == nullptr) {
    return;  // Empty list
  }

  Node<T>* temp = head;
  head = head->next;
  delete temp;
  count--;
}

// Insert at position - O(n)
template <typename T>
void LinkedList<T>::insert(size_t position, const T& value) {
  // Validate position
  if (position > count) {
    return;  // Invalid position
  }

  // Insert at beginning
  if (position == 0) {
    push_front(value);
    return;
  }

  // Traverse to node before insertion point
  Node<T>* current = head;
  for (size_t i = 0; i < position - 1; i++) {
    current = current->next;
  }

  // Insert new node
  Node<T>* newNode = new Node<T>(value, current->next);
  current->next = newNode;
  count++;
}

// Erase at position - O(n)
template <typename T>
void LinkedList<T>::erase(size_t position) {
  // Validate position
  if (position >= count || head == nullptr) {
    return;  // Invalid position or empty list
  }

  // Erase first element
  if (position == 0) {
    pop_front();
    return;
  }

  // Traverse to node before deletion point
  Node<T>* current = head;
  for (size_t i = 0; i < position - 1; i++) {
    current = current->next;
  }

  // Delete node
  Node<T>* toDelete = current->next;
  current->next = toDelete->next;
  delete toDelete;
  count--;
}

// Find element - O(n)
// Returns position if found, -1 if not found
template <typename T>
int LinkedList<T>::find(const T& value) const {
  Node<T>* current = head;
  int position = 0;

  while (current != nullptr) {
    if (current->data == value) {
      return position;
    }
    current = current->next;
    position++;
  }

  return -1;  // Not found
}

// Print list with color visualization
template <typename T>
void LinkedList<T>::print() const {
  if (head == nullptr) {
    std::cout << Color::WARNING << "Empty list" << Color::RESET << std::endl;
    return;
  }

  std::cout << Color::BRIGHT_WHITE << "[HEAD]" << Color::RESET;

  Node<T>* current = head;
  while (current != nullptr) {
    std::cout << Color::YELLOW << " -> " << Color::RESET;
    std::cout << Color::BRIGHT_WHITE << "[" << Color::RESET;
    std::cout << Color::CYAN << current->data << Color::RESET;
    std::cout << Color::BRIGHT_WHITE << "]" << Color::RESET;
    current = current->next;
  }

  std::cout << Color::YELLOW << " -> " << Color::RESET;
  std::cout << Color::DIM << "nullptr" << Color::RESET << std::endl;
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}

// Copy constructor - deep copy
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), count(0) {
  Node<T>* current = other.head;
  while (current != nullptr) {
    push_back(current->data);
    current = current->next;
  }
}

// Copy assignment operator - deep copy
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
  if (this != &other) {  // Self-assignment check
    clear();             // Clear existing data

    Node<T>* current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }
  return *this;
}

// Move constructor - transfer ownership
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head(other.head), count(other.count) {
  other.head = nullptr;
  other.count = 0;
}

// Move assignment operator - transfer ownership
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
  if (this != &other) {  // Self-assignment check
    clear();             // Clear existing data

    head = other.head;
    count = other.count;

    other.head = nullptr;
    other.count = 0;
  }
  return *this;
}

// Clear all nodes
template <typename T>
void LinkedList<T>::clear() {
  while (head != nullptr) {
    Node<T>* temp = head;
    head = head->next;
    delete temp;
  }
  count = 0;
}

// Private helper methods
template <typename T>
void LinkedList<T>::printSuccess(const std::string& msg) const {
  std::cout << Color::SUCCESS << msg << Color::RESET << std::endl;
}

template <typename T>
void LinkedList<T>::printError(const std::string& msg) const {
  std::cout << Color::ERROR << msg << Color::RESET << std::endl;
}

template <typename T>
void LinkedList<T>::printInfo(const std::string& msg) const {
  std::cout << Color::INFO << msg << Color::RESET << std::endl;
}

// Explicit template instantiations for supported types
template class LinkedList<int>;
template class LinkedList<double>;
template class LinkedList<std::string>;
