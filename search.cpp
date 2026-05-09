#include <iostream>

#include "flat.hpp"
#include "tree.hpp"
using namespace std;

size_t linear_search(flat* flats, size_t size, flat* find, string key) {
  if (!flats) return 0;
  size_t ans = 0;
  for (size_t i = 0; i < size; ++i) {
    if (flats[i] == key) {
      find[ans] = flats[i];
      ++ans;
    }
  }
  return ans;
}

int main() { return 0; }
