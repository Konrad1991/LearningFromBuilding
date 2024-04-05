
#include "linkedlists.hpp"
#define CATCH_CONFIG_MAIN
// #include "../catch/catch.hpp"


int main() {
  srand(time(nullptr));
  int i = 1;
  linkedList<int> list(i);

  for(int i = 2; i < 6; i++) {
    list.append(i);
  }

  list.print();

  for(int i = 0; i < 20; i++) {
    int idx = rand() % list.sz();
    int elem = rand() % 1000;
    list.insert(elem, idx);
  }

  list.print();

  for(size_t i = 0; i < list.sz(); i++) {
    std::cout << list[i] << std::endl;
  }
}
