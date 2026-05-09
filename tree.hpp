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
  void add_here(flat* new_flat);
  bool right_free() const;
  bool left_free() const;
  bool here_free() const;
  bool operator>=(flat* other) const;
  bool operator<(flat* other) const;
  leaf* get_right() const;
  leaf* get_left() const;

 private:
  flat* here;
  leaf* left;
  leaf* right;
};

class tree {
 public:
  tree(leaf* top = nullptr);
  tree(const tree& other) = delete;
  tree& operator=(const tree& other) = delete;
  ~tree();
  bool top_free() const;
  void add_elem(flat* new_elem);

 private:
  leaf* top;
  friend void clear_subtree(leaf*);
};

void fill_tree(tree* tr, flat* flats, size_t size);

void clear_subtree(leaf* tr);

#endif