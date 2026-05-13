#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
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
 * @brief Функция проверки числа на факт того, что оно является простым
 *
 * Проверяет все делители, кроме себя и 1, если что-то есть, значит число
 * простое
 * @param n - число, которое надо проверить
 * @return true, если число является простым, иначе false
 */
bool is_prime(size_t n) {
  bool res = true;
  for (size_t i = 2; i < n && res; ++i) {
    if (n % i == 0) res = false;
  }
  return res;
}

/**
 * @brief Функция находящая ближайшее большее простое число к текущему
 *
 * Инкрементирует и проверяет на простоту в бесконечном цикле, когда становится
 * простым - выходит из цикла
 * @param n - число, к которому надо найти ближайшее простое
 */
size_t nearest_prime(size_t n) {
  for (++n; !is_prime(n); ++n);
  return n;
}

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
flat* linear_search(flat* flats, const size_t& size1, const string& key,
                    size_t& size2) {
  size2 = 0;
  if (!flats) return nullptr;
  flat* find = new flat[size1];
  for (size_t i = 0; i < size1; ++i) {
    if (flats[i] == key) {
      find[size2] = flats[i];
      ++size2;
    }
  }
  return find;
}

/**
 * @brief Функция подсчета числа коллизий
 *
 * В случае успешного открытия файла, путь к которому передается единственным
 * аргументом считывает данные из файла и записывает в массив, считает число
 * коллизий и записывает в docs/collisions.txt
 */
void collisions_in_file(const string& filename) {
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
 * @brief Функция подсчета времени построения + поиска для разных методов
 *
 * В случае успешного открытия файла, путь к которому передается единственным
 * аргументом считывает данные из файла и записывает в массив, засекает время,
 * которое необходимо для переведения массива в определенную структуру (кроме
 * линейного поиска) и поиска элементов с ключом, соответствующим ключу
 * последнего элемента, результаты затраченного времени выводятся в файл
 * docs/times_with_fill.txt
 */
void fix_time_with_fill(const string& filename) {
  size_t size1, size2;
  flat* flats = load_from_csv(filename, size1);
  if (!flats) {
    cerr << "Ошибка: не удалось загрузить файл " << filename << endl;
    return;
  }
  ofstream fout("docs/times_with_fill.txt", ios::app);
  string key = flats[size1 - 1].get_owner();
  size_t prime = nearest_prime(size1);
  fout << "Размер данных: " << size1 << " квартир" << endl;
  fout << "Затраченное время:" << endl;

  auto start_linear = chrono::high_resolution_clock::now();
  flat* find_linear = linear_search(flats, size1, key, size2);
  auto end_linear = chrono::high_resolution_clock::now();
  size_t linear_total =
      chrono::duration_cast<chrono::microseconds>(end_linear - start_linear)
          .count();
  fout << "Линейный поиск:\t\t\t\t\t\t\t" << linear_total / 1000.0 << " мс"
       << endl;

  tree tr;
  auto start_tree = chrono::high_resolution_clock::now();
  fill_tree(&tr, flats, size1);
  flat* find_tree = tr.find(key, size2);
  auto end_tree = chrono::high_resolution_clock::now();
  size_t tree_total =
      chrono::duration_cast<chrono::microseconds>(end_tree - start_tree)
          .count();
  fout << "Поиск с помощью бинарного дерева:\t\t" << tree_total / 1000.0
       << " мс" << endl;

  hash_table table(prime);
  auto start_hash = chrono::high_resolution_clock::now();
  fill_table(&table, flats, size1);
  flat* find_hash = table.find(key, size2);
  auto end_hash = chrono::high_resolution_clock::now();
  size_t hash_total =
      chrono::duration_cast<chrono::microseconds>(end_hash - start_hash)
          .count();
  fout << "Поиск с помощью хэш-таблицы:\t\t\t" << hash_total / 1000.0 << " мс"
       << endl;

  rb_tree rbtree;
  auto start_rb = chrono::high_resolution_clock::now();
  fill_rb_tree(&rbtree, flats, size1);
  flat* find_rb = rbtree.find(key, size2);
  auto end_rb = chrono::high_resolution_clock::now();
  size_t rb_total =
      chrono::duration_cast<chrono::microseconds>(end_rb - start_rb).count();
  fout << "Поиск с помощью красно-черного дерева:\t" << rb_total / 1000.0
       << " мс" << endl;

  auto start_mm = chrono::high_resolution_clock::now();
  multimap<string, flat> mm;
  for (size_t i = 0; i < size1; ++i)
    mm.insert({flats[i].get_owner(), flats[i]});
  auto range = mm.equal_range(key);
  size_t count = distance(range.first, range.second);
  flat* find_mm = new flat[count];
  size_t idx = 0;
  for (auto it = range.first; it != range.second; ++it) {
    find_mm[idx++] = it->second;
  }
  auto end_mm = chrono::high_resolution_clock::now();
  double mm_time = chrono::duration<double, milli>(end_mm - start_mm).count();
  fout << "Поиск с помощью std::multimap:\t\t" << mm_time << " мс" << endl
       << endl;

  fout.close();
  delete[] flats;
  delete[] find_linear;
  delete[] find_tree;
  delete[] find_hash;
  delete[] find_rb;
  delete[] find_mm;
}

/**
 * @brief Функция подсчета времени поиска для разных методов
 *
 * В случае успешного открытия файла, путь к которому передается единственным
 * аргументом считывает данные из файла и записывает в массив, засекает время,
 * которое необходимо только для поиска элементов с ключом, соответствующим
 * ключу последнего элемента, результаты затраченного времени выводятся в файл
 * docs/times_no_fill.txt
 */
void fix_time_no_fill(const string& filename) {
  size_t size1, size2;
  flat* flats = load_from_csv(filename, size1);
  if (!flats) {
    cerr << "Ошибка: не удалось загрузить файл " << filename << endl;
    return;
  }
  ofstream fout("docs/times_no_fill.txt", ios::app);
  string key = flats[size1 - 1].get_owner();
  size_t prime = nearest_prime(size1);
  fout << "Размер данных: " << size1 << " квартир" << endl;
  fout << "Затраченное время:" << endl;

  auto start_linear = chrono::high_resolution_clock::now();
  flat* find_linear = linear_search(flats, size1, key, size2);
  auto end_linear = chrono::high_resolution_clock::now();
  size_t linear_total =
      chrono::duration_cast<chrono::microseconds>(end_linear - start_linear)
          .count();
  fout << "Линейный поиск:\t\t\t\t\t\t\t" << linear_total / 1000.0 << " мс"
       << endl;

  tree tr;
  fill_tree(&tr, flats, size1);
  auto start_tree = chrono::high_resolution_clock::now();
  flat* find_tree = tr.find(key, size2);
  auto end_tree = chrono::high_resolution_clock::now();
  size_t tree_total =
      chrono::duration_cast<chrono::microseconds>(end_tree - start_tree)
          .count();
  fout << "Поиск с помощью бинарного дерева:\t\t" << tree_total / 1000.0
       << " мс" << endl;

  hash_table table(prime);
  fill_table(&table, flats, size1);
  auto start_hash = chrono::high_resolution_clock::now();
  flat* find_hash = table.find(key, size2);
  auto end_hash = chrono::high_resolution_clock::now();
  size_t hash_total =
      chrono::duration_cast<chrono::microseconds>(end_hash - start_hash)
          .count();
  fout << "Поиск с помощью хэш-таблицы:\t\t\t" << hash_total / 1000.0 << " мс"
       << endl;

  rb_tree rbtree;
  fill_rb_tree(&rbtree, flats, size1);
  auto start_rb = chrono::high_resolution_clock::now();
  flat* find_rb = rbtree.find(key, size2);
  auto end_rb = chrono::high_resolution_clock::now();
  size_t rb_total =
      chrono::duration_cast<chrono::microseconds>(end_rb - start_rb).count();
  fout << "Поиск с помощью красно-черного дерева:\t" << rb_total / 1000.0
       << " мс" << endl;

  multimap<string, flat> mm;
  for (size_t i = 0; i < size1; ++i)
    mm.insert({flats[i].get_owner(), flats[i]});
  auto start_mm = chrono::high_resolution_clock::now();
  auto range = mm.equal_range(key);
  size_t count = distance(range.first, range.second);
  flat* find_mm = new flat[count];
  size_t idx = 0;
  for (auto it = range.first; it != range.second; ++it) {
    find_mm[idx++] = it->second;
  }
  auto end_mm = chrono::high_resolution_clock::now();
  double mm_time = chrono::duration<double, milli>(end_mm - start_mm).count();
  fout << "Поиск с помощью std::multimap:\t\t" << mm_time << " мс" << endl
       << endl;

  fout.close();
  delete[] flats;
  delete[] find_linear;
  delete[] find_tree;
  delete[] find_hash;
  delete[] find_rb;
  delete[] find_mm;
}

/**
 * @brief Точка начала работы программы
 */
int main() {
  fix_time_with_fill("CSV/apartments_100.csv");
  fix_time_with_fill("CSV/apartments_600.csv");
  fix_time_with_fill("CSV/apartments_1000.csv");
  fix_time_with_fill("CSV/apartments_2500.csv");
  fix_time_with_fill("CSV/apartments_7000.csv");
  fix_time_with_fill("CSV/apartments_10000.csv");
  fix_time_with_fill("CSV/apartments_20000.csv");
  fix_time_with_fill("CSV/apartments_30000.csv");
  fix_time_with_fill("CSV/apartments_50000.csv");
  fix_time_with_fill("CSV/apartments_100000.csv");

  fix_time_no_fill("CSV/apartments_100.csv");
  fix_time_no_fill("CSV/apartments_600.csv");
  fix_time_no_fill("CSV/apartments_1000.csv");
  fix_time_no_fill("CSV/apartments_2500.csv");
  fix_time_no_fill("CSV/apartments_7000.csv");
  fix_time_no_fill("CSV/apartments_10000.csv");
  fix_time_no_fill("CSV/apartments_20000.csv");
  fix_time_no_fill("CSV/apartments_30000.csv");
  fix_time_no_fill("CSV/apartments_50000.csv");
  fix_time_no_fill("CSV/apartments_100000.csv");

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
