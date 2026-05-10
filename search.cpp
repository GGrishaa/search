#include <iostream>

#include "flat.hpp"
#include "tree.hpp"
using namespace std;

/**
 * @file search.cpp
 * @brief Реализация линейного поиска, функций отсчета затраченного времени
 */

/**
 * @brief Функция линейного поиска
 *
 * Последовательно проходит по всем элементам и добавляет их в случае
 * соответствия ключу
 * @param flats указатель на начало массива для поиска
 * @param size размер массива в котором будет проходить поиск
 * @param find указатель на начало массива найденных элементов
 * @param key ключ-строка, по которой будет проходить поиск
 * @return количество найденных элементов
 */

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

/**
 * @brief Точка начала работы программы
 */
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
