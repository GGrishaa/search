#ifndef HASH_HPP
#define HASH_HPP

#define P1 73
#define P2 71
#define CAPACITY 100003
#define alphabet \
  "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ "

#include <algorithm>
#include <string>
#include <vector>

#include "flat.hpp"

using namespace std;

int index(const char& ch, const string& alph = alphabet);

long long my_hash1(const string& str);
long long my_hash2(const string& str);

class hash_table {
 public:
  hash_table(const size_t& capacity = CAPACITY);
  hash_table(const hash_table& other) = delete;
  hash_table& operator=(const hash_table& other) = delete;
  ~hash_table();

  bool insert(flat* Flat);
  flat* find(const string& key, size_t& size) const;

 private:
  vector<flat*> table_;
  size_t capacity_;
  size_t size_;
};
#endif

int fill_table(hash_table* table, flat* flats, const size_t& size);
int count_collisions(flat* flats, const size_t& size);