
#include "linkedlists.hpp"

template<typename T>
void linkedList<T>::print() const noexcept {
  auto copyHead = head;
  int counter = 0;
  std::cout << "[";
  while(copyHead -> next != nullptr) {
    std::cout << copyHead -> val << ", ";
    copyHead = copyHead -> next;
    if(counter == 10) std::cout << std::endl;
    counter++;
  }
  std::cout << copyHead -> val << "]" << std::endl;
}

template<typename T>
void linkedList<T>::printAddress() const noexcept {
  auto copyHead = head;
  size_t idx = 0;
  while(copyHead -> next != nullptr) {
    std::cout << "Idx: " << idx << "\t val: " << copyHead -> val << 
      "\t previous: " << copyHead -> previous <<
      "\t addr: " << copyHead <<
      "\t next: " << copyHead -> next << std::endl;
    idx++;
    copyHead = copyHead -> next;
  }
  std::cout << "Idx: " << idx << "\t val: " << copyHead -> val << 
    "\t previous: " << copyHead -> previous <<
    "\t addr: " << copyHead <<
    "\t next: " << copyHead -> next << std::endl;
}

template<typename T>
void linkedList<T>::checkAddresses() const noexcept {
  Node<T>* p = nullptr;
  Node<T>* a = nullptr;
  Node<T>* n = nullptr;
  Node<T>* copyHead = head;
  assert(head -> previous == nullptr);
  assert( (head -> next) -> previous == head);
  while(copyHead -> next != nullptr) {
    copyHead = copyHead -> next;
    if(copyHead == tail) break;
    assert( (copyHead -> next) -> previous == copyHead);
    assert( (copyHead -> previous) -> next == copyHead);
  }
  assert(copyHead -> next == nullptr);
  assert( (copyHead -> previous) -> next == copyHead);
}

template<typename T>
size_t linkedList<T>::sz() const noexcept {
  return size;
}

