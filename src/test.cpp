#include <iostream>
#include "heap.hpp"
#include <stdlib.h>
#include <time.h>
int main() {
  heap<int> A;
   srand (time(0));
  for (size_t i = 0; i < 1000; i++)
    A.insert(rand() % 200000 + -100000);

  A.print();
  for (size_t i = 0; i < 1000; i++)
    std::cout << A.pop_first() << std::endl;
  A.print();
}
