/**
 * @file Stack.tpp
 * @brief Template implementation file for Stack class
 *
 * This file contains the implementation of the Stack template class.
 * It is included at the end of Stack.hpp and should not be compiled separately.
 */

#ifndef STACK_TPP
#define STACK_TPP

// Default constructor
template <typename T> Stack<T>::Stack() : topNode(nullptr), stackSize(0) {}

// Constructor with JSON file initialization
template <typename T>
Stack<T>::Stack(const std::string &jsonFilePath)
    : topNode(nullptr), stackSize(0) {
  loadFromJSON(jsonFilePath);
}

// Copy constructor
template <typename T>
Stack<T>::Stack(const Stack &other) : topNode(nullptr), stackSize(0) {
  if (other.topNode == nullptr) {
    return;
  }

  // Copy elements from other stack
  Node *current = other.topNode;
  Node **insertPos = &topNode;

  while (current != nullptr) {
    *insertPos = new Node(current->data);
    insertPos = &((*insertPos)->next);
    current = current->next;
    stackSize++;
  }
}

// Assignment operator
template <typename T> Stack<T> &Stack<T>::operator=(const Stack &other) {
  if (this != &other) {
    // Clear current stack
    clear();

    if (other.topNode != nullptr) {
      // Copy elements from other stack
      Node *current = other.topNode;
      Node **insertPos = &topNode;

      while (current != nullptr) {
        *insertPos = new Node(current->data);
        insertPos = &((*insertPos)->next);
        current = current->next;
        stackSize++;
      }
    }
  }
  return *this;
}

// Destructor
template <typename T> Stack<T>::~Stack() { clear(); }

// Push operation
template <typename T> void Stack<T>::push(const T &value) {
  Node *newNode = new Node(value);
  newNode->next = topNode;
  topNode = newNode;
  stackSize++;
}

// Pop operation
template <typename T> void Stack<T>::pop() {
  if (isEmpty()) {
    throw std::underflow_error("Stack underflow: Cannot pop from empty stack");
  }

  Node *temp = topNode;
  topNode = topNode->next;
  delete temp;
  stackSize--;
}

// Top operation (non-const)
template <typename T> T &Stack<T>::top() {
  if (isEmpty()) {
    throw std::underflow_error("Stack is empty: Cannot access top element");
  }
  return topNode->data;
}

// Top operation (const)
template <typename T> const T &Stack<T>::top() const {
  if (isEmpty()) {
    throw std::underflow_error("Stack is empty: Cannot access top element");
  }
  return topNode->data;
}

// Check if stack is empty
template <typename T> bool Stack<T>::isEmpty() const {
  return topNode == nullptr;
}

// Get stack size
template <typename T> size_t Stack<T>::size() const { return stackSize; }

// Load from JSON file
template <typename T>
void Stack<T>::loadFromJSON(const std::string &jsonFilePath) {
  std::ifstream file(jsonFilePath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open JSON file: " + jsonFilePath);
  }

  json jsonData;
  try {
    file >> jsonData;
  } catch (const json::parse_error &e) {
    throw std::runtime_error("JSON parse error: " + std::string(e.what()));
  }

  if (!jsonData.contains("stack")) {
    throw std::runtime_error("JSON file must contain a 'stack' array");
  }

  if (!jsonData["stack"].is_array()) {
    throw std::runtime_error("'stack' must be an array");
  }

  // Clear existing stack
  clear();

  // Push elements from JSON in order (first element becomes bottom, last
  // becomes top)
  auto stackArray = jsonData["stack"];
  for (const auto &element : stackArray) {
    push(element.get<T>());
  }
}

// Load from nested JSON file with key
template <typename T>
void Stack<T>::loadFromJSON(const std::string &jsonFilePath,
                            const std::string &key) {
  std::ifstream file(jsonFilePath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open JSON file: " + jsonFilePath);
  }

  json jsonData;
  try {
    file >> jsonData;
  } catch (const json::parse_error &e) {
    throw std::runtime_error("JSON parse error: " + std::string(e.what()));
  }

  if (!jsonData.contains(key)) {
    throw std::runtime_error("JSON file must contain key: " + key);
  }

  auto keyData = jsonData[key];

  if (!keyData.contains("stack")) {
    throw std::runtime_error("Key '" + key + "' must contain a 'stack' array");
  }

  if (!keyData["stack"].is_array()) {
    throw std::runtime_error("'stack' in key '" + key + "' must be an array");
  }

  // Clear existing stack
  clear();

  // Push elements from JSON in order (first element becomes bottom, last
  // becomes top)
  auto stackArray = keyData["stack"];
  for (const auto &element : stackArray) {
    push(element.get<T>());
  }
}

// Save to JSON file
template <typename T>
void Stack<T>::saveToJSON(const std::string &jsonFilePath) const {
  json jsonData;
  json stackArray = json::array();

  // Traverse stack and collect elements (top to bottom)
  Node *current = topNode;
  while (current != nullptr) {
    stackArray.push_back(current->data);
    current = current->next;
  }

  // Reverse to get bottom to top order
  std::reverse(stackArray.begin(), stackArray.end());

  jsonData["stack"] = stackArray;

  std::ofstream file(jsonFilePath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to create JSON file: " + jsonFilePath);
  }

  file << jsonData.dump(4); // Pretty print with 4-space indentation
}

// Clear all elements
template <typename T> void Stack<T>::clear() {
  while (!isEmpty()) {
    pop();
  }
}

// Display stack contents
template <typename T> void Stack<T>::display() const {
  if (isEmpty()) {
    std::cout << Color::WARNING << Color::ITALIC << "Stack is empty"
              << Color::RESET << std::endl;
    return;
  }

  std::cout << Color::INFO << Color::BOLD << "Stack" << Color::RESET
            << Color::DIM << " (top to bottom): " << Color::RESET;

  Node *current = topNode;
  size_t position = 0;
  const size_t totalSize = stackSize;

  while (current != nullptr) {
    // Color elements based on position
    if (position == 0) {
      // Top element: Bold Green with background highlight
      std::cout << Color::BG_GREEN << Color::BLACK << Color::BOLD
                << " TOP: " << current->data << " " << Color::RESET;
    } else if (position == totalSize - 1) {
      // Bottom element: Blue with underline
      std::cout << Color::BLUE << Color::UNDERLINE
                << "BOTTOM: " << current->data << Color::RESET;
    } else {
      // Middle elements: Different colors based on position
      const char *color;
      switch (position % 6) {
      case 1:
        color = Color::CYAN;
        break;
      case 2:
        color = Color::YELLOW;
        break;
      case 3:
        color = Color::MAGENTA;
        break;
      case 4:
        color = Color::WHITE;
        break;
      case 5:
        color = Color::GREEN;
        break;
      default:
        color = Color::RED;
        break;
      }
      std::cout << color << current->data << Color::RESET;
    }

    if (current->next != nullptr) {
      std::cout << Color::DIM << " â†’ " << Color::RESET;
    }
    current = current->next;
    position++;
  }
  std::cout << std::endl;
}

#endif // STACK_TPP
