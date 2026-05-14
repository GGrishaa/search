#include "hash.hpp"

int index(const char& ch, const string& alph) {
  int a = alph.find(ch);
  if (a == string::npos) a = alph.find(' ');
  return a + 1;
}

unsigned long long my_hash1(const string& str) {
  unsigned long long hash = 0;
  for (size_t i = 0; i < str.length(); ++i)
    hash = (hash * P1 + index(str[i])) % MOD;
  return hash;
}

unsigned long long my_hash2(const string& str) {
  unsigned long long hash = 0;
  for (size_t i = 0; i < str.length(); ++i)
    hash = (hash * P2 + index(str[i])) % MOD;
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
  unsigned long long h1 = my_hash1(key), h2 = my_hash2(key);
  size_t index = h1 % capacity_, step = (h2 % (capacity_ - 1)) + 1;

  for (size_t k = 0; k < capacity_; ++k) {
    size_t pos = (index + k * step) % capacity_;
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
  unsigned long long h1 = my_hash1(key), h2 = my_hash2(key);
  size_t index = h1 % capacity_, step = (h2 % (capacity_ - 1)) + 1;
  for (size_t k = 0; k < capacity_; ++k) {
    size_t pos = (index + k * step) % capacity_;
    if (table_[pos] && table_[pos]->get_owner() == key)
      ++size;
    else if (table_[pos] == nullptr)
      break;
  }
  if (size == 0) return nullptr;

  flat* res = new flat[size];
  size_t idx = 0;
  for (size_t k = 0; k < capacity_; ++k) {
    size_t pos = (index + k * step) % capacity_;
    if (table_[pos] && table_[pos]->get_owner() == key) {
      res[idx++] = *table_[pos];
    } else if (table_[pos] == nullptr)
      break;
  }
  return res;
}

size_t fill_table(hash_table* table, flat* flats, const size_t& size) {
  size_t s = 0;
  for (size_t i = 0; i < size; ++i) s += table->insert(flats + i);
  return s;
}

size_t count_collisions(flat* flats, const size_t& size) {
  std::unordered_set<unsigned long long> unique_hash;
  size_t collisions = 0;
  for (size_t i = 0; i < size; ++i) {
    auto h = my_hash1(flats[i].get_owner());
    if (unique_hash.find(h) != unique_hash.end())
      ++collisions;
    else
      unique_hash.insert(h);
  }
  return collisions;
}