#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>

#include "flat.hpp"

class leaf {
 public:
  leaf(flat* here = nullptr, leaf* left = nullptr, leaf* right = nullptr);
  leaf(const leaf& other) = delete;
  leaf& operator=(const leaf& other) = delete;
  ~leaf() = default;
  void add_right(leaf* new_leaf);
  void add_left(leaf* new_leaf);
  bool right_free() const;
  bool left_free() const;
  bool here_free() const;
  bool operator>=(flat* other) const;
  bool operator<(flat* other) const;
  bool operator>=(const string& key) const;
  bool operator<(const string& key) const;
  bool operator==(const string& key) const;
  leaf* get_right() const;
  leaf* get_left() const;
  flat* get_here() const;

 private:
  flat* here_;
  leaf* left_;
  leaf* right_;
};

class tree {
 public:
  tree(leaf* top = nullptr);
  tree(const tree& other) = delete;
  tree& operator=(const tree& other) = delete;
  ~tree();
  bool top_free() const;
  void add_elem(flat* new_elem);
  flat* find(const string& key, size_t& size) const;

 private:
  leaf* top_;
  size_t size_;
};

void fill_tree(tree* tr, flat* flats, size_t size);

void clear_subtree(leaf* tr);

#endif