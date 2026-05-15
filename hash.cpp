#include "hash.hpp"

int index(const char& ch, const string& alph) {
  int a = alph.find(ch);
  if (a == string::npos) a = alph.find(' ');
  return a + 1;
}

unsigned long long my_hash(const string& str) {
  unsigned long long hash = 0;
  for (size_t i = 0; i < str.length(); ++i)
    hash = (hash * P + index(str[i])) % MOD;
  return hash;
}

hash_table::hash_table(const size_t& capacity) : capacity_(capacity) {
  table_ = new flat*[capacity_]();
  sizes_ = new size_t[capacity_]();
}

hash_table::~hash_table() {
  for (size_t i = 0; i < capacity_; ++i) {
    delete[] table_[i];
  }
  delete[] table_;
  delete[] sizes_;
}

void hash_table::insert(flat* Flat) {
  string key = Flat->get_owner();
  unsigned long long h = my_hash(key);
  size_t index = h % capacity_;
  flat* arr = table_[index];
  size_t sz = sizes_[index];
  flat* new_arr = new flat[sz + 1];
  if (sz > 0) {
    for (size_t i = 0; i < sz; ++i) new_arr[i] = arr[i];
    delete[] arr;
  }
  new_arr[sz] = *Flat;
  table_[index] = new_arr;
  sizes_[index] = sz + 1;
}

flat* hash_table::find(const string& key, size_t& size) const {
  size = 0;
  unsigned long long h = my_hash(key);
  size_t index = h % capacity_;
  flat* arr = table_[index];
  size_t sz = sizes_[index];
  for (size_t i = 0; i < sz; ++i) {
    if (arr[i].get_owner() == key) ++size;
  }
  if (size == 0) return nullptr;
  flat* res = new flat[size];
  size_t idx = 0;
  for (size_t i = 0; i < sz; ++i) {
    if (arr[i].get_owner() == key) res[idx++] = arr[i];
  }
  return res;
}

size_t fill_table(hash_table* table, flat* flats, const size_t& size) {
  size_t inserted = 0;
  for (size_t i = 0; i < size; ++i) {
    table->insert(flats + i);
    ++inserted;
  }
  return inserted;
}

size_t count_collisions(flat* flats, const size_t& size) {
  std::unordered_map<unsigned long long, std::string> hash_to_key;
  size_t collisions = 0;
  for (size_t i = 0; i < size; ++i) {
    unsigned long long h = my_hash(flats[i].get_owner());
    auto it = hash_to_key.find(h);
    if (it == hash_to_key.end()) {
      hash_to_key[h] = flats[i].get_owner();
    } else {
      if (it->second != flats[i].get_owner()) {
        ++collisions;
      }
    }
  }
  return collisions;
}