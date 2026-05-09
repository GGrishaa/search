#include "tree.hpp"

leaf::leaf(flat* here, leaf* left, leaf* right)
    : here(here), left(left), right(right) {}

void leaf::add_right(leaf* new_leaf) {
  if (!right) {
    right = new_leaf;
  }
}

void leaf::add_left(leaf* new_leaf) {
  if (!left) {
    left = new_leaf;
  }
}

void leaf::add_here(flat* new_flat) { here = new_flat; }

bool leaf::right_free() const { return !right; }

bool leaf::left_free() const { return !left; }

bool leaf::here_free() const { return !here; }

bool leaf::operator>=(flat* other) const {
  if (!this->here || !other) return false;
  return this->here->get_owner() >= other->get_owner();
}

bool leaf::operator<(flat* other) const {
  if (!this->here || !other) return false;
  return this->here->get_owner() < other->get_owner();
}

leaf* leaf::get_right() const { return right; }

leaf* leaf::get_left() const { return left; }

tree::tree(leaf* top) : top(top) {}

tree::~tree() { clear_subtree(this->top); }

bool tree::top_free() const { return !top; }

void tree::add_elem(flat* new_elem) {
  if (top_free()) {
    top = new leaf(new_elem);
    return;
  }
  leaf* cur = top;
  while (true) {
    if (*cur < new_elem) {
      if (cur->right_free()) {
        cur->add_right(new leaf(new_elem));
        break;
      } else {
        cur = cur->get_right();
      }
    } else {
      if (cur->left_free()) {
        cur->add_left(new leaf(new_elem));
        break;
      } else {
        cur = cur->get_left();
      }
    }
  }
}

void fill_tree(tree* tr, flat* flats, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    tr->add_elem(flats + i);
  }
}

void clear_subtree(leaf* l) {
  if (!l) return;
  clear_subtree(l->get_left());
  clear_subtree(l->get_right());
  delete l;
}