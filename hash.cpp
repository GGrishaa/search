#include "hash.hpp"

int index(const char& ch, const string& alph) {
  int a = alph.find(ch);
  if (a == string::npos) a = alph.find(' ');
  return a + 1;
}

long long my_hash1(const string& str) {
  long long p = 1, hash = 0;
  for (int i = 0; i < str.length(); ++i) {
    hash += index(str[i]) * p;
    p *= P1;
  }
  return hash;
}

long long my_hash2(const string& str) {
  long long p = 1, hash = 0;
  for (int i = 0; i < str.length(); ++i) {
    hash += index(str[i]) * p;
    p *= P2;
  }
  return hash;
}

hash_table::hash_table(const size_t& capacity) : capacity_(capacity), size_(0) {
  table_.resize(capacity_, nullptr);
}

hash_table::~hash_table() {
  for (size_t i = 0; i < capacity_; ++i) delete table_[i];
}

bool hash_table::insert(flat* Flat) {
  if (size_ == capacity_) return false;
  string key = Flat->get_owner();
  long long h1 = my_hash1(key), h2 = my_hash2(key);
  int index = h1 % capacity_, step = (h2 % (capacity_ - 1)) + 1;

  for (int k = 0; k < capacity_; ++k) {
    int pos = (index + k * step) % capacity_;
    if (table_[pos] == nullptr) {
      table_[pos] = new flat(*Flat);
      ++size_;
      return true;
    }
  }
  return false;
}

flat* hash_table::find(const string& key, size_t& size) const {
  size = 0;
  flat* res = new flat[capacity_];
  long long h1 = my_hash1(key), h2 = my_hash2(key);
  int index = h1 % capacity_, step = (h2 % (capacity_ - 1)) + 1;

  for (int k = 0; k < capacity_; ++k) {
    int pos = (index + k * step) % capacity_;
    if (table_[pos] && table_[pos]->get_owner() == key) {
      res[size] = *table_[pos];
      ++size;
    } else if (table_[pos] == nullptr) {
      if (!size) {
        delete[] res;
        res = nullptr;
      }
      return res;
    }
  }
  if (!size) {
    delete[] res;
    res = nullptr;
  }
  return res;
}

int fill_table(hash_table* table, flat* flats, const size_t& size) {
  int s = 0;
  for (size_t i = 0; i < size; ++i) s += table->insert(flats + i);
  return s;
}

size_t count_collisions(flat* flats, const size_t& size) {
  vector<long long> unique_hash;
  int collisions = 0;
  for (size_t i = 0; i < size; ++i) {
    if (find(unique_hash.begin(), unique_hash.end(),
             my_hash1(flats[i].get_owner())) != unique_hash.end())
      ++collisions;
    else
      unique_hash.push_back(my_hash1(flats[i].get_owner()));
  }
  return collisions;
}