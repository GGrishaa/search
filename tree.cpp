#include "tree.hpp"

leaf::leaf(flat* here, leaf* left, leaf* right)
    : here_(here), left_(left), right_(right) {}

leaf::~leaf() {
  delete here_;
  here_ = nullptr;
}

void leaf::add_right(leaf* new_leaf) {
  if (!right_) {
    right_ = new_leaf;
  }
}

void leaf::add_left(leaf* new_leaf) {
  if (!left_) {
    left_ = new_leaf;
  }
}

bool leaf::right_free() const { return !right_; }

bool leaf::left_free() const { return !left_; }

bool leaf::here_free() const { return !here_; }

bool leaf::operator>=(flat* other) const {
  if (!this->here_ || !other) return false;
  return this->here_->get_owner() >= other->get_owner();
}

bool leaf::operator<(flat* other) const {
  if (!this->here_ || !other) return false;
  return this->here_->get_owner() < other->get_owner();
}

bool leaf::operator>=(const string& key) const {
  if (!this->here_) return false;
  return this->here_->get_owner() >= key;
}

bool leaf::operator<(const string& key) const {
  if (!this->here_) return false;
  return this->here_->get_owner() < key;
}

bool leaf::operator==(const string& key) const {
  if (!this->here_) return false;
  return this->here_->get_owner() == key;
}

leaf* leaf::get_right() const { return right_; }

leaf* leaf::get_left() const { return left_; }

flat* leaf::get_here() const { return here_; };

tree::tree(leaf* top) : top_(top), size_(0) {}

tree::~tree() { clear_subtree(this->top_); }

bool tree::top_free() const { return !top_; }

void tree::add_elem(flat* new_elem) {
  if (!new_elem) return;
  ++size_;
  if (top_free()) {
    top_ = new leaf(new flat(*new_elem));
    return;
  }
  leaf* cur = top_;
  while (true) {
    if (*cur < new_elem) {
      if (cur->right_free()) {
        cur->add_right(new leaf(new flat(*new_elem)));
        break;
      } else {
        cur = cur->get_right();
      }
    } else {
      if (cur->left_free()) {
        cur->add_left(new leaf(new flat(*new_elem)));
        break;
      } else {
        cur = cur->get_left();
      }
    }
  }
}

flat* tree::find(const string& key, size_t& size) const {
  size = 0;
  if (top_free()) return nullptr;
  leaf* cur = top_;
  leaf* start = nullptr;
  while (true) {
    if (*cur == key) {
      ++size;
      if (!start) start = cur;
      if (cur->left_free()) break;
      cur = cur->get_left();
    } else if (*cur < key) {
      if (cur->right_free()) break;
      cur = cur->get_right();
    } else {
      if (cur->left_free()) break;
      cur = cur->get_left();
    }
  }
  if (size == 0) return nullptr;
  size_t c = 0;
  flat* res = new flat[size];
  while (true) {
    if (*start == key) {
      res[c] = *start->get_here();
      ++c;
      if (start->left_free()) return res;
      start = start->get_left();
    } else if (*start < key) {
      if (start->right_free()) return res;
      start = start->get_right();
    } else {
      if (start->left_free()) return res;
      start = start->get_left();
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