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

int main() {
  size_t s;
  flat* flats = load_from_csv("CSV/apartments_100.csv", s);
  tree tr;
  fill_tree(&tr, flats, s);
  flat* find = tr.find("Миронова Ирина Алексеевна", s);
  print_flats(find, s, cout);
  delete[] flats;
  delete[] find;
  return 0;
}
