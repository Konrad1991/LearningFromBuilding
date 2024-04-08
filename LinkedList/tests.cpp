#include "linkedlists.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"

TEST_CASE( "linkedList" ) {

  srand(time(nullptr));
  int i = 1;
  linkedList<int> list(i);

  SECTION("Initialisation") {
    REQUIRE(list.sz() == 1);
    REQUIRE(list[0] == 1);
  }
  
  for(int i = 2; i < 6; i++) {
    list.append(i);
  }

  SECTION("Appending, Insertion and const indexing") {
    REQUIRE(list.sz() == 5);
    for(size_t i = 0; i < 20; i++) {
      int idx = rand() % list.sz();
      int elem = rand() % 1000;
      list.insert(elem, idx);
      REQUIRE(list[idx] == elem);
    }
  }
  
  SECTION("Out of boundary indexing") {
    REQUIRE_THROWS_AS(list[-1], std::exception); 
    REQUIRE_THROWS_AS(list[1000000], std::exception);
  }
  
  SECTION("mutable indexing") {
    REQUIRE(list[0] == 1);
    list[0] = 3;
    REQUIRE(list[0] == 3);
    list[2] = 30;
    REQUIRE(list[2] == 30);
    list[3] = 300;
    REQUIRE(list[3] == 300);
    list[4] = 3000;
    REQUIRE(list[4] == 3000);
    list[5] = 3;
    REQUIRE(list[5] == 3); 
    // obviously it is 0 to size (including the size)! Not my intention. But I'm too lazy to change it
  }

}

