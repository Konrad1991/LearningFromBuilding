#include <iostream>

template<typename T>
struct Node {
  T val;
  Node* next;

  Node(T& inp) : val(inp) {}
  Node(T&& inp) : val(inp) {}
};

template<typename T>
Node<T>* createList(T& inp) {
  Node<T>* head = new Node<T>(inp);
  head -> next = nullptr;
  return head;
}

template<typename T>
void append(Node<T>* head, T& elem) {
  Node<T>* newNode = new Node<T>(elem);
  newNode -> next = nullptr;
  auto copyHead = head;   
  while(copyHead -> next != nullptr) {
    copyHead = copyHead -> next;
  }
  copyHead -> next = newNode;
}

template<typename T>
void destroy(Node<T>* head) {
  if (head -> next == nullptr) {
    delete head;
    return;
  }
  while(head -> next != nullptr) {
    auto toDelete = head;
    head = head -> next;
    delete toDelete;
  }
  delete head;
}

template<typename T>
void print(Node<T>* head) {
  auto copyHead = head;
  while(copyHead -> next != nullptr) {
    std::cout << copyHead -> val << std::endl;
    copyHead = copyHead -> next;
  }
  std::cout << copyHead -> val << std::endl;
}

int main() {
  int i = 1;
  Node<int>* head = createList(i);

  for(int i = 2; i < 5; i++) {
    append(head, i);
  }

  print(head);

  destroy(head);

}
