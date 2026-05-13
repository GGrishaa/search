#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <string>

#include "flat.hpp"

enum Color { RED, BLACK };

class rb_node {
 public:
  rb_node(flat* here = nullptr, rb_node* parent = nullptr,
          rb_node* left = nullptr, rb_node* right = nullptr,
          Color color = Color::RED);
  rb_node(const rb_node& other) = delete;
  rb_node& operator=(const rb_node& other) = delete;
  ~rb_node();

  bool right_free() const;
  bool left_free() const;
  rb_node* get_parent() const;
  void set_parent(rb_node* parent);
  flat* get_here() const;
  void set_here(flat* here);
  rb_node* get_left() const;
  void set_left(rb_node* left);
  rb_node* get_right() const;
  void set_right(rb_node* right);
  Color get_color() const;
  void set_color(Color color);

  bool operator<(flat* other) const;
  bool operator<(const string& key) const;
  bool operator>=(flat* other) const;
  bool operator>=(const string& key) const;
  bool operator==(flat* other) const;
  bool operator==(const string& key) const;

 private:
  rb_node* parent_;
  flat* here_;
  rb_node* left_;
  rb_node* right_;
  Color color_;
};

class rb_tree {
 public:
  rb_tree();
  rb_tree(const rb_tree&) = delete;
  rb_tree& operator=(const rb_tree&) = delete;
  ~rb_tree();

  rb_node* get_root() const;
  void set_root(rb_node* root);
  size_t get_size() const;
  rb_node* insert(flat* new_elem);
  void insert_fix(rb_node* son);

  rb_node* rotate_left(rb_node* node);
  rb_node* rotate_right(rb_node* node);

  flat* find(const string& key, size_t& size) const;

 private:
  rb_node* root_;
  size_t size_;
};

void clear_rb_subtree(rb_node* l);

#endif