#include <fstream>
#include <iostream>
#include <string>

#include "flat.hpp"
#include "hash.hpp"
#include "rb_tree.hpp"
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

void collisions_in_file(const string filename) {
  size_t size;
  flat* flats = load_from_csv(filename, size);
  if (!flats) {
    cerr << "Ошибка: не удалось загрузить файл " << filename << endl;
    return;
  }
  ofstream fout("docs/collisions.txt", ios::app);
  size_t collisions = count_collisions(flats, size);

  fout << "Размер данных: " << size << " квартир" << endl;
  fout << "Коллизий: " << collisions << endl;
  fout.close();
  delete[] flats;
}

/**
 * @brief Точка начала работы программы
 */
int main() {
  collisions_in_file("CSV/apartments_100.csv");
  collisions_in_file("CSV/apartments_600.csv");
  collisions_in_file("CSV/apartments_1000.csv");
  collisions_in_file("CSV/apartments_2500.csv");
  collisions_in_file("CSV/apartments_7000.csv");
  collisions_in_file("CSV/apartments_10000.csv");
  collisions_in_file("CSV/apartments_20000.csv");
  collisions_in_file("CSV/apartments_30000.csv");
  collisions_in_file("CSV/apartments_50000.csv");
  collisions_in_file("CSV/apartments_100000.csv");
  return 0;
}
